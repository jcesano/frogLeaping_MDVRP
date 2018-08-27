#include "stdafx.h"
#include "FrogLeapController.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>
#include "FrogObject.h"
#include "DecodedFrogLeapSolution.h"
#include "TspLibEuc2D.h"

const int LINE_MAX = 256;

FrogLeapController::FrogLeapController()
{
	this->failAttempts = 0;

	this->successAttempts = 0;

	this->timeSeedUsed = (unsigned)time(NULL);
	srand(this->timeSeedUsed);

	this->minCostValue = SHRT_MAX;

	this->totalImprovements = 0;
	this->localSearchImprovements = 0;
	this->globalImprovements = 0;

	this->tspLibEud2DPtr = NULL;
}

FrogLeapController::~FrogLeapController()
{
}

int FrogLeapController::getFailAttempts()
{
	return this->failAttempts;
}

void FrogLeapController::incFailAttempts()
{
	this->failAttempts++;
}

int FrogLeapController::getTotalImprovements()
{
	return this->localSearchImprovements + this->globalImprovements;
}

void FrogLeapController::incTotalImprovements()
{
	this->totalImprovements++;
}

int FrogLeapController::getLocalSearchImprovements()
{
	return this->localSearchImprovements;
}

void FrogLeapController::incLocalSearchImprovements()
{
	this->localSearchImprovements;
}

int FrogLeapController::getGlobalSearchImprovements()
{
	return this->globalImprovements;
}

void FrogLeapController::incGlobalSearchImprovements()
{
	this->globalImprovements++;
}

int FrogLeapController::getLocalGeneratedSolutions()
{
	return this->localGeneratedSolutions;
}

void FrogLeapController::incLocalGeneratedSolutions()
{
	this->localGeneratedSolutions++;
}

int FrogLeapController::getTope()
{
	return 500;
}

int FrogLeapController::getMinCostValue()
{
	return this->minCostValue;
}

void FrogLeapController::setMinCostValue(int cost)
{
	this->minCostValue = cost;
}

void FrogLeapController::setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution)
{
	this->ptrBestSolution = ptrSolution;
}

DecodedFrogLeapSolution * FrogLeapController::getBestDecodedFrogLeapSolution()
{
	return this->ptrBestSolution;
}

void FrogLeapController::setRandomSeed()
{
	srand(this->timeSeedUsed);
}

void FrogLeapController::applyLocalSearch()
{
	int newCost = this->ptrBestSolution->applyLocalSearch(this);
	this->setMinCostValue(newCost);
}

void FrogLeapController::printCtrl()
{
	printf("\n \n SHOWING DATA OF FROGLEAPING CONTROLLER \n");
	this->ptrBestSolution->printFrogObj();

	printf("\n Summary of Best Found Solution \n");
	printf("	Time Seed used %lld \n", (long long)this->timeSeedUsed);
	printf("	Number of success attempts: %d \n", this->successAttempts);
	printf("	Number of fail attempts: %d \n", this->failAttempts);
	printf("	Number of TOTAL Improvements: %d \n", this->getTotalImprovements());
	printf("	Number of Global Search Improvements: %d \n", this->globalImprovements);
	printf("	Number of Local Search Improvements: %d \n", this->localSearchImprovements);
	printf("	Evaluation of best found solution is: %d \n \n", this->getMinCostValue());

}

void FrogLeapController::loadTSPEUC2D_Data(char * fileName)
{
	fileName = "casog01.vrp";
	FILE * filePtr;

	TspLibEuc2D * tspLibEuc2DPtrAux = new TspLibEuc2D();

	// Opening file
	if ((filePtr = fopen(fileName, "r")) != NULL)
	{

		this->readTSPSection(filePtr, "NAME", ":");

		this->readTSPSection(filePtr, "COMMENT", ":");

		this->readTSPSection(filePtr, "TYPE", ":");

		this->readTSPSection(filePtr, "DIMENSION", ":");

		this->readTSPSection(filePtr, "EDGE_WEIGHT_TYPE", ":");

		this->readTSPSection(filePtr, "CAPACITY", ":");

		//fscanf(filePtr, "%s", nameSection);
		//fscanf(filePtr, "%s", ctrlChar);
		//printf("Section: %s %s\n", nameSection, ctrlChar);
	}
	else
	{
		printf("Error found opening file");
	}
}

void FrogLeapController::readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar)
{
	char * sectionTag = new char[50], *separatorChar = new char[1], buf[LINE_MAX];

	if (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		sscanf(buf, "%s %s", sectionTag, separatorChar);
		printf("Section: %s %s", sectionTag, separatorChar);

		if (sectionTag != ctrlSectionTag || separatorChar != ctrlSeparatorChar)
		{
			printf("Error in file format \n");
			return;
		}

		loadTSPSection(buf, sectionTag);
	}
	else
	{
		printf("Error buffering file content \n");
	}
}

void FrogLeapController::loadTSPSection(char * buf, char * sectionTag)
{
	char * auxStrContent = new char[50];
	short int auxShortInt;

	if (sectionTag == "NAME")
	{
		sscanf(buf, "%s", auxStrContent);

		this->tspLibEud2DPtr->setName(auxStrContent);
		return;
	}

	if (sectionTag == "TYPE")
	{
		sscanf(buf, "%s", auxStrContent);
		this->tspLibEud2DPtr->setType(auxStrContent);
		return;
	}

	if (sectionTag == "DIMENSION")
	{
		sscanf(buf, "%hu", &auxShortInt);

		this->tspLibEud2DPtr->setDimension(auxShortInt);
		return;
	}

	if (sectionTag == "EDGE_WEIGHT_TYPE")
	{
		sscanf(buf, "%s", auxStrContent);
		this->tspLibEud2DPtr->setEdgeWeightType(auxStrContent);
		return;
	}

	if (sectionTag == "CAPACITY")
	{
		sscanf(buf, "%hu", &auxShortInt);
		this->tspLibEud2DPtr->setCapacity(auxShortInt);
		return;
	}

	printf("Error in file format: Section does not exist");

	return;
}


void FrogLeapController::setFailAttempts(int vfailAttempts)
{
	this->failAttempts = vfailAttempts;
}

int FrogLeapController::getSuccessAttempts()
{
	return this->successAttempts;
}

void FrogLeapController::incSuccessAttempts()
{
	this->successAttempts++;
}

void FrogLeapController::setSuccessAttempts(int vsucessAttempts)
{
	this->successAttempts = vsucessAttempts;
}