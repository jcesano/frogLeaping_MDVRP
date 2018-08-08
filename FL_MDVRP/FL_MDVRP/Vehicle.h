#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

#include "FrogObject.h"

class FrogObjectCol;
class Graph;
class Pair;

class Vehicle : public FrogObject
{
	private:
		FrogObjectCol * customers;
		short int size;
		short int depotIndex;

		int pathCost;

		Graph * ptrGraph;

	public:
		Vehicle(short int id);

		Vehicle(short int id, Graph * g);

		void addCustomerPair(Pair * customerPair);

		void setDepotIndex(short int depot_v);

		short int getDepotIndex();

		int evalPath(Graph * g);

		void setGraph(Graph * g);

		Graph * getGraph();

		void setPathCost(int cost);

		int getPathCost();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif