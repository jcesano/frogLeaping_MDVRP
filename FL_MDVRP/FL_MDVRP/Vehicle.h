#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

#include "FrogObject.h"

class FrogObjectCol;
class Graph;
class Pair;
class FeasibleSolution;

const int VEHICLE_CAPACITY = 7;

class Vehicle : public FrogObject
{
	private:
		FrogObjectCol * customers;
		short int size;
		short int depotIndex;
		short int depotId;
		int capacity;
		int demand;
		bool isFeasible;
		short int notAddedCustomer;
		bool localSearchApplied;
		int pathCost;

		Graph * ptrGraph;

		short int * customerArray;

	public:
		Vehicle(short int id);

		Vehicle(short int id, Graph * g);

		~Vehicle();

		void addCustomerPair(Pair * customerPair);

		void setDepotIndex(short int depot_v);

		short int getDepotIndex();

		void setDepotId(short int v_depotId);

		short int getDepotId();

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

		void setupLocalSearch();

		int applyLocalSearch();

		short int ObtainCustomerIdFromIndex(short int position);

		short int ObtainDepotIdFromIndex();

		bool generateLocalSolutionsAndEvaluate();

		void updateBestSolution(FeasibleSolution * fs, int cost);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif