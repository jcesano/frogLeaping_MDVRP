#include "stdafx.h"
#include "FrogLeapSolution.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogLeapController.h"
#include "Vehicle.h"
#include "Graph.h"
#include "FrogObjectCol.h"
#include "FrogObject.h"
#include "Pair.h"
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

bool FrogLeapSolution::genRandomSolution(FrogLeapController * controller)
{
	float u;
	int a = this->size;	
	FrogObjectCol * feasibleDepotList = NULL;
	
	// reset all remaining capacities of depots and return them in a new list
	feasibleDepotList = initializeFeasibleDepotList(controller);
	bool result = true;
	int i = 0;
	
	while ((i < this->size) && (result == true))
	{
		u = assignRandomFeasibleDepot(feasibleDepotList, controller, i);

		// code to eliminate fixed random assignment of customers to depots
		//u = this->normalRandomAssigment(controller);

		//this->values[i] = u;

		if(u > 0)
		{
			this->values[i] = u;
		}
		else
		{
			result = false;			
		}

		i++;
	};

	feasibleDepotList->unReferenceFrogObjectCol();
	delete feasibleDepotList;
	feasibleDepotList = NULL;

	return result;
}

bool FrogLeapSolution::genRandomSolution2(FrogLeapController * controller)
{
	float u;
	int a = this->size;
			
	bool result = true;
	int i = 0;

	controller->resetDepotRemainingCapacities();

	while ((i < this->size) && (result == true))
	{
		u = assignRandomFeasibleDepot2(controller, i);

		// code to eliminate fixed random assignment of customers to depots
		//u = this->normalRandomAssigment(controller);

		//this->values[i] = u;

		if (u > 0)
		{
			this->values[i] = u;
		}
		else
		{
			result = false;
		}

		i++;
	};

	return result;
}

bool FrogLeapSolution::genRandomSolution3(FrogLeapController * controller)
{
	float u;
	int a = this->size;

	bool result = true;
	int i = 0;

	controller->resetDepotRemainingCapacities();

	FrogObjectCol * localDepotCol = controller->createDepotListOrderedByCapacity();

	while ((i < this->size) && (result == true))
	{
		u = assignRandomFeasibleDepot3(controller, localDepotCol, i);

		// code to eliminate fixed random assignment of customers to depots
		//u = this->normalRandomAssigment(controller);

		//this->values[i] = u;

		if (u >= 0)
		{
			this->values[i] = u;
		}
		else
		{
			result = false;
		}

		i++;
	};

	localDepotCol->unReferenceFrogObjectCol();
	delete localDepotCol;
	return result;
}

float FrogLeapSolution::normalRandomAssigment(FrogLeapController * controller)
{	
	float depotsNum = controller->getNumberOfDepots();
	float u = this->genRandomFloatingNumber(0, depotsNum);

	if ( u >= depotsNum)
	{
		u = u - 1;		
	}

	return u;
}

float FrogLeapSolution::assignRandomFeasibleDepot(FrogObjectCol * feasibleDepotList, FrogLeapController * controller, int customerIndex)
{	
	float u = -1;	
	
	FrogObjectCol * deletedFrogObjects = new FrogObjectCol();

	// obtain the customer demand to check the set of candidate depots
	int customerDemand = controller->getCustomerDemandByIndex(customerIndex);

	// eliminate all depots that have remainingCapacity lower than demand of the customer
	feasibleDepotList->removeAllLowerValueFrogObject(customerDemand, deletedFrogObjects);

	if (feasibleDepotList->getSize() > 0)
	{
		// select a random depot between the set of candidate depots
		int size = feasibleDepotList->getSize();
		u = this->genRandomFloatingNumber(0, size);
		int position = floor(u);
		if(position == size)
		{
			position--;
		}
		
		Pair * depotPair = (Pair *)feasibleDepotList->getFrogObject(position);

		//update remaining capacity of depot pair
		int newCapacity = depotPair->get_j_IntValue() - customerDemand;
		depotPair->set_j_IntValue(newCapacity);
		depotPair->setValue(newCapacity);

		int depotInternalId = depotPair->getId();
		int depotArrayIndex = controller->getDepotListIndexByInternal(depotInternalId);

		// This is to give a priority to establish the order in which the depot give the service to customers
		u = depotArrayIndex + this->genRandomFloatingNumber(0, 1);
		if (u >= depotArrayIndex + 1)
		{
			u = depotArrayIndex;
		}
	}

	if(deletedFrogObjects->getSize() > 0)
	{
		feasibleDepotList->addAllFrogObjects(deletedFrogObjects);
	}
	
	deletedFrogObjects->unReferenceFrogObjectCol();
	delete deletedFrogObjects;
	deletedFrogObjects = NULL;
	return  u;
}

float FrogLeapSolution::assignRandomFeasibleDepot2(FrogLeapController * controller, int customerIndex)
{	
	float u = -1, result = -1;
	
	int customerDemand = 0;

	int numberOfDepots = controller->getNumberOfDepots();

	u = this->genRandomFloatingNumber(0, numberOfDepots);
	
	if (u >= numberOfDepots) 
	{
		u = u - 1;
	}

	int position = floor(u);

	int depotRemainingCap = 0;

	int itCounter = 0;
	bool customerAllocated = false;
	Pair * depotPair = NULL;

	customerDemand = controller->getCustomerDemandByIndex(customerIndex);

	while(itCounter < numberOfDepots && customerAllocated == false)
	{
		depotRemainingCap = controller->getDepotRemainingCapacityByIndex(position);

		if (customerDemand <= depotRemainingCap)
		{
			customerAllocated = true;

			depotPair = (Pair *)controller->getDepotPairByIndex(position);

			//update remaining capacity of depot pair
			int newCapacity = depotPair->get_j_IntValue() - customerDemand;
			depotPair->set_j_IntValue(newCapacity);
			depotPair->setValue(newCapacity);

			result = position + this->genRandomFloatingNumber(0, 1);

			if (result >= position + 1)
			{
				result = position;
			}
		}
		else
		{
			position++;
			if(position == numberOfDepots)
			{
				position = 0;
			}
		}

		itCounter++;
	}

	depotPair = NULL;
	return  result;
}

float FrogLeapSolution::assignRandomFeasibleDepot3(FrogLeapController * controller, FrogObjectCol * localDepotCol, int customerIndex)
{
	float u = -1, result = -1;
	Pair * depotPairSelected = NULL;
	int lowBoundIndex = -1;

	// get the customer demand
	int customerDemand = controller->getCustomerDemandByIndex(customerIndex);

	// get the index of the first depot with capacity enough to attend customer demand
	localDepotCol->getFirstUpperValueFrogObjectIndex(customerDemand, lowBoundIndex);

	// if there is not any depot then return -1
	if(lowBoundIndex == -1)
	{
		return result;
	}

	// choose between the available depots with suffiecient capacity to attend the customer demand
	int numberOfDepots = controller->getNumberOfDepots();

	do
	{
		u = this->genRandomFloatingNumber(lowBoundIndex, numberOfDepots);
	} while (u >= numberOfDepots);

	int positionSelected = floor(u);

	// get the depotPair selected in the list of available depots
	depotPairSelected = (Pair *)localDepotCol->getFrogObject(positionSelected);
		
	//update remaining capacity of depot pair
	int depotRemainingCap = depotPairSelected->get_j_IntValue();		
	int newCapacity = depotRemainingCap - customerDemand;
	depotPairSelected->set_j_IntValue(newCapacity);
	depotPairSelected->setValue(newCapacity);

	localDepotCol->reorderFrogObject(depotPairSelected);

	// get the depot index in the controller of the selected depot
	int depotId = depotPairSelected->getId();
	int depotIndex = controller->getDepotListIndexByInternal(depotId);

	// assign a random number to the depot selected
	float randnum;

	do
	{
		randnum = this->genRandomFloatingNumber(0, 1);
	} while (randnum >= 1);

	result = depotIndex + randnum;

	return  result;
}

FrogObjectCol * FrogLeapSolution::initializeFeasibleDepotList(FrogLeapController *controller)
{
	Pair * depotPair = NULL;
	FrogObjectCol * feasibleDepotList = new FrogObjectCol();
	int depotNum = controller->getNumberOfDepots();

	controller->resetDepotRemainingCapacities();

	for (int i = 0; i < depotNum; i++)
	{
		depotPair = controller->getDepotPairByIndex(i);
		feasibleDepotList->AddLastFrogObject(depotPair);
		depotPair = NULL;
	}

	return feasibleDepotList;
}

DecodedFrogLeapSolution * FrogLeapSolution::decodeSolution(FrogLeapController * controller)
{
	controller->resetDepotRemainingCapacities();
	return this->decodeFrogLeapSolution(controller);
}

//if generated instance of DecodedFrogLeapSolution is NULL then solution is not valid due to a vehicle capacity violation
// This algorithm uses an int distance table
DecodedFrogLeapSolution * FrogLeapSolution::decodeFrogLeapSolution(FrogLeapController * controller)
{
	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(this->n_depots, controller);
	
	int i = 0;
	bool feasible = true;

	do 
	{
 		feasible = decodedSolution->decodeFrogLeapItem(controller, this->getFLValue(i), i, this->n_depots);
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
		printf("%.4f \n ", this->values[i]);
	}

	//printing the last element (replacing the comma by the point)
	printf("%.4f. \n", this->values[this->getSize() - 1]);	
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



