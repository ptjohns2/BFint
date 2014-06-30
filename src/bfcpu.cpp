#include "bfcpu.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>


bfcpu::bfcpu()
	:	stack()
{
	reset();
}

bfcpu::~bfcpu(){

}

//Member functions
void bfcpu::resetData(){
	//p = TAPE_SIZE / 2;
	p = 0;
	memset(&tape[0], 0, sizeof(tape));
}
void bfcpu::resetProgram(){
	programLength = 0;
	pc = 0;
	memset(&program[0], 0, sizeof(program));
}
void bfcpu::reset(){
	resetData();
	resetProgram();
}



void bfcpu::readStringToOptomizedProgram_operatorCollapse(string programString){
	unsigned int _PC=0, _opPC = 0;
	int numNests = 0;
	for(; _opPC<PROGRAM_SIZE && _PC<programString.length(); /*no incrementation*/){
		int _opOffset = 0;

		//Skip past non-instruction characters
		while(	programString[_PC] != '.'
			&&	programString[_PC] != ','
			&&	programString[_PC] != '['
			&&	programString[_PC] != ']'
			&&	programString[_PC] != '+'
			&&	programString[_PC] != '-'
			&&	programString[_PC] != '>'
			&&	programString[_PC] != '<'
			)
		{
			_PC++;
		}

		//======>PTR INCREMENTATION
		if(programString[_PC] == '>' || programString[_PC] == '<'){
			//Analyze
			while(true){ 
				if(programString[_PC] == '>'){
					_opOffset++;
				}else if(programString[_PC] == '<'){
					_opOffset--;
				}else{
					_PC--;
					break;
				}
				_PC++;
			}
			//Encode
			if(_opOffset != 0){
				program[_opPC] = '>';
				_opPC++;
				program[_opPC] = _opOffset;
			}else{
				_opPC--;
			}
		//======>VAL INCREMENTATION
		}else if(programString[_PC] == '+' || programString[_PC] == '-'){
			//Analyze
			while(true){
				if(programString[_PC] == '+'){
					_opOffset++;
				}else if(programString[_PC] == '-'){
					_opOffset--;
				}else{
					_PC--;
					break;
				}
				_PC++;
			}
			//Encode
			if(_opOffset != 0){
				program[_opPC] = '+';
				_opPC++;
				program[_opPC] = _opOffset;
			}else{
				_opPC--;
			}
		//======>NON-COLLAPSABLE
		}else{
			if(programString[_PC] == '['){numNests++;}
			program[_opPC] = programString[_PC];
		}

		//END cases, loop increments
		_PC++;
		_opPC++;
	}
	programLength = _opPC;
	stack.setSize(numNests);
}



void bfcpu::runOptimizedProgram_operatorCollapseMicrocode(){
	do{
		if(program[pc] == '+'){
			pc++;
			tape[p] += program[pc];
			pc++;
		}else if(program[pc] == '>'){
			pc++;
			p += program[pc];
			p %= TAPE_SIZE;
			pc++;
		}else if(program[pc] == '['){
			if(!( (program[pc+3] == ']' && (program[pc+1] == '+' || program[pc+1] == '>')) || (program[pc+1] == ']' && tape[p] ) )){
				if(tape[p]){
					//push current pc to stack to come back here later
					stack.push(pc);
					pc++;
				}else{
					//find next matching end bracket ]
					int numNests = 1;
					pc++;
					while(true){
						if(program[pc] == '['){
							numNests++;
						}else if(program[pc] == ']'){
							numNests--;
						}
						//matching end bracket ] found
						if(numNests == 0){break;}
						pc++;
					}
					//skip past matching end bracket ]
					pc++;
				}
			}else{
				//==>Loop microcode
				//[+] [-]
				if(program[pc+1] == '+'){
					tape[p] = 0; 
					pc+=4;
				}else if(program[pc+1] == '>'){
					//[<]
					if(program[pc+2] < 0){
						while(tape[p]){p++;}
						pc+=4;
					//[>]
					}else{
						while(tape[p]){p--;}
						pc+=4;
					}
				}else if(program[pc+1] == ']' && tape[p]){
					//INFINITE LOOP
					cout << "\n\nbfcpu::runOptimizedProgram_operatorCollapseMicrocode ERROR:\n" << 
						"Infinite loop \"[]\" detected at PC = " << pc << ".  Halting execution.";
					stack.setSize(0);
					exit(1);
				}
			}
		}else if(program[pc] == ']'){
			if(tape[p]){
				pc = stack.peak();
			}else{
				stack.pop();
			}
			pc++;
		}else if(program[pc] == '.'){
			putchar(tape[p]);
			pc++;
		}else if(program[pc] == ','){
			tape[p] = getchar();
			pc++;
		}else{
			char unrecognizedInstruction = program[pc];
			cout << unrecognizedInstruction;
		}
	}while(pc < programLength);
}




















