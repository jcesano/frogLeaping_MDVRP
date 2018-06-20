#include "FrogLeapSolution.h"


FrogLeapSolution::FrogLeapSolution(short int size_v)
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

	if (this->getSize() != fs->getSize())
	{
		return false;
	}

	for (int i = 0; i < this->getSize(); i++)
	{
		if (this->values[i] != fs->values[i]
			return false;		
	}

	return true;
}



