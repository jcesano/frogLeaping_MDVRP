#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Graph.h"
#include "DistanceTable.h"

Vehicle::Vehicle(short int id):FrogObject(id)
{
	customers = NULL;
	size = 0;
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
	DistanceTable * dt = g->getDistanceTable();

	originId = g->getDepotId(depotIndex);

	if(this->customers->getSize() > 0)
	{
		for(int i = 0; i < this->customers->getSize(); i++)
		{
			destinationPair = (Pair *) this->customers->getFrogObject(i);
			destinationIndex = destinationPair->get_i_IntValue();
			destinationId = g->getCustomerId(destinationIndex);

			vehiclePathResult = vehiclePathResult + dt->getEdge(originId, destinationId);

			originId = destinationId;
		}		
	}

	return vehiclePathResult;
}

// abstract methods
void Vehicle::printFrogObj()
{
	
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return false;
}
