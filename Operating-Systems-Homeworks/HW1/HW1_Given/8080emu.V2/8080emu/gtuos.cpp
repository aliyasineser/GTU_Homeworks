#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"

uint64_t GTUOS::handleCall(const CPU8080 & cpu){
	std::cout <<  "Unimplemented OS call";
	throw -1;
	return 0;
}
