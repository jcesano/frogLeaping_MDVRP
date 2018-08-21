#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

#include "FrogObject.h"

class FrogObjectCol;
class Graph;
class Pair;

const int VEHICLE_CAPACITY = 7;

class Vehicle : public FrogObject
{
	private:
		FrogObjectCol * customers;
		short int size;
		short int depotIndex;
		int capacity;
		int demand;
		bool isFeasible;
		short int notAddedCustomer;

		int pathCost;

		Graph * ptrGraph;

	public:
		Vehicle(short int id);

		Vehicle(short int id, Graph * g);

		~Vehicle();

		void addCustomerPair(Pair * customerPair);

		void setDepotIndex(short int depot_v);

		short int getDepotIndex();

		int evalPath(Graph * g);

		void setGraph(Graph * g);

		Graph * getGraph();

		void setPathCost(int cost);

		int getPathCost();

		int getCapacity();

		int incDemand(int aditionalDemand);

		int getDemand();

		void setAsFeasible();

		void setAsUnFeasible();

		bool getIsFeasible();

		short int getNotAddedCustomer();

		void setNotAddedCustomer(short int customerId);


		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif