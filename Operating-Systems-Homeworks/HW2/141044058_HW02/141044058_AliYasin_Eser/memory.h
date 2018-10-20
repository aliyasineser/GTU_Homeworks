#ifndef H_MEMORY
#define H_MEMORY

#include "memoryBase.h"

class memory: public MemoryBase {
public:
    uint32_t baseRegister;
    uint32_t limitRegister;
    memory();
    ~memory();
    virtual uint8_t & at(uint32_t ind); // Virtual protection
    virtual uint8_t & physicalAt(uint32_t ind); // Direct Ram access
private:
    uint8_t * mem;
    
		
};

#endif


