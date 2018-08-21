#include "stdafx.h"
#include "FeasibleSolution.h"
#include "FeasibleSolCol.h"

FeasibleSolution::FeasibleSolution(short int n)
{
	solVect = new short int[n];
	size = n;
	isFeasible = true;

	// initialize random seed
	timeSeedUsed = time(NULL);

	srand(timeSeedUsed);

}

FeasibleSolution::FeasibleSolution(FeasibleSolution * fs)
{
	solVect = new short int[fs->size];
	size = fs->size;
	isFeasible = true;

	for (short int i = 0; i<this->size; i++)
	{
		this->solVect[i] = fs->getSolFactValue(i);
	}

	// initialize random seed
	timeSeedUsed = time(NULL);

	srand(timeSeedUsed);

}

FeasibleSolution::~FeasibleSolution()
{
	delete this->solVect;
}

void FeasibleSolution::setSolFactValue(short int pos, short int val)
{
	solVect[pos] = val;
};

int FeasibleSolution::getSolFactValue(short int pos)
{
	return this->solVect[pos];
}

// Swap elements i and j: return a new FeasibleSolution containing in position i, the element of position j and viceversa
FeasibleSolution * FeasibleSolution::swapItems(short int pos1, short int pos2)
{
	short int tempValue;

	tempValue = this->getSolFactValue(pos1); //store value of position pos1

											 // in position pos1, set element of position pos2
	this->setSolFactValue(pos1, this->getSolFactValue(pos2));

	// in position pos2, set element of position pos1
	this->setSolFactValue(pos2, tempValue);

	return this;
};

bool FeasibleSolution::isTheSame(FeasibleSolution * fs)
{
	bool result = true;
	short int i = 0;

	if (this->size != fs->size)
	{
		return 0;
	};

	while (result == true && i < this->size)
	{
		if (this->solVect[i] != fs->solVect[i])
		{
			result = false;
		}

		i++;
	};

	return result;
}

void FeasibleSolution::printFeasibleSolution()
{
	for (short int i = 0; i < this->size; i++)
	{
		printf("%d ", this->solVect[i]);
	}

	printf("\n");
}

FeasibleSolution * FeasibleSolution::genRandomSwapSolution(short int bottom, short int top)
{
	short int randomValue;

	FeasibleSolution * randomFs = new FeasibleSolution(this);

	if (top - bottom == 1)
	{
		randomFs->swapItems(bottom, top);
	}
	else {

		do
		{
			randomValue = (rand() % (top + 1 - bottom)) + bottom;
		} while (randomValue == bottom);

		randomFs->swapItems(bottom, randomValue);
	}

	return randomFs;
}

FeasibleSolCol * FeasibleSolution::genRandomFeasibleSolCol()
{
	FeasibleSolCol * randomFsCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	randomFsCol->AddFeasibleSol(this);

	fs = this;
	for (short int i = 0; i < this->size - 1; i++)
	{
		fs = fs->genRandomSwapSolution(i, this->size - 1);

		randomFsCol->AddFeasibleSol(fs);
	}

	return randomFsCol;
}

void FeasibleSolution::setRandomSolution()
{
	FeasibleSolution * fsIndex = new FeasibleSolution(this->size);

	fsIndex->setIndexesAsValues();

	for (short int i = 0; i <= this->size - 1; i++)
	{
		short int randValue = fsIndex->popRandomValue();

		this->setSolFactValue(i, randValue);
	}

	delete fsIndex;
}

FeasibleSolCol * FeasibleSolution::genPermutations(short int distance, FeasibleSolCol * sourceSolutionCol)
{
	if (distance == 1)
	{
		FeasibleSolCol * fscol = this->genOneSwapPermutations();

		if (sourceSolutionCol == NULL)
		{
			return fscol;
		}
		else {
			fscol->removeFeasibleSolutions(sourceSolutionCol);
			return fscol;
		}
	}
	else {
		FeasibleSolCol * tempCol = this->genOneSwapPermutations(), *tempCol_i = NULL, *fullCol = new FeasibleSolCol();
		FeasibleSolution * fs_i;


		if (sourceSolutionCol == NULL)
		{
			sourceSolutionCol = new FeasibleSolCol();
		}

		sourceSolutionCol->AddFeasibleSol(this);

		for (int i = 1; i <= tempCol->getSize(); i++)
		{
			fs_i = tempCol->getFeasibleSolution(i);

			sourceSolutionCol->AddFeasibleSol(fs_i);

			tempCol_i = fs_i->genPermutations(distance - 1, sourceSolutionCol);

			fullCol->ConcatCol(tempCol_i);
		}

		//sourceSolutionCol->AddFeasibleSol(this);

		//fullCol->removeFeasibleSolutions(sourceSolutionCol);

		return fullCol;
	}
}

FeasibleSolCol * FeasibleSolution::genOneSwapPermutations()
{
	FeasibleSolCol * colptr = NULL;

	if (this->size == 1)
	{
		return NULL;
	}// end if

	if (this->size == 2)
	{
		colptr = new FeasibleSolCol();

		// swap first and second and generate a new FeasibleSolution
		colptr->AddFeasibleSol(this->swapItems(0, 1));
	}
	else
	{
		FeasibleSolution * colptr_i_j;
		colptr = new FeasibleSolCol();

		for (short int i = 0; i < this->size; i++)
		{
			for (short int j = i + 1; j < this->size; j++)
			{
				colptr_i_j = new FeasibleSolution(this);

				colptr_i_j->swapItems(i, j);

				colptr->AddFeasibleSol(colptr_i_j);
			}//end for j
		}//end for i
	}// end else

	return colptr;
};


void FeasibleSolution::setIndexesAsValues()
{
	for (short int i = 0; i < this->size; i++)
	{
		this->setSolFactValue(i, i);
	};
}

void FeasibleSolution::removeValue(short int position)
{
	for (int i = position; i < this->size - 1; i++)
	{
		this->setSolFactValue(i, this->getSolFactValue(i + 1));
	}

	this->size--;
}

short int FeasibleSolution::popRandomValue()
{
	short int randomIndex = rand() % (this->size); // random number between 0 and size-1

	short int randomValue = this->getSolFactValue(randomIndex);

	this->removeValue(randomIndex);

	return randomValue;
}

int FeasibleSolution::factorial(short int n)
{
	long int result = 1;

	if (n == 0)
	{
		return 1;
	};

	for (int i = 1; i <= n; i++)
	{
		result = result * i;
	};

	return result;
}



