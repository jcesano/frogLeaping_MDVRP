#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include "Graph.h"
#include "FrogLeapController.h"


DecodedFrogLeapSolution::DecodedFrogLeapSolution(int n_depots):FrogObject()
{
	//this->vehicles = new FrogObjectCol();
	this->vehicles = new FrogObjectCol * [n_depots];

	for (int i = 0; i < n_depots; i++) {
		vehicles[i] = new FrogObjectCol();
	};	

	this->ptrController = NULL;
	this->isFeasibleSolution = true;	
	this->numDepots = n_depots;
}

DecodedFrogLeapSolution::DecodedFrogLeapSolution(int n_depots, FrogLeapController * controller) :FrogObject()
{
	//this->vehicles = new FrogObjectCol();
	this->vehicles = new FrogObjectCol *[n_depots];

	for (int i = 0; i < n_depots; i++) {
		vehicles[i] = new FrogObjectCol();
	};

	this->ptrController = controller;
	this->isFeasibleSolution = true;	
	this->numDepots = n_depots;
}


DecodedFrogLeapSolution::~DecodedFrogLeapSolution()
{
	//printf("Destroying of DecodedFrogLeapSolution: Started \n");

	int nDepots = this->ptrController->getNumberOfDepots();

	if(this->vehicles != NULL)
	{
		//for (int i = 0; i < nDepots; i++)
		//{
		//	delete this->vehicles[i];
		//}
		
		this->deleteArrayOfFrogObjectCols(this->vehicles, nDepots);		
		delete [] vehicles;
	}
	
	this->vehicles = NULL;
	//printf("Destroying of DecodedFrogLeapSolution: vehicles destroyed  \n");

	this->ptrController = NULL;		

	//printf("Destroying of DecodedFrogLeapSolution: FINISHED \n");
}

void DecodedFrogLeapSolution::deleteArrayOfFrogObjectCols(FrogObjectCol ** arrayPtr, int v_size)
{
	int size = v_size;

	for (int i = 0; i < size; i++)
	{
		delete arrayPtr[i];
		arrayPtr[i] = NULL;
	}	
}

void DecodedFrogLeapSolution::addVehicle(int depotIndex, Vehicle * v_vehicle)
{
	//this->vehicles->addFrogObject(v_vehicle);
	this->vehicles[depotIndex]->addFrogObject(v_vehicle);	
}

/*
void DecodedFrogLeapSolution::addVehicle(Vehicle * vehicle)
{
	vehicles->addFrogObject(vehicle);
}


Vehicle * DecodedFrogLeapSolution::getVehicle(int pos)
{
	return NULL;

	//return (Vehicle *) this->vehicles->getFrogObject(pos);
}
*/

int DecodedFrogLeapSolution::decodeFixedFloatFrogLeapValue(float fvalue, int numberOfDepots)
{
	int result = floor(fvalue);

	if (result == numberOfDepots)
	{
		result--;
	};

	return result;
}

int DecodedFrogLeapSolution::decodeFrogLeapValue(float fvalue, int numberOfDepots)
{
	int result = floor(fvalue);

	if (result == numberOfDepots)
	{
		result--;
	};

	return result;
}

bool DecodedFrogLeapSolution::decodeFrogLeapItem(FrogLeapController * controller, float fvalue, int customerIndex, int numberOfDepots)
{
	bool result = true;
	int vehicleId;
	int depotIndex = this->decodeFrogLeapValue(fvalue, numberOfDepots);

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);
	int remainingDepotCapacity = this->ptrController->getDepotRemainingCapacityByIndex(depotIndex);
	int customerId = this->ptrController->getCustomerInternalId(customerIndex);

	if(customerDemand > controller->getVehicleCapacity() || customerDemand > remainingDepotCapacity)
	{
		this->setIsFeasibleSolution(false);
		this->setNotAddedCustomer(customerId);
		result = false;
		return result;
	}

	this->ptrController->decRemainingDepotCapacity(depotIndex, customerDemand);

	//assign vehicle to customer	
	//get the element with minimum remaining capacity enough
	Vehicle * veh = (Vehicle *)this->vehicles[depotIndex]->getFirstUpperValueFrogObject(customerDemand); 
	//Vehicle * veh = (Vehicle *)this->getFirstUpperValueVehicle(customerDemand, depotIndex);
	
	if(veh == NULL)
	{
		vehicleId = controller->getGlobalVehicleId();

 		veh = new Vehicle(vehicleId, this->ptrController);
		
		veh->decRemainingCapacity(customerDemand);				

		//int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);
				
		this->vehicles[depotIndex]->addFrogObjectOrdered(veh);		
	}
	else
	{
		veh->decRemainingCapacity(customerDemand);

		//this->vehicles[depotIndex]->reorderFrogObject(veh);
		this->vehicles[depotIndex]->reorderFrogObject(veh);		
	}

	Pair * customerPair = new Pair(PairType::IntVsFloat);
	customerPair->set_i_IntValue(customerIndex);
	customerPair->set_j_FloatValue(fvalue);
	customerPair->setValue(fvalue);
	customerPair->setId(customerIndex);

	veh->addCustomerPair(customerPair);	

	customerPair = NULL;
	veh = NULL;
	return result;
}

bool DecodedFrogLeapSolution::decodeFrogLeapItemWithAngularCriteria(FrogLeapController * controller, float fvalue, int customerIndex, int numberOfDepots)
{
	bool result = true;
	int vehicleId;
	int depotIndex = this->decodeFrogLeapValue(fvalue, numberOfDepots);

	int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);
	int remainingDepotCapacity = this->ptrController->getDepotRemainingCapacityByIndex(depotIndex);
	int customerId = this->ptrController->getCustomerInternalId(customerIndex);

	if (customerDemand > controller->getVehicleCapacity() || customerDemand > remainingDepotCapacity)
	{
		this->setIsFeasibleSolution(false);
		this->setNotAddedCustomer(customerId);
		result = false;
		return result;
	}

	this->ptrController->decRemainingDepotCapacity(depotIndex, customerDemand);

	//assign vehicle to customer	
	//get the element with minimum remaining capacity enough
	Vehicle * veh = (Vehicle *)this->vehicles[depotIndex]->getFirstUpperValueFrogObject(customerDemand);
	//Vehicle * veh = (Vehicle *)this->getFirstUpperValueVehicle(customerDemand, depotIndex);

	if (veh == NULL)
	{
		vehicleId = controller->getGlobalVehicleId();

		veh = new Vehicle(vehicleId, this->ptrController);

		veh->decRemainingCapacity(customerDemand);

		//int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);

		this->vehicles[depotIndex]->addFrogObjectOrdered(veh);
	}
	else
	{
		veh->decRemainingCapacity(customerDemand);

		//this->vehicles[depotIndex]->reorderFrogObject(veh);
		this->vehicles[depotIndex]->reorderFrogObject(veh);
	}

	Pair * veh_customerPair = new Pair(PairType::IntVsFloat);
	veh_customerPair->set_i_IntValue(customerIndex);
	veh_customerPair->set_j_FloatValue(fvalue);

	// we calculate angular values
	Pair * customerPair = controller->getCustomerPairByIndex(customerIndex);
	int customerInternalId = controller->getCustomerInternalId(customerIndex);
	
	Pair * depotPair = controller->getDepotPairByIndex(depotIndex);
	int depotInternalId = controller->getDepotInternalId(depotIndex);

	controller->setAngularValues(veh_customerPair, customerInternalId, depotInternalId);	
	
	veh_customerPair->setId(customerIndex);

	veh->addCustomerPairDoubleOrdered(veh_customerPair);

	veh_customerPair = NULL;
	veh = NULL;
	return result;
}

//bool DecodedFrogLeapSolution::decodeFrogLeapAssignCustomerToDepotWithAngularValues(FrogLeapController * controller, float fvalue, int customerIndex, int numberOfDepots)
//{
	//bool result = true;
	//int vehicleId;
	//int depotIndex = this->decodeFrogLeapValue(fvalue, numberOfDepots);

	//int customerDemand = this->ptrController->getCustomerDemandByIndex(customerIndex);
	//int remainingDepotCapacity = this->ptrController->getDepotRemainingCapacityByIndex(depotIndex);
	//int customerId = this->ptrController->getCustomerId(customerIndex);

	//if (customerDemand > controller->getVehicleCapacity() || customerDemand > remainingDepotCapacity)
	//{
	//	this->setIsFeasibleSolution(false);
	//	this->setNotAddedCustomer(customerId);
	//	result = false;
	//	return result;
	//}

	//this->ptrController->decRemainingDepotCapacity(depotIndex, customerDemand);

	//// calculate the angular value of the customer
	//Pair customerAssign = (Pair *) this->calculateAngularValue(customerIndex, depotIndex, controller)



	////assign vehicle to customer	
	////get the element with maximum remaining capacity
	//Vehicle * veh = (Vehicle *)this->vehicles[depotIndex]->getFirstUpperValueFrogObject(customerDemand);
	////Vehicle * veh = (Vehicle *)this->getFirstUpperValueVehicle(customerDemand, depotIndex);

	//if (veh == NULL)
	//{
	//	vehicleId = controller->getGlobalVehicleId();

	//	veh = new Vehicle(vehicleId, this->ptrController);

	//	veh->decRemainingCapacity(customerDemand);

	//	//int depotIndex = vehicleId / numberOfDepots;
	//	veh->setDepotIndex(depotIndex);

	//	this->vehicles[depotIndex]->addFrogObjectOrdered(veh);
	//}
	//else
	//{
	//	veh->decRemainingCapacity(customerDemand);

	//	//this->vehicles[depotIndex]->reorderFrogObject(veh);
	//	this->vehicles[depotIndex]->reorderFrogObject(veh);
	//}

	//Pair * customerPair = new Pair(PairType::IntVsFloat);
	//customerPair->set_i_IntValue(customerIndex);
	//customerPair->set_j_FloatValue(fvalue);
	//customerPair->setValue(fvalue);
	//customerPair->setId(customerIndex);

	//veh->addCustomerPair(customerPair);

	//customerPair = NULL;
	//veh = NULL;
	//return result;
//}

float DecodedFrogLeapSolution::evalSolution()
{
	Vehicle * vehPtr = NULL;
	float result = 0;

	for(int i = 0; i < this->numDepots; i++)
	{
		for (int j = 0; j < this->vehicles[i]->getSize(); j++)
		{
			vehPtr = (Vehicle *)this->vehicles[i]->getFrogObject(j);
			result = result + vehPtr->evalPath(this->ptrController);
		}
	}

	//for (int j = 0; j < this->vehicles->getSize(); j++)
	//{
	//	vehPtr = (Vehicle *)this->vehicles->getFrogObject(j);
	//	result = result + vehPtr->evalPath(this->ptrController);
	//}	

	return result;
}

// abstract methods
void DecodedFrogLeapSolution::printFrogObj()
{
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
	
	printf("Vehículos por depósito\n");
	for(int i=0; i < this->numDepots; i++)
	{
		printf("Depósito: %d \n", i);

		int numVehicles_i = this->vehicles[i]->getSize();
		
		printf("Cantidad de vehículos: %d \n", numVehicles_i);

		for (int j = 0; j < numVehicles_i; j++)
		{
			vehPtr = (Vehicle *)this->vehicles[i]->getFrogObject(j);			
			vehPtr->printFrogObj();
		}
	}

	printf("DecodedFrogLeapSolution FINISHED \n");
}

bool DecodedFrogLeapSolution::isTheSame(FrogObject * fs)
{
	return (this == fs);
}

void DecodedFrogLeapSolution::setController(FrogLeapController * controller)
{
	this->ptrController = controller;
}

FrogLeapController * DecodedFrogLeapSolution::getController()
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

float DecodedFrogLeapSolution::applyLocalSearch(FrogLeapController * controller)
{
	Vehicle * vehPtr = NULL;

	float newLocalCostFound = 0;

	this->localSearchApplied = true;

	for(int i = 0; i < this->numDepots; i++)
	{
		for (int j = 0; j < this->vehicles[i]->getSize(); j++)
		{
			vehPtr = (Vehicle *)this->vehicles[i]->getFrogObject(j);
			newLocalCostFound += vehPtr->applyLocalSearch(controller);
		}
	}

	//for (int j = 0; j < this->vehicles->getSize(); j++)
	//{
	//	vehPtr = (Vehicle *)this->vehicles->getFrogObject(j);
	//	newLocalCostFound += vehPtr->applyLocalSearch(controller);
	//}

	return newLocalCostFound;
}

int DecodedFrogLeapSolution::getNotAddedCustomer()
{
	return this->notAddedCustomer;
}

void DecodedFrogLeapSolution::setNotAddedCustomer(int customerId)
{
	this->notAddedCustomer = customerId;
}

Vehicle * DecodedFrogLeapSolution::getFirstUpperValueVehicle(int customerDemand, int depotIndex)
{
	Vehicle * cur_veh = NULL, * result_veh = NULL;
	int size = this->vehicles[depotIndex]->getSize();
	int i = 0;
	bool found = false;

	while (i < size && found == false)
	{
		cur_veh = (Vehicle *)this->vehicles[depotIndex]->getFrogObject(i);

		if(cur_veh->getDepotIndex() == depotIndex)		
		{
			result_veh = cur_veh;
			found = true;
		}
		else
		{
			i++;
		}		
	}

	return result_veh;
}

void DecodedFrogLeapSolution::adjustVehicleRoutes(FrogLeapController * controller)
{
	for(int i = 0; i < controller->getNumberOfDepots(); i++)
	{
		this->adjustDepotVehicleRoutes(this->vehicles[i], controller);
	}	
}

void DecodedFrogLeapSolution::adjustDepotVehicleRoutes(FrogObjectCol * vehicleList, FrogLeapController * controller)
{
	Vehicle * currentVehicle = NULL;
	int size = vehicleList->getSize();

	for(int i = 0; i < size; i++)
	{
		currentVehicle = (Vehicle *)vehicleList->getFrogObject(i);

		currentVehicle->adjustCustomerRoute(controller);
	}
}

//Pair * DecodedFrogLeapSolution::calculateAngularValue(int customerIndex, int depotIndex, FrogLeapController * controller)
//{
//	return nullptr;
//}
