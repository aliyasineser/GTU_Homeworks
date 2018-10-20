/* Program that takes a file name and a key string. 
 * Finds key in the file and creates an output file includes 
 * line and column information of where the key found.*/

/* Written by Ali Yasin Eser, on 6 march 2016*/
/* Student ID:141044058 for Homework 3 */


/* Includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>


/* Macros */

/* FILE MACROS */
#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_APPEND | O_CREAT)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)

/* SIZE AND OPERATION MACROS */
#define CONTAINER_SIZE 1024
#define LOGFILE "gfF.log"
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
#define ARG_TWO 2

/*
 *  Main file,  takes arguments. Arguments are file that program will open and a string for finding this key string in the file.
 * @param argc argument count
 * @param argv argument array, char**
 * @return 0 if successful, otherwise error number
 */
int main(int argc, char *argv[]) {
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
            temp[CONTAINER_SIZE + ONE_MORE] = ""; /* temporary string for reading from file */

    
    
    /*Usage error, user will be warned and program ends*/
    if (argc != NEED_THREE_ARGS) {
        fprintf(stderr, "Usage: %s which_file which_word", argv[ZERO]);
        exit(ERROR_EXIT_CODE);
    }
    /* Target file, should've open. Otherwise, error and exit */
    if ((fileThatWeRead = open(argv[ONE], READ_FLAGS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {
        error = errno;
        fprintf(stderr, "Failed to open file: %s.\n", strerror(errno));
        errno = error;
        exit(ERROR_EXIT_CODE);
    }
    /* Output file, should've open. Otherwise, error and exit */
    if ((fileThatWeWrite = open(LOGFILE, WRITE_FLAGS, WRITE_PERMS)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS) {

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
        while ((bytes = read(fileThatWeRead, temp, CONTAINER_SIZE)) == ERROR_CONTROL_CODE_FOR_FUNCTION_RETURNS && errno == EINTR);


        /* As long as read success, string will grow and string from file will be added to our file string */
        if (bytes > ZERO) {

            temp[bytes + ONE_MORE] = '\0';
            stringOfFullFile = (char*) realloc(stringOfFullFile, strlen(stringOfFullFile) + CONTAINER_SIZE);
            strcat(stringOfFullFile, temp);



        } else if(bytes < ZERO) {

            fprintf(stderr, "Problem occured when read from file, inform the developer\n");

        }
        else break;
    }



    /* Document name added to output file */
    write(fileThatWeWrite, argv[ONE], strlen(argv[ONE]));
    write(fileThatWeWrite, "\n", ONE);

    /* File string will be split into substrings those have the newline character at the end, after that searh begins */
    for (lineString = strtok(stringOfFullFile, "\n");
            lineString != NULL;
            lineString = strtok(NULL, "\n")) {
        ++lineCount;

        /* 	 */
        for (i = START; i < strlen(lineString); ++i) {


            if (lineString[i] == argv[ARG_TWO][START]) {

                /* Array's start from index zero, but files are not. So  i increased columnCount 1 */
                columnCount = i + ONE_MORE;
                /* Found is TRUE first, if any character doesn't match with the key string, then will be assigned FALSE  */
                found = TRUE;
                for (j = START; i + j < strlen(lineString) && j < strlen(argv[ARG_TWO]) && found; ++j) {

                    /* If character does not match, found will be FALSE */
                    if (lineString[i + j] != argv[ARG_TWO][j]) {
                        found = FALSE;
                    }
                }
                /* ıf in the end of the line, there is a half piece of word, then found will be assigned FALSE */
                if (i + strlen(argv[ARG_TWO]) - ONE_LESS >= strlen(lineString)) {

                    found = FALSE;
                }

                /* If all charaters checked and match found, found will be assigned TRUE and informations about word will be written to output file */
                if (found == TRUE) {
                    ++countOfWordFound;
                    sprintf(stringForWritingToFile, "\t%d. found at Line: %d Column: %d\n", countOfWordFound, lineCount, columnCount);
                    write(fileThatWeWrite, stringForWritingToFile, strlen(stringForWritingToFile));


                }
            }
        }

    }
	/*Printing the message to the terminal, prints how many times word found */
	printf("%s found %d times in %s.\n", argv[ARG_TWO], countOfWordFound, argv[ONE]);



    /*Closing files and freeing allocated memory*/
    free(stringOfFullFile);
    close(fileThatWeRead);
    close(fileThatWeWrite);
}

