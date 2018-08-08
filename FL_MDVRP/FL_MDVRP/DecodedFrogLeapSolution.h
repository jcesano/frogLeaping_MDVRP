#ifndef DECODEDFROGLEAPSOLUTION_H_   /* Include guard */
#define DECODEDFROGLEAPSOLUTION_H_

#include "FrogObject.h"

class FrogObjectCol;
class Vehicle;
class Graph;

class DecodedFrogLeapSolution : public FrogObject
{
	private:
		FrogObjectCol * vehicles;

		Graph * ptrG;
	
	public:

		DecodedFrogLeapSolution();

		DecodedFrogLeapSolution(Graph * g);

		void addVehicle(Vehicle * v);

		//Vehicle * getVehicle(short int pos);

		short int decodeFrogLeapValue(float fvalue, short int numberOfVehicles);

		void decodeFrogLeapItem(float fvalue, short int customerId, short int numberOfDepots, short int numberOfVehicles);		

		int evalSolution();

		void setGraph(Graph * g);

		Graph * getGraph();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif