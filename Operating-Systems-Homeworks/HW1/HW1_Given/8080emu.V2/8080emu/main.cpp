#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"

int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);

	CPU8080 theCPU;
	GTUOS	theOS;

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	

	do	
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall())
			theOS.handleCall(theCPU);
	}	while (!theCPU.isHalted())
;
	return 0;
}

