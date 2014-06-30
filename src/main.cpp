#include "bfcpu.hpp"
#include "PCstack.hpp"

#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* args[]){
	if(argc <= 1){return 0;}
	fstream file;
	file.open(args[1]);
	if(!file.is_open()){
		file.close(); return 0;
	}
	stringstream fileContents;
	fileContents << file.rdbuf();
	string program = fileContents.str();

	bfcpu cpu = bfcpu();

	
	cpu.readStringToOptomizedProgram_operatorCollapse(program);
	cpu.runOptimizedProgram_operatorCollapseMicrocode();
	
	return 0;
}

