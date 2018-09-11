#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FeasibleSolution;
class DecodedFrogLeapSolution;
class Graph;
class FrogLeapController;
enum class SolutionGenerationType;
enum class SourceType;

class FrogLeapSolution: public FrogObject
{
	private:
	
		float * values;
		short int size;			// number of customers

		short int n_depots;		// number of depots
		short int nElementsToSort;
		//time_t timeSeedUsed;
		SolutionGenerationType sgt;
		SourceType st;

		float genRandomFloatingNumber(float a, float b);		

	public:
	
		FrogLeapSolution(SolutionGenerationType v_sgt, SourceType v_sourceType, short int ncustomers, short int n_depots_v, short int id);

		~FrogLeapSolution();

		float getFLValue(short int i);

		void setSize(short int size_v);

		short int getSize();

		void genRandomSolution();

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
