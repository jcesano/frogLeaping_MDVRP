#include "stdafx.h"
#include "Vehicle.h"
#include "IndexList.h"

Vehicle::Vehicle()
{
	customers = NULL;
	size = 0;
}

void Vehicle::addCustomerId(short int customerId)
{
	if (this->customers == NULL)
	{
		this->customers = new IndexList;		
	}

	this->customers->addIndex(customerId);
}

// abstract methods
void Vehicle::printFrogObj()
{
	
}

bool Vehicle::isTheSame(FrogObject * fs)
{
	return false;
}
