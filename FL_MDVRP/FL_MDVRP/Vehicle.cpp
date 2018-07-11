#include "stdafx.h"
#include "Vehicle.h"
#include "FrogObjectCol.h"
#include "Pair.h"

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

	this->customers->addFrogObject(customerPair);
}

void Vehicle::setDepotIndex(short int depot_v)
{
	this->depotIndex = depot_v;
}

short int Vehicle::getDepotIndex()
{
	return this->depotIndex;
}

// abstract methods
void Vehicle::printFrogObj()
{
	
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return false;
}
