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

#include "8080emuCPP.h"

#define PRINTOPS 1

namespace 
{
static int parity(int x, int size)
{
	int i;
	int p = 0;
	x = (x & ((1<<size)-1));
	for (i=0; i<size; i++)
	{
		if (x & 0x1) p++;
		x = x >> 1;
	}
	return (0 == (p & 0x1));
}


unsigned char cycles8080[] = {
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x00..0x0f
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x10..0x1f
	4, 10, 16, 5, 5, 5, 7, 4, 4, 10, 16, 5, 5, 5, 7, 4, //etc
	4, 10, 13, 5, 10, 10, 10, 4, 4, 10, 13, 5, 5, 5, 7, 4,
	
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5, //0x40..0x4f
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,
	
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4, //0x80..8x4f
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, //0xc0..0xcf
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, 
	11, 10, 10, 18, 17, 11, 7, 11, 11, 5, 10, 5, 17, 17, 7, 11, 
	11, 10, 10, 4, 17, 11, 7, 11, 11, 5, 10, 4, 17, 17, 7, 11, 
};

int Disassemble8080Op(unsigned char *codebuffer, int pc)
{
	unsigned char *code = &codebuffer[pc];
	char buf[50];
	int opbytes = 1;
	printf("%04x ", pc);
	switch (*code)
	{
		case 0x00: sprintf(buf, "NOP"); break;
		case 0x01: sprintf(buf, "LXI    B,#$%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x02: sprintf(buf, "STAX   B"); break;
		case 0x03: sprintf(buf, "INX    B"); break;
		case 0x04: sprintf(buf, "INR    B"); break;
		case 0x05: sprintf(buf, "DCR    B"); break;
		case 0x06: sprintf(buf, "MVI    B,#$%02x", code[1]); opbytes=2; break;
		case 0x07: sprintf(buf, "RLC"); break;
		case 0x08: sprintf(buf, "NOP"); break;
		case 0x09: sprintf(buf, "DAD    B"); break;
		case 0x0a: sprintf(buf, "LDAX   B"); break;
		case 0x0b: sprintf(buf, "DCX    B"); break;
		case 0x0c: sprintf(buf, "INR    C"); break;
		case 0x0d: sprintf(buf, "DCR    C"); break;
		case 0x0e: sprintf(buf, "MVI    C,#$%02x", code[1]); opbytes = 2;	break;
		case 0x0f: sprintf(buf, "RRC"); break;
			
		case 0x10: sprintf(buf, "NOP"); break;
		case 0x11: sprintf(buf, "LXI    D,#$%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x12: sprintf(buf, "STAX   D"); break;
		case 0x13: sprintf(buf, "INX    D"); break;
		case 0x14: sprintf(buf, "INR    D"); break;
		case 0x15: sprintf(buf, "DCR    D"); break;
		case 0x16: sprintf(buf, "MVI    D,#$%02x", code[1]); opbytes=2; break;
		case 0x17: sprintf(buf, "RAL"); break;
		case 0x18: sprintf(buf, "NOP"); break;
		case 0x19: sprintf(buf, "DAD    D"); break;
		case 0x1a: sprintf(buf, "LDAX   D"); break;
		case 0x1b: sprintf(buf, "DCX    D"); break;
		case 0x1c: sprintf(buf, "INR    E"); break;
		case 0x1d: sprintf(buf, "DCR    E"); break;
		case 0x1e: sprintf(buf, "MVI    E,#$%02x", code[1]); opbytes = 2; break;
		case 0x1f: sprintf(buf, "RAR"); break;
			
		case 0x20: sprintf(buf, "NOP"); break;
		case 0x21: sprintf(buf, "LXI    H,#$%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x22: sprintf(buf, "SHLD   $%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x23: sprintf(buf, "INX    H"); break;
		case 0x24: sprintf(buf, "INR    H"); break;
		case 0x25: sprintf(buf, "DCR    H"); break;
		case 0x26: sprintf(buf, "MVI    H,#$%02x", code[1]); opbytes=2; break;
		case 0x27: sprintf(buf, "DAA"); break;
		case 0x28: sprintf(buf, "NOP"); break;
		case 0x29: sprintf(buf, "DAD    H"); break;
		case 0x2a: sprintf(buf, "LHLD   $%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x2b: sprintf(buf, "DCX    H"); break;
		case 0x2c: sprintf(buf, "INR    L"); break;
		case 0x2d: sprintf(buf, "DCR    L"); break;
		case 0x2e: sprintf(buf, "MVI    L,#$%02x", code[1]); opbytes = 2; break;
		case 0x2f: sprintf(buf, "CMA"); break;
			
		case 0x30: sprintf(buf, "NOP"); break;
		case 0x31: sprintf(buf, "LXI    SP,#$%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x32: sprintf(buf, "STA    $%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x33: sprintf(buf, "INX    SP"); break;
		case 0x34: sprintf(buf, "INR    M"); break;
		case 0x35: sprintf(buf, "DCR    M"); break;
		case 0x36: sprintf(buf, "MVI    M,#$%02x", code[1]); opbytes=2; break;
		case 0x37: sprintf(buf, "STC"); break;
		case 0x38: sprintf(buf, "NOP"); break;
		case 0x39: sprintf(buf, "DAD    SP"); break;
		case 0x3a: sprintf(buf, "LDA    $%02x%02x", code[2], code[1]); opbytes=3; break;
		case 0x3b: sprintf(buf, "DCX    SP"); break;
		case 0x3c: sprintf(buf, "INR    A"); break;
		case 0x3d: sprintf(buf, "DCR    A"); break;
		case 0x3e: sprintf(buf, "MVI    A,#$%02x", code[1]); opbytes = 2; break;
		case 0x3f: sprintf(buf, "CMC"); break;
			
		case 0x40: sprintf(buf, "MOV    B,B"); break;
		case 0x41: sprintf(buf, "MOV    B,C"); break;
		case 0x42: sprintf(buf, "MOV    B,D"); break;
		case 0x43: sprintf(buf, "MOV    B,E"); break;
		case 0x44: sprintf(buf, "MOV    B,H"); break;
		case 0x45: sprintf(buf, "MOV    B,L"); break;
		case 0x46: sprintf(buf, "MOV    B,M"); break;
		case 0x47: sprintf(buf, "MOV    B,A"); break;
		case 0x48: sprintf(buf, "MOV    C,B"); break;
		case 0x49: sprintf(buf, "MOV    C,C"); break;
		case 0x4a: sprintf(buf, "MOV    C,D"); break;
		case 0x4b: sprintf(buf, "MOV    C,E"); break;
		case 0x4c: sprintf(buf, "MOV    C,H"); break;
		case 0x4d: sprintf(buf, "MOV    C,L"); break;
		case 0x4e: sprintf(buf, "MOV    C,M"); break;
		case 0x4f: sprintf(buf, "MOV    C,A"); break;
			
		case 0x50: sprintf(buf, "MOV    D,B"); break;
		case 0x51: sprintf(buf, "MOV    D,C"); break;
		case 0x52: sprintf(buf, "MOV    D,D"); break;
		case 0x53: sprintf(buf, "MOV    D.E"); break;
		case 0x54: sprintf(buf, "MOV    D,H"); break;
		case 0x55: sprintf(buf, "MOV    D,L"); break;
		case 0x56: sprintf(buf, "MOV    D,M"); break;
		case 0x57: sprintf(buf, "MOV    D,A"); break;
		case 0x58: sprintf(buf, "MOV    E,B"); break;
		case 0x59: sprintf(buf, "MOV    E,C"); break;
		case 0x5a: sprintf(buf, "MOV    E,D"); break;
		case 0x5b: sprintf(buf, "MOV    E,E"); break;
		case 0x5c: sprintf(buf, "MOV    E,H"); break;
		case 0x5d: sprintf(buf, "MOV    E,L"); break;
		case 0x5e: sprintf(buf, "MOV    E,M"); break;
		case 0x5f: sprintf(buf, "MOV    E,A"); break;
            
		case 0x60: sprintf(buf, "MOV    H,B"); break;
		case 0x61: sprintf(buf, "MOV    H,C"); break;
		case 0x62: sprintf(buf, "MOV    H,D"); break;
		case 0x63: sprintf(buf, "MOV    H.E"); break;
		case 0x64: sprintf(buf, "MOV    H,H"); break;
		case 0x65: sprintf(buf, "MOV    H,L"); break;
		case 0x66: sprintf(buf, "MOV    H,M"); break;
		case 0x67: sprintf(buf, "MOV    H,A"); break;
		case 0x68: sprintf(buf, "MOV    L,B"); break;
		case 0x69: sprintf(buf, "MOV    L,C"); break;
		case 0x6a: sprintf(buf, "MOV    L,D"); break;
		case 0x6b: sprintf(buf, "MOV    L,E"); break;
		case 0x6c: sprintf(buf, "MOV    L,H"); break;
		case 0x6d: sprintf(buf, "MOV    L,L"); break;
		case 0x6e: sprintf(buf, "MOV    L,M"); break;
		case 0x6f: sprintf(buf, "MOV    L,A"); break;
            
		case 0x70: sprintf(buf, "MOV    M,B"); break;
		case 0x71: sprintf(buf, "MOV    M,C"); break;
		case 0x72: sprintf(buf, "MOV    M,D"); break;
		case 0x73: sprintf(buf, "MOV    M.E"); break;
		case 0x74: sprintf(buf, "MOV    M,H"); break;
		case 0x75: sprintf(buf, "MOV    M,L"); break;
		case 0x76: sprintf(buf, "HLT");        break;
		case 0x77: sprintf(buf, "MOV    M,A"); break;
		case 0x78: sprintf(buf, "MOV    A,B"); break;
		case 0x79: sprintf(buf, "MOV    A,C"); break;
		case 0x7a: sprintf(buf, "MOV    A,D"); break;
		case 0x7b: sprintf(buf, "MOV    A,E"); break;
		case 0x7c: sprintf(buf, "MOV    A,H"); break;
		case 0x7d: sprintf(buf, "MOV    A,L"); break;
		case 0x7e: sprintf(buf, "MOV    A,M"); break;
		case 0x7f: sprintf(buf, "MOV    A,A"); break;
            
		case 0x80: sprintf(buf, "ADD    B"); break;
		case 0x81: sprintf(buf, "ADD    C"); break;
		case 0x82: sprintf(buf, "ADD    D"); break;
		case 0x83: sprintf(buf, "ADD    E"); break;
		case 0x84: sprintf(buf, "ADD    H"); break;
		case 0x85: sprintf(buf, "ADD    L"); break;
		case 0x86: sprintf(buf, "ADD    M"); break;
		case 0x87: sprintf(buf, "ADD    A"); break;
		case 0x88: sprintf(buf, "ADC    B"); break;
		case 0x89: sprintf(buf, "ADC    C"); break;
		case 0x8a: sprintf(buf, "ADC    D"); break;
		case 0x8b: sprintf(buf, "ADC    E"); break;
		case 0x8c: sprintf(buf, "ADC    H"); break;
		case 0x8d: sprintf(buf, "ADC    L"); break;
		case 0x8e: sprintf(buf, "ADC    M"); break;
		case 0x8f: sprintf(buf, "ADC    A"); break;
            
		case 0x90: sprintf(buf, "SUB    B"); break;
		case 0x91: sprintf(buf, "SUB    C"); break;
		case 0x92: sprintf(buf, "SUB    D"); break;
		case 0x93: sprintf(buf, "SUB    E"); break;
		case 0x94: sprintf(buf, "SUB    H"); break;
		case 0x95: sprintf(buf, "SUB    L"); break;
		case 0x96: sprintf(buf, "SUB    M"); break;
		case 0x97: sprintf(buf, "SUB    A"); break;
		case 0x98: sprintf(buf, "SBB    B"); break;
		case 0x99: sprintf(buf, "SBB    C"); break;
		case 0x9a: sprintf(buf, "SBB    D"); break;
		case 0x9b: sprintf(buf, "SBB    E"); break;
		case 0x9c: sprintf(buf, "SBB    H"); break;
		case 0x9d: sprintf(buf, "SBB    L"); break;
		case 0x9e: sprintf(buf, "SBB    M"); break;
		case 0x9f: sprintf(buf, "SBB    A"); break;
            
		case 0xa0: sprintf(buf, "ANA    B"); break;
		case 0xa1: sprintf(buf, "ANA    C"); break;
		case 0xa2: sprintf(buf, "ANA    D"); break;
		case 0xa3: sprintf(buf, "ANA    E"); break;
		case 0xa4: sprintf(buf, "ANA    H"); break;
		case 0xa5: sprintf(buf, "ANA    L"); break;
		case 0xa6: sprintf(buf, "ANA    M"); break;
		case 0xa7: sprintf(buf, "ANA    A"); break;
		case 0xa8: sprintf(buf, "XRA    B"); break;
		case 0xa9: sprintf(buf, "XRA    C"); break;
		case 0xaa: sprintf(buf, "XRA    D"); break;
		case 0xab: sprintf(buf, "XRA    E"); break;
		case 0xac: sprintf(buf, "XRA    H"); break;
		case 0xad: sprintf(buf, "XRA    L"); break;
		case 0xae: sprintf(buf, "XRA    M"); break;
		case 0xaf: sprintf(buf, "XRA    A"); break;
            
		case 0xb0: sprintf(buf, "ORA    B"); break;
		case 0xb1: sprintf(buf, "ORA    C"); break;
		case 0xb2: sprintf(buf, "ORA    D"); break;
		case 0xb3: sprintf(buf, "ORA    E"); break;
		case 0xb4: sprintf(buf, "ORA    H"); break;
		case 0xb5: sprintf(buf, "ORA    L"); break;
		case 0xb6: sprintf(buf, "ORA    M"); break;
		case 0xb7: sprintf(buf, "ORA    A"); break;
		case 0xb8: sprintf(buf, "CMP    B"); break;
		case 0xb9: sprintf(buf, "CMP    C"); break;
		case 0xba: sprintf(buf, "CMP    D"); break;
		case 0xbb: sprintf(buf, "CMP    E"); break;
		case 0xbc: sprintf(buf, "CMP    H"); break;
		case 0xbd: sprintf(buf, "CMP    L"); break;
		case 0xbe: sprintf(buf, "CMP    M"); break;
		case 0xbf: sprintf(buf, "CMP    A"); break;
            
		case 0xc0: sprintf(buf, "RNZ"); break;
		case 0xc1: sprintf(buf, "POP    B"); break;
		case 0xc2: sprintf(buf, "JNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xc3: sprintf(buf, "JMP    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xc4: sprintf(buf, "CNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xc5: sprintf(buf, "PUSH   B"); break;
		case 0xc6: sprintf(buf, "ADI    #$%02x",code[1]); opbytes = 2; break;
		case 0xc7: sprintf(buf, "RST    0"); break;
		case 0xc8: sprintf(buf, "RZ"); break;
		case 0xc9: sprintf(buf, "RET"); break;
		case 0xca: sprintf(buf, "JZ     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xcb: sprintf(buf, "JMP    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xcc: sprintf(buf, "CZ     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xcd: sprintf(buf, "CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xce: sprintf(buf, "ACI    #$%02x",code[1]); opbytes = 2; break;
		case 0xcf: sprintf(buf, "RST    1"); break;
            
		case 0xd0: sprintf(buf, "RNC"); break;
		case 0xd1: sprintf(buf, "POP    D"); break;
		case 0xd2: sprintf(buf, "JNC    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xd3: sprintf(buf, "OUT    #$%02x",code[1]); opbytes = 2; break;
		case 0xd4: sprintf(buf, "CNC    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xd5: sprintf(buf, "PUSH   D"); break;
		case 0xd6: sprintf(buf, "SUI    #$%02x",code[1]); opbytes = 2; break;
		case 0xd7: sprintf(buf, "RST    2"); break;
		case 0xd8: sprintf(buf, "RC");  break;
		case 0xd9: sprintf(buf, "RET"); break;
		case 0xda: sprintf(buf, "JC     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xdb: sprintf(buf, "IN     #$%02x",code[1]); opbytes = 2; break;
		case 0xdc: sprintf(buf, "CC     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xdd: sprintf(buf, "CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xde: sprintf(buf, "SBI    #$%02x",code[1]); opbytes = 2; break;
		case 0xdf: sprintf(buf, "RST    3"); break;
            
		case 0xe0: sprintf(buf, "RPO"); break;
		case 0xe1: sprintf(buf, "POP    H"); break;
		case 0xe2: sprintf(buf, "JPO    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xe3: sprintf(buf, "XTHL");break;
		case 0xe4: sprintf(buf, "CPO    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xe5: sprintf(buf, "PUSH   H"); break;
		case 0xe6: sprintf(buf, "ANI    #$%02x",code[1]); opbytes = 2; break;
		case 0xe7: sprintf(buf, "RST    4"); break;
		case 0xe8: sprintf(buf, "RPE"); break;
		case 0xe9: sprintf(buf, "PCHL");break;
		case 0xea: sprintf(buf, "JPE    $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xeb: sprintf(buf, "XCHG"); break;
		case 0xec: sprintf(buf, "CPE     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xed: sprintf(buf, "CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xee: sprintf(buf, "XRI    #$%02x",code[1]); opbytes = 2; break;
		case 0xef: sprintf(buf, "RST    5"); break;
            
		case 0xf0: sprintf(buf, "RP");  break;
		case 0xf1: sprintf(buf, "POP    PSW"); break;
		case 0xf2: sprintf(buf, "JP     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xf3: sprintf(buf, "DI");  break;
		case 0xf4: sprintf(buf, "CP     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xf5: sprintf(buf, "PUSH   PSW"); break;
		case 0xf6: sprintf(buf, "ORI    #$%02x",code[1]); opbytes = 2; break;
		case 0xf7: sprintf(buf, "RST    6"); break;
		case 0xf8: sprintf(buf, "RM");  break;
		case 0xf9: sprintf(buf, "SPHL");break;
		case 0xfa: sprintf(buf, "JM     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xfb: sprintf(buf, "EI");  break;
		case 0xfc: sprintf(buf, "CM     $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xfd: sprintf(buf, "CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break;
		case 0xfe: sprintf(buf, "CPI    #$%02x",code[1]); opbytes = 2; break;
		case 0xff: sprintf(buf, "RST    7"); break;
	}
	printf("%-15s", buf);
	
	return opbytes;
}

void LogicFlagsA(State8080 *state)
{
	state->cc.cy = state->cc.ac = 0;
	state->cc.z = (state->a == 0);
	state->cc.s = (0x80 == (state->a & 0x80));
	state->cc.p = parity(state->a, 8);
}

void ArithFlagsA(State8080 *state, uint16_t res)
{
	state->cc.cy = (res > 0xff);
	state->cc.z = ((res&0xff) == 0);
	state->cc.s = (0x80 == (res & 0x80));
	state->cc.p = parity(res&0xff, 8);
}

void UnimplementedInstruction(uint8_t * memory, State8080* state)
{
	//pc will have advanced one, so undo that
	printf ("Error: Unimplemented instruction\n");
	state->pc--;
	Disassemble8080Op(memory, state->pc);
	printf("\n");
	exit(1);
}

void WriteMem(uint8_t * mem, uint16_t address, uint8_t value)
{
        mem[address] = value;
}

uint8_t ReadFromHL(uint8_t * memory, State8080* state)
{ 
    uint16_t offset = (state->h << 8) | state->l;
    return memory[offset];
}

void WriteToHL(uint8_t * memory, State8080* state, uint8_t value)
{
    uint16_t offset = (state->h << 8) | state->l;
    WriteMem(memory, offset, value);
}

void Push(uint8_t * memory, State8080* state, uint8_t high, uint8_t low)
{
    WriteMem(memory, state->sp-1, high);
    WriteMem(memory, state->sp-2, low);
    state->sp = state->sp - 2;    
    //    printf ("%04x %04x\n", state->pc, state->sp);
}

void Pop(uint8_t * memory, State8080* state, uint8_t *high, uint8_t *low)
{
    *low = memory[state->sp];
    *high = memory[state->sp+1];
    state->sp += 2;    
    //    printf ("%04x %04x pop\n", state->pc, state->sp);
}

void FlagsZSP(State8080 *state, uint8_t value)
{
    state->cc.z = (value == 0);
    state->cc.s = (0x80 == (value & 0x80));
    state->cc.p = parity(value, 8);    
}
} // End of unnamed namespace


unsigned CPU8080::Emulate8080p(int debug)
{
	lastOpcode = &memory[state->pc];
    
	if(debug != 0)
		Disassemble8080Op(memory, state->pc);


	state->pc+=1;    
    
	switch (*lastOpcode)
	{
		case 0x00: break;	//NOP
		case 0x01: 							//LXI	B,word
			state->c = lastOpcode[1];
			state->b = lastOpcode[2];
			state->pc += 2;
			break;
		case 0x02: 							//STAX B
        {
            uint16_t offset=(state->b<<8) | state->c;
            WriteMem(memory, offset, state->a);
        }
			break;
		case 0x03: 							//INX    B
			state->c++;
			if (state->c == 0)
				state->b++;
			break;
		case 0x04: 							//INR	B
            state->b += 1;
            FlagsZSP(state,state->b);
			break;		
		case 0x05: 							//DCR    B
			state->b -= 1;
            FlagsZSP(state,state->b);
			break;
		case 0x06: 							//MVI B,byte
			state->b = lastOpcode[1];
			state->pc++;
			break;
		case 0x07: 							//RLC
        {
            uint8_t x = state->a;
            state->a = ((x & 0x80) >> 7) | (x << 1);
            state->cc.cy = (0x80 == (x&0x80));
        }
			break;
		case 0x08: UnimplementedInstruction(memory, state); break;
		case 0x09: 							//DAD B
        {
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t bc = (state->b << 8) | state->c;
			uint32_t res = hl + bc;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
        }
			break;
		case 0x0a: 							//LDAX   B
        {
			uint16_t offset=(state->b<<8) | state->c;
			state->a = memory[offset];
        }
			break;
		case 0x0b:							//DCX B 
			state->c -= 1;
			if (state->c==0xff)
				state->b-=1;
			break;
		case 0x0c:                          //INR C
            state->c += 1;
            FlagsZSP(state,state->c);
			break;		
            
		case 0x0d: 							//DCR C
            state->c -= 1;
            FlagsZSP(state,state->c);
			break;
		case 0x0e: 							//MVI C,byte
			state->c = lastOpcode[1];
			state->pc++;
			break;
		case 0x0f: 							//RRC
        {
            uint8_t x = state->a;
            state->a = ((x & 1) << 7) | (x >> 1);
            state->cc.cy = (1 == (x&1));
        }
			break;
			
		case 0x10: UnimplementedInstruction(memory, state); break;
		case 0x11: 							//LXI	D,word
			state->e = lastOpcode[1];
			state->d = lastOpcode[2];
			state->pc += 2;
			break;
		case 0x12: 							//STAX D
        {
            uint16_t offset=(state->d<<8) | state->e;
            WriteMem(memory, offset, state->a);
        }
			break;
		case 0x13: 							//INX    D
			state->e++;
			if (state->e == 0)
				state->d++;
			break;		
		case 0x14: 							//INR D
            state->d += 1;
            FlagsZSP(state,state->d);
			break;		
		case 0x15: 							//DCR    D
            state->d -= 1;
            FlagsZSP(state,state->d);
			break;
		case 0x16: 							//MVI D,byte
			state->d = lastOpcode[1];
			state->pc++;
			break;
		case 0x17:                           //RAL
        {
            uint8_t x = state->a;
            state->a = state->cc.cy  | (x << 1);
            state->cc.cy = (0x80 == (x&0x80));
        }
			break;			
		case 0x18: UnimplementedInstruction(memory, state); break;
		case 0x19: 							//DAD    D
        {
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t de = (state->d << 8) | state->e;
			uint32_t res = hl + de;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
        }
			break;
		case 0x1a: 							//LDAX	D
        {
			uint16_t offset=(state->d<<8) | state->e;
			state->a = memory[offset];
        }
			break;
		case 0x1b: 							//DCX D
			state->e -= 1;
			if (state->e==0xff)
				state->d-=1;
			break;
		case 0x1c:							//INR E
            state->e += 1;
            FlagsZSP(state,state->e);
			break;		
            
		case 0x1d: 							//DCR    E
            state->e -= 1;
            FlagsZSP(state,state->e);
			break;
		case 0x1e: 							//MVI E,byte
			state->e = lastOpcode[1];
			state->pc++;
			break;
		case 0x1f:                           //RAR
        {
            uint8_t x = state->a;
            state->a = (state->cc.cy << 7) | (x >> 1);
            state->cc.cy = (1 == (x&1));
        }
			break;			
		case 0x20: UnimplementedInstruction(memory, state); break;
		case 0x21: 							//LXI	H,word
			state->l = lastOpcode[1];
			state->h = lastOpcode[2];
			state->pc += 2;
			break;
		case 0x22: 							//SHLD
        {
            uint16_t offset = lastOpcode[1] | (lastOpcode[2] << 8);
            WriteMem(memory, offset, state->l);
            WriteMem(memory, offset+1, state->h);
            state->pc += 2;
        }
			break;
		case 0x23: 							//INX    H
			state->l++;
			if (state->l == 0)
				state->h++;
			break;		
		case 0x24:							//INR	H 
            state->h += 1;
            FlagsZSP(state,state->h);
			break;		
		case 0x25: 							//DCR    H
            state->h -= 1;
            FlagsZSP(state,state->h);
			break;
		case 0x26:  							//MVI H,byte
			state->h = lastOpcode[1];
			state->pc++;
			break;
		case 0x27: 
            if ((state->a &0xf) > 9)
                state->a += 6;
            if ((state->a&0xf0) > 0x90)
            {
                uint16_t res = (uint16_t) state->a + 0x60;
                state->a = res & 0xff;
                ArithFlagsA(state, res);
            }
            break;
		case 0x28: UnimplementedInstruction(memory, state); break;
		case 0x29: 								//DAD    H
        {
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t res = hl + hl;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) != 0);
        }
			break;
		case 0x2a: 								//LHLD adr
        {
            uint16_t offset = lastOpcode[1] | (lastOpcode[2] << 8);
            state->l = memory[offset];
            state->h = memory[offset+1];
            state->pc += 2;
        }
			break;
		case 0x2b: 								//DCX H
			state->l -= 1;
			if (state->l==0xff)
				state->h-=1;
			break;		
		case 0x2c:								//INR L
            state->l += 1;
            FlagsZSP(state,state->l);
			break;		
		case 0x2d: 							//DCR    L
            state->l -= 1;
            FlagsZSP(state,state->l);
			break;
		case 0x2e:  						//MVI L,byte
			state->l = lastOpcode[1];
			state->pc++;
			break;
		case 0x2f:
			state->a = ~state->a;			//CMA 
			break;
		case 0x30: UnimplementedInstruction(memory, state); break;
		case 0x31: 							//LXI	SP,word
			state->sp = (lastOpcode[2]<<8) | lastOpcode[1];
			state->pc += 2;
			break;
		case 0x32: 							//STA    (word)
        {
			uint16_t offset = (lastOpcode[2]<<8) | (lastOpcode[1]);
            WriteMem(memory, offset, state->a);
			state->pc += 2;
        }
			break;
		case 0x33: 							//INX    SP
			state->sp++;
			break;		
		case 0x34: 							//INR	M
        {
			uint8_t res = ReadFromHL(memory, state) + 1;
            FlagsZSP(state, res);
            WriteToHL(memory, state, res);
        }
			break;			
		case 0x35: 							//DCR    M
        {
			uint8_t res = ReadFromHL(memory, state) - 1;
            FlagsZSP(state, res);
            WriteToHL(memory, state, res);
        }
			break;			
		case 0x36: 							//MVI	M,byte
        {					
            WriteToHL(memory, state, lastOpcode[1]);
			state->pc++;
        }
			break;
		case 0x37: state->cc.cy = 1; break;
		case 0x38: UnimplementedInstruction(memory, state); break;
		case 0x39: 							//DAD    SP
        {
			uint32_t hl = (state->h << 8) | state->l;
			uint32_t res = hl + state->sp;
			state->h = (res & 0xff00) >> 8;
			state->l = res & 0xff;
			state->cc.cy = ((res & 0xffff0000) > 0);
        }
			break;
		case 0x3a: 							//LDA    (word)
        {
			uint16_t offset = (lastOpcode[2]<<8) | (lastOpcode[1]);
			state->a = memory[offset];
			state->pc+=2;
        }
			break;
		case 0x3b: 							//DCX SP
			state->sp -= 1;
			break;
		case 0x3c: 							//INR A
            state->a += 1;
            FlagsZSP(state,state->a);
			break;		
		case 0x3d:							//DCR A
            state->a -= 1;
            FlagsZSP(state,state->a);
			break;
		case 0x3e: 							//MVI    A,byte
			state->a = lastOpcode[1];
			state->pc++;
			break;
		case 0x3f: state->cc.cy = 0; break;
			
		case 0x40: state->b = state->b; break;
		case 0x41: state->b = state->c; break;
		case 0x42: state->b = state->d; break;
		case 0x43: state->b = state->e; break;
		case 0x44: state->b = state->h; break;
		case 0x45: state->b = state->l; break;
		case 0x46: state->b = ReadFromHL(memory, state); break;
		case 0x47: state->b = state->a; break;
            
		case 0x48: state->c = state->b; break;
		case 0x49: state->c = state->c; break;
		case 0x4a: state->c = state->d; break;
		case 0x4b: state->c = state->e; break;
		case 0x4c: state->c = state->h; break;
		case 0x4d: state->c = state->l; break;
		case 0x4e: state->c = ReadFromHL(memory, state); break;
		case 0x4f: state->c = state->a; break;
			
		case 0x50: state->d = state->b; break;
		case 0x51: state->d = state->c; break;
		case 0x52: state->d = state->d; break;
		case 0x53: state->d = state->e; break;
		case 0x54: state->d = state->h; break;
		case 0x55: state->d = state->l; break;
		case 0x56: state->d = ReadFromHL(memory, state); break;
		case 0x57: state->d = state->a; break;
            
		case 0x58: state->e = state->b; break;
		case 0x59: state->e = state->c; break;
		case 0x5a: state->e = state->d; break;
		case 0x5b: state->e = state->e; break;
		case 0x5c: state->e = state->h; break;
		case 0x5d: state->e = state->l; break;
		case 0x5e: state->e = ReadFromHL(memory, state); break;
		case 0x5f: state->e = state->a; break;
            
		case 0x60: state->h = state->b; break;
		case 0x61: state->h = state->c; break;
		case 0x62: state->h = state->d; break;
		case 0x63: state->h = state->e; break;
		case 0x64: state->h = state->h; break;
		case 0x65: state->h = state->l; break;
		case 0x66: state->h = ReadFromHL(memory, state); break;
		case 0x67: state->h = state->a; break;
            
		case 0x68: state->l = state->b; break;
		case 0x69: state->l = state->c; break;
		case 0x6a: state->l = state->d; break;
		case 0x6b: state->l = state->e; break;
		case 0x6c: state->l = state->h; break;
		case 0x6d: state->l = state->l; break;
		case 0x6e: state->l = ReadFromHL(memory, state); break;
		case 0x6f: state->l = state->a; break;
            
		case 0x70: WriteToHL(memory, state, state->b); break;		//MOV    M,B
		case 0x71: WriteToHL(memory, state, state->c); break;		//MOV    M,C
		case 0x72: WriteToHL(memory, state, state->d); break;		//MOV    M,D
		case 0x73: WriteToHL(memory, state, state->e); break;		//MOV    M,E
		case 0x74: WriteToHL(memory, state, state->h); break;		//MOV    M,H
		case 0x75: WriteToHL(memory, state, state->l); break;		//MOV    M,L
		case 0x76:  break;                                  //HLT
		case 0x77: WriteToHL(memory, state, state->a); break;		//MOV    M,A
            
		case 0x78: state->a  = state->b; break;
		case 0x79: state->a  = state->c; break;
		case 0x7a: state->a  = state->d;  break;
		case 0x7b: state->a  = state->e;  break;
		case 0x7c: state->a  = state->h;  break;
		case 0x7d: state->a  = state->l;  break;
		case 0x7e: state->a = ReadFromHL(memory, state); break;
		case 0x7f: break;
            
		case 0x80:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->b; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD B
		case 0x81:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->c; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD C
		case 0x82:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->d; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD D
		case 0x83:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->e; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD E
		case 0x84:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->h; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD H
		case 0x85:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->l; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADD L
		case 0x86:  					//ADD M
        { 
            uint16_t res = (uint16_t) state->a + (uint16_t) ReadFromHL(memory, state); 
            ArithFlagsA(state, res); 
            state->a=(res&0xff); 
        } break;  
		case 0x87:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->a; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC A
            
		case 0x88:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->b + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC B
		case 0x89:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->c + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC C
		case 0x8a:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->d + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC D
		case 0x8b:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->e + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC E
		case 0x8c:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->h + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC H
		case 0x8d:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->l + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC L
		case 0x8e: 					//ADC M
        { 
            uint16_t res = (uint16_t) state->a + (uint16_t) ReadFromHL(memory, state) + state->cc.cy; 
            ArithFlagsA(state, res); 
            state->a=(res&0xff); 
        } break;  
		case 0x8f:  { uint16_t res = (uint16_t) state->a + (uint16_t) state->a + state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //ADC A
            
            
		case 0x90:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->b; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB B
		case 0x91:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->c; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB C
		case 0x92:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->d; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB D
		case 0x93:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->e; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB E
		case 0x94:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->h; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB H
		case 0x95:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->l; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB L
		case 0x96:  					//SUB M
        { 
            uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(memory, state); 
            ArithFlagsA(state, res); 
            state->a=(res&0xff); 
        } break;  
		case 0x97:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->a; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SUB A
            
		case 0x98:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->b - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB B
		case 0x99:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->c - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB C
		case 0x9a:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->d - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB D
		case 0x9b:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->e - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB E
		case 0x9c:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->h - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB H
		case 0x9d:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->l - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB L
		case 0x9e: 					//SBB M
        { 
            uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(memory, state) - state->cc.cy; 
            ArithFlagsA(state, res); 
            state->a=(res&0xff); 
        } break;  
		case 0x9f:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->a - state->cc.cy; ArithFlagsA(state, res); state->a=(res&0xff); } break;  //SBB A
            
		case 0xa0: state->a = state->a & state->b; LogicFlagsA(state);	break;
		case 0xa1: state->a = state->a & state->c; LogicFlagsA(state);	break;
		case 0xa2: state->a = state->a & state->d; LogicFlagsA(state);	break;
		case 0xa3: state->a = state->a & state->e; LogicFlagsA(state);	break;
		case 0xa4: state->a = state->a & state->h; LogicFlagsA(state);	break;
		case 0xa5: state->a = state->a & state->l; LogicFlagsA(state);	break;
		case 0xa6: state->a = state->a & ReadFromHL(memory, state); LogicFlagsA(state);	break;
		case 0xa7: state->a = state->a & state->a; LogicFlagsA(state);	break;
            
		case 0xa8: state->a = state->a ^ state->b; LogicFlagsA(state);	break;
		case 0xa9: state->a = state->a ^ state->c; LogicFlagsA(state);	break;
		case 0xaa: state->a = state->a ^ state->d; LogicFlagsA(state);	break;
		case 0xab: state->a = state->a ^ state->e; LogicFlagsA(state);	break;
		case 0xac: state->a = state->a ^ state->h; LogicFlagsA(state);	break;
		case 0xad: state->a = state->a ^ state->l; LogicFlagsA(state);	break;
		case 0xae: state->a = state->a ^ ReadFromHL(memory, state); LogicFlagsA(state);	break;
		case 0xaf: state->a = state->a ^ state->a; LogicFlagsA(state);	break;
            
		case 0xb0: state->a = state->a | state->b; LogicFlagsA(state);	break;
		case 0xb1: state->a = state->a | state->c; LogicFlagsA(state);	break;
		case 0xb2: state->a = state->a | state->d; LogicFlagsA(state);	break;
		case 0xb3: state->a = state->a | state->e; LogicFlagsA(state);	break;
		case 0xb4: state->a = state->a | state->h; LogicFlagsA(state);	break;
		case 0xb5: state->a = state->a | state->l; LogicFlagsA(state);	break;
		case 0xb6: state->a = state->a | ReadFromHL(memory, state); LogicFlagsA(state);	break;
		case 0xb7: state->a = state->a | state->a; LogicFlagsA(state);	break;
            
		case 0xb8:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->b; ArithFlagsA(state, res); } break;  //CMP B
		case 0xb9:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->c; ArithFlagsA(state, res); } break;  //CMP C
		case 0xba:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->d; ArithFlagsA(state, res); } break;  //CMP D
		case 0xbb:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->e; ArithFlagsA(state, res); } break;  //CMP E
		case 0xbc:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->h; ArithFlagsA(state, res); } break;  //CMP H
		case 0xbd:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->l; ArithFlagsA(state, res); } break;  //CMP L
		case 0xbe:  { uint16_t res = (uint16_t) state->a - (uint16_t) ReadFromHL(memory, state); ArithFlagsA(state, res); } break;  //CMP L
		case 0xbf:  { uint16_t res = (uint16_t) state->a - (uint16_t) state->a; ArithFlagsA(state, res); } break;  //CMP A
            
		case 0xc0:						//RNZ
			if (state->cc.z == 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;
            
		case 0xc1: 						//POP    B
            Pop(memory, state, &state->b, &state->c);
			break;
		case 0xc2: 						//JNZ address
			if (0 == state->cc.z)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xc3:						//JMP address
			state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			break;
		case 0xc4: 						//CNZ adr
			if (state->cc.z == 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
            
		case 0xc5: 						//PUSH   B
            Push(memory, state, state->b, state->c);
			break;
		case 0xc6: 						//ADI    byte
        {
			uint16_t x = (uint16_t) state->a + (uint16_t) lastOpcode[1];
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x&0xff;
			state->pc++;
        }
			break;
		case 0xc7: 					//RST 0
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x0000;
        }
			break;
		case 0xc8: 					//RZ
			if (state->cc.z)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1] << 8);
				state->sp += 2;
			}
			break;
		case 0xc9: 						//RET
			state->pc = memory[state->sp] | (memory[state->sp+1] << 8);
			state->sp += 2;
			break;
		case 0xca: 						//JZ adr
			if (state->cc.z)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xcb: UnimplementedInstruction(memory, state); break;
		case 0xcc: 						//CZ adr
			if (state->cc.z == 1)
			{
                uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
                state->sp = state->sp - 2;
                state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
		case 0xcd: 						//CALL address
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
        }
 			break;
		case 0xce:					//ACI  byte 
        {
			uint16_t x = state->a + lastOpcode[1] + state->cc.cy;
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x & 0xff;
			state->pc++;
        }
			break;
		case 0xcf: 					//RST 1
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x0008;
        }
			break;
            
		case 0xd0:					//RNC
			if (state->cc.cy == 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;
		case 0xd1: 						//POP    D
            Pop(memory, state, &state->d, &state->e);
			break;
		case 0xd2:						//JNC
			if (state->cc.cy == 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xd3:                      //OUT d8
			state->pc++;
			break;
		case 0xd4:						//CNC adr
			if (state->cc.cy == 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
		case 0xd5: 						//PUSH   D
            Push(memory, state, state->d, state->e);
			break;
		case 0xd6: 						//SUI    byte
        {
			uint8_t x = state->a - lastOpcode[1];
            FlagsZSP(state, x&0xff);
			state->cc.cy = (state->a < lastOpcode[1]);
			state->a = x;
			state->pc++;
        }
			break;
		case 0xd7: 					//RST 2
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x10;
        }
			break;
		case 0xd8: 					//RC
			if (state->cc.cy != 0)
			{
                state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
                state->sp += 2;
			}
			break;
		case 0xd9: UnimplementedInstruction(memory, state); break;
		case 0xda: 					//JC
			if (state->cc.cy != 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;		
		case 0xdb: 					//IN d8
			state->pc++;
			break;
		case 0xdc: 					//CC adr
			if (state->cc.cy != 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
		case 0xdd: UnimplementedInstruction(memory, state); break;
		case 0xde: 					//SBI byte
        {
			uint16_t x = state->a - lastOpcode[1] - state->cc.cy;
            FlagsZSP(state, x&0xff);
			state->cc.cy = (x > 0xff);
			state->a = x & 0xff;
			state->pc++;
        }
			break;
		case 0xdf: 					//RST 3
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x18;
        }
			break;
            
		case 0xe0:					//RPO
			if (state->cc.p == 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;
		case 0xe1: 					//POP    H
            Pop(memory, state, &state->h, &state->l);
			break;
		case 0xe2: 						//JPO
			if (state->cc.p == 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xe3:						//XTHL 
        {
            uint8_t h = state->h;
            uint8_t l = state->l;
            state->l = memory[state->sp];
            state->h = memory[state->sp+1]; 
            WriteMem(memory, state->sp, l );
            WriteMem(memory, state->sp+1, h );
        }
			break;
		case 0xe4: 						//CPO adr
			if (state->cc.p == 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
		case 0xe5: 						//PUSH   H
            Push(memory, state, state->h, state->l);
			break;
		case 0xe6: 						//ANI    byte
        {
			state->a = state->a & lastOpcode[1];
			LogicFlagsA(state);
			state->pc++;
        }
			break;
		case 0xe7: 					//RST 4
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x20;
        }
			break;
		case 0xe8: 					//RPE
			if (state->cc.p != 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;
		case 0xe9: 						//PCHL
			state->pc = (state->h << 8) | state->l;
			break;
		case 0xea: 						//JPE
			if (state->cc.p != 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;		
		case 0xeb: 					//XCHG
        {
            uint8_t save1 = state->d;
            uint8_t save2 = state->e;
            state->d = state->h;
            state->e = state->l;
            state->h = save1;
            state->l = save2;
        }
			break;
		case 0xec: 					//CPE adr
			if (state->cc.p != 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
		case 0xed: UnimplementedInstruction(memory, state); break;
		case 0xee: 					//XRI data
        {
			uint8_t x = state->a ^ lastOpcode[1];
            FlagsZSP(state, x);
			state->cc.cy = 0;		//data book says clear cy
			state->a = x;
			state->pc++;
        }
			break;
		case 0xef: 					//RST 5
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x28;
        }
			break;
            
		case 0xf0: 					//RP
			if (state->cc.s == 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;		
		case 0xf1: 					//POP PSW
            Pop(memory, state, &state->a,(unsigned char*) &state->cc);
			break;
		case 0xf2: 
			if (state->cc.s == 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xf3: state->int_enable = 0;  break;
		case 0xf4: 						//CP
			if (state->cc.s == 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
            
		case 0xf5: 						//PUSH   PSW
            Push(memory, state, state->a, *(unsigned char*)&state->cc);
			break;
            
		case 0xf6: 						//ORI    byte
        {
			//AC set if lower nibble of h was zero prior to dec
			uint8_t x = state->a | lastOpcode[1];
            FlagsZSP(state, x);
			state->cc.cy = 0;
			state->a = x;
			state->pc++;
        }
			break;
		case 0xf7: 					//RST 6
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x30;
        }
			break;
		case 0xf8:					//RM
			if (state->cc.s != 0)
			{
				state->pc = memory[state->sp] | (memory[state->sp+1]<<8);
				state->sp += 2;
			}
			break;
		case 0xf9: 					//SPHL
			state->sp = state->l | (state->h << 8);
			break;
		case 0xfa: 					//JM
			if (state->cc.s != 0)
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			else
				state->pc += 2;
			break;
		case 0xfb: state->int_enable = 1;  break;
		case 0xfc: 					//CM
			if (state->cc.s != 0)
			{
				uint16_t	ret = state->pc+2;
                WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
                WriteMem(memory, state->sp-2, (ret & 0xff));
				state->sp = state->sp - 2;
				state->pc = (lastOpcode[2] << 8) | lastOpcode[1];
			}
			else
				state->pc += 2;
			break;
            
		case 0xfd: UnimplementedInstruction(memory, state); break;
		case 0xfe: 						//CPI  byte
        {
			uint8_t x = state->a - lastOpcode[1];
            FlagsZSP(state, x);
			state->cc.cy = (state->a < lastOpcode[1]);
			state->pc++;
        }
			break;
		case 0xff: 					//RST 7
        {
			uint16_t	ret = state->pc+2;
            WriteMem(memory, state->sp-1, (ret >> 8) & 0xff);
            WriteMem(memory, state->sp-2, (ret & 0xff));
			state->sp = state->sp - 2;
			state->pc = 0x38;
        }
			break;
	}

	if(debug != 0)
	{
		printf("\t");
		printf("%c", state->cc.z ? 'z' : '.');
		printf("%c", state->cc.s ? 's' : '.');
		printf("%c", state->cc.p ? 'p' : '.');
		printf("%c", state->cc.cy ? 'c' : '.');
		printf("%c  ", state->cc.ac ? 'a' : '.');
		printf("A $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP %04x\n", state->a, state->b, state->c,
           		state->d, state->e, state->h, state->l, state->sp);
	}
	return cycles8080[*lastOpcode];
}


void CPU8080::ReadFileIntoMemoryAt(const char* filename, uint32_t offset)
{
	FILE *f= fopen(filename, "rb");
	if (f==NULL)
	{
		printf("error: Couldn't open %s\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	uint8_t *buffer = &memory[offset];
	fread(buffer, fsize, 1, f);
	fclose(f);
}

CPU8080::CPU8080()
{
	state = (State8080*) calloc(1,sizeof(State8080));
	memory = (uint8_t*) malloc(0x10000);  //16K
}

CPU8080::~CPU8080()
{
	free(state);
	free(memory);
}

bool CPU8080::isHalted() const
{
	return (*lastOpcode == 0x76);
}

bool CPU8080::isSystemCall() const
{
	if(state->pc == 0x0007)
		return true;
	return false;
}


