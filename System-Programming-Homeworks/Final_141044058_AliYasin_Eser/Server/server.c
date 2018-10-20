/* Program's main specialties(file_send, using fork and tcp communication system) 
 * copied and edited from:
 * https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Course-Notes/07-file_transfer_ex.pdf
 * Edit part is too much. But i took a little bit help from there.
 */
/*Includes*/
#include <stdio.h> /* printf and standard I/O */
#include <sys/socket.h> /* socket, connect, socklen_t */
#include <arpa/inet.h> /* sockaddr_in, inet_pton */
#include <string.h> /* strlen */
#include <stdlib.h> /* atoi */
#include <fcntl.h> /* O_WRONLY, O_CREAT */
#include <signal.h>
#include <dirent.h>
#include <semaphore.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h> /* close, write, read */
#include <sys/stat.h>
#include <netinet/ip.h> /* superset of previous */
#include "restart.h"
#include <strings.h>
#include <sys/wait.h>
#include <time.h>

/* SIZE AND OPERATION MACROS */
#define LISTEN_ENQ 5 /* for listen backlog */
#define MAX_RECV_BUF 256
#define MAX_SEND_BUF 256
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif
#define SEM_NAME "/semaphoreForFinalOfSystemProgramming"
#define CONTAINER_SIZE 1024
#define TRUE 1
#define FALSE 0
#define ZERO 0
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
#define SEM_PERMS (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SEM_FLAGS (O_CREAT)
#define CLIENT_INFO_FILE_NAME "clientFileInformationFile_Final_System_programming.bin"
#define WRITE_ERROR -5
#define NO_FILE_ERROR -4

/*Global variables*/
const char *endOfProgramMsg = "exitProgram";
const char *listServerMsg = "listServer";
const char *sendFileMsg = "sendFile";
pid_t* childrenPidInformationPtr = NULL; /* Children array */
const char *errorMsg = "No valid command";
const char *lsClientsMsg = "lsClients";
sem_t *semForClientInfoFile = NULL; /*Semaphore*/
int listen_fd, conn_fd, counterOfChilds = 0;
int currClientID = 0;

/*Function prototypes*/
int recv_file(int sock, char* file_name);
void get_file_name(int, char*);
int send_file(int, char*);
void sig_chld(int);
void sig_int(int);
void fillWithLocalFiles(FILE *iptr);
void childCommunication(int listen_fd);
void sig_int_child(int signo);

int main(int argc, char* argv[]) {

    struct sockaddr_in srv_addr, cli_addr;
    socklen_t cli_len;
    pid_t child_pid; /* pid of child process */
    char file_name [MAX_RECV_BUF]; /* name of the file to be sent */
    char print_addr [INET_ADDRSTRLEN]; /* readable IP address */
    memset(&srv_addr, 0, sizeof (srv_addr)); /* zero-fill srv_addr structure*/
    memset(&cli_addr, 0, sizeof (cli_addr)); /* zero-fill cli_addr structure*/
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    FILE *clientInfoFilePtr = NULL;

    /*Usage*/
    if (argc != 2) {
        printf("usage: %s [port number]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*CONNECTIONS*/
    /* if port number supplied, use it, otherwise use SRV_PORT */
    srv_addr.sin_port = htons(atoi(argv[1]));

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    /* bind to created socket */
    if (bind(listen_fd, (struct sockaddr*) &srv_addr, sizeof (srv_addr)) < 0) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }


    if (listen(listen_fd, LISTEN_ENQ) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    /*SEMAPHORE FOR CLIENT ID FILE*/
    sem_unlink(SEM_NAME);

    /*Creation of semaphore and error handling*/
    while (((semForClientInfoFile = sem_open(SEM_NAME, SEM_FLAGS, SEM_PERMS, 1)) == SEM_FAILED) &&
            (errno == EINTR));

    if (semForClientInfoFile == SEM_FAILED) {
        perror("Named semaphore error: ");
        return -1;
    }



    /* install signal handler */
    signal(SIGCHLD, sig_chld);
    signal(SIGINT, sig_int);
    /*Initialize the array of childs*/
    counterOfChilds = 0;
    childrenPidInformationPtr = (pid_t*) malloc(counterOfChilds * sizeof (pid_t));

    while (1) /* run forever*/ {
        cli_len = sizeof (cli_addr);
        printf("Waiting for a client to connect...\n\n");
        /* block until some client connects */
        if ((conn_fd = accept(listen_fd, (struct sockaddr*) &cli_addr,
                &cli_len)) < 0) {
            perror("accept error");
            break; /* exit from the for loop */
        }

        /* convert numeric IP to readable format for displaying */
        inet_ntop(AF_INET, &(cli_addr.sin_addr), print_addr, INET_ADDRSTRLEN);
        printf("Client connected from %s:%d\n",
                print_addr, (int) (ntohs(cli_addr.sin_port)));
        /* fork a new child process */
        ++counterOfChilds;
        childrenPidInformationPtr = realloc(childrenPidInformationPtr, counterOfChilds * sizeof (pid_t));
        if ((childrenPidInformationPtr[counterOfChilds - ONE_LESS] = fork()) == 0) /* fork returns 0 for child */ {
            close(listen_fd); /* close child's copy of listen_fd */
            sem_close(semForClientInfoFile);
            if (childrenPidInformationPtr != NULL)
                free(childrenPidInformationPtr);
            childrenPidInformationPtr = NULL;
            currClientID = counterOfChilds;
            childCommunication(conn_fd);

            printf("Closing connection\n");
            /* done */
            close(conn_fd); /* close connected socket*/
            exit(0); /* exit child process */
        }
        close(conn_fd); /* close parent's copy of conn_fd */

        /****************** entry section *******************************/
        while (sem_wait(semForClientInfoFile) == -1)
            if (errno != EINTR) {
                fprintf(stderr, "Thread failed to lock semaphore\n");
                return ZERO;
            }

        if ((clientInfoFilePtr = fopen(CLIENT_INFO_FILE_NAME, "wb")) == NULL) {

            fprintf(stderr, "Couldn't open the client info file\n");
            exit(ERROR_EXIT_CODE);
        }

        fwrite(&counterOfChilds, sizeof (int), 1, clientInfoFilePtr);
        fwrite(childrenPidInformationPtr, sizeof (pid_t), counterOfChilds, clientInfoFilePtr);

        fclose(clientInfoFilePtr);

        /****************** exit section ********************************/
        if (sem_post(semForClientInfoFile) == -1)
            fprintf(stderr, "Thread failed to unlock semaphore\n");



    } /* end for */
    remove(CLIENT_INFO_FILE_NAME);
    sem_close(semForClientInfoFile);
    if (childrenPidInformationPtr != NULL)
        free(childrenPidInformationPtr);
    childrenPidInformationPtr = NULL;
    sem_unlink(SEM_NAME);
    close(listen_fd); /* close listening socket*/
    return 0;
}

/* copied and edited from:
 * https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Course-Notes/07-file_transfer_ex.pdf
 * Edit part is too much. But i took a little bit help from there.
 */
void get_file_name(const int sock, char* file_name) {
    char recv_str[PIPE_BUF]; /* to store received string */
    ssize_t rcvd_bytes; /* bytes received from socket */

    /* read name of requested file from socket */
    if ((rcvd_bytes = recv(sock, recv_str, PIPE_BUF, 0)) < 0) {
        perror("recv error");
        return;
    }
    sscanf(recv_str, "%s\n", file_name); /* discard CR/LF */
}

/* copied and edited from:
 * https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Course-Notes/07-file_transfer_ex.pdf
 * Edit part is too much. But i took a little bit help from there.
 */
int send_file(int sock, char *file_name) {
    int sent_count; /* how many sending chunks, for debugging */
    ssize_t read_bytes, /* bytes read from local file */
            sent_bytes, /* bytes sent to connected socket */
            sent_file_size;
    char send_buf[PIPE_BUF]; /* max chunk size for sending file */
    char * errmsg_notfound = "File not found\n";
    int f; /* file handle for reading local file*/
    sent_count = 0;
    sent_file_size = 0;
    /* attempt to open requested file for reading */
    if ((f = open(file_name, O_RDONLY)) < 0) /* can't open requested file */ {
        perror(file_name);
        if ((sent_bytes = send(sock, errmsg_notfound,
                strlen(errmsg_notfound), 0)) < 0) {
            perror("send error");
            return -1;
        }
    } else /* open file successful */ {
        printf("Sending file: %s\n", file_name);
        while ((read_bytes = read(f, send_buf, MAX_RECV_BUF)) > 0) {
            if ((sent_bytes = send(sock, send_buf, read_bytes, 0))
                    < read_bytes) {
                perror("send error");
                return -1;
            }
            sent_count++;
            sent_file_size += sent_bytes;
        }
        close(f);
    } /* end else */

    /* printf("Done with this client. Sent %d bytes in %d send(s)\n\n",
             (int) sent_file_size, sent_count);*/
    return sent_count;
}

/*server-client communication*/
void childCommunication(int listen_fd) {

    char request[PIPE_BUF] = "";
    char lel[PIPE_BUF] = "";
    int readBytes, writeBytes;
    char fileNameForSending[PATH_MAX] = "";
    int i;
    FILE *inptr = NULL;
    int counterOfChilds = 0;
    FILE *clientInfoFilePtr = NULL;
    char tempFileForOperations[PATH_MAX];
    int read_bytes = 0;
    int srcFD, destFD;
    char recv_str[MAX_RECV_BUF];
    FILE *clientIdFilePtr = NULL;
    int toClient = 0;
    int isThere;
    int whichSendFileSegment = 0;
    char currentDirectoryEntryPath[PATH_MAX];
    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */
    time_t startFunc = time(NULL);
    sigset_t signal_set;
    sigemptyset(&signal_set);

    sigaddset(&signal_set, SIGINT);



    /*Creation of semaphore and error handling*/
    while (((semForClientInfoFile = sem_open(SEM_NAME, SEM_FLAGS, SEM_PERMS, 1)) == SEM_FAILED) &&
            (errno == EINTR));

    if (semForClientInfoFile == SEM_FAILED) {
        perror("Named semaphore error: ");
        return;
    }

    signal(SIGINT, sig_int_child);

    while (1) {

        sigprocmask(SIG_BLOCK, &signal_set, NULL);
        bzero(request, PIPE_BUF);
        if ((readBytes = r_read(listen_fd, request, PIPE_BUF)) < 0) {
            fprintf(stderr, "Read error!\n");
            exit(1);
        } else if (readBytes == 0)
            continue;

        if (strcmp(listServerMsg, request) == 0) {
            fprintf(stderr, "[%f ms] Client %d requested listServer\n",
                    difftime(time(NULL), startFunc), currClientID);
            //write(listen_fd, errorMsg, strlen(errorMsg));
            sprintf(fileNameForSending, "%ld_server.txt", (long) getpid());

            if ((inptr = fopen(fileNameForSending, "w")) == NULL) {
                fprintf(stderr, "Temp file creation error!\n");
                exit(1);
            }
            fillWithLocalFiles(inptr);
            fclose(inptr);
            bzero(lel, PIPE_BUF);


            if ((writeBytes = send(listen_fd, fileNameForSending, strlen(fileNameForSending), 0)) < 0) {
                perror("send error");
                return;
            }
            get_file_name(listen_fd, lel);
            send_file(listen_fd, fileNameForSending);
            remove(fileNameForSending);
        } else if (strcmp(request, endOfProgramMsg) == 0) {
            fprintf(stderr, "[%f ms] Client %d requested end of connection\n",
                    difftime(time(NULL), startFunc), currClientID);
            return;
        } else if (strcmp(request, lsClientsMsg) == 0) {
            fprintf(stderr, "[%f ms] Client %d requested lsClient\n",
                    difftime(time(NULL), startFunc), currClientID);
            //write(listen_fd, errorMsg, strlen(errorMsg));
            /****************** entry section *******************************/
            while (sem_wait(semForClientInfoFile) == -1)
                if (errno != EINTR) {
                    fprintf(stderr, "Thread failed to lock semaphore\n");
                    return;
                }
            if ((clientInfoFilePtr = fopen(CLIENT_INFO_FILE_NAME, "rb")) == NULL) {

                fprintf(stderr, "Couldn't open the client info file\n");
                exit(ERROR_EXIT_CODE);
            }
            fread(&counterOfChilds, sizeof (int), 1, clientInfoFilePtr);
            childrenPidInformationPtr = (pid_t*) calloc(counterOfChilds, sizeof (pid_t));
            fread(childrenPidInformationPtr, sizeof (pid_t), counterOfChilds, clientInfoFilePtr);
            fclose(clientInfoFilePtr);
            /****************** exit section ********************************/
            if (sem_post(semForClientInfoFile) == -1)
                fprintf(stderr, "Thread failed to unlock semaphore\n");

            sprintf(fileNameForSending, "lsClientInfo_%ld.txt", (long) getpid());
            if ((clientIdFilePtr = fopen(fileNameForSending, "w")) == NULL) {

                fprintf(stderr, "Couldn't open the client info file\n");
                exit(ERROR_EXIT_CODE);
            }
            for (i = 0; i < counterOfChilds; ++i) {
                if (childrenPidInformationPtr[i] != -1) {
                    fprintf(clientIdFilePtr, "%d\n", i);
                }
            }
            fclose(clientIdFilePtr);
            if ((writeBytes = send(listen_fd, fileNameForSending, strlen(fileNameForSending), 0)) < 0) {
                perror("send error");
                return;
            }
            get_file_name(listen_fd, lel);
            send_file(listen_fd, fileNameForSending);
            remove(fileNameForSending);
            if (childrenPidInformationPtr != NULL)free(childrenPidInformationPtr);
            childrenPidInformationPtr = NULL;
        } else if (strncmp(request, sendFileMsg, strlen(sendFileMsg)) == 0) {
            fprintf(stderr, "[%f ms] Client %d requested sendFile\n",
                    difftime(time(NULL), startFunc), currClientID);
            //write(listen_fd, errorMsg, strlen(errorMsg));
            if (sscanf(request, "%s %s %d", lel, fileNameForSending, &toClient) == 3) {
                whichSendFileSegment = 3; // 3 parameter valid

            } else if (sscanf(request, "%s %s", lel, fileNameForSending) == 2) {
                whichSendFileSegment = 2;

                /* Opening directory */
                if ((dirp = opendir(".")) == NULL && errno == ENOTDIR) {
                    perror("Directory couldn't be opened.");
                    return;

                } else if (errno == ENAMETOOLONG) {
                    perror("File name is too long for opening file.");
                    return;
                }
                /*Checks is there a file with carries the same name with our file_name*/
                while ((direntp = readdir(dirp)) != NULL) {
                    if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 ||
                            direntp->d_name[strlen(direntp->d_name) - 1] == '~')
                        continue;
                    getcwd(currentDirectoryEntryPath, PATH_MAX);
                    strcat(currentDirectoryEntryPath, "/");
                    strcat(currentDirectoryEntryPath, direntp->d_name);

                    if (stat(currentDirectoryEntryPath, &statbuf) == -1)
                        continue;

                    if (strcmp(direntp->d_name, fileNameForSending) == 0) {
                        isThere = 1;
                        break;
                    }

                }
                closedir(dirp);
                /*If any file in the directory carries the same name with our file_name,
                 * file in the directory copies itself and changes the name.
                 * copy file name starts with time of change.
                 */
                if (isThere == 1) {
                    sprintf(tempFileForOperations, "[%s] %s", ctime(&startFunc), fileNameForSending);
                    if ((srcFD = open(fileNameForSending, O_RDONLY)) < 0) /* can't open requested file */ {
                        perror(fileNameForSending);
                        return;
                    }
                    if ((destFD = open(tempFileForOperations, O_WRONLY | O_CREAT, 0777)) < 0) {
                        perror("error creating file");
                        return;
                    }
                    while ((read_bytes = r_read(srcFD, recv_str, 1)) > 0) {

                        if ((writeBytes = write(destFD, recv_str, 1)) < 0) {
                            perror("error writing to file");
                            return;
                        }
                    }
                    close(destFD);
                    close(srcFD);
                }
                recv_file(listen_fd, fileNameForSending);

            }
        }
        sigprocmask(SIG_UNBLOCK, &signal_set, NULL);
    }

}

/*Fills file with local files*/
void fillWithLocalFiles(FILE *iptr) {

    char currentDirectoryEntryPath[PATH_MAX];
    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */

    if (iptr == NULL)
        return;

    /* Opening directory */
    if ((dirp = opendir(".")) == NULL && errno == ENOTDIR) {
        perror("Directory couldn't be opened.");
        return;

    } else if (errno == ENAMETOOLONG) {
        perror("File name is too long for opening file.");
        return;
    }
    while ((direntp = readdir(dirp)) != NULL) {
        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 ||
                direntp->d_name[strlen(direntp->d_name) - 1] == '~' ||
                strcmp(direntp->d_name, CLIENT_INFO_FILE_NAME) == 0)
            continue;
        getcwd(currentDirectoryEntryPath, PATH_MAX);
        strcat(currentDirectoryEntryPath, "/");
        strcat(currentDirectoryEntryPath, direntp->d_name);

        if (stat(currentDirectoryEntryPath, &statbuf) == -1)
            continue;
        fprintf(iptr, "\t%s\n", direntp->d_name);

    }
    closedir(dirp);
}

/* copied and edited from:
 * https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Course-Notes/07-file_transfer_ex.pdf
 * Edit part is too much. But i took a little bit help from there.
 */
int recv_file(int sock, char* file_name) {
    char send_str [PIPE_BUF]; /* message to be sent to server*/
    int f; /* file handle for receiving file*/
    ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
    int recv_count; /* count of recv() calls*/
    int writeBytes = 0;
    char recv_str[PIPE_BUF]; /* buffer to hold received data */
    size_t send_strlen; /* length of transmitted string */

    sprintf(send_str, "%s\n", file_name); /* add CR/LF (new line) */
    send_strlen = strlen(send_str); /* length of message to be transmitted */
    bzero(recv_str, PIPE_BUF);
    bzero(send_str, PIPE_BUF);
    if ((sent_bytes = send(sock, file_name, send_strlen, 0)) < 0) {
        perror("send error");
        return -1;
    }

    /* attempt to create file to save received data. 0644 = rw-r--r-- */
    if ((f = open(file_name, O_WRONLY | O_CREAT, 0777)) < 0) {
        perror("error creating file");
        return -1;
    }

    recv_count = 0; /* number of recv() calls required to receive the file */
    rcvd_file_size = 0; /* size of received file */
    bzero(recv_str, PIPE_BUF);
    bzero(send_str, PIPE_BUF);
    /* continue receiving until ? (data or close) */
    while ((rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) > 0) {
        recv_count++;
        rcvd_file_size += rcvd_bytes;
        if ((writeBytes = write(f, recv_str, rcvd_bytes)) < 0) {
            perror("error writing to file");
            return -1;
        }
        if (rcvd_bytes < MAX_RECV_BUF)
            break;
        bzero(recv_str, PIPE_BUF);
        bzero(send_str, PIPE_BUF);
    }
    close(f); /* close file*/
    //printf("Client Received: %d bytes in %d recv(s)\n", (int) rcvd_file_size, recv_count);
    return rcvd_file_size;


}

/* define signal hanlder */

/* copied and edited from:
 * https://lms.ksu.edu.sa/bbcswebdav/users/mdahshan/Courses/CEN463/Course-Notes/07-file_transfer_ex.pdf
 * Edit part is too much. But i took a little bit help from there.
 */
void sig_chld(int signo) {
    pid_t pid;
    int stat;
    int i;
    FILE *clientInfoFilePtr;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
        for (i = 0; i < counterOfChilds; ++i) {
            if (childrenPidInformationPtr[i] == pid) {
                childrenPidInformationPtr[i] = -1;
            }
        }
    }

    /****************** entry section *******************************/
    while (sem_wait(semForClientInfoFile) == -1)
        if (errno != EINTR) {
            fprintf(stderr, "Thread failed to lock semaphore\n");
            return;
        }

    if ((clientInfoFilePtr = fopen(CLIENT_INFO_FILE_NAME, "wb")) == NULL) {

        fprintf(stderr, "Couldn't open the client info file\n");
        exit(ERROR_EXIT_CODE);
    }

    fwrite(&counterOfChilds, sizeof (int), 1, clientInfoFilePtr);
    fwrite(childrenPidInformationPtr, sizeof (pid_t), counterOfChilds, clientInfoFilePtr);
    fclose(clientInfoFilePtr);

    /****************** exit section ********************************/
    if (sem_post(semForClientInfoFile) == -1)
        fprintf(stderr, "Thread failed to unlock semaphore\n");

    /* for debugging only, i/o not recommended here */
    return;
}

/* define signal hanlder */
void sig_int(int signo) {
    pid_t pid;
    int stat;
    int i;

    for (i = 0; i < counterOfChilds; ++i) {
        if (childrenPidInformationPtr[i] != -1) {
            kill(SIGINT, childrenPidInformationPtr[i]);
            childrenPidInformationPtr[i] = -1;
        }
    }

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);

    remove(CLIENT_INFO_FILE_NAME);
    free(childrenPidInformationPtr);
    close(conn_fd);

    /* for debugging only, i/o not recommended here */
    exit(1);
}

/* define signal hanlder */
void sig_int_child(int signo) {
    pid_t pid;
    int stat;

    fprintf(stderr, "Mini-server %ld terminated\n", (long) getpid());
    if (childrenPidInformationPtr != NULL)free(childrenPidInformationPtr);
    childrenPidInformationPtr = NULL;
    close(conn_fd);
    sem_close(semForClientInfoFile);
    /* for debugging only, i/o not recommended here */
    exit(1);
}


