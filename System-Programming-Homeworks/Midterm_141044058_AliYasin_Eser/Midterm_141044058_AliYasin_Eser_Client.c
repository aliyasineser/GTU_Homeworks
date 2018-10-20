/*LIBRARIES*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <assert.h>
#include <matheval.h>
#include <dirent.h>
#include <time.h>
#include "restart.h"

/* SIZE AND OPERATION MACROS */
#define CONTAINER_SIZE 1024
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
#define WRITE_FLAGS_FOR_LOG_FILE (O_WRONLY | O_CREAT | O_TRUNC)
#define FIFO_PERM  (S_IRUSR | S_IWUSR)
#define TEN 10
#define ONE_MORE 1
#define SIZE_MULTIPLER_FOR_BIG_FILES 1
#define NEED_THREE_ARGS 3
#define ERROR_EXIT_CODE 1
#define ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS -1
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define START 0
#define ONE_LESS 1
#define SIZE_OF_PIPE_ARRAY_MEMBER 2
#define ARG_TWO 2
#define ERROR_CHAR 'e'
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif
#define OK_CHAR 'g'
#define REPEAT_MAX 100
#define REQUEST_FIFO "request.fifo"
#define SEQUENCE_FIFO  "sequence.fifo"
#define SLEEP_MAX 5

/*VARIABLES*/
int i = 0; /*counter*/
pid_t reqbuf = 0; /*request buffer*/
int reqfd = 0, seqfd = 0; /*request and reply descriptors*/
long fifonum = 0; /*mini server id*/
pid_t selfPid = 0; /*self client pid*/
char fifoForReq[PATH_MAX] = ""; /*fifo name for request*/
char fifoForSeq[PATH_MAX] = ""; /*fifo name for sequence*/
char contentOfFi[PIPE_BUF] = ""; /*content of Fi text*/
int bytes = 0; /* bytes that program reads or writes */
char stringResult[PIPE_BUF] = ""; /* String Result */
double resultOfIntegral = 0; /*Result of the Integral*/
int countOfError = 0; /*Error count for reading*/
int interval = 0; /*time interval*/
double *results = NULL; /*result array*/
int resultsSize = 0; /*Result array size*/
char stringOfFirstFile[PIPE_BUF] = ""; /*First file content*/
pid_t tempPid; /*temp pid for swap and operation*/ 
char stringOfSecondFile[PIPE_BUF] = ""; /*Sec file content*/
char temp[CONTAINER_SIZE + ONE_MORE] = ""; /*temp array for reading*/
char logFileOfClient[PATH_MAX] = ""; /*log File Name*/
char contentOfFj[PIPE_BUF] = ""; /*Content of fj text*/
int fildesOfFi = 0, fildesOfFj = 0; /*Fi and Fj descriptor*/
int fildesOfLogFile = 0;/*First log file*/ 
char firstFile[TEN] = ""; /*first file name*/
char secFile[TEN] = ""; /*sec file name*/
char tempStrForWriting[PIPE_BUF] = ""; /*temp string for writing*/

/*Signal handler function for client*/
static void handlerClient(int signo) {

    kill(fifonum, SIGINT);
    if (results != NULL)free(results);

    results = NULL;

    if (fildesOfLogFile != 0)
        r_write(fildesOfLogFile, "Client interrupted by CTRL+C\n", strlen("Client interrupted by CTRL+C\n"));
    if (results != NULL) free(results);
    if (fildesOfFi != 0) close(fildesOfFi);
    if (fildesOfFj != 0) close(fildesOfFj);
    if (reqfd != 0) close(reqfd);
    if (seqfd != 0) close(seqfd);

    exit(1);

}

int main(int argc, char *argv[]) {

	/*Signal handling*/
    struct sigaction act;
    act.sa_handler = handlerClient;
    act.sa_flags = 0;
    if ((sigemptyset(&act.sa_mask) == -1) ||
            (sigaction(SIGINT, &act, NULL) == -1)) {
        perror("Failed to set SIGUSR1 signal handler");
        return 1;
    }

	/*Usage*/
    if (argc != 5 || argv[ONE][ZERO] != '-' || argv[TWO][ZERO] != '-' || argv[THREE][ZERO] != '-' || argv[FOUR][ZERO] != '-') {
        fprintf(stderr, "Usage: %s first_func sec_func time_interval operation\n", argv[0]);
        return 1;
    }
    /*Opening fifos*/
    if (((reqfd = open(REQUEST_FIFO, O_WRONLY)) == -1) ||
            ((seqfd = open(SEQUENCE_FIFO, O_RDONLY)) == -1)) {
        perror("Client failed to open a FIFO");
        return 1;
    }
	/*Giving pid for connection*/
    reqbuf = getpid();
    if (r_write(reqfd, &reqbuf, sizeof (pid_t)) == -1) {
        perror("Client failed to write request");
        exit(ERROR_EXIT_CODE);
    }
    /*Taking mini server pid for connection*/
    if ((bytes = r_read(seqfd, &tempPid, sizeof (long))) != sizeof (long)) {
        fprintf(stderr, "Client failed to read full fifo name number [%d] [%d]\n", bytes, (int) sizeof (tempPid));
        reqbuf = -1;
        r_write(reqfd, &reqbuf, sizeof (pid_t));
        exit(ERROR_EXIT_CODE);
    }
    fifonum = (pid_t) tempPid;

    sprintf(fifoForReq, "%ld_request.fifo", (long) fifonum);
    sprintf(fifoForSeq, "%ld_sequence.fifo", (long) fifonum);

	/*Close*/
    close(reqfd);
    close(seqfd);
	/*Open special fifos for connection*/
    if (((reqfd = open(fifoForReq, O_WRONLY)) == -1) ||
            ((seqfd = open(fifoForSeq, O_RDONLY)) == -1)) {
        perror("Client failed to open a FIFO");
        return 1;
    }
    tempPid = getpid();
    r_write(reqfd, &tempPid, sizeof (tempPid));

    sprintf(firstFile, "%s.txt", &argv[1][1]);
    sprintf(secFile, "%s.txt", &argv[2][1]);
	/*Reading function file*/
    if (((fildesOfFi = open(firstFile, O_RDONLY)) == -1) ||
            ((fildesOfFj = open(secFile, O_RDONLY)) == -1)) {
        perror("Client failed to open function files");
        return 1;
    }


    if ((bytes = r_read(fildesOfFi, stringOfFirstFile, PIPE_BUF)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        perror("Failed to read first function file.");
    }
    	stringOfFirstFile[bytes-1] = '\0';
    	if(bytes < ZERO) {
        fprintf(stderr, "Problem occured when read from file, inform the developer\n");
        exit(1);
    }


	/*Reading function file*/
    if ((bytes = r_read(fildesOfFj, stringOfSecondFile, PIPE_BUF)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        perror("Failed to read second function file.");
    }

	stringOfSecondFile[bytes-1] = '\0';
     if (bytes < ZERO) {

        fprintf(stderr, "Problem occured when read from file, inform the developer\n");
        exit(1);

    }
	/*Send to mini server*/
    selfPid = getpid();

    r_write(reqfd, stringOfFirstFile, strlen(stringOfFirstFile));
    r_write(reqfd, "\n", 1);

    r_write(reqfd, stringOfSecondFile, strlen(stringOfSecondFile));
    r_write(reqfd, "\n", 1);


    r_write(reqfd, &argv[3][1], strlen(&argv[3][1]));
    r_write(reqfd, "\n", 1);


    r_write(reqfd, &argv[4][1], strlen(&argv[4][1]));
    r_write(reqfd, "\n", 1);


    interval = atoi(&argv[3][1]);
    results = (double*) malloc(sizeof (double) * resultsSize);
    sprintf(logFileOfClient, "Client[%ld].log", (long) getpid());

    fildesOfLogFile = open(logFileOfClient, WRITE_FLAGS_FOR_LOG_FILE, WRITE_PERMS);
    sprintf(tempStrForWriting, "Client id: %ld\nFunction: (%s)%s(%s)\nInterval: %s\nIntegral results:\n", (long) getpid(), stringOfFirstFile, &argv[4][1], stringOfSecondFile, &argv[3][1]);
    r_write(fildesOfLogFile, tempStrForWriting, strlen(tempStrForWriting));

    /*  Will read the integral results and writes it to log file. If server dies, client will wait for result 4*time_interval times and after that it will break.*/
    while (TRUE) {

        bytes = 0;
        stringResult[0] = '\0';
        resultOfIntegral = -1;
        if ((bytes = r_read(seqfd, &resultOfIntegral, sizeof (double))) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {

            perror("Failed to read from named pipe.");
        }


        if (bytes < ZERO) {

            fprintf(stderr, "Problem occured when read from file, inform the developer\n");
            exit(1);

        }

        if (bytes == 0) {
            ++countOfError;
        } else {
            results = (double*) realloc(results, sizeof (double) * ++resultsSize);
            results[resultsSize - 1] = resultOfIntegral;
            sprintf(tempStrForWriting, "%.4lf\n", results[resultsSize - 1]);
            r_write(fildesOfLogFile, tempStrForWriting, strlen(tempStrForWriting));

        }

        if (countOfError == 4) {
            strcpy(tempStrForWriting, "Waited server four times of the interval but no result recieved. Client ended.");
            r_write(fildesOfLogFile, tempStrForWriting, strlen(tempStrForWriting));
            break;
        }
        sleep(interval);

    }
    
    /*Close and free*/
    free(results);
    close(reqfd);
    close(seqfd);
    close(fildesOfLogFile);
    close(fildesOfFj);
    close(fildesOfFi);


    return 0;
}
