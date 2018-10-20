all: 
	gcc -c server.c  restart.c 
	gcc -o fileShareServer server.o  restart.o -lpthread
	
clean:
	rm -rf *.o fileShareServer 
