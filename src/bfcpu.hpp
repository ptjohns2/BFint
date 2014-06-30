#ifndef __BFCPU_HPP__
#define __BFCPU_HPP__

#include "PCstack.hpp"
#include <string>

using namespace std;

#define TAPE_SIZE	30000	//32768
#define PROGRAM_SIZE 32768


class bfcpu{
	public:
		bfcpu();
		~bfcpu();

		//Member functions
		//- Clears program state
		void resetData();
		void resetProgram();
		void reset();

		//- Reads "++++-[>>>+.]---" for example into optimized program string "+3[>3+1.]+2"
		void readStringToOptomizedProgram_operatorCollapse(string programString);
		//- Executes the aforementioned optimized program string
		void runOptimizedProgram_operatorCollapseMicrocode();


		//Members
		int pc;
		int p;
		unsigned char tape[TAPE_SIZE];
		//MAKE INT
		char program[PROGRAM_SIZE];
		int programLength;
		PCstack stack;
		
	private:

};

#endif