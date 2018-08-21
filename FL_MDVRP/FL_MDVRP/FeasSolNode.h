#ifndef FEASSOLNODE_H_   /* Include guard */
#define FEASSOLNODE_H_

class FeasibleSolution; //forward declaration

class FeasSolNode
{
	FeasibleSolution * feasibleSol;

	FeasSolNode * next;

public:

	FeasSolNode(FeasibleSolution * fs, FeasSolNode * fsnodeptr);

	~FeasSolNode();

	void printNodeItems();

	FeasibleSolution * getSolution();

	FeasSolNode * getNextFeasSolNode();

	void setNextFeasSolNode(FeasSolNode * node);
};

#endif
