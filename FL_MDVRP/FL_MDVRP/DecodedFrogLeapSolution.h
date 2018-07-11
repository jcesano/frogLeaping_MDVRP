#ifndef DECODEDFROGLEAPSOLUTION_H_   /* Include guard */
#define DECODEDFROGLEAPSOLUTION_H_

#include "FrogObject.h"

class FrogObjectCol;
class Vehicle;

class DecodedFrogLeapSolution : public FrogObject
{
	private:
		FrogObjectCol * vehicles;
	
	public:

		DecodedFrogLeapSolution();

		void addVehicle(Vehicle * v);

		//Vehicle * getVehicle(short int pos);

		short int decodeFrogLeapValue(float fvalue);

		void decodeFrogLeapItem(float fvalue, short int customerId, short int numberOfDepots);		

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif