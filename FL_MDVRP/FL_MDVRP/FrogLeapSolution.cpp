#include "stdafx.h"
#include "FrogLeapSolution.h"

#include <iostream>
#include <time.h>




FrogLeapSolution::FrogLeapSolution(short int size_v):FrogObject()
{
	this->size = size_v;
	this->values = new float[this->size];	
}

float FrogLeapSolution::getFLValue(short int i)
{
	return this->values[i];
}

void FrogLeapSolution::setSize(short int size_v)
{
	this->size = size_v;
}

short int FrogLeapSolution::getSize()
{
	return this->size;
}

void FrogLeapSolution::genRandomSolution()
{
	float u;
	int a = 50;

	srand((unsigned)time(NULL));

	for (int i = 0; i < this->size; i++)
	{
		u = (float)rand() / (float)(RAND_MAX / a);
		this->values[i] = u;
	};
}

// inherited methods
void FrogLeapSolution::printFrogObj()
{
	printf("Printing values of frog leaping solution \n");
	printf("Values are the following: \n");

	for(int i = 0; i < this->getSize();i++)
	{
		printf("%.2f, ", this->values[i]);
	}

	printf("\n");
}

bool FrogLeapSolution::isTheSame(FrogObject * fs)
{
	FrogLeapSolution * fls = (FrogLeapSolution *)fs;

	if (this->getSize() != fls->getSize())
	{
		return false;
	}

	for (int i = 0; i < this->getSize(); i++)
	{
		if (this->values[i] != fls->values[i])
			return false;		
	}

	return true;
}



