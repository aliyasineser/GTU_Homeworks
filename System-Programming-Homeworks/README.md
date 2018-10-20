# CSE244_Homeworks_2016_Spring

System programming homeworks. 


# HW1
Program that takes a file name and a key string. Finds key in the file and creates an output file includes line and column information of where the key found.
# HW2
Program that takes a directory name and a key string. Finds key in all files in the directory and creates an output file includes line and column information of where the key found. Used child processes to check subdirectory structures and files in the current structures. Information stored as text files and collected by main process. Since main process is a child if it is in inner directory structure, it's information is copied to up directory and handled from there.
# HW3
HW2 with pipe+fifo usage. 

Pipe for:

Directories process <- Child processes for file search

Fifo for:

Directories process <- Child process to handle subdirectories
# HW4
HW3 + using thread for file processing, child process for subdirectory handling. Signals.
# HW5
HW4 but semaphore instead of file. 
# HW6
Message Queues.

# Midterm
Client-Server model. Clients calculate the desired integral value and send to other clients the logs.

# Final
FTP server. Information over IP+Ports. Multiclient feature is supported.
