#ifndef FEASIBLESOLUTION_H_   /* Include guard */
#define FEASIBLESOLUTION_H_

class FeasibleSolution
{
	short int * solVect;

	short int size;

	bool isFeasible;

	time_t timeSeedUsed;

public:
	FeasibleSolution(short int n);

	FeasibleSolution(FeasibleSolution * fs);

	void setSolFactValue(short int pos, short int val);

	int getSolFactValue(short int pos);

	FeasibleSolution * swapItems(short int pos1, short int pos2);

	FeasibleSolCol * genOneSwapPermutations();

	FeasibleSolCol * genPermutations(short int distance, FeasibleSolCol * sourceSolutionCol);

	bool isTheSame(FeasibleSolution * fs);

	void printFeasibleSolution();

	FeasibleSolution * genRandomSwapSolution(short int bottom, short int top);

	FeasibleSolCol * genRandomFeasibleSolCol();

	void setRandomSolution();

	void setIndexesAsValues();

	void removeValue(short int position);

	short int popRandomValue();

	int factorial(short int n);
};

#endif
