#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"


uint64_t GTUOS::handleCall(const CPU8080 & cpu){

	// Use for address. Almost all of the calls requirement that 
	// generate address from b and c registers.
	uint16_t address = ((uint16_t)cpu.state->b << 8) | cpu.state->c;

	// Print num
	if(cpu.state->a == (uint8_t)1){
		std::cout << "System Call: PRINT_B" << std::endl;
		std::cout << "Value of B: " << (int)cpu.state->b << std::endl;
		return (uint64_t)10;	
	}
	// Print memory content
	else if(cpu.state->a == (uint8_t)2){
		std::cout << "System Call: PRINT_MEM" << std::endl;
		std::cout << "Content of Memory: " << (int)cpu.memory[address] << std::endl; 
		return (uint64_t)10;	
	}
	// Read an integer. Integer will be casted to 8 bit integer.
	else if(cpu.state->a == (uint8_t)3){
		std::cout << "System Call: READ_B" << std::endl;
		int temp;
		std::cin >> temp;
		cpu.state->b = (uint8_t)temp;
		std::cin.clear();
		return (uint64_t)10;
	}
	// Read memory content
	else if(cpu.state->a == (uint8_t)4){
		std::cout << "System Call: READ_MEM" << std::endl;
		uint8_t num;
		std::cin >> num;
		std::cin.clear();
		cpu.memory[address] = num;
		return (uint64_t)10;
	}
	// Print a string
	else if(cpu.state->a == (uint8_t)5){
		std::cout << "System Call: PRINT_STR" << std::endl;
		for (uint16_t i = address; ; ++i)
		{	
			if(cpu.memory[i] != (uint8_t)0)
				std::cout << (char)cpu.memory[i];
			else
				break;
		}
		std::cout << std::endl;
		return (uint64_t)100;
	}
	// Read a string. String will be read until there will be a whitespace char.
	else if(cpu.state->a == (uint8_t)6){
		std::cout << "System Call: READ_STR" << std::endl;
		std::string str = "";
		std::cin >> str;
		int count;
		uint16_t i;
		for (i = address, count = 0; count < str.length(); ++i, ++count)
		{	
			cpu.memory[i] = str[count];
		}
		cpu.memory[i] = (uint8_t)'\0';
		std::cin.clear();
		return (uint64_t)100;
	}

	// Case of unimplemented call. 
	std::cout <<  "Unimplemented OS call";
	throw -1;
	
	return 0;
}
// Writes memory to file "exe.mem" 
void GTUOS::memToFile(const CPU8080 & cpu){

	FILE *optr;

	optr = fopen("exe.mem" , "w");	 // open

	if(optr == NULL){ // control
		fprintf(stderr, "File couldn't opened to write.\n");
		exit(1);
	}	
	// Write part
	for(uint32_t i=0x0; i < 0x10000; i += 0x00010){
		fprintf(optr, "%.4x:		", i);
		for(uint16_t j = 0x00000; j < 0x00010; ++j){
			fprintf(optr, "%.2x ", cpu.memory[i+j]);
		}
		fprintf(optr, "\n");
	}


	fclose(optr); // close
	return;
}

