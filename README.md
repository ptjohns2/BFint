#BFint   

   
##Brainf*ck interpreter written in C++  
 
http://esolangs.org/wiki/brainfuck  
  
Brainf*ck is an esoteric programming language consisting of:  
-An array of chars   
-A pointer to somewhere in the array   
-8 commands:   
	>		p++    
	<		p--     
	+		*p++     
	-		*p--     
	.		putchar(*p)     
	,		*p = getchar()     
	[		while(*p) - start     
	]		while(*p) - end     

###Specifications
- Tape: size 30000 array of unsigned chars   
- Max program length: 32768 instructions (after instruction collapse optimization)   
   
###Added features:   
- Infinite loop detection and halting (will stop at "[]" if tape[p]!=0 and notify user of infinite loop)      
- Instruction collapsing ("++++++++++-[-+>>>+.]---" collapses to "+9[>3+1.]-3")      
- Expensive code snippet precomputation ("[-]" or "[+]" optimized to tape[p]=0, etc)      
      
###Usage           
./BFint [program_name.bf]     
      
![Alt ext](/windows_usage.png?raw=true)  