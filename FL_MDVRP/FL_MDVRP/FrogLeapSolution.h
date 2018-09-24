#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FeasibleSolution;
class DecodedFrogLeapSolution;
class Graph;
class FrogLeapController;
class FrogObjectCol;
class FrogObject;
enum class SolutionGenerationType;
enum class SourceType;

class FrogLeapSolution: public FrogObject
{
	private:
	
		float * values;
		int size;			// number of customers

		int n_depots;		// number of depots
		int nElementsToSort;
		//time_t timeSeedUsed;
		SolutionGenerationType sgt;
		SourceType st;

		float genRandomFloatingNumber(float a, float b);		

	public:
	
		FrogLeapSolution(SolutionGenerationType v_sgt, SourceType v_sourceType, int ncustomers, int n_depots_v, int id);

		~FrogLeapSolution();

		float getFLValue(int i);

		void setSize(int size_v);

		int getSize();

		bool genRandomSolution(FrogLeapController * controller);

		bool genRandomSolution2(FrogLeapController * controller);

		float normalRandomAssigment(FrogLeapController * controller);

		float assignRandomFeasibleDepot(FrogObjectCol * feasibleDepotList, FrogLeapController * controller, int customerIndex);

		float assignRandomFeasibleDepot2(FrogLeapController * controller, int customerIndex);

		FrogObjectCol * initializeFeasibleDepotList(FrogLeapController * controller);

		DecodedFrogLeapSolution * decodeSolution(FrogLeapController * g);

		DecodedFrogLeapSolution * decodeFloatFixedFrogLeapSolution();

		DecodedFrogLeapSolution * decodeFrogLeapSolution(FrogLeapController * controller);

		void setSolutionGenerationType(SolutionGenerationType v_sgt);

		SolutionGenerationType getSolutionGenerationType();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif
