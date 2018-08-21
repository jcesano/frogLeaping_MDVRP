#include "stdafx.h"
#include "FeasibleSolCol.h"
#include "FeasSolNode.h"
#include "FeasibleSolution.h"

FeasibleSolCol::FeasibleSolCol()
{
	head = NULL;

	this->colSize = 0;
}

FeasibleSolCol::~FeasibleSolCol()
{
	FeasSolNode * temp = head;

	while (this->head != NULL)
	{
		temp = temp->getNextFeasSolNode();
		delete head;
		head = temp;
	}
}

void FeasibleSolCol::AddFeasibleSol(FeasibleSolution * fs)
{
	FeasSolNode * ptr;

	ptr = new FeasSolNode(fs, head);

	head = ptr;

	this->colSize = this->colSize + 1;
};

void FeasibleSolCol::printFeasSolCol()
{
	printf("Printing permutations \n");

	if (head != NULL)
	{
		head->printNodeItems();
	}
}

int FeasibleSolCol::getSize()
{
	return this->colSize;
}

//returns the solution in position i in the list, first position is 1.
FeasibleSolution * FeasibleSolCol::getFeasibleSolution(int i)
{
	// assign the first element
	FeasSolNode * result = head;

	if (this->head != NULL)
	{
		// if i == 1 then for is not executed, otherwise we start from i = 2 
		// cause result is pointing to the first Node already 
		for (int j = 2; j <= i; j++)
		{
			result = result->getNextFeasSolNode();
		}
	}

	if (result != NULL)
	{
		return result->getSolution();
	}

	return NULL;
}

void FeasibleSolCol::removeFeasibleSolutions(FeasibleSolCol * sourceSolutionCol)
{
	if (sourceSolutionCol != NULL)
	{
		for (int i = 1; i <= sourceSolutionCol->colSize; i++)
		{
			FeasibleSolution * fs = sourceSolutionCol->getFeasibleSolution(i);
			if (this->feasibleSolExists(fs) == 1)
			{
				this->removeFeasibleSolution(fs);
			}
		}
	}

}

void FeasibleSolCol::removeFeasibleSolution(FeasibleSolution * fs)
{
	FeasSolNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	if (fs != NULL)
	{
		while (nodePtr != NULL)
		{
			if (nodePtr->getSolution() != NULL)
			{
				if (nodePtr->getSolution()->isTheSame(fs) == 1)
				{

					// if the element is located at the begining of the list
					if (head == nodePtr)
					{
						nodePtrTemp = head;
						head = head->getNextFeasSolNode();
						nodePtr = head;
						// add a delete nodePtrTemp
						this->colSize--;
					}
					else {
						nodePtrTemp = nodePtr;
						nodePtrPrev->setNextFeasSolNode(nodePtr->getNextFeasSolNode());
						nodePtr = nodePtrTemp->getNextFeasSolNode();
						// add a delete nodePtrTemp
						this->colSize--;
					}
				}
				else {
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFeasSolNode();
				}
			} // end if (nodePtr->getSolution() != NULL)
		} // end while (nodePtr != NULL)
	} // end if(fs != NULL)
}

FeasibleSolCol * FeasibleSolCol::removeRepetedItems()
{
	FeasibleSolCol * remRepItemsCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	for (int i = 1; i <= this->getSize(); i++)
	{
		fs = this->getFeasibleSolution(i);

		if (remRepItemsCol->feasibleSolExists(fs) == 0)
		{
			remRepItemsCol->AddFeasibleSol(fs);
		}
	}

	return remRepItemsCol;
}

// It returns the position of the first repeated item. Otherwise returns 0.
int FeasibleSolCol::areThereRepetedItems()
{
	int repeated = 0, i = 1;
	FeasibleSolCol * auxCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	while (i <= this->getSize() && repeated == 0)
	{
		fs = this->getFeasibleSolution(i);
		if (auxCol->feasibleSolExists(fs) == 0)
		{
			repeated = i;
		}
	}

	return repeated;
}

int FeasibleSolCol::feasibleSolExists(FeasibleSolution * fs)
{
	int found = 0, i;

	if (this != NULL)
	{
		FeasSolNode * nodePtr;
		FeasibleSolution * solPtr;

		i = 1;

		nodePtr = this->head;

		while (found == 0 && i <= this->getSize() && nodePtr != NULL)
		{
			solPtr = nodePtr->getSolution();

			found = solPtr->isTheSame(fs);

			nodePtr = nodePtr->getNextFeasSolNode();
			i = i + 1;
		}
	}

	return found;
}

void FeasibleSolCol::ConcatCol(FeasibleSolCol * fscol)
{
	FeasSolNode * tmp;
	FeasibleSolution * fs;

	for (int i = 1; i <= fscol->getSize(); i++)
	{
		fs = fscol->getFeasibleSolution(i);
		this->AddFeasibleSol(fs);
	}
}
