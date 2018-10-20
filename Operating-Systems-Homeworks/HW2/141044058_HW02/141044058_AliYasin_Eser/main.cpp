#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

	// This is just a sample main function, you should rewrite this file to handle problems 
	// with new multitasking and virtual memory additions.
int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
    // Debug value, effects the information that will be printed.
	int DEBUG = atoi(argv[2]);
    // Memory instance.
	memory mem;
    // Total cycle counter.
	uint64_t cycle = 0;
    // Cpu Instance.
	CPU8080 theCPU(&mem);
    // Operating System Instance.
	GTUOS	theOS(&mem, &theCPU);
    // Variable for assigning instruction cycle and updating.
    uint16_t instructionCycle=0;  
    // Cycle counter for round robin scheduling. 
    uint16_t roundCycle=0;
    
    // First program load, handling manually.
	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	
    theOS.setSlot(0, true);
    ProcessInformation p = theOS.getEmptyProcessEntry();
    p.fileName = argv[1];
    p.processPid = theOS.getPid();
    theOS.incrementPid();
    p.processState = runningState;
    theOS.cleanCpuState(p);
    // memory register initialization for first program.
    mem.limitRegister = 0x4000;
    mem.baseRegister =  0x0000;
    
    // Cpu starts to execute
	do	
	{
        //TODO: Blocked state control, if there is a block we should do only the system call, and maybe we can decrement pc to fix it. If we block all the time, cpu will execute waitpid forever(not forever, checks child arrival)
        // Take current process state from process table, update register values.
        theOS.setCpuState(p.processCpuState); 
        if( p.processState != blockedState ){ // If process not blocked
            p.processState = runningState; // Process is running now.
            // Every process has 100 cycles to do it's part. It's the time slice
            while( p.processState != blockedState && roundCycle < 100){  
                //Instruction handle
                instructionCycle += theCPU.Emulate8080p(DEBUG);
                
                //System call handle
                if(theCPU.isSystemCall()){
                    // Before system call, need to update process table.
                    theOS.updateState(p);
                    theOS.setProcInfo(theOS.getTurn(), p);
                    // Give the control to OS 
                    instructionCycle += theOS.handleCall(cycle);
                    // Get updated version of the process. 
                    p = theOS.getProcInfo(theOS.getTurn());
                    //std::cout << theOS.getTurn()<< " " <<p.processState << std::endl;
                }
                //Cycle update 
                p.consumedCycle += instructionCycle;
                cycle += instructionCycle;
                roundCycle += instructionCycle;
                // Reset the instruction cycle
                instructionCycle = 0; 
                // Process table update
                theOS.setProcInfo(theOS.getTurn(), p);
                // If current process ends, need to remove it.
                if(theCPU.isHalted()){  
                    std::cout << "End of process: " << theOS.getTurn() << std::endl;
                    theOS.endProcess();
                    break;
                }
            }
            
        }else{
            // If the process is in the blocked state, it is probably
            // waiting it's child
            // std::cout << "Blocked process: " << p.processPid  << " for pid: " << (int)p.processCpuState.b<< std::endl;
            // Check if child process is dead or not
            if(theOS.isProcessDead(p.processCpuState.b)){
                // If child process is dead, parent is ready to continue
                p.processState = readyState;
            }
        }
        
        if(DEBUG == 2)
            std::cout << "Process swith from: " << p.fileName;
        p = theOS.getNextProcess(p); // Scheduler gives next process
        if(DEBUG == 2){
            std::cout << " to: " << p.fileName << std::endl;
            std::cout << "Consumed cycle: " << roundCycle; 
        }
        if(DEBUG == 3)
            theOS.printProcessTable();
        // Reset round cycle to count new process execution time
        roundCycle = 0;    
        // Memory update. No need to update limit register, all of the same and 16K
        mem.baseRegister = p.baseRegister;
        // Loop until there is no process
	}	while (theOS.isThereAnyProcess());

    // Write memory contents to file
	theOS.memToFile();
    // Print total cycle
	std::cout << "Total Cycle: " << (int)cycle << std::endl;
    //End of the simulation
	return 0;
}

