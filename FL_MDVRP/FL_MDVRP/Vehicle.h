#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

#include "FrogObject.h"

class IndexList;

class Vehicle : public FrogObject
{
	private:
		IndexList * customers;
		short int size;

	public:
		Vehicle(short int id);

		void addCustomerId(short int customerId);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif