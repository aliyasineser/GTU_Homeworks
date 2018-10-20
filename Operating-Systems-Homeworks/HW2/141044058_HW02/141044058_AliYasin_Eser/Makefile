all:
	g++ -c -ansi gtuos.cpp main.cpp 8080emu.cpp memory.cpp
	g++ -o sim8080 gtuos.o main.o 8080emu.o memory.o

clean:
	rm -rf *.o
