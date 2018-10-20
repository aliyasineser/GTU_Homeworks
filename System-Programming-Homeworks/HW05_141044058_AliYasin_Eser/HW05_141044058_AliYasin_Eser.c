/* Program that takes a directory name and a key string. 
 * Finds key in all files in the directory and creates an output file includes 
 * line and column information of where the key found.*/

/* Written by Ali Yasin Eser, on 1 may 2016*/
/* Student ID:141044058 for Homework 5 */


/* Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <pthread.h>
#include <time.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif
#define SEM_NAME "/semaphoreForFifo"



/* Macros */

/* FILE MACROS */
#define READ_FLAGS O_RDONLY
#define READ_WRITE_FLAGS (O_RDWR | O_APPEND | O_CREAT)
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
#define WRITE_FLAGS_FOR_LOG_FILE (O_WRONLY | O_CREAT | O_TRUNC)
#define FIFO_PERM  (S_IRUSR | S_IWUSR)
#define SEM_PERMS (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SEM_FLAGS (O_CREAT)



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
#define SEM_PROCESS_SHARED 1
#define SEM_PROCESS_PRIVATE 0


typedef struct {
    char file_name[PIPE_BUF];
    char key[PIPE_BUF];
    int pipeDescriptor;
    pid_t parent;
} threadParamData;


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
pthread_t* threadInformationPtr = NULL; /* Thread array */
int *temporaryPipe = NULL;
pid_t selfPidOfProcess = 0; /* process id of process that doing this function */
char tempPidStringForSum[PATH_MAX] = "", /* temp String name for all the child pid temp files */
        lastOutputFileNameArray[PATH_MAX] = "", /* Output name, log file for child that entered directory */
        pathOfTheDirectory[PATH_MAX] = "", /* Directory path -> current path / directory */
        currentPath[PATH_MAX] = "", /* Getting current path */
        currentDirectoryEntryPath[PATH_MAX] = ""; /* For each entry, a path needed */
int sumFifoFd;
pid_t grandParent = 0;
pid_t owner = 0;
void *res = NULL;

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
sem_t *semForLog = NULL; /*Semaphore*/
threadParamData *threadDataArrayPtr;

static void handlerDir(int signo) {
    for (countOfChild = 0; countOfChild < counterOfChilds; countOfChild++) {
        sprintf(tempStringforKeepingCurrentDir, "%d.myfifo", countOfChild);
        remove(tempStringforKeepingCurrentDir);

        if (childrenPidInformationPtr[countOfChild] != -1) kill(childrenPidInformationPtr[countOfChild], SIGINT);
        if (threadInformationPtr[countOfChild] != -1)pthread_cancel(threadInformationPtr[countOfChild]);

    }
    if (getpid() != grandParent) {
        kill(owner, SIGINT);

    } else
        write(logFileFd, "Error occured: User entered ^C character\n", 41);

    exit(1);
}

static void handlerFile(int signo) {

    kill(owner, SIGINT);
    exit(1);
}
/* Function for thread that does file reading */
void *grepfromFileThread(void *args) {

    threadParamData* data = (threadParamData*) args;


    grepfromfile(data->file_name, data->key, data->pipeDescriptor, data->parent);


    pthread_exit(NULL);

}


/* Helper function prototypes */

int grepfromfile(const char* file_name, const char* key, const int pipeDescriptor, const pid_t parent);
int grepfromdirectory(const char* directory_name, const char* key, int fifoDesc, pid_t parent);

/* Main function */
int main(int argc, char *argv[]) {

    char pidNameForReadingStringArr[PATH_MAX] = "", /* pid.log file */
            entryPathForRemovingFile[PATH_MAX] = "", /* current path / file name */
            tempPathForGettingCurrentPath[PATH_MAX] = "", /* current path + file name */
            fifoFileForGatheringAll[PATH_MAX] = "";
    int fileReadDescriptor = 0, fileWriteDescriptor = 0; /* write and read descriptors */
    int fifoDesc;
    owner = getpid();
    grandParent = getpid();

    


	/* Usage control */
    if (argc != NEED_THREE_ARGS) {
        fprintf(stderr, "Usage: %s which_file which_word\n", argv[ZERO]);
        exit(ERROR_EXIT_CODE);
    }
	/*We should unlink the semaphore, because there can be a semaphore that has same name and it can be locked*/
	sem_unlink(SEM_NAME);
    sprintf(fifoFileForGatheringAll, "%ld.myfifo", (long) getpid());
	/*Fifo creation*/
    if (mkfifo(fifoFileForGatheringAll, FIFO_PERM) == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n",
                    (long) getpid(), fifoFileForGatheringAll, strerror(errno));
            return 0;
        }
    }
	/* Fifo opening */
    while (((fifoDesc = open(fifoFileForGatheringAll, READ_WRITE_FLAGS)) == -1) && (errno == EINTR));
    if (fifoDesc == -1) {
        fprintf(stderr, "[%ld]:failed to open named pipe %s for read: %s\n",
                (long) getpid(), fifoFileForGatheringAll, strerror(errno));
        unlink(fifoFileForGatheringAll);
        return 1;
    }



	/*Creation of semaphore and error handling*/
	while (((semForLog = sem_open(SEM_NAME, SEM_FLAGS, SEM_PERMS,1)) == SEM_FAILED) &&
		(errno == EINTR));

	if(semForLog == SEM_FAILED){
		perror("Named semaphore error: ");
		return -1;
	}



   /*Log file creation*/
    while (((fileWriteDescriptor = open(LOG_FILE_NAME, WRITE_FLAGS_FOR_LOG_FILE, WRITE_PERMS)) ==
            ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) && errno == EINTR);
  
    
    /* Starting search */
 	grepfromdirectory(argv[ONE], argv[ARG_TWO], fifoDesc, selfPidOfProcess);
 	
	/*From fifo to Log file*/
    /****************** entry section *******************************/
    while (sem_wait(semForLog) == -1)
        if (errno != EINTR) {
            fprintf(stderr, "Thread failed to lock semaphore\n");
            return ZERO;
        }


	
    /* Loop for file reading. If size is not enough reallocate executes. */
    while (TRUE) {
        /*  Read while interrupt happens  */
        bytes = r_read(fifoDesc, temp, CONTAINER_SIZE);


        /* As long as read success, string will grow and string from file will be added to our file string */
        if (bytes > ZERO) {

            temp[bytes + ONE_MORE] = '\0';
            
            r_write(fileWriteDescriptor, temp, strlen(temp));

			if(bytes < CONTAINER_SIZE)
				break;

        } else if(bytes < ZERO) {

            fprintf(stderr, "Problem occured when read from file, inform the developer\n");

        }
        else break;
    }

	 /****************** exit section ********************************/
    if (sem_post(semForLog) == -1) 
        fprintf(stderr, "Thread failed to unlock semaphore\n");


	/*While program doing grepfromdirectory function, it entering a directory. So program should go back. */
	chdir("..");

    /* Closing files */
	close(fifoDesc);
    close(fileWriteDescriptor);
	if(unlink(fifoFileForGatheringAll) == -1)
		perror("Couldn't delete the fifo: ");
		
	sem_close(semForLog);
	sem_unlink(SEM_NAME);
		

    return 0;
}


/*Recursive function that gives a log file that includes positions of text files that matches with the given key*/
int grepfromdirectory(const char* directory_name, const char* key, int fifoDesc, pid_t parent) {

	sem_t *fifoSem;
	int counterOfDirectories = 0;
    owner = parent;
	
    struct sigaction act;
    act.sa_handler = handlerDir;
    act.sa_flags = 0;
    if ((sigemptyset(&act.sa_mask) == -1) ||
            (sigaction(SIGINT, &act, NULL) == -1)) {
        perror("Failed to set SIGINT signal handler");
        return 1;
    }


	while (((fifoSem = sem_open(SEM_NAME, O_RDWR)) == SEM_FAILED) &&
	(errno == EINTR));

	if(fifoSem == SEM_FAILED){
		perror("Named semaphore error: ");
		return -1;
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
            ++counterOfDirectories;

        } else if (S_ISREG(statbuf.st_mode)) {
            ++counterOfChilds;

        }

    }




    /* Allocating array for storing children pids and pipes*/
    childrenPidInformationPtr = (pid_t*) malloc(counterOfChilds * sizeof (pid_t));
    childrenPipeInformationPtr = malloc(counterOfChilds * sizeof (int*));
    threadDataArrayPtr = (threadParamData*) malloc(counterOfChilds * sizeof (threadParamData));
    threadInformationPtr = (pthread_t*) malloc(counterOfChilds * sizeof (pthread_t));


    for (i = 0; i < counterOfChilds; ++i) {
        threadInformationPtr[i] = -1;
        childrenPidInformationPtr[i] = -1;

    }



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

            childrenPidInformationPtr[countForForkLoop] = fork();


            if (childrenPidInformationPtr[countForForkLoop] == 0) {



                for (i = 0; i < counterOfChilds; ++i) {
                    free(childrenPipeInformationPtr[i]);
                }
                sem_close(fifoSem);
                free(childrenPipeInformationPtr);
                free(childrenPidInformationPtr);
                closedir(dirp);
                free(threadInformationPtr);
                free(threadDataArrayPtr);
                grepfromdirectory(direntp->d_name, key, fifoDesc, selfPidOfProcess);

             


                exit(ZERO);
            }
            ++countForForkLoop;
        } else if (S_ISREG(statbuf.st_mode)) { /* If file founds */



            if (pipe(childrenPipeInformationPtr[countForForkLoop]) == -1) {
                fprintf(stderr, "Failed to open pipe: %s.\n", strerror(errno));
            }


            strncpy(threadDataArrayPtr[countForForkLoop].file_name, direntp->d_name, strlen(direntp->d_name) + 1);

            strcpy(threadDataArrayPtr[countForForkLoop].key, key);

            threadDataArrayPtr[countForForkLoop].pipeDescriptor = childrenPipeInformationPtr[countForForkLoop][ONE];
            threadDataArrayPtr[countForForkLoop].parent = getpid();


            if (error = pthread_create(&(threadInformationPtr[countForForkLoop]), NULL,
                    grepfromFileThread, &(threadDataArrayPtr[countForForkLoop]))) {
                fprintf(stderr, "Failed to start thread %d:%s\n", countForForkLoop, strerror(error));
                exit(1);
            }


            ++countForForkLoop;
        }
    }



    /* Waiting all the children */
    while (r_wait(NULL) > 0);

    for (countForForkLoop = 0; countForForkLoop < counterOfChilds; ++countForForkLoop) {

        if (threadInformationPtr[countForForkLoop] != -1) {
            pthread_join(threadInformationPtr[countForForkLoop], &res);
        }


    }




    /****************** entry section *******************************/
    while (sem_wait(fifoSem) == -1) /* Entry section */
        if (errno != EINTR) {
            fprintf(stderr, "Thread failed to lock semaphore\n");
            return ZERO;
        }



    /* Process traversing all it's child's temp files. Taking all the information 
     * in the files and copying to one file, the file that we opened in subdirectory. */
    for (countForForkLoop = 0; countForForkLoop < counterOfChilds; ++countForForkLoop) {

        if (childrenPipeInformationPtr[countForForkLoop][ZERO] != -1) {
            close(childrenPipeInformationPtr[countForForkLoop][ONE]);
            copyfile(childrenPipeInformationPtr[countForForkLoop][ZERO], fifoDesc); /*  File copy*/
            close(childrenPipeInformationPtr[countForForkLoop][ZERO]);
        }


    }
 
	
    /****************** exit section ********************************/
    if (sem_post(fifoSem) == -1) /* Exit section */
        fprintf(stderr, "Thread failed to unlock semaphore\n");

	sprintf(tempPidStringForSum, "%ld.myfifo", (long) getpid());
    remove(tempPidStringForSum);



    /*Freeing array memories*/
    for (i = 0; i < counterOfChilds; ++i) {
        free(childrenPipeInformationPtr[i]);
    }

    /* Closing file */
    closedir(dirp);
    sem_close(fifoSem);
    close(sumFifoFd);
    close(fileThatWeWrite);
    free(childrenPidInformationPtr);
    free(threadInformationPtr);
    free(threadDataArrayPtr);
    free(childrenPipeInformationPtr);

}



int grepfromfile(const char* file_name, const char* key, const int pipeDescriptor, const pid_t parent) {


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
            temp[CONTAINER_SIZE + ONE_MORE] = ""; /* temporary string for reading from file */
	char tempCharForReading;
	int count=0;
	int iptr = 0;

    owner = parent;

    struct sigaction act;
    act.sa_handler = handlerFile;
    act.sa_flags = 0;
    if ((sigemptyset(&act.sa_mask) == -1) ||
            (sigaction(SIGINT, &act, NULL) == -1)) {
        perror("Failed to set SIGUSR1 signal handler");
        return 1;
    }

   



	if ((iptr = open(file_name, O_RDONLY)) == -1 ){
		fprintf(stderr, "Couldn't open the file\n");
		exit(1);
	}
	

	while(r_read(iptr, &tempCharForReading, sizeof(char)) != 0)
		++count;
	
	

	close(iptr);
	
	
	
	 /* Target file, should've open. Otherwise, error and exit */
    if ((fileThatWeRead = open(file_name, READ_FLAGS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        error = errno;
        fprintf(stderr, "Failed to open file: %s.\n", strerror(errno));
        errno = error;
        return ERROR_EXIT_CODE;
    }
	
    /* Initial allocate for file string */
    stringOfFullFile = (char*) malloc(sizeof (char) * count+1);
	stringOfFullFile[0] = '\0';
    r_read(fileThatWeRead, stringOfFullFile, count);


    /* Full file path creating */
    getcwd(tempStringforKeepingCurrentDir, PATH_MAX);
    sprintf(pathOfTheFile, "%s/%s\n", tempStringforKeepingCurrentDir, file_name);

    /* Document name added to output file */
    write(pipeDescriptor, pathOfTheFile, strlen(pathOfTheFile));


	if(count == 0){
		sprintf(stringForWritingToFile, "\tEmpty file\n");
		write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));
		free(stringOfFullFile);
		close(fileThatWeRead);
		return 0;
	}




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
                   
                    if(countOfWordFound == 1){
                    	sprintf(stringForWritingToFile, "\t%6s %6s %6s\n", "No", "Line", "Column");
                
 						write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));
                    }
                    
                    sprintf(stringForWritingToFile, "\t%6d %6d %6d\n", countOfWordFound, lineCount, columnCount);
                 
                    write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));


                }
            }
        }

    }
    
    if(countOfWordFound == 0){
    	sprintf(stringForWritingToFile, "\tNo words match with the key: %s\n", key);
		write(pipeDescriptor, stringForWritingToFile, strlen(stringForWritingToFile));
    }

    
    

    /*Closing files and freeing allocated memory*/
    free(stringOfFullFile);
    close(fileThatWeRead);
	

    return countOfWordFound;
}
