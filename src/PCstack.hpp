#ifndef __PCSTACK_HPP__
#define __PCSTACK_HPP__
	
#define NULL 0

class PCstack{
	public:
		PCstack();
		~PCstack();

		//Member functions
		void push(int val);
		int peak();
		int pop();

		void setSize(int size);
		

	private:
		//Members
		int* ptr;
		int top;
		int size;
		
};
	
	
#endif