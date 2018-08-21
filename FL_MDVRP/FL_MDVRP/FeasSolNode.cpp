#include "stdafx.h"
#include "FeasSolNode.h"
#include "FeasibleSolution.h"

FeasSolNode::FeasSolNode(FeasibleSolution * fs, FeasSolNode * fsnodeptr)
{
	feasibleSol = fs;
	next = fsnodeptr;
}

FeasSolNode::~FeasSolNode()
{
	delete this->feasibleSol;
}

void FeasSolNode::printNodeItems()
{
	if (this->feasibleSol != NULL)
	{
		this->feasibleSol->printFeasibleSolution();
	}

	FeasSolNode * tempNodePtr = next;
	while (tempNodePtr != NULL)
	{
		tempNodePtr->feasibleSol->printFeasibleSolution();
		tempNodePtr = tempNodePtr->next;
	};
}

FeasibleSolution * FeasSolNode::getSolution()
{
	return this->feasibleSol;
}

FeasSolNode * FeasSolNode::getNextFeasSolNode()
{
	return this->next;
}


void FeasSolNode::setNextFeasSolNode(FeasSolNode * node)
{
	this->next = node;
}