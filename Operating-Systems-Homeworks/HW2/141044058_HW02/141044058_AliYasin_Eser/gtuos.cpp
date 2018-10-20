#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"

// This is just a simple OS with no virtual addresses. 
// You will write your own OS .
GTUOS::GTUOS(MemoryBase *mem, CPU8080 *theCpu){
    nextPid = INITIALPID;
    takeTurn = 0;
    for(int i=0; i < MAXPROCESSNUMBER; ++i)
        slot[i] = false;
    memory = mem;
    cpu = theCpu;
}

void GTUOS::printProcessTable(){

    for(int i=0; i < MAXPROCESSNUMBER; ++i)
        if(slot[i])
            fprintf(stdout, "%3ld   %3ld   %8ld   %8ld   %s\n",
                (long )processTable[i].processPid, (long)processTable[i].parentPid, 
                (long)processTable[i].startCycle, (long)processTable[i].consumedCycle, processTable[i].fileName.c_str() );
    


}

void GTUOS::cleanCpuState(ProcessInformation & p){
      //memset(&p.processCpuState, 0, sizeof(State8080)); 
      p.processCpuState.pc = 0;
}

ProcessInformation GTUOS::getNextProcess(ProcessInformation procInf){
    if(procInf.processState != blockedState) 
        procInf.processState = readyState;
    procInf.processCpuState = *(cpu->state);
    processTable[takeTurn] = procInf;
    int temp = takeTurn;
    //for(int i=0; i < 4; i++){std::cout << "hey i'm " << i  << "and i'm  " << slot[i] << std::endl;}
    //std::cout << "Context Switching to " << takeTurn << std::endl;
    if(isThereAnyProcess()){
        for(takeTurn = ++takeTurn%MAXPROCESSNUMBER;slot[takeTurn] != true; 
        takeTurn = ++takeTurn%MAXPROCESSNUMBER)
        { }
        std::cout << "Winner is "<< takeTurn << " " <<  processTable[takeTurn].fileName << std::endl;
        return processTable[takeTurn];

    }
    ProcessInformation emptyProcess = getEmptyProcessEntry();
    return emptyProcess;
    
}

ProcessInformation GTUOS::getEmptyProcessEntry(){

    ProcessInformation p;
    
    p.baseRegister = 0x0;
    p.limitRegister = PROCESSLOADMULTIPLIER;
    p.processPid = -1000;
    p.parentPid = 0;    
    p.startCycle = 0;
    p.consumedCycle = 0;
    p.physicalLocation = 0x0;
    p.processState = readyState;
    cleanCpuState(p);
    return p;
}

void GTUOS::setProcessRange(ProcessInformation& p, int turn){
    p.physicalLocation = p.baseRegister = turn * PROCESSLOADMULTIPLIER;
    
}

bool GTUOS::isProcessDead(int pid){
    for(int i=0; i < MAXPROCESSNUMBER; ++i){
        if(processTable[i].processPid == pid && !slot[i]) return true;
    }
    return false;
}

int GTUOS::getEmptyIndex(){
    for(int i=0 ; i < MAXPROCESSNUMBER; ++i)
        if( slot[i] == false )
            return i;
    
    return -1;
}

uint64_t GTUOS::handleCall(uint64_t cycle){

	// Use for address. Almost all of the calls requirement that 
	// generate address from b and c registers.
	uint16_t address = ((uint16_t)cpu->state->b << 8) | cpu->state->c;


	// Print num
	if(cpu->state->a == (uint8_t)1){
		std::cout << "System Call: PRINT_B" << std::endl;
		std::cout << (int)cpu->state->b << std::endl;
		return (uint64_t)10;	
	}
	// Print memory content
	else if(cpu->state->a == (uint8_t)2){
		std::cout << "System Call: PRINT_MEM" << std::endl;
		std::cout << (int)cpu->memory->at(address) << std::endl;
		return (uint64_t)10;	
	}
	// Read an integer. Integer will be casted to 8 bit integer.
	else if(cpu->state->a == (uint8_t)3){
		std::cout << "System Call: READ_B" << std::endl;
		int temp;
		std::cin >> temp; // Read the integer
        // Add the number to register, but only 8 bits.
		cpu->state->b = (uint8_t)temp; 
		std::cin.ignore();
		return (uint64_t)10;
	}
	// Read memory content
	else if(cpu->state->a == (uint8_t)4){
		std::cout << "System Call: READ_MEM" << std::endl;
		int num;
		std::cin >> num; // Read the memory
		std::cin.ignore();
		cpu->memory->at(address) = (uint8_t)num;
		return (uint64_t)10;
	}
	// Print a string
	else if(cpu->state->a == (uint8_t)5){
		std::cout << "System Call: PRINT_STR" << std::endl;
		for (uint16_t i = address; ; ++i)
		{	
			if(cpu->memory->at(i) != (uint8_t)0)
                std::cout << (char)cpu->memory->at(i);
			else
				break;
		}
		std::cout << std::endl;
		return (uint64_t)100;
	}
	// Read a string. String will be read.
	else if(cpu->state->a == (uint8_t)6){
		std::cout << "System Call: READ_STR" << std::endl;
		std::string str = "";
		std::getline(std::cin, str);
		int count;
		uint16_t i;
		for (i = address, count = 0; count < str.length(); ++i, ++count)
		{	
			cpu->memory->at(i) = str[count];
		}
		cpu->memory->at(i) = (uint8_t)'\0';
		//std::cin.ignore();
        std::cin.clear();
		return (uint64_t)100;
	}
    // Fork
    else if(cpu->state->a == (uint8_t)7){
        std::cout << "System Call: FORK" << std::endl;
        if(isThereAnySpace()){// if we have less than 4 processes
            int index = getEmptyIndex(); // take an empty entry index
            // create new process table entry, update parent process entry as well
            ProcessInformation p = getProcInfo(getTurn());
            ProcessInformation parent = getProcInfo(getTurn());
            p.parentPid = p.processPid;
            incrementPid();
            
            p.processPid = getPid(); // Child id goes to parents a register
            p.baseRegister = p.processPid * 0x4000;
            p.consumedCycle = 0;
            p.processState = readyState;
            p.processCpuState.b = 0;
            p.startCycle = cycle;
            parent.processCpuState.b = p.processPid;
            setProcessRange(p, index);

            uint32_t i = parent.baseRegister; 
            uint32_t j = p.baseRegister;
            std::cout << "child p: "<<p.baseRegister << " parent p: "<< parent.baseRegister<<std::endl;
             
            for(;i < parent.baseRegister + PROCESSLOADMULTIPLIER;){  
                memory->physicalAt(j) = memory->physicalAt(i);
                //std::cout << "i: " << i << " j: " << j << std::endl;
                ++i;
                ++j;
            }
            
            // Make the changes
            setProcInfo(index, p);
            setProcInfo(getTurn(), parent);
            // Now we have the child process, make it real.
            slot[index] = true;
            setCpuState(parent.processCpuState);
        }
        return (uint64_t)50;
    }
    // Exec
    else if(cpu->state->a == (uint8_t)8){
        std::cout << "System Call: EXEC" << std::endl;
        std::string str = "";
        for (uint16_t i = address; ; ++i)
        {
            if(cpu->memory->at(i) != (uint8_t)0)
                str += (char)cpu->memory->at(i);
            else
                break;
        }
        //std::cout << "Exe: " << str << std::endl;
        ProcessInformation p = getProcInfo(getTurn());
        p.fileName = str;
        cpu->ReadFileIntoMemoryAt(p.fileName.c_str(), 
            getTurn() * PROCESSLOADMULTIPLIER);
        //std::cout << "It worked" << std::endl;
        cleanCpuState(p);
        setProcInfo(getTurn(), p);
        setCpuState(p.processCpuState);
        return (uint64_t)80;
    }
    // Waitpid
    else if(cpu->state->a == (uint8_t)9){
        std::cout << "System Call: WAITPID" << std::endl;
        ProcessInformation p = getProcInfo(getTurn());
        

        p.processState = blockedState;
        setProcInfo(getTurn(), p);
        setCpuState(p.processCpuState);
        return (uint64_t)80;
    }
	// Case of unimplemented call. 
	std::cout <<  "Unimplemented OS call";
	throw -1;
	
	return 0;
}


// Writes memory to file "exe.mem" 
void GTUOS::memToFile(){

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
			fprintf(optr, "%.2x ", cpu->memory->physicalAt(i+j));
		}
		fprintf(optr, "\n");
	}


	fclose(optr); // close
	return;
}



// TODOO
void GTUOS::readPageIntoMemoryAt(const char* filename, uint32_t offsetRam, uint32_t offsetFile)
{
    
    int counter = 0;
	FILE *f= fopen(filename, "rb");
	if (f==NULL)
	{
		printf("error: Couldn't open %s\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	uint8_t *buffer = &memory->physicalAt(offsetRam);
    for(;counter < offsetFile;++counter){
        fseek(f,offsetFile, SEEK_SET);
    }
	if(fsize < offsetFile){ 
        fread(buffer, 0x400*sizeof(uint8_t), 1, f);
        
    }
    fclose(f);
    
}
