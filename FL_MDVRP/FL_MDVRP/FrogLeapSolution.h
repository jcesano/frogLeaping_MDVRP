#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FeasibleSolution;
class DecodedFrogLeapSolution;

class FrogLeapSolution: public FrogObject
{
	private:
	
		float * values;
		short int size;
		short int n_vehicles;
		time_t timeSeedUsed;

		float genRandomFloatingNumber(float a, float b);

	public:
	
		FrogLeapSolution(short int size_v, short int n_vehicles_v, short int id);

		float getFLValue(short int i);

		void setSize(short int size_v);

		short int getSize();

		void genRandomSolution();

		DecodedFrogLeapSolution * decodeFrogLeapSolution();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif
