/*Includes*/
#include <stdio.h> /* printf and standard I/O */
#include <sys/socket.h> /* socket, connect, socklen_t */
#include <arpa/inet.h> /* sockaddr_in, inet_pton */
#include <string.h> /* strlen */
#include <stdlib.h> /* atoi */
#include <fcntl.h> /* O_WRONLY, O_CREAT */
#include <signal.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h> /* close, write, read */
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <netinet/ip.h> /* superset of previous */
#include "restart.h"


/*MACROS*/
#define MAX_RECV_BUF 256
#define MAX_SEND_BUF 256
#ifndef PATH_MAX
#define PATH_MAX 255
#endif
#ifndef PIPE_BUF
#define PIPE_BUF 4096
#endif
#define WRITE_ERROR -5
#define NO_FILE_ERROR -4

/*Constant variables for communication*/
const char * errmsg_notfound_global = "File not found\n";
const char *listServerMsg = "listServer";
const char *endOfProgramMsg = "exitProgram";
const char *lsClientsMsg = "lsClients";
const char *sendFileMsg = "sendFile";
const char *listLocalMsg = "listLocal";
const char *errorMsg = "No valid command";
const char *helpMsg = "help";

/*Functions*/
int recv_file(int, char*);
void printHelp();
void listServer(int);
void printLocalFiles();
int sendFile(int, char *, int);
void lsClient(int);

int main(int argc, char* argv[]) {
    int sock_fd;
    struct sockaddr_in srv_addr;
    char request[PIPE_BUF] = "";
    char temp[PIPE_BUF] = "";
    char fileNameForSending[PIPE_BUF] = "";
    int toClient = 0;
    /*Usage*/
    if (argc != 3) {
        printf("usage: %s <IP address> [port number]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*CONNECTION PART*/
    memset(&srv_addr, 0, sizeof (srv_addr)); /* zero-fill srv_addr structure*/

    /* create a client socket */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    srv_addr.sin_family = AF_INET; /* internet address family */

    /* convert command line argument to numeric IP */
    if (inet_pton(AF_INET, argv[1], &(srv_addr.sin_addr)) < 1) {
        printf("Invalid IP address\n");
        exit(EXIT_FAILURE);
    }

    /* if port number supplied, use it, otherwise error */
    srv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof (srv_addr)) < 0) {
        perror("connect error");
        exit(EXIT_FAILURE);
    }

    /*CLIENT READY TO BE SERVED*/
    fprintf(stderr, "Connected to: %s:%s\n", argv[1], argv[2]);
    while (1) {
        bzero(request, PIPE_BUF);
        fflush(stdin);
         
        
        
        fprintf(stderr, "What is it you want? If you don't know the commands, just enter \"help\"!\n");
        fgets(request, PIPE_BUF, stdin);
        request[strlen(request) - 1] = '\0';

        if (strcmp(request, listServerMsg) == 0) {
            listServer(sock_fd);
        } else if (strcmp(request, lsClientsMsg) == 0) {
            lsClient(sock_fd);
        } else if (strcmp(request, listLocalMsg) == 0) {
            printLocalFiles();
        } else if (strcmp(request, helpMsg) == 0) {
            printHelp();
        } else if (strncmp(request, sendFileMsg, strlen(sendFileMsg)) == 0) {
            if (sscanf(request, "%s %s %d", temp, fileNameForSending, &toClient) == 3) {

                sendFile(sock_fd, fileNameForSending, toClient);
            } else if (sscanf(request, "%s %s", temp, fileNameForSending) == 2) {

                sendFile(sock_fd, fileNameForSending, -1);
            } else {
                fprintf(stderr, "%s%s%s", "sendFile format error, format should be like:\n",
                        "sendFile <filename>\n", "sendFile <filename> <toClient>\n");
                continue;
            }

        } else if (strcmp(request, endOfProgramMsg) == 0) {
            break;
        } else {
            fprintf(stderr, "%s%s", "Command format error, command doesn't exist!\n",
                    "You can enter \"help\" for commands\n");
            continue;
        }
    }

    write(sock_fd, endOfProgramMsg, strlen(endOfProgramMsg));

    /* close socket*/
    if (close(sock_fd) < 0) {
        perror("socket close error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

/*printing local files*/
void printLocalFiles() {

    char currentDirectoryEntryPath[PATH_MAX];
    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */

    /* Opening directory */
    if ((dirp = opendir(".")) == NULL && errno == ENOTDIR) {
        perror("Directory couldn't be opened.");
        return;

    } else if (errno == ENAMETOOLONG) {
        perror("File name is too long for opening file.");
        return;
    }
    /*Printing every file in the current directory*/
    fprintf(stderr, "Local Files:\n");
    while ((direntp = readdir(dirp)) != NULL) {

        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 ||
                direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;
        getcwd(currentDirectoryEntryPath, PATH_MAX);
        strcat(currentDirectoryEntryPath, "/");
        strcat(currentDirectoryEntryPath, direntp->d_name);

        if (stat(currentDirectoryEntryPath, &statbuf) == -1)
            continue;

        fprintf(stderr, "\t%s\n", direntp->d_name);

    }
    fprintf(stderr, "\n");
}

/*help command*/
void printHelp() {
    fprintf(stderr, "listLocal -> to list the local files\n");
    fprintf(stderr, "listServer -> to list the server's local files\n");
    fprintf(stderr, "lsClients -> lists the clients currently connected to the server with their respective clientids\n");
    fprintf(stderr, "%s%s%s%s\n", "sendFile <filename> <clientid> -> send the file <filename> (if file exists)",
            " from local directory to the client with client id clientid. ", "If no client id is given the file is send to the servers local directory.",
            " If you want to use sendFile your file name should has no space!!!");
    fprintf(stderr, "help -> displays the available comments and their usage\n");
    fprintf(stderr, "exitProgram -> exit from program\n\n");
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

    printf("Client Received: %d bytes in %d recv(s)\n", (int) rcvd_file_size, recv_count);

    return rcvd_file_size;


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

/*listServer command function*/
void listServer(int sockfd) {

    int readBytes = 0, writeBytes = 0;
    char fileNameOfList[PATH_MAX] = "";
    FILE *iptr;
    char tempCharForReading;
    /*request send*/
    writeBytes = write(sockfd, listServerMsg, strlen(listServerMsg));
    if (writeBytes != strlen(listServerMsg))
        exit(1);
    /*reply comes as file, take the name*/
    bzero(fileNameOfList, PATH_MAX);
    get_file_name(sockfd, fileNameOfList);
    if (strcmp(fileNameOfList, errmsg_notfound_global) == 0) {
        fprintf(stderr, "%s", errmsg_notfound_global);
        exit(1);
    }
    /*Take reply file*/
    recv_file(sockfd, fileNameOfList);
    if ((iptr = fopen(fileNameOfList, "r")) == NULL) {
        fprintf(stderr, "Couldn't open the file\n");
        exit(1);
    }
    /*Read and print the reply*/
    fprintf(stderr, "Server Files:\n");
    while (fscanf(iptr, "%c", &tempCharForReading) > 0)
        fprintf(stderr, "%c", tempCharForReading);
    /*Cleaning*/
    fclose(iptr);
    remove(fileNameOfList);

}

/*lsClient command function*/
void lsClient(int sockfd) {

    int readBytes = 0, writeBytes = 0;
    char fileNameOfList[PATH_MAX] = "";
    FILE *iptr;
    char tempCharForReading;

    writeBytes = write(sockfd, lsClientsMsg, strlen(lsClientsMsg));
    if (writeBytes != strlen(lsClientsMsg))
        exit(1);


    get_file_name(sockfd, fileNameOfList);
    if (strcmp(fileNameOfList, errmsg_notfound_global) == 0) {
        fprintf(stderr, "%s", errmsg_notfound_global);
        exit(1);
    }

    recv_file(sockfd, fileNameOfList);

    if ((iptr = fopen(fileNameOfList, "r")) == NULL) {
        fprintf(stderr, "Couldn't open the file\n");
        exit(1);
    }
    fprintf(stderr, "Connected Clients:\n");
    while (fscanf(iptr, "%c", &tempCharForReading) > 0)
        fprintf(stderr, "%c", tempCharForReading);
    fprintf(stderr, "\n");

    /*Cleaning*/
    fclose(iptr);
    remove(fileNameOfList);

}

/*sendFile function for sending the file to server or client*/
int sendFile(int sockfd, char *file_name, int toClient) {

    int readBytes = 0, writeBytes = 0;
    char fileNameOfList[PATH_MAX] = "";
    FILE *iptr;
    int isThere = 0;
    char fileNameForSending[PATH_MAX] = "";
    char communicationMsg[PIPE_BUF] = "";
    char tempCharForReading;
    char currentDirectoryEntryPath[PATH_MAX];
    struct dirent *direntp = NULL; /* Directory entry */
    DIR *dirp = NULL; /* Directory */
    struct stat statbuf; /* For stat function */

    /* Opening directory */
    if ((dirp = opendir(".")) == NULL && errno == ENOTDIR) {
        perror("Directory couldn't be opened.");
        return;

    } else if (errno == ENAMETOOLONG) {
        perror("File name is too long for opening file.");
        return;
    }

    bzero(communicationMsg, PIPE_BUF);
    while ((direntp = readdir(dirp)) != NULL) {
        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0 ||
                direntp->d_name[strlen(direntp->d_name) - 1] == '~')
            continue;
        getcwd(currentDirectoryEntryPath, PATH_MAX);
        strcat(currentDirectoryEntryPath, "/");
        strcat(currentDirectoryEntryPath, direntp->d_name);

        if (stat(currentDirectoryEntryPath, &statbuf) == -1)
            continue;

        if (strcmp(direntp->d_name, file_name) == 0) {
            isThere = 1;
            break;
        }

    }
	closedir(dirp);
    if (isThere == 0) {
        return NO_FILE_ERROR;
    }

    if (toClient < 0) {
        sprintf(communicationMsg, "sendFile %s", file_name);
    } else {
        sprintf(communicationMsg, "sendFile %s %d", file_name, toClient);
    }

    writeBytes = write(sockfd, communicationMsg, strlen(communicationMsg));
    if (writeBytes != strlen(communicationMsg))
        return WRITE_ERROR;

    get_file_name(sockfd, fileNameForSending);
    send_file(sockfd, fileNameForSending);

    return 0;


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

    printf("Done with this client. Sent %d bytes in %d send(s)\n\n",
            (int) sent_file_size, sent_count);
    return sent_count;
}
