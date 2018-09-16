#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Graph.h"
#include "DistanceTable.h"
#include "FrogObject.h"
#include "FeasibleSolution.h"
#include "FrogLeapController.h"

Vehicle::Vehicle(short int id):FrogObject(id)
{
	customers = NULL;
	this->ptrController = NULL;
	size = 0;
	this->pathCost = 0;
	this->capacity = VEHICLE_CAPACITY;
	this->setValue(this->capacity);
	this->isFeasible = true;  // used for testing purpose in printing information
	localSearchApplied = false;
}

Vehicle::Vehicle(short int id, FrogLeapController * controller) :FrogObject(id)
{
	customers = NULL;
	this->ptrController = controller;
	size = 0;
	this->pathCost = 0;
	this->capacity = VEHICLE_CAPACITY;
	this->setValue(this->capacity);
	this->remaining_capacity = VEHICLE_CAPACITY;
	this->isFeasible = true;  // used for testing purpose in printing information
	localSearchApplied = false;	
}

Vehicle::~Vehicle()
{
	if(this->customers != NULL)
	{
		delete this->customers;
	}
	
	this->ptrController = NULL;
}

void Vehicle::addCustomerPair(Pair * customerPair)
{
	if (this->customers == NULL)
	{
		this->customers = new FrogObjectCol();		
	}

	this->customers->addFrogObjectOrdered(customerPair);
}

void Vehicle::setDepotIndex(short int depot_v)
{
	this->depotIndex = depot_v;
}

short int Vehicle::getDepotIndex()
{
	return this->depotIndex;
}

void Vehicle::setDepotId(short int v_depotId)
{
	this->depotId = v_depotId;
}

short int Vehicle::getDepotId()
{
	return this->depotId;
}

int Vehicle::evalPath(FrogLeapController * controller)
{
	int vehiclePathResult = 0;

	short int depotIndex = this->getDepotIndex(), depotId;
	Pair * originPair, * destinationPair;
	int originIndex, originId, destinationIndex, destinationId;
	DistanceTable * dt = this->ptrController->getDistanceTable();

	originId = this->ptrController->getDepotId(depotIndex);

	if(this->customers->getSize() > 0)
	{
		for(int i = 0; i < this->customers->getSize(); i++)
		{
			destinationPair = (Pair *) this->customers->getFrogObject(i);
			destinationIndex = destinationPair->get_i_IntValue();
			destinationId = this->ptrController->getCustomerId(destinationIndex);

			vehiclePathResult = vehiclePathResult + dt->getEdge(originId, destinationId);

			originId = destinationId;
		}

		// add the last edgde from the last customer to the depot
		destinationId = this->ptrController->getDepotId(depotIndex);
		vehiclePathResult = vehiclePathResult + dt ->getEdge(originId, destinationId);
	}

	this->setPathCost(vehiclePathResult);

	return vehiclePathResult;
}

void Vehicle::setController(FrogLeapController * controller)
{
	this->ptrController = controller;
}

FrogLeapController * Vehicle::getController()
{
	return this->ptrController;
}

void Vehicle::setPathCost(int cost)
{
	this->pathCost = cost;
}

int Vehicle::getPathCost()
{
	return this->pathCost;
}

int Vehicle::getCapacity()
{
	return this->capacity;
}

int Vehicle::getRemainingCapacity()
{
	return this->remaining_capacity;
}

void Vehicle::decRemainingCapacity(int capacity_to_dec)
{
	this->remaining_capacity = this->remaining_capacity - capacity_to_dec;
	this->setValue(this->remaining_capacity);
}

int Vehicle::incDemand(int aditionalDemand)
{
	return this->demand += aditionalDemand;
}

int Vehicle::getDemand()
{
	return this->demand;
}

void Vehicle::setAsFeasible()
{
	this->isFeasible = true;
}

void Vehicle::setAsUnFeasible()
{
	this->isFeasible = false;
}

bool Vehicle::getIsFeasible()
{
	return this->isFeasible;
}

void Vehicle::setupLocalSearch()
{
	//NOT FINISHED
	short int n_customers = this->customers->getSize();

	this->vehicleCustomerArray = new short int [n_customers];

	for (int i = 0; i < n_customers; i++)
	{
		//obtaining the customerId (internal id) in the graph, from customer index (position) in customerList
		vehicleCustomerArray[i] = this->ObtainCustomerIdFromIndex(i);
	}

	//obtaining the depotId in the graph, from depot index (position)
	this->setDepotId(this->ObtainDepotIdFromIndex());	
}

short int Vehicle::ObtainDepotIdFromIndex()
{
	// Aux variable
	Pair * tmp = NULL;
	short int depotId, depotIndex;
	
	depotIndex = this->getDepotIndex(); //obtaining Pair(CustomerIndex, flValue)	
	depotId = this->ptrController->getDepotId(depotIndex); //obtaining the customerId in the graph

	return depotId;
}

short int Vehicle::ObtainCustomerIdFromIndex(short int position)
{
	// Aux variable
	Pair * tmp = NULL;
	short int customerId, customerIndex;

	tmp = (Pair *) this->customers->getFrogObject(position); //obtaining Pair(CustomerIndex, flValue)
	customerIndex = tmp->get_i_IntValue();
	customerId = this->ptrController->getCustomerId(customerIndex); //obtaining the customerId in the graph

	return customerId;
}

//return the new cost found or the previous value instead
int Vehicle::applyLocalSearch(FrogLeapController * controller)
{
	bool exitLocalSearch = false;
	bool improvementFound = false;
	int nextPathCost;

	if(this->localSearchApplied == false)
	{
		setupLocalSearch();		
		this->localSearchApplied = true;
	}

	// until we do not find any better solution we continue applying local search to each improvement solution found.
	while(!exitLocalSearch)
	{
		// we look for 100 local solutions. If we find an improvement then generateLocalSolutionsAndEvaluate = true to keep in the loop
		// and execute a new local search for new solutions from the last solution found
		improvementFound = generateLocalSolutionsAndEvaluate(controller);
		if (improvementFound == false)
		{
			exitLocalSearch = true;
		}		
	}

	return this->pathCost;
}

bool Vehicle::generateLocalSolutionsAndEvaluate(FrogLeapController * controller)
{
	FeasibleSolution * fs = new FeasibleSolution(this->customers->getSize(), this->vehicleCustomerArray);

	// generate a one distance permutation solutions, evaluate each one and stop when there is an improvement 
	// and update the best solution in the vehicle or stop when 100 different solutions where evaluated without any udpate.
	bool improvement = fs->searchOneSwapFeasibleSolutionsAndEval(this, controller);

	delete fs;

	return improvement;
}

void Vehicle::updateBestSolution(FeasibleSolution * fs, int cost)
{
	for(short int i=0; i < fs->getSize(); i++)
	{
		this->vehicleCustomerArray[i] = fs->getSolFactValue(i);
	}

	this->pathCost = cost;
}

// abstract methods
void Vehicle::printFrogObj()
{
	printf("\n SHOWING VEHICLE INFORMATION \n");
	if (this->getIsFeasible() == true)
	{
		printf(" Vehicle Id (feasible): %d with number of customers assigned = %d and path cost %d \n", this->getId(), this->customers->getSize(), this->getPathCost());
	}
	else 
	{
		printf(" Vehicle Id (NOT feasible): %d with number of customers assigned = %d \n", this->getId(), this->customers->getSize());
	}
	
	if (this->customers->getSize() > 0)
	{
		if(this->localSearchApplied == true)
		{
			printLocalSolution();
		}
		else
		{
			printGlobalSolution();
		}
	}
}

void Vehicle::printLocalSolution()
{
	short int depotIndex = this->getDepotIndex(), depotIddestinationId;
	Pair * originPair, *destinationPair;
	int originIndex, originId, destinationIndex, destinationId, originLabelId, destinationLabelId;

	originId = this->ptrController->getDepotId(depotIndex);
	originLabelId = this->ptrController->getLabel(originId);

	printf("\n SHOWING LOCAL SOLUTION \n");
	printf("		List of customers Ids (depot and customers): ");

	for (short int i = 0; i < this->customers->getSize(); i++)
	{
		destinationId = this->vehicleCustomerArray[i];
		destinationLabelId = this->ptrController->getLabel(destinationId);

		printf("(%d - %d) = %f  ", originLabelId, destinationLabelId, this->ptrController->getDistanceTable()->getEdge(originId, destinationId));

		originId = destinationId;
		originLabelId = this->ptrController->getLabel(originId);
	}

	// add the last edgde from the last customer to the depot
	destinationId = this->ptrController->getDepotId(depotIndex);
	destinationLabelId = this->ptrController->getLabel(destinationId);
	printf("(%d - %d) = %f  \n", originLabelId, destinationLabelId, this->ptrController->getDistanceTable()->getEdge(originId, destinationId));	
}

void Vehicle::printGlobalSolution()
{
	short int depotIndex = this->getDepotIndex(), depotId;
	Pair * originPair, *destinationPair;
	int originIndex, originId, destinationIndex, destinationId, originLabelId, destinationLabelId;

	originId = this->ptrController->getDepotId(depotIndex);
	originLabelId = this->ptrController->getLabel(originId);

	printf("\n SHOWING GLOBAL SOLUTION \n");
	printf("		List of customers Ids (depot and customers): ");

	for (short int i = 0; i < this->customers->getSize(); i++)
	{
		Pair * customerPair = (Pair *) this->customers->getFrogObject(i);
		short int customerIndex = customerPair->get_i_IntValue();
		destinationId = this->ptrController->getCustomerId(customerIndex);
		destinationLabelId = this->ptrController->getLabel(destinationId);
		printf("(%d - %d) = %d  ", originLabelId, destinationLabelId, this->ptrController->getDistanceTable()->getEdge(originId, destinationId));

		originId = destinationId;
		originLabelId = this->ptrController->getLabel(originId);
	}

	if (this->getIsFeasible() == true)
	{
		// add the last edgde from the last customer to the depot
		destinationId = this->ptrController->getDepotId(depotIndex);
		destinationLabelId = this->ptrController->getLabel(destinationId);
		printf("(%d - %d) = %d  \n", originLabelId, destinationLabelId, this->ptrController->getDistanceTable()->getEdge(originId, destinationId));
	}
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return (this == fs);
}
