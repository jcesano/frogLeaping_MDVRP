#include "stdafx.h"
#include "DecodedFrogLeapSolution.h"
#include "FrogObjectCol.h"
#include "Pair.h"
#include "Vehicle.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

DecodedFrogLeapSolution::DecodedFrogLeapSolution():FrogObject()
{
	this->vehicles = new FrogObjectCol();

}

void DecodedFrogLeapSolution::addVehicle(Vehicle * v)
{
	this->vehicles->addFrogObject(v);
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

short int DecodedFrogLeapSolution::decodeFrogLeapValue(float fvalue, short int numberOfVehicles)
{
	short int result = floor(fvalue);

	if (result == numberOfVehicles)
	{
		result--;
	};

	return result;
}

void DecodedFrogLeapSolution::decodeFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots, short int numberOfVehicles)
{
	short int vehicleId = this->decodeFrogLeapValue(fvalue, numberOfVehicles);

	Vehicle * veh = (Vehicle *)this->vehicles->getFrogObjectById(vehicleId);

	if(veh == NULL)
	{
		veh = new Vehicle(vehicleId);
		short int depotIndex = vehicleId / numberOfDepots;
		veh->setDepotIndex(depotIndex);

		this->vehicles->addFrogObject(veh);
	}

	Pair * customerPair = new Pair(PairType::IntVsFloat);
	customerPair->set_i_IntValue(customerIndex);
	customerPair->set_j_FloatValue(fvalue);
	customerPair->setValue(fvalue);
	customerPair->setId(customerIndex);

	veh->addCustomerPair(customerPair);
}

int DecodedFrogLeapSolution::evalSolution(Graph * g)
{
	Vehicle * vehPtr = NULL;
	int result = 0;

	for(int i = 0; i < this->vehicles->getSize(); i++)
	{
		vehPtr = (Vehicle *)this->vehicles->getFrogObject(i);
		result = result + vehPtr->evalPath(g);
	}

	return result;
}

// abstract methods
void DecodedFrogLeapSolution::printFrogObj()
{

}

bool DecodedFrogLeapSolution::isTheSame(FrogObject * fs)
{
	return (this == fs);
}
