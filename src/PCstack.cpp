#include "PCstack.hpp"

#include <iostream>
using namespace std;

PCstack::PCstack(){
	ptr = NULL;
	setSize(0);
}

PCstack::~PCstack(){
	delete[] ptr;
}


//Member functions
void PCstack::push(int val){
	top++;
	ptr[top] = val;
}

int PCstack::peak(){
	return ptr[top];
}

int PCstack::pop(){
	top--;
	return ptr[top+1];
}


void PCstack::setSize(int size){
	if(size < 0){size = 0;}
	this->size = size;
	top = -1;
	delete[] ptr;
	if(size == 0){
		ptr = NULL;
	}else{
		ptr = new int[size];
	}
}



