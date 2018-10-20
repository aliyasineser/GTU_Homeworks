#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"


class GTUOS{
	public:
		uint64_t handleCall(const CPU8080 & cpu); // handles call which comes from the hw
		void memToFile(const CPU8080 & cpu); // writes memory content to file "exe.mem"
};	

#endif
