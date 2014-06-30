make: src/main.cpp src/PCstack.cpp src/bfcpu.cpp
	g++ -o main.o src/main.cpp -c
	g++ -o PCstack.o src/PCstack.cpp -c
	g++ -o bfcpu.o src/bfcpu.cpp -c
	g++ -o bfint main.o PCstack.o bfcpu.o
	rm *.o

