#ifndef DECODEDFROGLEAPSOLUTION_H_   /* Include guard */
#define DECODEDFROGLEAPSOLUTION_H_

#include "FrogObject.h"

class FrogObjectCol;
class Vehicle;
class Graph;
class FrogLeapController;

class DecodedFrogLeapSolution : public FrogObject
{
	private:
		FrogObjectCol * * vehicles;

		FrogLeapController * ptrController;

		bool isFeasibleSolution;

		short int notAddedCustomer;

		bool localSearchApplied;

		short int globalVehicleId;

		short int numDepots;
	
	public:

		DecodedFrogLeapSolution(short int n_depots);

		DecodedFrogLeapSolution(short int n_depots, FrogLeapController * controller);

		~DecodedFrogLeapSolution();

		void addVehicle(short int depotIndex, Vehicle * v);

		//Vehicle * getVehicle(short int pos);

		short int decodeFixedFloatFrogLeapValue(float fvalue, short int numberOfVehicles);

		short int decodeFrogLeapValue(float fvalue, short int numberOfVehicles);

		bool decodeFloatFixedFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots, short int numberOfVehicles);

		bool decodeFrogLeapItem(float fvalue, short int customerIndex, short int numberOfDepots);		

		int evalSolution();

		void setController(FrogLeapController * controller);

		FrogLeapController * getController();

		void setIsFeasibleSolution(bool v_isFeasible);

		bool getIsFeasibleSolution();

		int applyLocalSearch(FrogLeapController * controller);

		short int getGlobalVehicleId();
		
		short int getNotAddedCustomer();

		void setNotAddedCustomer(short int customerId);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif