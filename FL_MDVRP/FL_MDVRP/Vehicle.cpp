#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Graph.h"
#include "DistanceTable.h"
#include "FrogObject.h"

Vehicle::Vehicle(short int id):FrogObject(id)
{
	customers = NULL;
	this->ptrGraph = NULL;
	size = 0;
	this->pathCost = 0;
	this->capacity = VEHICLE_CAPACITY;
	this->isFeasible = true;  // used for testing purpose in printing information

}

Vehicle::Vehicle(short int id, Graph * g) :FrogObject(id)
{
	customers = NULL;
	this->ptrGraph = g;
	size = 0;
	this->pathCost = 0;
	this->capacity = VEHICLE_CAPACITY;
	this->isFeasible = true;  // used for testing purpose in printing information
}

Vehicle::~Vehicle()
{
	if(this->customers != NULL)
	{
		delete this->customers;
	}
	
	this->ptrGraph = NULL;
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

int Vehicle::evalPath(Graph * g)
{
	int vehiclePathResult = 0;

	short int depotIndex = this->getDepotIndex(), depotId;
	Pair * originPair, * destinationPair;
	int originIndex, originId, destinationIndex, destinationId;
	DistanceTable * dt = this->getGraph()->getDistanceTable();

	originId = this->getGraph()->getDepotId(depotIndex);

	if(this->customers->getSize() > 0)
	{
		for(int i = 0; i < this->customers->getSize(); i++)
		{
			destinationPair = (Pair *) this->customers->getFrogObject(i);
			destinationIndex = destinationPair->get_i_IntValue();
			destinationId = this->getGraph()->getCustomerId(destinationIndex);

			vehiclePathResult = vehiclePathResult + dt->getEdge(originId, destinationId);

			originId = destinationId;
		}

		// add the last edgde from the last customer to the depot
		destinationId = this->getGraph()->getDepotId(depotIndex);
		vehiclePathResult = vehiclePathResult + dt ->getEdge(originId, destinationId);
	}

	this->setPathCost(vehiclePathResult);

	return vehiclePathResult;
}

void Vehicle::setGraph(Graph * g)
{
	this->ptrGraph = g;
}

Graph * Vehicle::getGraph()
{
	return this->ptrGraph;
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

short int Vehicle::getNotAddedCustomer()
{
	return this->notAddedCustomer;
}

void Vehicle::setNotAddedCustomer(short int customerId)
{
	this->notAddedCustomer = customerId;
}

// abstract methods
void Vehicle::printFrogObj()
{
	short int depotIndex = this->getDepotIndex(), depotId;
	Pair * originPair, *destinationPair;
	int originIndex, originId, destinationIndex, destinationId;
	
	originId = this->ptrGraph->getDepotId(depotIndex);


	if (this->getIsFeasible() == true)
	{
		printf("		Vehicle Id (feasible): %d with number of customers assigned = %d and path cost %d\n", this->getId(), this->customers->getSize(), this->getPathCost());
	}
	else 
	{
		printf("		Vehicle Id (NOT feasible): %d with number of customers assigned = %d, not added CustId %d and total demand is %d\n", this->getId(), this->customers->getSize(), this->getNotAddedCustomer(), this->getDemand());
	}
	
	if (this->customers->getSize() > 0)
	{
		printf("		List of customers Ids (depot and customers): ");

		for (short int i = 0; i < this->customers->getSize(); i++)
		{
			Pair * customerPair = (Pair *) this->customers->getFrogObject(i);
			short int customerIndex = customerPair->get_i_IntValue();
			short int destinationId = this->ptrGraph->getCustomerId(customerIndex);

			printf("(%d - %d) = %d  ", originId, destinationId, this->ptrGraph->getDistanceTable()->getEdge(originId, destinationId));

			originId = destinationId;
		}

		if(this->getIsFeasible() == true)
		{
			// add the last edgde from the last customer to the depot
			destinationId = this->ptrGraph->getDepotId(depotIndex);
			printf("(%d - %d) = %d  \n", originId, destinationId, this->ptrGraph->getDistanceTable()->getEdge(originId, destinationId));
		}
	}
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return false;
}
