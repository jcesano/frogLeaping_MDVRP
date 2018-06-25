#include "stdafx.h"
#include "FrogLeapSolution.h"
#include "Vehicle.h"
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

float FrogLeapSolution::genRandomFloatingNumber(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void FrogLeapSolution::genRandomSolution()
{
	float u;
	int a = this->size;

	this->timeSeedUsed = (unsigned)time(NULL);
	srand(this->timeSeedUsed);

	for (int i = 0; i < this->size; i++)
	{
		u = this->genRandomFloatingNumber(0, this->size);
		this->values[i] = u;
	};
}

FeasibleSolution * FrogLeapSolution::decodeFrogLeapSolution()
{
	//FeasibleSolution * decodeSolution = new FeasibleSolution();
	return NULL;
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



