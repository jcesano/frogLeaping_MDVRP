#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Graph.h"
#include "DistanceTable.h"

Vehicle::Vehicle(short int id):FrogObject(id)
{
	customers = NULL;
	this->ptrGraph = NULL;
	size = 0;
	this->pathCost = 0;
}

Vehicle::Vehicle(short int id, Graph * g) :FrogObject(id)
{
	customers = NULL;
	this->ptrGraph = g;
	size = 0;
	this->pathCost = 0;
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

// abstract methods
void Vehicle::printFrogObj()
{
	short int depotIndex = this->getDepotIndex(), depotId;
	Pair * originPair, *destinationPair;
	int originIndex, originId, destinationIndex, destinationId;
	
	originId = this->ptrGraph->getDepotId(depotIndex);


	printf("Vehicle Id: %d with number of customers assigned = %d and path cost \n", this->getId(), this->customers->getSize(), this->getPathCost());

	
	if (this->customers->getSize() > 0)
	{
		printf("List of customers Ids (depot and customers): ");

		for (short int i = 0; i < this->customers->getSize(); i++)
		{
			Pair * customerPair = (Pair *) this->customers->getFrogObject(i);
			short int customerIndex = customerPair->get_i_IntValue();
			short int destinationId = this->ptrGraph->getCustomerId(customerIndex);

			printf("(%d - %d) = %d  ", originId, destinationId, this->ptrGraph->getDistanceTable()->getEdge(originId, destinationId));

			originId = destinationId;
		}

		// add the last edgde from the last customer to the depot
		destinationId = this->ptrGraph->getDepotId(depotIndex);
		printf("(%d - %d) = %d  \n", originId, destinationId, this->ptrGraph->getDistanceTable()->getEdge(originId, destinationId));
	}
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return false;
}
