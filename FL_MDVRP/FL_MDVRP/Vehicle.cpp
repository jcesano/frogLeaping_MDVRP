#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"
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

int Vehicle::evalPath(DistanceTable * dt)
{
	int vehiclePathResult = 0;

	short int depotIndex = this->getDepotIndex();
	Pair * originPair, * destinationPair;
	int origin, destination;

	origin = depotIndex;

	if(this->customers->getSize() > 0)
	{
		for(int i = 1; i <= this->customers->getSize(); i++)
		{
			destinationPair = (Pair *) this->customers->getFrogObject(i);
			destination = destinationPair->get_i_IntValue();

			vehiclePathResult = vehiclePathResult + dt->getEdge(origin, destination);

			origin = destination;
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
