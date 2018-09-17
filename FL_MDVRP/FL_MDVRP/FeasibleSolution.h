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
	int * solVect;

	int size;

	bool isFeasible;

	time_t timeSeedUsed;

public:
	FeasibleSolution(int n);

	FeasibleSolution(FeasibleSolution * fs);

	FeasibleSolution(int arr_size, int * array);

	~FeasibleSolution();

	void setSolFactValue(int pos, int val);

	int getSolFactValue(int pos);

	int getSize();

	//this method modifies the this instance
	FeasibleSolution * swapItems(int pos1, int pos2); 

	//this method makes a copy and creates a new instance
	FeasibleSolution * genSwappedItemsFs(int pos1, int pos2); 

	FeasibleSolCol * genOneSwapPermutations(FrogLeapController * controller);

	bool searchOneSwapFeasibleSolutionsAndEval(Vehicle * veh, FrogLeapController * controller);

	FeasibleSolCol * genPermutations(int distance, FeasibleSolCol * sourceSolutionCol, FrogLeapController * controller);

	bool isTheSame(FeasibleSolution * fs);

	void printFeasibleSolution();

	FeasibleSolution * genRandomSwapSolution(int bottom, int top);

	FeasibleSolCol * genRandomFeasibleSolCol();

	void setRandomSolution();

	void setIndexesAsValues();

	void removeValue(int position);

	int popRandomValue();

	int factorial(int n);

	float Evaluate(FrogLeapController * controller, int depotId);
};

#endif
