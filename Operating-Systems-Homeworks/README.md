# 2016-2017_CSE312_Homeworks

HW-1 implementing GTUOS (special Operating System for lecture ) for some System Calls on Intel 8080 processor emulator in C++ 

[Intel 8080] https://en.wikipedia.org/wiki/Intel_8080 

[.asm file to .com file] http://asdasd.rpg.fi/~svo/i8080/ Assemby code should be convert to .com from website

./GTUOS file.com DEBUGMODE

DEBUGMODE : 
0. run the code and show output only 
1. run the code and show output with CPU status 
2. wait for an from the keyboard and it will continue for the next instruction 
All modes prints the number of cycles at the end of execution

System Calls for HW-1

1. PRINT_B : print the value in register B (reg A : 1) (10 cycle ) 
2. PRINT_MEM : print the content of memory pointed registers B and C (reg A : 2) (10 cycle) 
3. READ_B : reads value int keyboard and pust the register B (reg A : 3) (10 cycle) 
4. READ_MEM : reads an int from keyboard and put it pointed memory adress of B an C (regA :4) (10 cycle) 
5. PRINT_STR: print the string pointed by regB and regC ( reg A: 5)(100 cycle) 
6. READ_STR : gets a string from keyboard and puts the memory started at pointed by regB and regC (regA : 6) (100 cycle)
Test Output

System Calls for HW-2


7. FORK : it works like fork() in Unix Systems , It returns result in A. On Success PID of Child process returned in parent and 0 is returned in child , On Failure return 1 for no new process is created. ( RegA : 7 ) ( 50 cycle ) 
8. EXEC : it works similar to Unix execl() system call , It load the asm program and lets the schedular to run (RegA : 8 , BC = adress of the filename) ( 80 cycle ) 
9. WAITPID : Blocks the calling process until the process with PID is terminated ( RegA = 9 RegB = holds the PID ) (80 cycle)

./GTUOS file.com DEBUGMODE

DEBUGMODE : 
3 . Information about each process is printed to screen when a process switch occurs , This information will be very similar to "ps -ef" commmand in Unix systems. It will include the process name and all of the process table entry. 3 1 2

Please examine the ASM files for using Operating System Calls.
