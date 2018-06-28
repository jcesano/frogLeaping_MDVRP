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

		//void addVehicle();

		//Vehicle * getVehicle(short int pos);

		short int decodeFrogLeapItem(float fvalue);

		void addFrogLeapItem(float fvalue, short int customerId);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif