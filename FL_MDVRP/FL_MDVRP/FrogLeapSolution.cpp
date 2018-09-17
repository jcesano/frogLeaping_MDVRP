#include "stdafx.h"
#include "FrogLeapSolution.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogLeapController.h"
#include "Vehicle.h"
#include "Graph.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>

FrogLeapSolution::FrogLeapSolution(SolutionGenerationType v_sgt, SourceType v_sourceType, int ncustomers, int n_depots_v, int id):FrogObject(id)
{
	this->sgt = v_sgt;
	this->st = v_sourceType;
	
	this->n_depots = n_depots_v;

	this->size = ncustomers;
	this->nElementsToSort = this->n_depots;
		
	this->values = new float[this->size];		
}

FrogLeapSolution::~FrogLeapSolution()
{
	delete[] values;
}

float FrogLeapSolution::getFLValue(int i)
{
	return this->values[i];
}

void FrogLeapSolution::setSize(int size_v)
{
	this->size = size_v;
}

int FrogLeapSolution::getSize()
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

//	this->timeSeedUsed = (unsigned)time(NULL);
//	srand(this->timeSeedUsed);

	for (int i = 0; i < this->size; i++)
	{
		u = this->genRandomFloatingNumber(0, this->nElementsToSort);
		this->values[i] = u;
	};
}


DecodedFrogLeapSolution * FrogLeapSolution::decodeSolution(FrogLeapController * controller)
{
	controller->resetDepotRemainingCapacities();
	return this->decodeFrogLeapSolution(controller);
}

// This algorithm uses a float distance table and the fixed algorithm
DecodedFrogLeapSolution * FrogLeapSolution::decodeFloatFixedFrogLeapSolution()
{
	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(NULL);

	int i = 0;
	bool feasible = true;

	do
	{
		feasible = decodedSolution->decodeFrogLeapItem(this->getFLValue(i), i, this->n_depots);
		i++;
	} while (i < this->getSize() && feasible == true);

	return decodedSolution;
}

//if generated instance of DecodedFrogLeapSolution is NULL then solution is not valid due to a vehicle capacity violation
// This algorithm uses an int distance table and the Graph instance
DecodedFrogLeapSolution * FrogLeapSolution::decodeFrogLeapSolution(FrogLeapController * controller)
{
	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(this->n_depots, controller);
	
	int i = 0;
	bool feasible = true;

	do 
	{
 		feasible = decodedSolution->decodeFrogLeapItem(this->getFLValue(i), i, this->n_depots);
		i++;
	} while (i < this->getSize() && feasible == true);	
	
	return decodedSolution;
}

void FrogLeapSolution::setSolutionGenerationType(SolutionGenerationType v_sgt)
{
	this->sgt = v_sgt;
}

SolutionGenerationType FrogLeapSolution::getSolutionGenerationType()
{
	return this->sgt;
}

// inherited methods
void FrogLeapSolution::printFrogObj()
{
	printf("\nPrinting values of frog leaping solution \n");
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



