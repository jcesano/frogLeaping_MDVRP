#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include "Graph.h"

DecodedFrogLeapSolution::DecodedFrogLeapSolution():FrogObject()
{
	this->vehicles = new FrogObjectCol();
	this->ptrG = NULL;
	this->isFeasibleSolution = true;
}

DecodedFrogLeapSolution::DecodedFrogLeapSolution(Graph * g) :FrogObject()
{
	this->vehicles = new FrogObjectCol();
	this->ptrG = g;
	this->isFeasibleSolution = true;
}

DecodedFrogLeapSolution::~DecodedFrogLeapSolution()
{
	delete this->vehicles;
	delete this->ptrG;
}

void DecodedFrogLeapSolution::addVehicle(Vehicle * v)
{
	this->vehicles->addFrogObject(v);
}


/*
void DecodedFrogLeapSolution::addVehicle(Vehicle * vehicle)
{
	vehicles->addFrogObject(vehicle);
}


Vehicle * DecodedFrogLeapSolution::getVehicle(short int pos)
{
	return NULL;

	//return (Vehicle *) this->vehicles->getFrogObject(pos);
}
*/

short int DecodedFrogLeapSolution::decodeFrogLeapValue(float fvalue, short int numberOfVehicles)
{
	short int result = floor(fvalue);

	if (result == numberOfVehicles)
	{
		result--;
	};

	return result;
}

bool DecodedFrogLeapSolution::decodeFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots, short int numberOfVehicles)
{
	bool result = true;

	short int vehicleId = this->decodeFrogLeapValue(fvalue, numberOfVehicles);

	Vehicle * veh = (Vehicle *)this->vehicles->getFrogObjectById(vehicleId);

	if(veh == NULL)
	{
		veh = new Vehicle(vehicleId, this->getGraph());
		short int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);

		this->vehicles->addFrogObject(veh);
	}

	int customerDemand = this->ptrG->getCustomerDemandByIndex(customerIndex);

	if((veh->getCapacity() >= veh->getDemand() + customerDemand) && (veh->getIsFeasible() == true))
	{
		veh->incDemand(customerDemand);
		
		Pair * customerPair = new Pair(PairType::IntVsFloat);
		customerPair->set_i_IntValue(customerIndex);
		customerPair->set_j_FloatValue(fvalue);
		customerPair->setValue(fvalue);
		customerPair->setId(customerIndex);

		veh->addCustomerPair(customerPair);
	}
	else
	{
		result = false;
		veh->incDemand(customerDemand);
		veh->setAsUnFeasible();
		this->setIsFeasibleSolution(false);
		int customerId = this->ptrG->getCustomerId(customerIndex);
		veh->setNotAddedCustomer(customerId);

	}

	return result;
}

int DecodedFrogLeapSolution::evalSolution()
{
	Vehicle * vehPtr = NULL;
	int result = 0;

	for(int i = 0; i < this->vehicles->getSize(); i++)
	{
		vehPtr = (Vehicle *)this->vehicles->getFrogObject(i);
		result = result + vehPtr->evalPath(this->getGraph());
	}

	return result;
}

// abstract methods
void DecodedFrogLeapSolution::printFrogObj()
{
	short int numVehicles = this->vehicles->getSize();
	Vehicle * vehPtr;

	printf("Cantidad de vehículos: %d \n", numVehicles);

	for(short int i = 0; i < numVehicles; i++)
	{
		vehPtr = (Vehicle *)this->vehicles->getFrogObject(i);
		vehPtr->printFrogObj();
	}
}

bool DecodedFrogLeapSolution::isTheSame(FrogObject * fs)
{
	return (this == fs);
}

void DecodedFrogLeapSolution::setGraph(Graph * g)
{
	this->ptrG = g;
}

Graph * DecodedFrogLeapSolution::getGraph()
{
	return this->ptrG;
}

void DecodedFrogLeapSolution::setIsFeasibleSolution(bool v_isFeasible)
{
	this->isFeasibleSolution = v_isFeasible;
}

bool DecodedFrogLeapSolution::getIsFeasibleSolution()
{
	return this->isFeasibleSolution;
}
