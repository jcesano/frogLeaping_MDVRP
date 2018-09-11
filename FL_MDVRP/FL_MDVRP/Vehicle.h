#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

#include "FrogObject.h"

class FrogObjectCol;
class Graph;
class Pair;
class FeasibleSolution;
class FrogLeapController;

class Vehicle : public FrogObject
{
	private:
		FrogObjectCol * customers;
		short int size;
		short int depotIndex;
		short int depotId;
		int capacity;
		int remaining_capacity;
		int demand;
		bool isFeasible;
		
		bool localSearchApplied;
		int pathCost;

		FrogLeapController * ptrController;

		short int * vehicleCustomerArray;

	public:
		Vehicle(short int id);

		Vehicle(short int id, FrogLeapController * controller);

		~Vehicle();

		void addCustomerPair(Pair * customerPair);

		void setDepotIndex(short int depot_v);

		short int getDepotIndex();

		void setDepotId(short int v_depotId);

		short int getDepotId();

		int evalPath(FrogLeapController * controller);

		void setController(FrogLeapController * controller);

		FrogLeapController * getController();

		void setPathCost(int cost);

		int getPathCost();

		int getCapacity();

		int getRemainingCapacity();

		void decRemainingCapacity(int capacity_to_dec);

		int incDemand(int aditionalDemand);

		int getDemand();

		void setAsFeasible();

		void setAsUnFeasible();

		bool getIsFeasible();

		void setupLocalSearch();

		int applyLocalSearch(FrogLeapController * controller);

		short int ObtainCustomerIdFromIndex(short int position);

		short int ObtainDepotIdFromIndex();

		bool generateLocalSolutionsAndEvaluate(FrogLeapController * controller);

		void updateBestSolution(FeasibleSolution * fs, int cost);

		void printLocalSolution();

		void printGlobalSolution();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif