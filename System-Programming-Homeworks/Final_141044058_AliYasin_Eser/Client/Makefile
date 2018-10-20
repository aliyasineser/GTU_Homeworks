all: 
	gcc -c  client.c restart.c 
	gcc -o client client.o restart.o -lpthread
	
clean:
	rm -rf *.o client
