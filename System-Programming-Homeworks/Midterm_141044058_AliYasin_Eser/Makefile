all:
	gcc -c Midterm_141044058_AliYasin_Eser_Client.c restart.c  -lmatheval -I/usr/local/include -L/usr/local/lib -Wall
	gcc -o Client Midterm_141044058_AliYasin_Eser_Client.o restart.o -lm -lmatheval
	gcc -c Midterm_141044058_AliYasin_Eser_Server.c restart.c  -lmatheval -I/usr/local/include -L/usr/local/lib -Wall
	gcc -o IntegralGen Midterm_141044058_AliYasin_Eser_Server.o restart.o -lm -lmatheval

clean:
	rm -rf *o IntegralGen Client 
	
wipe: 
	rm -rf *o IntegralGen Client *_sequence.fifo *_request.fifo *.log
