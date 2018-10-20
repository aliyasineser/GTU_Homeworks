#ifndef H_GTUOS
#define H_GTUOS


#include <string>
#include "8080emuCPP.h"
#include "memory.h"
#include "page.h"

#define MAXPROCESSNUMBER 4
#define MAXFILENAMELENGTH 256
#define INITIALPID 10
#define PROCESSLOADMULTIPLIER 0x4000

// Process State static globals
static const char * readyState = "State_Ready";
static const char * blockedState = "State_Blocked";
static const char * runningState = "State_Running";


typedef struct ProcInfo {
    std::string fileName;   // File name of the process, "exe" name
    State8080 processCpuState;  // Register information of the process
    uint32_t baseRegister;  // Ram start location of the process
    uint32_t limitRegister; // Program length, all processes have 16k ram(virtually)
    int processPid;    // Process id
    int parentPid; // Pid of the process' parent
    uint64_t startCycle;    // Start time of the process
    uint64_t consumedCycle; //How many cycle program consumed
    uint32_t physicalLocation;  //Physical location, base register
    const char * processState;  // Running, Blocked or Ready
} ProcessInformation;



class GTUOS{
    friend class memory;
public:
    uint64_t handleCall(uint64_t cycle); // handles call which comes from the hw
    void memToFile(); // writes memory content to file "exe.mem"
    GTUOS(MemoryBase *mem, CPU8080 *theCpu);    // Constructor
    // Getter and setter of the slot. Slot means is there a process
    bool getSlot(int index){return slot[index%MAXPROCESSNUMBER];}
    bool setSlot(int index, bool val){return slot[index%MAXPROCESSNUMBER] = val;}
    // Pid getter and updater
    long getPid(){return nextPid;}
    void incrementPid(){++nextPid;}
    // Updater and getter of the Process Information
    ProcessInformation getProcInfo(int index){return processTable[index];}
    void setProcInfo(int index, ProcessInformation &procInfo){ processTable[index] = procInfo;}
    // Updater and getter of the cpu state(Registers etc.)
    void updateState(ProcessInformation &p){p.processCpuState = *(cpu->state);}
    State8080 getCpuState(){ return *(cpu->state) ;}
    void setCpuState(State8080 stateVal){ *(cpu->state)  = stateVal;}
    // Index of the running process
    int getTurn(){return takeTurn;}
    // Round robin implementation, returns new process if there is any
    ProcessInformation getNextProcess(ProcessInformation procInf);
    // Checks that there is a process or not
    bool isThereAnyProcess(){return slot[0]|slot[1]|slot[2]|slot[3];}
    // Ends the process
    void endProcess(){slot[takeTurn] = false;} //TODO: Update table entry, change pid
    // Checks that is there a space for loading program
    bool isThereAnySpace(){return !(slot[0]&&slot[1]&&slot[2]&&slot[3]);}
    // Returns empty index for new process
    int getEmptyIndex();
    // Returns empty, clean process entry
    ProcessInformation getEmptyProcessEntry();
    // Sets base register according to process number
    void setProcessRange(ProcessInformation& p, int turn);
    // Clears cpuState8080
    void cleanCpuState(ProcessInformation & p);
    // Check if there is a process with that pid
    bool isProcessDead(int pid);
    void printProcessTable();
    void readPageIntoMemoryAt(const char* filename, uint32_t offsetRam, uint32_t offsetFile);

private:
    // "Is there a process" table
    bool slot[MAXPROCESSNUMBER];
    // Who's turn ?
    int takeTurn;
    // Process Table, struct array
    ProcessInformation processTable[MAXPROCESSNUMBER];
    // Pid counter
    int nextPid;
    // Memory pointer
    MemoryBase * memory;
    // Cpu pointer
    CPU8080 * cpu;
};

#endif
