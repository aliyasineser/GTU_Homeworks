/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */
 
#ifndef H_8080EMUCPP
#define H_8080EMUCPP

#include <cstdio>
#include <cstring>
#include <cstdlib>

#if defined __UINT32_MAX__ or UINT32_MAX
  #include <inttypes.h>
#else
  typedef unsigned char uint8_t;
  typedef unsigned short uint16_t;
  typedef unsigned long uint32_t;
  typedef unsigned long long uint64_t;
#endif

#include "memoryBase.h"

//#include <sys/time>

//Some code cares that these flags are in exact 
// right bits when.  For instance, some code
// "pops" values into the PSW that they didn't push.
//
typedef struct ConditionCodes {
	uint8_t		cy:1;
	uint8_t		pad:1;
	uint8_t		p:1;
	uint8_t		pad2:1;
	uint8_t		ac:1;
	uint8_t		pad3:1;
	uint8_t		z:1;
	uint8_t		s:1;
} ConditionCodes;

typedef struct State8080 {
	uint8_t		a;
	uint8_t		b;
	uint8_t		c;
	uint8_t		d;
	uint8_t		e;
	uint8_t		h;
	uint8_t		l;
	uint16_t	sp;
	uint16_t	pc;
//	uint8_t		*memory;
	struct ConditionCodes		cc;
	uint8_t		int_enable;

} State8080;



class CPU8080 {
	friend class GTUOS;
public:
        CPU8080(MemoryBase * mem);
		~CPU8080();
        unsigned Emulate8080p(int debug = 0);
        bool isHalted() const;
        bool isSystemCall() const;
	void ReadFileIntoMemoryAt(const char* filename, uint32_t offset);
private:
        State8080 * state;
        MemoryBase * memory;
		unsigned char * lastOpcode;
		void operator=(const CPU8080 & o) {}
		CPU8080(const CPU8080 & o) {}
};

#endif


