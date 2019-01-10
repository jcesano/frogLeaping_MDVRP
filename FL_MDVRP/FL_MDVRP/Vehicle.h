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
		int size;
		int depotIndex;
		int depotId;
		long int capacity;
		long int remaining_capacity;
		int demand;
		bool isFeasible;
		
		bool localSearchApplied;
		float pathCost;

		FrogLeapController * ptrController;

		int * vehicleCustomerArray;

	public:
		Vehicle(int id);

		Vehicle(int id, FrogLeapController * controller);

		virtual ~Vehicle();

		void addCustomerPair(Pair * customerPair);

		void addCustomerPairDoubleOrdered(Pair * customerPair);

		void addLastCustomerPair(Pair * customerPair);

		void setDepotIndex(int depot_v);

		int getDepotIndex();

		void setDepotId(int v_depotId);

		int getDepotId();

		float evalPath(FrogLeapController * controller);

		void setController(FrogLeapController * controller);

		FrogLeapController * getController();

		void setPathCost(float cost);

		float getPathCost();

		long int getCapacity();

		long int getRemainingCapacity();

		void decRemainingCapacity(int capacity_to_dec);

		int incDemand(int aditionalDemand);

		int getDemand();

		void setAsFeasible();

		void setAsUnFeasible();

		bool getIsFeasible();

		void setupLocalSearch();

		float applyLocalSearch(FrogLeapController * controller);

		int ObtainCustomerIdFromIndex(int position);

		int ObtainDepotIdFromIndex();

		bool generateLocalSolutionsAndEvaluate(FrogLeapController * controller);

		void updateBestSolution(FeasibleSolution * fs, float cost);

		void printLocalSolution();

		void printGlobalSolution();

		void adjustCustomerRoute(FrogLeapController * controller);

		
		Pair * getClosestIndexCustomerPairToDepot(int depotInternalId, FrogLeapController * controller);

		Pair * getClosestIndexCustomerPairToCustomer(int depotInternalId, FrogLeapController * controller);
		
		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif