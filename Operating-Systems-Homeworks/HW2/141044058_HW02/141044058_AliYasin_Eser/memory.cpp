#include <iostream>
#include "memory.h"

using namespace std;

memory::memory(){
    mem = (uint8_t*) malloc(0x10000);
    baseRegister = 0;
    limitRegister = 0;
}

memory::~memory(){
    free(mem);
}

uint8_t & memory::at(uint32_t ind) {
    //std::cout << "Trying to reach " << baseRegister  + ind << std::endl;
    if(ind < limitRegister) // Protection
        return  mem[baseRegister + ind];
    std::cout << "Segmentation fault , " << baseRegister  + ind << std::endl;
    exit(1);
    
}

uint8_t & memory::physicalAt(uint32_t ind) {
        return mem[ind];
        
}
