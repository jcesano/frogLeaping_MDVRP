#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FeasibleSolution;
class DecodedFrogLeapSolution;
class Graph;

class FrogLeapSolution: public FrogObject
{
	private:
	
		float * values;
		short int size;			// number of customers
		short int n_vehicles;	// number of vehicles
		short int n_depots;		// number of depots
		short int nElementsToSort;
		//time_t timeSeedUsed;
		SolutionGenerationType sgt;

		float genRandomFloatingNumber(float a, float b);		

	public:
	
		FrogLeapSolution(SolutionGenerationType v_sgt, short int ncustomers, short int n_vehicles_v, short int n_depots_v, short int id);

		~FrogLeapSolution();

		float getFLValue(short int i);

		void setSize(short int size_v);

		short int getSize();

		void genRandomSolution();

		DecodedFrogLeapSolution * decodeFrogLeapSolution(Graph * g);

		void setSolutionGenerationType(SolutionGenerationType v_sgt);

		SolutionGenerationType getSolutionGenerationType();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif
