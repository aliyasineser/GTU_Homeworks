/* Program that takes a directory name and a key string. 
 * Finds key in all files in the directory and creates an output file includes 
 * line and column information of where the key found.*/

/* Written by Ali Yasin Eser, on 20 march 2016*/
/* Student ID:141044058 for Homework 2 */


/* Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <dirent.h>
#include <time.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

/* Macros */

/* FILE MACROS */
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
#define WRITE_FLAGS_FOR_LOG_FILE (O_WRONLY | O_CREAT)


/* SIZE AND OPERATION MACROS */
#define CONTAINER_SIZE 1024
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define LOG_FILE_NAME "gfD.log"
#define ONE_MORE 1
#define SIZE_MULTIPLER_FOR_BIG_FILES 1
#define NEED_THREE_ARGS 3
#define ERROR_EXIT_CODE 1
#define ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS -1
#define ONE 1
#define START 0
#define ONE_LESS 1
#define ARG_TWO 2
#define CHILD_PID_INITIAL_COUNT 10
#define BLKSIZE 1024

/* Helper function prototypes */
pid_t r_wait(int *stat_loc);
int grepfromdirectory(const char* directory_name, const char* key);
int grepfromfile(const char* file_name, const char* key);
int copyfile(int fromfd, int tofd);


/* Main function */
int main(int argc, char *argv[]) {

    char pidNameForReadingStringArr[PATH_MAX] = "", /* pid.log file */
            entryPathForRemovingFile[PATH_MAX] = "", /* current path / file name */
            tempPathForGettingCurrentPath[PATH_MAX] = ""; /* current path + file name */
    int fileReadDescriptor = 0, fileWriteDescriptor = 0; /* write and read descriptors */

    /* Usage control */
    if (argc != NEED_THREE_ARGS) {
        fprintf(stderr, "Usage: %s which_file which_word", argv[ZERO]);
        exit(ERROR_EXIT_CODE);
    }
    /* Starting search */
    grepfromdirectory(argv[ONE], argv[ARG_TWO]);

    /* When functions exit, we are still in the directory that user entered. 
     * Should've out and create the log file */
    chdir("..");
    sprintf(pidNameForReadingStringArr, "%ld.log", (long) getpid());

    /* Opening directories */
    while (((fileReadDescriptor = open(pidNameForReadingStringArr, READ_FLAGS)) == 
    		ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) && errno == EINTR);
    while (((fileWriteDescriptor = open(LOG_FILE_NAME, WRITE_FLAGS_FOR_LOG_FILE, WRITE_PERMS)) == 
    		ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) && errno == EINTR);

    /* Real log file is in the directory. And it's name is the process id. 
     * But we need "gfD.log" , so changing the file and copying it.  */
    copyfile(fileReadDescriptor, fileWriteDescriptor);

    /* Setting the path for removing the inner file. All the processID.log files are removed. Last one is this guy. */
    getcwd(tempPathForGettingCurrentPath, PATH_MAX);
    sprintf(entryPathForRemovingFile, "%s/%s", tempPathForGettingCurrentPath, pidNameForReadingStringArr);
    /* Remove operation */
    remove(entryPathForRemovingFile);

	

    /* Closing directories */
    close(fileReadDescriptor);
    close(fileWriteDescriptor);



    return 0;
}

int grepfromdirectory(const char* directory_name, const char* key) {

    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */
    int fileThatWeWrite = 0, fileThatWeRead = 0, /* Write and read file descriptors */ 
            statOfEntry = 0, /* Entry stats */
            counterOfChilds = 0, /* how many directories and files found */
            countForForkLoop = 0, /* index for pid_t array */
            error = 0; /* Error for storing errno */
    pid_t* childrenPidInformationPtr = NULL; /* Children arrau */
    pid_t selfPidOfProcess = 0;  /* process id of process that doing this function */
    char tempPidStringForSum[PATH_MAX] = "", /* temp String name for all the child pid temp files */
            lastOutputFileNameArray[PATH_MAX] = "", /* Output name, log file for child that entered directory */
            pathOfTheDirectory[PATH_MAX] = "", /* Directory path -> current path / directory */
            currentPath[PATH_MAX] = "", /* Getting current path */
            currentDirectoryEntryPath[PATH_MAX] = ""; /* For each entry, a path needed */
	

    /* Storing self adress */
    selfPidOfProcess = getpid();

    /* Opening directory */
    if ((dirp = opendir(directory_name)) == NULL && errno == ENOTDIR) {
        perror("Directory couldn't be opened.");
        return 1;

    } else if (errno == ENAMETOOLONG) {
        perror("File name is too long for opening file.");
        return 1;
    }

    /* Setting and changing directory */
    getcwd(currentDirectoryEntryPath, PATH_MAX);
    strcat(currentDirectoryEntryPath, "/");
    strcat(currentDirectoryEntryPath, directory_name);

    chdir(currentDirectoryEntryPath);

    /* Traversing in directory and if there is a file or directory increments the counter */
    while ((direntp = readdir(dirp)) != NULL) {

        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 || 
        	direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;
        getcwd(currentDirectoryEntryPath, PATH_MAX);
        strcat(currentDirectoryEntryPath, "/");
        strcat(currentDirectoryEntryPath, direntp->d_name);

        if (stat(currentDirectoryEntryPath, &statbuf) == -1)
            continue;
        else if (S_ISDIR(statbuf.st_mode)) {
            ++counterOfChilds;

        } else if (S_ISREG(statbuf.st_mode)) {
            ++counterOfChilds;

        }

    }

    /* Allocating array for storing children pids */
    childrenPidInformationPtr = (pid_t*) malloc(counterOfChilds * sizeof (pid_t));


    /* Initialize of the counter and restarting the directory */
    countForForkLoop = 0;
    rewinddir(dirp);

    /* Traversing in the directory and if there is a directory, program doin fork 
     * and sending the child to directory to search. If there is a regular file(readable) 
     * program doin fork and sends the child to file to find the word. */
    while ((direntp = readdir(dirp)) != NULL) {

		/*Setting the path*/
        getcwd(currentDirectoryEntryPath, PATH_MAX);
        strcat(currentDirectoryEntryPath, "/");
        strcat(currentDirectoryEntryPath, direntp->d_name);

        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 || 
        	direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;

        if (stat(currentDirectoryEntryPath, &statbuf) == -1)
            continue;
        else if (S_ISDIR(statbuf.st_mode)) { /* If directory founds */

            if (getpid() == selfPidOfProcess)
                childrenPidInformationPtr[countForForkLoop] = fork();

            if (childrenPidInformationPtr[countForForkLoop] == 0) {
                free(childrenPidInformationPtr);
                closedir(dirp);
                grepfromdirectory(direntp->d_name, key);
                exit(ZERO);
            }
            ++countForForkLoop;
        } else if (S_ISREG(statbuf.st_mode)) { /* If file founds */

            if (getpid() == selfPidOfProcess)
                childrenPidInformationPtr[countForForkLoop] = fork();
            if (childrenPidInformationPtr[countForForkLoop] == 0) {
                free(childrenPidInformationPtr);
                closedir(dirp);
                grepfromfile(direntp->d_name, key);
                exit(ZERO);
            }
            ++countForForkLoop;
        }
    }
    /* Waiting all the children */
    while (r_wait(NULL) > 0);
    
	
	/* Setting the path again and naming the file that sums all the temp files */
    getcwd(currentDirectoryEntryPath, PATH_MAX);
    sprintf(lastOutputFileNameArray, "%ld.log", (long) (getpid()));

	
	/* Going superdirectory and creating a file. With this way, when childs exits all the 
	 * temp files are deleted. After creating, going subdirectory again. */
    chdir("..");
    while (((fileThatWeWrite = open(lastOutputFileNameArray, WRITE_FLAGS, WRITE_PERMS)) == 
    		ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) && errno == EINTR);
    chdir(currentDirectoryEntryPath);

	/* Process traversing all it's child's temp files. Taking all the information 
	 * in the files and copying to one file, the file that we opened in subdirectory. */
    for (countForForkLoop = 0; countForForkLoop < counterOfChilds; ++countForForkLoop) {
        chdir(currentDirectoryEntryPath);
        sprintf(tempPidStringForSum, "%ld.log", (long) (childrenPidInformationPtr[countForForkLoop]));
        /* Opening the file */
        if ((fileThatWeRead = open(tempPidStringForSum, READ_FLAGS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) { 
            error = errno;
            fprintf(stderr, "Failed to open file: [%s] => %s .\n", tempPidStringForSum, strerror(errno));
            errno = error;
            closedir(dirp);
            exit(ERROR_EXIT_CODE);
        }

        copyfile(fileThatWeRead, fileThatWeWrite); /*  File copy*/
        write(fileThatWeWrite, "\n", ONE);	/* Newline for no confuse */
        close(fileThatWeRead);	/* Close file */
        /* Removing file */
        sprintf(lastOutputFileNameArray, "%s/%s", currentDirectoryEntryPath, tempPidStringForSum);
        remove(lastOutputFileNameArray);
    }
    /* Closing file */
    closedir(dirp);
    close(fileThatWeWrite);
    free(childrenPidInformationPtr);
    
}

int grepfromfile(const char* file_name, const char* key) {
    /* Variables */
    int fileThatWeRead,
            fileThatWeWrite, /* File descriptors for argument file and output file */
            bytes, /*Bytes that read from file*/
            error, /* If an error occurs, this variable will keep the error */
            i, /* index for string line */
            j, /* If there is a match, j index will check the word without changing real index */
            found, /* If found assign TRUE */
            lineCount = ZERO, /* line counter  */
            columnCount, /* column counter, if there is a match this variable will be assigned */
            countOfWordFound = ZERO, /* word counter */
            sizeMultiplier = SIZE_MULTIPLER_FOR_BIG_FILES; /* If string size is not enough multipler will increase */

    char *stringOfFullFile = NULL, /* char *  for reading complete file */
            stringForWritingToFile[CONTAINER_SIZE] = "", /* If there is a match, this string will be fill and write to file */
            *lineString = NULL, /* string for breaking file to lines and reading them */
            temp[CONTAINER_SIZE + ONE_MORE] = "", /* temporary string for reading from file */
            nameOfOutputFile[PATH_MAX] = "", /* Output file name pid.log */
            pathOfTheFile[PATH_MAX] = "", /* Full file path */
            temStringforKeepingCurrentDir[PATH_MAX]; /* Temp for Current path / file name */
    
    

	/* Output file */
    sprintf(nameOfOutputFile, "%ld.log", (long) (getpid()));
    

    /* Target file, should've open. Otherwise, error and exit */
    if ((fileThatWeRead = open(file_name, READ_FLAGS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        error = errno;
        fprintf(stderr, "Failed to open file: %s.\n", strerror(errno));
        errno = error;
        exit(ERROR_EXIT_CODE);
    }
    /* Output file, should've open. Otherwise, error and exit */
    if ((fileThatWeWrite = open(nameOfOutputFile, WRITE_FLAGS, WRITE_PERMS)) == 
    	ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {

        error = errno;
        fprintf(stderr, "Failed to open file: %s.\n", strerror(errno));
        errno = error;
        exit(ERROR_EXIT_CODE);
    }

    /* Initial allocate for file string */
    stringOfFullFile = (char*) malloc(sizeof (char) * CONTAINER_SIZE);
    stringOfFullFile[ZERO] = '\0';


    /* Loop for file reading. If size is not enough reallocate executes. */
    while (TRUE) {
        /*  Read while interrupt happens  */
        while ((bytes = read(fileThatWeRead, temp, CONTAINER_SIZE)) == 
        ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS && errno == EINTR);


        /* As long as read success, string will grow and string from file will be added to our file string */
        if (bytes > ZERO) {

            temp[bytes + ONE_MORE] = '\0';
            stringOfFullFile = (char*) realloc(stringOfFullFile, strlen(stringOfFullFile) + CONTAINER_SIZE);
            strcat(stringOfFullFile, temp);

        } else if (bytes < ZERO) {

            fprintf(stderr, "Problem occured when read from file, inform the developer: %s\n", strerror(bytes));
            return 0;

        } else break;
    }

	/* Full file path creating */
    getcwd(temStringforKeepingCurrentDir, PATH_MAX);
    sprintf(pathOfTheFile, "%s/%s", temStringforKeepingCurrentDir, file_name);

    /* Document name added to output file */
    write(fileThatWeWrite, pathOfTheFile, strlen(pathOfTheFile));
    write(fileThatWeWrite, "\n", ONE);

    /* File string will be split into substrings those have the newline character at the end, after that searh begins */
    for (lineString = strtok(stringOfFullFile, "\n");
            lineString != NULL;
            lineString = strtok(NULL, "\n")) {
        ++lineCount;

        /* 	 */
        for (i = START; i < strlen(lineString); ++i) {


            if (lineString[i] == key[START]) {

                /* Array's start from index zero, but files are not. So  i increased columnCount 1 */
                columnCount = i + ONE_MORE;
                /* Found is TRUE first, if any character doesn't match with the key string, then will be assigned FALSE  */
                found = TRUE;
                for (j = START; i + j < strlen(lineString) && j < strlen(key) && found; ++j) {

                    /* If character does not match, found will be FALSE */
                    if (lineString[i + j] != key[j]) {
                        found = FALSE;
                    }
                }
                /* ıf in the end of the line, there is a half piece of word, then found will be assigned FALSE */
                if (i + strlen(key) - ONE_LESS >= strlen(lineString)) {

                    found = FALSE;
                }

                /* If all charaters checked and match found, found will be assigned TRUE and 
                 * informations about word will be written to output file */
                if (found == TRUE) {
                    ++countOfWordFound;
                    sprintf(stringForWritingToFile, "\t%d. found at Line: %d Column: %d\n", countOfWordFound, lineCount, columnCount);
                    write(fileThatWeWrite, stringForWritingToFile, strlen(stringForWritingToFile));


                }
            }
        }

    }

    

    /*Closing files and freeing allocated memory*/
    free(stringOfFullFile);
    close(fileThatWeRead);
    close(fileThatWeWrite);
    
    return countOfWordFound;
}
/* Copied from course book. Copies one file to another. */
/* Unix Systems Programming , Communications, Concurrency and Threads-Kay A.Robins-Steven Robins */
int copyfile(int fromfd, int tofd) {
    char *bp;
    char buf[BLKSIZE];
    int bytesread;
    int byteswritten = 0;
    int totalbytes = 0;

    for (;;) {
        while (((bytesread = read(fromfd, buf, BLKSIZE)) == -1) &&
                (errno == EINTR)); /* handle interruption by signal */
        if (bytesread <= 0) /* real error or end-of-file on fromfd */
            break;
        bp = buf;
        while (bytesread > 0) {
            while (((byteswritten = write(tofd, bp, bytesread)) == -1) &&
                    (errno == EINTR)); /* handle interruption by signal */
            if (byteswritten < 0) /* real error on tofd */
                break;
            totalbytes += byteswritten;
            bytesread -= byteswritten;
            bp += byteswritten;
        }
        if (byteswritten == -1) /* real error on tofd */
            break;
    }
    return totalbytes;
}
/* Copied from course book. Wait function. */
/* Unix Systems Programming , Communications, Concurrency and Threads-Kay A.Robins-Steven Robins */
pid_t r_wait(int *stat_loc) {
    int retval;
    while (((retval = wait(stat_loc)) == -1) && (errno == EINTR));
    return retval;
}

