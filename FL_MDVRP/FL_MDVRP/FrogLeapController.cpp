#include "stdafx.h"
#include "FrogLeapController.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>
#include <string>
#include "FrogObject.h"
#include "DecodedFrogLeapSolution.h"
#include "TspLibEuc2D.h"
#include "Pair.h"

using std::string;

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

void FrogLeapController::loadTSPEUC2D_Data(char * fileName){
	
	FILE * filePtr;	
	
	TspLibEuc2D * tspLibEuc2DPtrAux = new TspLibEuc2D();
	
	char * sectionTag = new char[50], *separatorChar = new char[1], buf[LINE_MAX];

	string ctrlSectionTagStr, ctrlSeparatorCharStr, sectionTagStr, separatorCharStr;

	ctrlSeparatorCharStr = string(":");
		
	// Opening file
	if ((filePtr = fopen(fileName, "r")) != NULL)
	{
		
		// Reading section tag NAME
		char * name = new char[50];
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, name);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, name);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("NAME");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setName(name);
		}
		else
		{
			printf("Error reading file \n");
		}

		// reading COMMENT
		char * comment = new char[100];
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, comment);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, comment);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;
			ctrlSectionTagStr = string("COMMENT");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setComment(comment);
		}
		else
		{
			printf("Error reading file \n");
		}

		
		// reading type
		char * type = new char[50];
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, type);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, type);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("TYPE");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setType(type);
		}
		else
		{
			printf("Error reading file \n");
		}

		// reading DIMENSION
		int dimension;
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &dimension);
			printf("Section: %s %s %d \n", sectionTag, separatorChar, dimension);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("DIMENSION");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setDimension(dimension);
		}
		else
		{
			printf("Error reading file \n");
		}
		
		// reading EDGE_WEIGHT_TYPE
		char * edge_weight_type = new char[50];;
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %s", sectionTag, separatorChar, edge_weight_type);
			printf("Section: %s %s %s \n", sectionTag, separatorChar, edge_weight_type);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("EDGE_WEIGHT_TYPE");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setEdgeWeightType(edge_weight_type);
		}
		else
		{
			printf("Error reading file \n");
		}
		

		// reading CAPACITY
		int capacity;
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s %s %d", sectionTag, separatorChar, &capacity);
			printf("Section: %s %s %d \n", sectionTag, separatorChar, capacity);

			sectionTagStr = sectionTag;
			separatorCharStr = separatorChar;

			ctrlSectionTagStr = string("CAPACITY");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			tspLibEuc2DPtrAux->setCapacity(capacity);
		}
		else
		{
			printf("Error reading file \n");
		}

		// reading Node Coord Section
		char * nodeCoordSection = new char[50];;
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s ", nodeCoordSection);
			printf("Section: %s \n", nodeCoordSection);

			sectionTagStr = nodeCoordSection;
			
			ctrlSectionTagStr = string("NODE_COORD_SECTION");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
			{
				printf("Error in file format \n");
				return;
			}

			// Loading coordinates
			this->loadCoordinates(filePtr, tspLibEuc2DPtrAux);

			this->loadDemand(filePtr, tspLibEuc2DPtrAux);

			this->loadDepots(filePtr, tspLibEuc2DPtrAux);

			this->tspLibEud2DPtr = tspLibEuc2DPtrAux;
		}
		else
		{
			printf("Error reading file \n");
		}
		
	}
	else
	{
		printf("Error found opening file");
	}
}

void FrogLeapController::loadCoordinates(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{
	bool stopLoop = false;
	int nodeId = 0, x_coord = 0, y_coord = 0, v_dimension = tspLibEuc2DPtr->getDimension();
	char buf[LINE_MAX];

	for(short int i=0; i < v_dimension;i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%d %d %d", &nodeId, &x_coord, &y_coord);
			printf("Coordinate: %d %d %d \n", nodeId, x_coord, y_coord);

			Pair * currPair = new Pair(PairType::IntVsFloat, nodeId);

			currPair->set_i_IntValue(x_coord);
			currPair->set_j_IntValue(y_coord);
			currPair->setValue(nodeId);

			tspLibEuc2DPtr->AddNodeCoordItem(currPair);
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

void FrogLeapController::loadDemand(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{	
	int nodeId = -1, demand = 0;
	char * demandSection = new char[50];
	char buf [LINE_MAX];

	if (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		sscanf(buf, "%s ", demandSection);
		printf("Section: %s \n", demandSection);
	}

	string sectionTagStr = demandSection;

	string ctrlSectionTagStr = string("DEMAND_SECTION");

	if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
	{
		printf("Error in file format \n");
		return;
	}

	short int dimension = tspLibEuc2DPtr->getDimension();

	for (short int i = 0; i < dimension; i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%d %d", &nodeId, &demand);
			printf("Demand: %d %d \n", nodeId, demand);

	
			Pair * currPair = new Pair(PairType::IntVsInt, nodeId);

			currPair->set_i_IntValue(nodeId);
			currPair->set_j_IntValue(demand);
			currPair->setValue(nodeId);

			tspLibEuc2DPtr->AddDemandItem(currPair);
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

void FrogLeapController::loadDepots(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{
	int depotId = -2;
	char * depotSection = new char[50];
	char buf[LINE_MAX];

	if (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		sscanf(buf, "%s ", depotSection);
		printf("Section: %s \n", depotSection);
	}

	string sectionTagStr = depotSection;

	string ctrlSectionTagStr = string("DEPOT_SECTION");

	if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
	{
		printf("Error in file format \n");
		return;
	}
	
	bool stopLoop = false;

	while(!stopLoop)	
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%d ", &depotId);
			printf("%d \n", depotId);

			if(depotId != -1)
			{
				tspLibEuc2DPtr->AddDepotItem(depotId);
			}
			else
			{
				stopLoop = true;
			}
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

void FrogLeapController::readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar, int * off_set)
{
	char * sectionTag = new char[50], *separatorChar = new char[1], buf[LINE_MAX];

	string ctrlSectionTagStr = ctrlSectionTag, ctrlSeparatorCharStr = ctrlSeparatorChar;

	if (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		sscanf(buf, "%s %s", sectionTag, separatorChar);
		printf("Section: %s %s", sectionTag, separatorChar);

		string sectionTagStr = sectionTag;
		string separatorCharStr = separatorChar;

		if (sectionTagStr.compare(ctrlSectionTagStr) != 0 || separatorCharStr.compare(ctrlSeparatorCharStr) != 0)
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
	char * auxContentCharPtr = new char[50];
	string auxContentStr, sectionTagStr;
	short int auxShortInt;

	sectionTagStr = sectionTag;

	if (sectionTagStr.compare("NAME") == 0)
	{
		sscanf(buf, "%s", auxContentCharPtr);

		this->tspLibEud2DPtr->setName(auxContentCharPtr);
		return;
	}

	if (sectionTagStr.compare("TYPE") == 0)
	{
		sscanf(buf, "%s", auxContentCharPtr);
		this->tspLibEud2DPtr->setType(auxContentCharPtr);
		return;
	}

	if (sectionTagStr.compare("DIMENSION") == 0)
	{
		sscanf(buf, "%hu", &auxShortInt);

		this->tspLibEud2DPtr->setDimension(auxShortInt);
		return;
	}

	if (sectionTagStr.compare("EDGE_WEIGHT_TYPE") == 0)
	{
		sscanf(buf, "%s", auxContentCharPtr);
		this->tspLibEud2DPtr->setEdgeWeightType(auxContentCharPtr);
		return;
	}

	if (sectionTagStr.compare("CAPACITY") == 0)
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