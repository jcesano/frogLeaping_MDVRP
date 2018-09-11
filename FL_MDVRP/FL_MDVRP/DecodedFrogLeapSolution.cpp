#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include "Graph.h"
#include "FrogLeapController.h"

DecodedFrogLeapSolution::DecodedFrogLeapSolution(short int n_depots):FrogObject()
{
	this->vehicles = new FrogObjectCol * [n_depots];

	for (short int i = 0; i < n_depots; i++) {
		vehicles[i] = new FrogObjectCol();
	};

	this->ptrController = NULL;
	this->isFeasibleSolution = true;
	this->globalVehicleId = 0;
	this->numDepots = n_depots;
}

DecodedFrogLeapSolution::DecodedFrogLeapSolution(short int n_depots, FrogLeapController * controller) :FrogObject()
{
	this->vehicles = new FrogObjectCol *[n_depots];

	for (short int i = 0; i < n_depots; i++) {
		vehicles[i] = new FrogObjectCol();
	};

	this->ptrController = controller;
	this->isFeasibleSolution = true;
	this->globalVehicleId = 0;
	this->numDepots = n_depots;
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

void DecodedFrogLeapSolution::addVehicle(short int depotIndex, Vehicle * v)
{
	this->vehicles[depotIndex]->addFrogObject(v);
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

short int DecodedFrogLeapSolution::getGlobalVehicleId()
{
	short int result = this->globalVehicleId;

	this->globalVehicleId++;

	return result;
}

bool DecodedFrogLeapSolution::decodeFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots)
{
	bool result = true;
	short int vehicleId;
	short int depotIndex = this->decodeFrogLeapValue(fvalue, numberOfDepots);

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);
	int remainingDepotCapacity = this->ptrController->getDepotRemainingCapacityByIndex(depotIndex);

	if(customerDemand > VEHICLE_CAPACITY || customerDemand > remainingDepotCapacity)
	{
		result = false;
		return result;
	}

	//assing vehicle to customer	
	//get the element with maximum remaining capacity
	Vehicle * veh = (Vehicle *)this->vehicles[depotIndex]->getMaxValueFrogObject(); 

	if(veh == NULL)
	{
		vehicleId = this->getGlobalVehicleId();

		veh = new Vehicle(vehicleId, this->ptrController);
		
		veh->decRemainingCapacity(customerDemand);		
		
		//short int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);
				
		this->vehicles[depotIndex]->addFrogObject(veh);
	}
	else
	{
		int remainingVehicleCapacity = veh->getRemainingCapacity();
		if(customerDemand <= remainingVehicleCapacity)
		{
			veh->decRemainingCapacity(customerDemand);
		}
		else
		{
			vehicleId = this->getGlobalVehicleId();

			veh = new Vehicle(vehicleId, this->ptrController);

			veh->decRemainingCapacity(customerDemand);

			//short int depotIndex = vehicleId / numberOfDepots;
			veh->setDepotIndex(depotIndex);

			this->vehicles[depotIndex]->addFrogObject(veh);
		}
	}

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);

	//if((veh->getCapacity() >= veh->getDemand() + customerDemand) && (veh->getIsFeasible() == true))
	// assign customer to vehicle
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

	for(short int i; i < this->numDepots; i++)
	{
		for (int j = 0; j < this->vehicles[i]->getSize(); j++)
		{
			vehPtr = (Vehicle *)this->vehicles[i]->getFrogObject(j);
			newLocalCostFound += vehPtr->applyLocalSearch(controller);
		}
	}

	return newLocalCostFound;
}
