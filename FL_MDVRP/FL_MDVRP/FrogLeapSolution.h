#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

#include "SortedLinkedList.h"
#include <iostream>
#include <time.h>

class FrogLeapSolution: public FrogObject
{
private:
	float * values;
	short int size;

public:
	
	FrogLeapSolution(short int size_v);

	float getFLValue(short int i);

	void setSize(short int size_v);

	short int getSize();

	void genRandomSolution();

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);



};

#endif
