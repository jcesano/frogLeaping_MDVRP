#include "stdafx.h"
#include "FrogLeapSolution.h"
#include "DecodedFrogLeapSolution.h"
#include "Vehicle.h"
#include "Graph.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>

FrogLeapSolution::FrogLeapSolution(short int size_v, short int n_vehicles_v, short int n_depots_v, short int id):FrogObject(id)
{
	this->size = size_v;
	this->n_vehicles = n_vehicles_v;
	this->n_depots = n_depots_v;
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
		u = this->genRandomFloatingNumber(0, this->n_vehicles);
		this->values[i] = u;
	};
}

DecodedFrogLeapSolution * FrogLeapSolution::decodeFrogLeapSolution(Graph * g)
{
	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(g);
	
	for (short int i = 0; i < this->getSize(); i++)
	{
		decodedSolution->decodeFrogLeapItem(this->getFLValue(i), i, this->n_depots, this->n_vehicles);
	}
	
	return decodedSolution;
}


// inherited methods
void FrogLeapSolution::printFrogObj()
{
	printf("Printing values of frog leaping solution \n");
	printf("Values are the following: \n");

	for(int i = 0; i < this->getSize() - 1;i++)
	{
		printf("%.2f, ", this->values[i]);
	}

	//printing the last element (replacing the comma by the point)
	printf("%.2f. \n", this->values[this->getSize() - 1]);	
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



