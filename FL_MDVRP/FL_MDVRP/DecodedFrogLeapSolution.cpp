#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

DecodedFrogLeapSolution::DecodedFrogLeapSolution():FrogObject()
{
	this->vehicles = new FrogObjectCol();

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

short int DecodedFrogLeapSolution::decodeFrogLeapItem(float fvalue)
{
	return floor(fvalue);
}

void DecodedFrogLeapSolution::addFrogLeapItem(float fvalue, short int customerId)
{
	short int vehicleId = this->decodeFrogLeapItem(fvalue);

	Vehicle * veh = (Vehicle *)this->vehicles->getFrogObjectById(vehicleId);

	if(veh == NULL)
	{
		Vehicle * veh = new Vehicle(vehicleId);

		this->vehicles->addFrogObject(veh);
	}

	veh->addCustomerId(customerId);
}

// abstract methods
void DecodedFrogLeapSolution::printFrogObj()
{

}

bool DecodedFrogLeapSolution::isTheSame(FrogObject * fs)
{
	return (this == fs);
}
