#ifndef DECODEDFROGLEAPSOLUTION_H_   /* Include guard */
#define DECODEDFROGLEAPSOLUTION_H_

#include "FrogObject.h"
#include <vector>
using namespace std;


class FrogObjectCol;
class Vehicle;
class Graph;
class FrogLeapController;


class DecodedFrogLeapSolution : public FrogObject
{
	private:
		FrogObjectCol * * vehicles;
		//vector<FrogObjectCol> vehicles;
		//FrogObjectCol * vehicles;

		FrogLeapController * ptrController;

		bool isFeasibleSolution;

		int notAddedCustomer;

		bool localSearchApplied;

		long long int globalVehicleId;

		int numDepots;
	
	public:

		DecodedFrogLeapSolution(int n_depots);

		DecodedFrogLeapSolution(int n_depots, FrogLeapController * controller);

		virtual ~DecodedFrogLeapSolution();

		void deleteArrayOfFrogObjectCols(FrogObjectCol ** arrayPtr, int v_size);

		void addVehicle(int depotIndex, Vehicle * v);

		//Vehicle * getVehicle(int pos);

		int decodeFixedFloatFrogLeapValue(float fvalue, int numberOfVehicles);

		int decodeFrogLeapValue(float fvalue, int numberOfVehicles);

		//bool decodeFloatFixedFrogLeapItem(float fvalue, int customerIndex, int numberOfDepots, int numberOfVehicles);

		bool decodeFrogLeapItem(FrogLeapController * controller, float fvalue, int customerIndex, int numberOfDepots);		

		float evalSolution();

		void setController(FrogLeapController * controller);

		FrogLeapController * getController();

		void setIsFeasibleSolution(bool v_isFeasible);

		bool getIsFeasibleSolution();

		float applyLocalSearch(FrogLeapController * controller);

		long long int getGlobalVehicleId();
		
		int getNotAddedCustomer();

		void setNotAddedCustomer(int customerId);

		Vehicle * getFirstUpperValueVehicle(int customerDemand, int depotIndex);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif