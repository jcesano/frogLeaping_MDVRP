#ifndef FEASIBLESOLCOL_H_   /* Include guard */
#define FEASIBLESOLCOL_H_

class FeasSolNode; //forward declaration
class FeasibleSolution;

class FeasibleSolCol
{
	FeasSolNode * head;

	int colSize;

public:
	FeasibleSolCol();

	~FeasibleSolCol();

	void AddFeasibleSol(FeasibleSolution * fs);

	void printFeasSolCol();

	int getSize();

	FeasibleSolution * getFeasibleSolution(int i);

	void removeFeasibleSolutions(FeasibleSolCol * sourceSolutionCol);

	void removeFeasibleSolution(FeasibleSolution * fs);

	FeasibleSolCol * removeRepetedItems();

	int areThereRepetedItems();

	int feasibleSolExists(FeasibleSolution * fs);

	void ConcatCol(FeasibleSolCol * fs);
};


#endif
