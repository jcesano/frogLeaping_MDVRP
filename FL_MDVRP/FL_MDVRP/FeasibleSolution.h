#ifndef FEASIBLESOLUTION_H_   /* Include guard */
#define FEASIBLESOLUTION_H_

#include <iostream>
#include <time.h>

class FeasibleSolCol;
class Graph;
class DistanceTable;
class Vehicle;
class FrogLeapController;

class FeasibleSolution
{
	short int * solVect;

	short int size;

	bool isFeasible;

	time_t timeSeedUsed;

public:
	FeasibleSolution(short int n);

	FeasibleSolution(FeasibleSolution * fs);

	FeasibleSolution(short int arr_size, short int * array);

	~FeasibleSolution();

	void setSolFactValue(short int pos, short int val);

	int getSolFactValue(short int pos);

	short int getSize();

	//this method modifies the this instance
	FeasibleSolution * swapItems(short int pos1, short int pos2); 

	//this method makes a copy and creates a new instance
	FeasibleSolution * genSwappedItemsFs(short int pos1, short int pos2); 

	FeasibleSolCol * genOneSwapPermutations(FrogLeapController * controller);

	bool searchOneSwapFeasibleSolutionsAndEval(Vehicle * veh, FrogLeapController * controller);

	FeasibleSolCol * genPermutations(short int distance, FeasibleSolCol * sourceSolutionCol, FrogLeapController * controller);

	bool isTheSame(FeasibleSolution * fs);

	void printFeasibleSolution();

	FeasibleSolution * genRandomSwapSolution(short int bottom, short int top);

	FeasibleSolCol * genRandomFeasibleSolCol();

	void setRandomSolution();

	void setIndexesAsValues();

	void removeValue(short int position);

	short int popRandomValue();

	int factorial(short int n);

	int Evaluate(FrogLeapController * controller, short int depotId);
};

#endif
