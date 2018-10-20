/* Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <matheval.h>

#include <assert.h>
#include <time.h>


/* SIZE AND OPERATION MACROS */
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)
#define WRITE_FLAGS_FOR_LOG_FILE (O_WRONLY | O_CREAT | O_TRUNC)
#define FIFO_PERM  (S_IRUSR | S_IWUSR)
#include "restart.h"
#define MS_TO_SEC 1000
#define REQUEST_FIFO "request.fifo"
#define SEQUENCE_FIFO  "sequence.fifo"
#define REQ_PERMS (S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH)
#define SEQ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP| S_IROTH)
#define CONTAINER_SIZE 1024
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define TWO 2
#define RESULT_SIZE 80
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
#define CONNECTION_FILE "serverConnectPidList.log"

/*Variables*/
char buf[ONE] = ""; /*buffer*/
int reqfd = ZERO, seqfd = ZERO; /*Descriptors*/
int serveCount = ZERO; /*counter */
char fifoForReq[PATH_MAX] = "";/*fifo name for request*/
char fifoForSeq[PATH_MAX] = "";/*fifo name for sequence*/
pid_t selfPidOfProcess = ZERO; /*self pid*/
pid_t reqClient = ZERO; /*request client*/
long seqnum = ONE; /*sequence number*/
pid_t selfPidOfChild = ZERO; /*child pid*/
pid_t childPid = -1; /* child pid for fork*/
char tempArrayForConnectionLog[PIPE_BUF] = ""; /*temp array for connection log file*/
long tempPidForStore = ZERO;/*temp pid*/
int maxClient = ZERO; /*max client*/
pid_t *arrayOfserve = NULL; /*serve array*/ 
int serveArraySize = 0; /*size of serve array*/ 
time_t serverStartTime;/*server start time*/
int loopCounter = 0;
char seqArr[PATH_MAX] = SEQUENCE_FIFO; /*fifo sequence*/
char reqArr[PATH_MAX] = REQUEST_FIFO; /*fifo request*/
/*Strings for reading and storing expressions and informations*/
char *stringOfFullInfoPtr = NULL,
        *stringOfFirstFilePtr = NULL,
        *stringOfSecondFilePtr = NULL,
        *stringOfIntervalPtr = NULL,
        *tempStrPtr = NULL,
        *stringOfOperationPtr = NULL,
        temp[CONTAINER_SIZE] = "",
        operation = '\0',
        *allExpressionPtr = NULL;
time_t beforeOperation = 0, afterOperation = 0; /*operation times*/
char result[RESULT_SIZE] = ""; /*result information*/
double sum1 = 0.0; /*sum1*/
double resolution = 0;/*resolution info*/
double sum2 = 0.0; /*sum2*/
void *secondPartOfTheFunc = NULL; /*second part of the function*/
void *func = NULL; /*all expression function*/
int connectionFildes = 0;/*connection file descriptors*/
int i = 0; /*counter*/
int stepOfIntegralOfIntegral = 0; /*step of the integral*/
double lowerLimit = 0, upperLimit = 0, timeInterval = 0, connectionTime = 0; /*connection time and limits*/
double resultOfTheIntegral = 0;/*result integral*/
int time_interval = 0, bytes = 0; /*interval and read bytes*/
struct sigaction act; /*signal handler struct*/

/*signal handler of serve*/
static void handlerServerServe(int signo) {

    if (arrayOfserve != NULL)
        for (i = 0; i < serveArraySize; ++i) {
            if (arrayOfserve[i] != -1)
                kill(arrayOfserve[i], signo);
        }
    if (arrayOfserve != NULL) free(arrayOfserve);
    arrayOfserve = NULL;
    if (strcmp(fifoForReq, "") != 0) remove(fifoForReq);
    strcpy(fifoForReq, "");
    if (strcmp(fifoForSeq, "") != 0) remove(fifoForSeq);
    strcpy(fifoForSeq, "");
    if (stringOfFirstFilePtr != NULL) free(stringOfFirstFilePtr);
    stringOfFirstFilePtr = NULL;
    if (stringOfOperationPtr != NULL) free(stringOfOperationPtr);
    stringOfOperationPtr = NULL;
    if (stringOfSecondFilePtr != NULL) free(stringOfSecondFilePtr);
    stringOfSecondFilePtr = NULL;
    if (stringOfIntervalPtr != NULL) free(stringOfIntervalPtr);
    stringOfIntervalPtr = NULL;
    if (tempStrPtr != NULL) free(tempStrPtr);
    tempStrPtr = NULL;
    if (func != NULL)evaluator_destroy(func);
    func = NULL;
    if (secondPartOfTheFunc != NULL) evaluator_destroy(secondPartOfTheFunc);
    secondPartOfTheFunc = NULL;
    if (stringOfFirstFilePtr != NULL)free(stringOfFirstFilePtr);
    stringOfFirstFilePtr = NULL;
    if (stringOfOperationPtr != NULL)free(stringOfOperationPtr);
    stringOfOperationPtr = NULL;
    if (stringOfSecondFilePtr != NULL)free(stringOfSecondFilePtr);
    stringOfSecondFilePtr = NULL;
    if (stringOfIntervalPtr != NULL)free(stringOfIntervalPtr);
    stringOfIntervalPtr = NULL;


    kill(reqClient, signo);

    exit(1);
}
/*Signal handler of main func*/
static void handlerServerMain(int signo) {
    if (childPid != 0) {
		if(arrayOfserve != NULL)
			for(i=0; i < serveArraySize; ++i){
				if(arrayOfserve[i] != -1){
					kill(arrayOfserve[i], signo);
					arrayOfserve[i] = -1;
					}
		}
        if (arrayOfserve != NULL) free(arrayOfserve);
        arrayOfserve = NULL;
        if(strcmp(reqArr, "") != 0) remove(REQUEST_FIFO);
        strcpy(reqArr, "");
        if(strcmp(seqArr, "") != 0) remove(SEQUENCE_FIFO);
        strcpy(seqArr, "");
    } else {
       
        if (strcmp(fifoForReq, "") != 0) remove(fifoForReq);
        strcpy(fifoForReq, "");
     
        if (strcmp(fifoForSeq, "") != 0) remove(fifoForSeq);
        strcpy(fifoForSeq, "");

    }


    exit(1);
}



void serveClient(char* fifoForReq, char* fifoForSeq, pid_t client_id, time_t serverStartTime, char *resolutionOfIntegral);

int main(int argc, char *argv[]) {

	/*Usage*/
    if (argc != 3 || argv[ONE][ZERO] != '-' || argv[TWO][ZERO] != '-') {
        fprintf(stderr, "Usage: %s -resolution -max_number_of_clients\n", argv[0]);
        return 1;
    }
	/*Connection info and log file*/
    connectionFildes = open(CONNECTION_FILE, WRITE_FLAGS_FOR_LOG_FILE, WRITE_PERMS);
    serveArraySize = atoi(&argv[2][1]);
    maxClient = atoi(&argv[2][1]);
    serverStartTime = time(NULL);
    arrayOfserve = (pid_t*) malloc(sizeof (pid_t) * atoi(&argv[2][1]));
    for (loopCounter = 0; loopCounter < serveArraySize; ++loopCounter) {
        arrayOfserve[loopCounter] = -1;
    }



	/*Signal handling*/
    act.sa_handler = handlerServerMain;
    act.sa_flags = 0;
    if ((sigemptyset(&act.sa_mask) == -1) ||
            (sigaction(SIGINT, &act, NULL) == -1) ||
            (sigaction(SIGTERM, &act, NULL) == -1) ||
            (sigaction(SIGQUIT, &act, NULL) == -1)) {
        perror("Failed to set SIGINT signal handler");
        return 1;
    }


    /* Storing self adress */
    selfPidOfProcess = getpid();

    /* create a named pipe to handle incoming requests */
    if ((mkfifo(REQUEST_FIFO, REQ_PERMS) == -1) && (errno != EEXIST)) {
        perror("Server failed to create request FIFO");
        return 1;
    }
    if ((mkfifo(SEQUENCE_FIFO, SEQ_PERMS) == -1) && (errno != EEXIST)) {
        perror("Server failed to create sequence FIFO");
        if (unlink(REQUEST_FIFO) == -1)
            perror("Server failed to unlink request FIFO");
        return 1;
    }
   	/*Opening files*/
    if (((reqfd = open(REQUEST_FIFO, O_RDWR)) == -1) ||
            ((seqfd = open(SEQUENCE_FIFO, O_RDWR)) == -1)) {
        perror("Server failed to open one of the FIFOs");
        return 1;
    }

	/*Infinite client wait loop*/
    while (TRUE) {
		/*If program not serves max clients, connects another. Otherwise it'll wait at least one client end.*/
        if (serveCount < atoi(&argv[2][1])) {
        	/*Proper reading*/
            if (r_read(reqfd, &reqClient, sizeof (reqClient)) == sizeof (reqClient)) {
            	/*Client pid check*/
                if (reqClient > 0) {
                	/*Child will serve the client, parent will wait the other clients*/
                    childPid = fork(); 
                    
                    if (childPid == 0) { /*Child code*/
                        selfPidOfChild = getpid();
                        tempPidForStore = (long) getpid();
						
                        sprintf(fifoForReq, "%ld_request.fifo", (long) getpid());
                        sprintf(fifoForSeq, "%ld_sequence.fifo", (long) getpid());

                        /* create a named pipe to handle incoming requests */
                        if ((mkfifo(fifoForReq, REQ_PERMS) == -1) && (errno != EEXIST)) {
                            perror("Server failed to create request FIFO");
                            return 1;
                        }
                        if ((mkfifo(fifoForSeq, SEQ_PERMS) == -1) && (errno != EEXIST)) {
                            perror("Server failed to create sequence FIFO");
                            if (unlink(fifoForReq) == -1)
                                perror("Server failed to unlink request FIFO");
                            return 1;
                        }

						/*Sending child id to client for communication*/
                        if (r_write(seqfd, &tempPidForStore, sizeof (long)) == -1) {
                            perror("Server failed to write reply");
                            exit(ERROR_EXIT_CODE);
                        }
						/*Serve function*/
                        serveClient(fifoForReq, fifoForSeq, reqClient, serverStartTime, &argv[1][1]);
                        free(arrayOfserve);
                        if (strcmp(fifoForReq, "") != 0) remove(fifoForReq);
						strcpy(fifoForReq, "");
					 
						if (strcmp(fifoForSeq, "") != 0) remove(fifoForSeq);
						strcpy(fifoForSeq, "");
                        exit(ZERO);
                    } else {
                    	/*Updating the connection log file.*/
                        sprintf(tempArrayForConnectionLog, "Server time: %lf	Client id: %ld\n", difftime(time(NULL), serverStartTime), (long) reqClient);
                        r_write(connectionFildes, tempArrayForConnectionLog, strlen(tempArrayForConnectionLog));
                        /*Adding child's pid to serveArray for if signal comes killing them*/
                        for (loopCounter = 0; loopCounter < serveArraySize; ++loopCounter) {
                            if (arrayOfserve[loopCounter] == -1) {

                                arrayOfserve[loopCounter] = childPid;
                                break;
                            }
                        }

                        serveCount++;

                    }
                    /*Illegal client*/
                } else if (reqClient < 0) {

                    break;

                }
            }
			
        } else {/* Maximum serve, need to wait at least one child for serving another client */
            if ((childPid = r_wait(NULL)) > 0) {
                for (loopCounter = 0; loopCounter < serveArraySize; ++loopCounter) {
                    if (arrayOfserve[loopCounter] == childPid) {

                        arrayOfserve[loopCounter] = -1;
                        break;
                    }
                }
                serveCount--;

            } else {
                perror("Error of server children");
                exit(1);
            }
        }

    }
	/*Close and free and ending*/
	if(arrayOfserve != NULL)
			for(i=0; i < serveArraySize; ++i){
				if(arrayOfserve[i] != -1){
					kill(arrayOfserve[i], SIGINT);
					arrayOfserve[i] = -1;
					}
	}
        if (arrayOfserve != NULL) free(arrayOfserve);
        arrayOfserve = NULL;
        if(strcmp(reqArr, "") != 0) remove(REQUEST_FIFO);
        strcpy(reqArr, "");
        if(strcmp(seqArr, "") != 0) remove(SEQUENCE_FIFO);
        strcpy(seqArr, "");

    if (unlink(REQUEST_FIFO) == -1)
        perror("Server failed to unlink request FIFO");
    if (unlink(SEQUENCE_FIFO) == -1)
        perror("Server failed to unlink sequence FIFO");
    return 0;
}
/*Serving client as mini server*/
void serveClient(char* fifoForReq, char* fifoForSeq, pid_t client_id, time_t serverStartTime, char *resolutionOfIntegral) {

	/*Signal handling*/
    act.sa_handler = handlerServerServe;
    act.sa_flags = 0;
    if ((sigemptyset(&act.sa_mask) == -1) ||
            (sigaction(SIGINT, &act, NULL) == -1) ||
            (sigaction(SIGTERM, &act, NULL) == -1) ||
            (sigaction(SIGQUIT, &act, NULL) == -1)) {
        perror("Failed to set SIGINT signal handler");
    }
	/*Opening files*/
    if (((reqfd = open(fifoForReq, O_RDWR)) == -1) ||
            ((seqfd = open(fifoForSeq, O_RDWR)) == -1)) {
        perror("Server failed to open one of the FIFOs");


    }
	/*Reading client again*/
    r_read(reqfd, &client_id, sizeof (client_id));

    /* Initial allocate for file string */
    stringOfFullInfoPtr = (char*) malloc(sizeof (char) * CONTAINER_SIZE + 1);
    stringOfFullInfoPtr[ZERO] = '\0';

    /* Loop for file reading. If size is not enough reallocate executes. */
    while (TRUE) {

        /*  Read while interrupt happens  */
        while ((bytes = read(reqfd, temp, CONTAINER_SIZE)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS && errno == EINTR);


        /* As long as read success, string will grow and string from file will be added to our file string */
        if (bytes > ZERO) {

            temp[bytes + ONE_MORE] = '\0';
            stringOfFullInfoPtr = (char*) realloc(stringOfFullInfoPtr, strlen(stringOfFullInfoPtr) + CONTAINER_SIZE + 1);
            strcat(stringOfFullInfoPtr, temp);

            if (bytes != CONTAINER_SIZE) break;

        } else if (bytes < ZERO) {
            fprintf(stderr, "Problem occured when read from file, inform the developer\n");
            exit(1);
        } else break;




    }
	/*Tokenize the string*/
	/*First expression*/
    stringOfFirstFilePtr = strtok(stringOfFullInfoPtr, "\n");
    tempStrPtr = (char*) malloc(strlen(stringOfFirstFilePtr) * sizeof (char) + 1);
    strcpy(tempStrPtr, stringOfFirstFilePtr);
    stringOfFirstFilePtr = tempStrPtr;
	/*Second expression*/
    tempStrPtr = NULL;
    stringOfSecondFilePtr = strtok(NULL, "\n");
    tempStrPtr = (char*) malloc(strlen(stringOfSecondFilePtr) * sizeof (char) + 1);
    strcpy(tempStrPtr, stringOfSecondFilePtr);
    stringOfSecondFilePtr = tempStrPtr;
	/*Time Interval*/
    tempStrPtr = NULL;
    stringOfIntervalPtr = strtok(NULL, "\n");
    tempStrPtr = (char*) malloc(strlen(stringOfIntervalPtr) * sizeof (char) + 1);
    strcpy(tempStrPtr, stringOfIntervalPtr);
    stringOfIntervalPtr = tempStrPtr;
    time_interval = atoi(stringOfIntervalPtr);
	/*Operation*/
    tempStrPtr = NULL;
    stringOfOperationPtr = strtok(NULL, "\n");
    tempStrPtr = (char*) malloc(strlen(stringOfOperationPtr) * sizeof (char) + 1);
    strcpy(tempStrPtr, stringOfOperationPtr);
    stringOfOperationPtr = tempStrPtr;
    operation = stringOfOperationPtr[0];
    tempStrPtr = NULL;
    
	/*First function correcting for evaluate*/
    for (i = 0; i < strlen(stringOfFirstFilePtr); ++i) {

        if (stringOfFirstFilePtr[i] == 't')
            stringOfFirstFilePtr[i] = 'x';
        


    }
	/*Second function correcting for evaluate*/
    for (i = 0; i < strlen(stringOfSecondFilePtr); ++i) {

        if (stringOfSecondFilePtr[i] == 't')
            stringOfSecondFilePtr[i] = 'x';
       


    }

	/* Second part of the function. Program will evaluate it seperately because if p1 / p2  should be evaluated and p2 == 0 there will be a problem */
    secondPartOfTheFunc = evaluator_create(stringOfSecondFilePtr);
    assert(stringOfSecondFilePtr);
	/* Allocation for all expression */
    allExpressionPtr = (char*) malloc(strlen(stringOfFirstFilePtr) + 1 + strlen(stringOfSecondFilePtr) + 1);
    allExpressionPtr[0] = '\0';
	/*Filling the array with expression*/
    sprintf(allExpressionPtr, "(%s)%s(%s)", stringOfFirstFilePtr, stringOfOperationPtr, stringOfSecondFilePtr);
	
    func = evaluator_create(allExpressionPtr);
    assert(func);
	/*Taking connection and initializing lower limit.*/
    connectionTime = MS_TO_SEC * difftime(time(NULL), serverStartTime);
    lowerLimit = connectionTime;
	/*Resolution evaluating*/
    resolution = atof(resolutionOfIntegral);
	/*Evaluate integral forever and send the result*/
    while (TRUE) {
    	/*Limit handle*/
        upperLimit = lowerLimit + time_interval*MS_TO_SEC;
        /* For every integral calculation, program calculates a time sequence between integral calculation start and end.*/
        beforeOperation = time(NULL);
        /*Integral calculation part*/
        sum1 = 0;
        sum2 = 0;
        stepOfIntegralOfIntegral = (upperLimit - lowerLimit) / resolution;
        for (i = 0; i < stepOfIntegralOfIntegral; i++)
            if (operation != '/' || evaluator_evaluate_x(secondPartOfTheFunc, lowerLimit + resolution * i + resolution / 2.0) != 0)
                sum1 += evaluator_evaluate_x(func, lowerLimit + resolution * i + resolution / 2.0);

        for (i = 1; i < stepOfIntegralOfIntegral; i++)
            if (operation != '/' || evaluator_evaluate_x(secondPartOfTheFunc, lowerLimit + resolution * i) != 0)
                sum2 += evaluator_evaluate_x(func, lowerLimit + resolution * i);

		/*Result calculation*/
        resultOfTheIntegral = resolution / 6.0 * (evaluator_evaluate_x(func, lowerLimit) + evaluator_evaluate_x(func, upperLimit) + 4.0 * sum1 + 2.0 * sum2);
        afterOperation = time(NULL);
        /*For synchronize the interval that we need to calculate integral, program should sleep interval - calculation_time  */
        sleep(time_interval - difftime(afterOperation, beforeOperation));
        /*Calculation result send*/
        r_write(seqfd, &resultOfTheIntegral, sizeof (double));
        /*new lower limit*/
        lowerLimit += time_interval*MS_TO_SEC;
    }
	/*Close and free*/
    if (func != NULL)evaluator_destroy(func);
    func = NULL;
    if (secondPartOfTheFunc != NULL) evaluator_destroy(secondPartOfTheFunc);
    secondPartOfTheFunc = NULL;
    if (stringOfFirstFilePtr != NULL)free(stringOfFirstFilePtr);
    stringOfFirstFilePtr = NULL;
    if (stringOfOperationPtr != NULL)free(stringOfOperationPtr);
    stringOfOperationPtr = NULL;
    if (stringOfSecondFilePtr != NULL)free(stringOfSecondFilePtr);
    stringOfSecondFilePtr = NULL;
    if (stringOfIntervalPtr != NULL)free(stringOfIntervalPtr);
    stringOfIntervalPtr = NULL;





}















