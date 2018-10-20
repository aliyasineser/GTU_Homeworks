#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"

// This is just a simple OS with no virtual addresses. 
// You will write your own OS .

uint64_t GTUOS::handleCall(const CPU8080 & cpu){
	switch(cpu.state->a){
		case 1:
		std::cout << (int)cpu.state->b << "";
		break;
		case 2:
		std::cout << (int)cpu.memory->at(cpu.state->b*256 + cpu.state->c);
		break;
		case 5:
		std::cout << &cpu.memory->at(cpu.state->b*256 + cpu.state->c);
		break;
		default:
			std::cout <<  "Unimplemented OS call";
	}

	return 0;
}
