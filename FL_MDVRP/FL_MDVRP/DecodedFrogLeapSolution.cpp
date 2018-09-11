#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include "Graph.h"
#include "FrogLeapController.h"

DecodedFrogLeapSolution::DecodedFrogLeapSolution():FrogObject()
{
	this->vehicles = new FrogObjectCol();
	this->ptrController = NULL;
	this->isFeasibleSolution = true;
}

DecodedFrogLeapSolution::DecodedFrogLeapSolution(FrogLeapController * controller) :FrogObject()
{
	this->vehicles = new FrogObjectCol();
	this->ptrController = controller;
	this->isFeasibleSolution = true;
}

DecodedFrogLeapSolution::~DecodedFrogLeapSolution()
{
	printf("Destroying of DecodedFrogLeapSolution: Started \n");

	if(this->vehicles != NULL)
	{
		delete this->vehicles;
	}
	
	printf("Destroying of DecodedFrogLeapSolution: vehicles destroyed  \n");
	
	this->ptrController = NULL;	

	printf("Destroying of DecodedFrogLeapSolution: FINISHED \n");
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

short int DecodedFrogLeapSolution::decodeFixedFloatFrogLeapValue(float fvalue, short int numberOfDepots)
{
	short int result = floor(fvalue);

	if (result == numberOfDepots)
	{
		result--;
	};

	return result;
}

short int DecodedFrogLeapSolution::decodeFrogLeapValue(float fvalue, short int numberOfDepots)
{
	short int result = floor(fvalue);

	if (result == numberOfDepots)
	{
		result--;
	};

	return result;
}

bool DecodedFrogLeapSolution::decodeFloatFixedFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots, short int numberOfVehicles)
{
	bool result = true;

	short int vehicleId = this->decodeFrogLeapValue(fvalue, numberOfVehicles);

	Vehicle * veh = (Vehicle *)this->vehicles->getFrogObjectById(vehicleId);

	if (veh == NULL)
	{
		veh = new Vehicle(vehicleId, this->getGraph());
		short int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);

		this->vehicles->addFrogObject(veh);
	}

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);

	if ((veh->getCapacity() >= veh->getDemand() + customerDemand) && (veh->getIsFeasible() == true))
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
		int customerId = this->ptrController->getCustomerId(customerIndex);
		veh->setNotAddedCustomer(customerId);
	}

	return result;
}

bool DecodedFrogLeapSolution::decodeFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots)
{
	bool result = true;

	short int depotIndex = this->decodeFrogLeapValue(fvalue, numberOfDepots);

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);
	int remainingCapacity = this->ptrController->getDepotRemainingCapacityByIndex(depotIndex);

	if(customerDemand > VEHICLE_CAPACITY || customerDemand > remainingCapacity)
	{
		result = false;
		return result;
	}

	//assing vehicle to customer	
	Vehicle * veh = (Vehicle *)this->vehicles[depotIndex]->getFrogObject(0); //get the first element

	if(veh == NULL)
	{
		vehicleId = this->getVehicleId();

		veh = new Vehicle(vehicleId, this->ptrController);

		if(c)
		{

		}

		

		//short int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);

		this->vehicles->addFrogObject(veh);
	}

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);

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
		int customerId = this->ptrController->getCustomerId(customerIndex);
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

	printf("\n Showing DecodedFrogLeapSolution data results: ");
	if(this->isFeasibleSolution == true)
	{
		printf("Feasible \n");
	}
	else
	{
		printf("NOT FEASIBLE \n");
	}
	
	printf("Cantidad de vehículos: %d \n", numVehicles);

	for(short int i = 0; i < numVehicles; i++)
	{
		vehPtr = (Vehicle *)this->vehicles->getFrogObject(i);
		vehPtr->printFrogObj();
	}

	printf("DecodedFrogLeapSolution FINISHED \n");
}

bool DecodedFrogLeapSolution::isTheSame(FrogObject * fs)
{
	return (this == fs);
}

void DecodedFrogLeapSolution::setGraph(Graph * g)
{
	this->ptrController = g;
}

Graph * DecodedFrogLeapSolution::getGraph()
{
	return this->ptrController;
}

void DecodedFrogLeapSolution::setIsFeasibleSolution(bool v_isFeasible)
{
	this->isFeasibleSolution = v_isFeasible;
}

bool DecodedFrogLeapSolution::getIsFeasibleSolution()
{
	return this->isFeasibleSolution;
}

int DecodedFrogLeapSolution::applyLocalSearch(FrogLeapController * controller)
{
	Vehicle * vehPtr = NULL;

	int newLocalCostFound = 0;

	this->localSearchApplied = true;

	for (int i = 0; i < this->vehicles->getSize(); i++)
	{
		vehPtr = (Vehicle *)this->vehicles->getFrogObject(i);
		newLocalCostFound += vehPtr->applyLocalSearch(controller);
	}

	return newLocalCostFound;
}
