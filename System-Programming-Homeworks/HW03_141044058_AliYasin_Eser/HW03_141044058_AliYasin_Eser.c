/* Program that takes a directory name and a key string. 
 * Finds key in all files in the directory and creates an output file includes 
 * line and column information of where the key found.*/

/* Written by Ali Yasin Eser, on 26 march 2016*/
/* Student ID:141044058 for Homework 3 */


/* Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif

/* Macros */

/* FILE MACROS */
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
#define WRITE_FLAGS_FOR_LOG_FILE (O_WRONLY | O_CREAT | O_TRUNC)
#define FIFO_PERM  (S_IRUSR | S_IWUSR)


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
#define SIZE_OF_PIPE_ARRAY_MEMBER 2
#define ARG_TWO 2


 /* Variables for grepFromDir */
    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */
    int fileThatWeWrite = ZERO, fileThatWeRead = ZERO, /* Write and read file descriptors */
            statOfEntry = ZERO, /* Entry stats */
            counterOfChilds = ZERO, /* how many directories and files found */
            countForForkLoop = ZERO, /* index for pid_t array */
            error = ZERO,
            fd = ZERO,
            logFileFd,
            tempFileDescriptor = 0; /* Error for storing errno */
    pid_t* childrenPidInformationPtr = NULL; /* Children array */
    int **childrenPipeInformationPtr = NULL; /* Pipe array */
    int *temporaryPipe = NULL;
    pid_t selfPidOfProcess = 0; /* process id of process that doing this function */
    char tempPidStringForSum[PATH_MAX] = "", /* temp String name for all the child pid temp files */
            lastOutputFileNameArray[PATH_MAX] = "", /* Output name, log file for child that entered directory */
            pathOfTheDirectory[PATH_MAX] = "", /* Directory path -> current path / directory */
            currentPath[PATH_MAX] = "", /* Getting current path */
            currentDirectoryEntryPath[PATH_MAX] = ""; /* For each entry, a path needed */

	pid_t grandParent = 0;
	pid_t owner = 0;

  /* Variables for grepFromFile*/
    int bytes = ZERO, /*Bytes that read from file*/
            i = ZERO, /* index for string line */
            j = ZERO, /* If there is a match, j index will check the word without changing real index */
            found = ZERO, /* If found assign TRUE */
            lineCount = ZERO, /* line counter */
            columnCount = ZERO, /* column counter, if there is a match this variable will be assigned */
            countOfWordFound = ZERO, /* word counter */
            sizeMultiplier = SIZE_MULTIPLER_FOR_BIG_FILES; /* If string size is not enough multipler will increase */
    char *stringOfFullFile = NULL, /* char *  for reading complete file */
            stringForWritingToFile[CONTAINER_SIZE] = "", /* If there is a match, this string will be fill and write to file */
            *lineString = NULL, /* string for breaking file to lines and reading them */
            temp[CONTAINER_SIZE + ONE_MORE] = "", /* temporary string for reading from file */
            nameOfOutputFile[PATH_MAX] = "", /* Output file name pid.log */
            pathOfTheFile[PATH_MAX] = "", /* Full file path */
            tempStringforKeepingCurrentDir[PATH_MAX] = ""; /* Temp for Current path / file name */

	int countOfChild = ZERO;

static void handlerDir(int signo) { 
	for(countOfChild =0; countOfChild < counterOfChilds; countOfChild++){
		sprintf(tempStringforKeepingCurrentDir, "%d.myfifo", countOfChild);
		remove(tempStringforKeepingCurrentDir);
		kill(childrenPidInformationPtr[countOfChild], SIGINT);
		
	}
	if(getpid() != grandParent){
		kill(owner, SIGINT);
		
	}else
		write(logFileFd, "Error occured: User entered ^C character\n", 41);
		
	
		
	
	exit(1);
}

static void handlerFile(int signo) {
	free(stringOfFullFile);
			kill(owner, SIGINT);
	exit(1);
}



/* Helper function prototypes */

int grepfromdirectory(const char* directory_name, const char* key, int fifoDesc,  pid_t parent);
int grepfromfile(const char* file_name, const char* key, const int pipeDescriptor, pid_t parent);

/* Main function */
int main(int argc, char *argv[]) {

    char pidNameForReadingStringArr[PATH_MAX] = "", /* pid.log file */
            entryPathForRemovingFile[PATH_MAX] = "", /* current path / file name */
            tempPathForGettingCurrentPath[PATH_MAX] = ""; /* current path + file name */
    int fileReadDescriptor = 0, fileWriteDescriptor = 0; /* write and read descriptors */
	owner = getpid();
	grandParent = getpid();
    /* Usage control */
    if (argc != NEED_THREE_ARGS) {
        fprintf(stderr, "Usage: %s which_file which_word", argv[ZERO]);
        exit(ERROR_EXIT_CODE);
    }
    while (((fileWriteDescriptor = open(LOG_FILE_NAME, WRITE_FLAGS_FOR_LOG_FILE, WRITE_PERMS)) ==
            ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) && errno == EINTR);
	logFileFd = fileWriteDescriptor;
    /* Starting search */
    
    grepfromdirectory(argv[ONE], argv[ARG_TWO], fileWriteDescriptor, selfPidOfProcess);
	
    /* Closing directories */

    close(fileWriteDescriptor);



    return 0;
}

int grepfromdirectory(const char* directory_name, const char* key, int fifoDesc , pid_t parent) {
	
	owner = parent;
	
	struct sigaction act;
	act.sa_handler = handlerDir;
	act.sa_flags = 0;
	if ((sigemptyset(&act.sa_mask) == -1) ||
		(sigaction(SIGINT, &act, NULL) == -1) ) {
		perror("Failed to set SIGUSR1 signal handler");
		return 1;
	}
	
  
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

    /* Allocating array for storing children pids and pipes*/
    childrenPidInformationPtr = (pid_t*) malloc(counterOfChilds * sizeof (pid_t));
    childrenPipeInformationPtr = malloc(counterOfChilds * sizeof (int*));

    /* Pipes for pipe arrays */
    for (i = 0; i < counterOfChilds; ++i) {
        childrenPipeInformationPtr[i] = malloc(sizeof (int) * 2);
    }

    for (i = 0; i < counterOfChilds; ++i) {
        childrenPipeInformationPtr[i][ZERO] = -1;
        childrenPipeInformationPtr[i][ONE] = -1;
    }


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
			
            if (getpid() == selfPidOfProcess) {
                sprintf(tempPidStringForSum, "%d.myfifo", countForForkLoop);
                if (mkfifo(tempPidStringForSum, FIFO_PERM) == -1) { /* create a named pipe */
                    if (errno != EEXIST) {
                        fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
                                (long) getpid(), tempPidStringForSum, strerror(errno));
                        for (i = 0; i < counterOfChilds; ++i) {
                            free(childrenPipeInformationPtr[i]);
                        }
                        free(childrenPipeInformationPtr);
                        free(childrenPidInformationPtr);
                        closedir(dirp);
                        return 0;
                    }
                }


                childrenPidInformationPtr[countForForkLoop] = fork();

            }
            if (getpid() == selfPidOfProcess) {
                while (((childrenPipeInformationPtr[countForForkLoop][ZERO] = open(tempPidStringForSum, READ_FLAGS)) == -1) && (errno == EINTR));
                if (fd == -1) {
                    fprintf(stderr, "[%ld]:failed to open named pipe %s for read: %s\n",
                            (long) getpid(), tempPidStringForSum, strerror(errno));
                    for (i = 0; i < counterOfChilds; ++i) {
                        free(childrenPipeInformationPtr[i]);
                    }
                    free(childrenPipeInformationPtr);
                    free(childrenPidInformationPtr);
                    close(fd);
                    closedir(dirp);
                    return 1;
                }
            }

            if (childrenPidInformationPtr[countForForkLoop] == 0) {


                while (((fd = open(tempPidStringForSum, O_WRONLY)) == -1) && (errno == EINTR));
                if (fd == -1) {
                    fprintf(stderr, "[%ld]:failed to open named pipe %s for write: %s\n",
                            (long) getpid(), tempPidStringForSum, strerror(errno));
                    return 1;
                }

                for (i = 0; i < counterOfChilds; ++i) {
                    free(childrenPipeInformationPtr[i]);
                }
                free(childrenPipeInformationPtr);
                free(childrenPidInformationPtr);
                closedir(dirp);
                grepfromdirectory(direntp->d_name, key, fd, selfPidOfProcess);

                close(fd);



                exit(ZERO);
            }
            ++countForForkLoop;
        } else if (S_ISREG(statbuf.st_mode)) { /* If file founds */

            if (getpid() == selfPidOfProcess) {

                if (pipe(childrenPipeInformationPtr[countForForkLoop]) == -1) {
                    fprintf(stderr, "Failed to open pipe: %s.\n", strerror(errno));
                }
                childrenPidInformationPtr[countForForkLoop] = fork();
            }
            if (childrenPidInformationPtr[countForForkLoop] == 0) {

                fd = childrenPipeInformationPtr[countForForkLoop][ONE];
                for (i = 0; i < counterOfChilds; ++i) {
                    free(childrenPipeInformationPtr[i]);
                }
                free(childrenPipeInformationPtr);
                grepfromfile(direntp->d_name, key, fd, selfPidOfProcess);
                free(childrenPidInformationPtr);
                closedir(dirp);

                exit(ZERO);
            }
            ++countForForkLoop;
        }
    }
  	raise(SIGINT);
    /* Waiting all the children */
    while (r_wait(NULL) > 0);

  

    /* Process traversing all it's child's temp files. Taking all the information 
     * in the files and copying to one file, the file that we opened in subdirectory. */
    for (countForForkLoop = 0; countForForkLoop < counterOfChilds; ++countForForkLoop) {

	if(childrenPipeInformationPtr[countForForkLoop][ZERO] != -1){
        close(childrenPipeInformationPtr[countForForkLoop][ONE]);
        copyfile(childrenPipeInformationPtr[countForForkLoop][ZERO], fifoDesc); /*  File copy*/
        close(childrenPipeInformationPtr[countForForkLoop][ZERO]);
     }
	
        /* Removing file */
        sprintf(lastOutputFileNameArray, "%d.myfifo", countForForkLoop);

        remove(lastOutputFileNameArray);
    }

    /*Freeing array memories*/
    for (i = 0; i < counterOfChilds; ++i) {
        free(childrenPipeInformationPtr[i]);
    }

    /* Closing file */
    closedir(dirp);
    close(fileThatWeWrite);
    free(childrenPidInformationPtr);
    free(childrenPipeInformationPtr);

}

int grepfromfile(const char* file_name, const char* key, const int pipeDescriptor, pid_t parent) {
  
  	owner = parent;
  
	struct sigaction act;
	act.sa_handler = handlerFile;
	act.sa_flags = 0;
	if ((sigemptyset(&act.sa_mask) == -1) ||
		(sigaction(SIGINT, &act, NULL) == -1) ) {
		perror("Failed to set SIGUSR1 signal handler");
		return 1;
	}

    /* Target file, should've open. Otherwise, error and exit */
    if ((fileThatWeRead = open(file_name, READ_FLAGS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        error = errno;
        fprintf(stderr, "Failed to open file: %s.\n", strerror(errno));
        errno = error;
        return ERROR_EXIT_CODE;
    }



    /* Initial allocate for file string */
    stringOfFullFile = (char*) malloc(sizeof (char) * PIPE_BUF);

    for (i = 0; i < PIPE_BUF; ++i) {
        stringOfFullFile[i] = '\0';
    }

	


    r_read(fileThatWeRead, stringOfFullFile, PIPE_BUF);


    /* Full file path creating */
    getcwd(tempStringforKeepingCurrentDir, PATH_MAX);
    sprintf(pathOfTheFile, "%s/%s\n", tempStringforKeepingCurrentDir, file_name);

    /* Document name added to output file */
    write(pipeDescriptor, pathOfTheFile, strlen(pathOfTheFile));
 
    sprintf(stringForWritingToFile, "\t%6s %6s %6s\n", "No", "Line", "Column");
    write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));


    /* File string will be split into substrings those have the newline character at the end, after that searh begins */
    for (lineString = strtok(stringOfFullFile, "\n");
            lineString != NULL;
            lineString = strtok(NULL, "\n")) {
        ++lineCount;

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
                    sprintf(stringForWritingToFile, "\t%6d %6d %6d\n", countOfWordFound, lineCount, columnCount);
                    write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));


                }
            }
        }

    }

    /*Closing files and freeing allocated memory*/
    free(stringOfFullFile);
    close(fileThatWeRead);


    return countOfWordFound;
}


