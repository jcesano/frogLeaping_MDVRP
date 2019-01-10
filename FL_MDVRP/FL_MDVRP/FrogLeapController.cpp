#include "stdafx.h"
#include "FrogLeapController.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>
#include <string>
#include "FrogObject.h"
#include "FrogObjectCol.h"
#include "DecodedFrogLeapSolution.h"
#include "TspLibEuc2D.h"
#include "TestCaseObj.h"
#include "Pair.h"
#include "DistanceTable.h"
#include "FloatDistanceTable.h"
#include "Graph.h"
#include "FrogLeapSolution.h"
#include "Pair.h"
#include "IndexList.h"
#include "Vehicle.h"
#include <limits>
#include <iostream>
#include <string>
#include <functional>
#include <random>
#include <utility>

//using std::string;
//using std::cout;
//using std::endl;
//using std::cin;
//using std::string;
//using std::random_device;
//using std::default_random_engine;

using namespace std;

const int LINE_MAX = 256;

FrogLeapController::FrogLeapController()
{
	this->failAttempts = 0;

	this->successAttempts = 0;

	this->timeSeedUsed = (unsigned)time(NULL);
	//this->timeSeedUsed = 1537280770;
	//srand(this->timeSeedUsed);

	this->minCostValue = std::numeric_limits<float>::max();;

	this->totalImprovements = 0;
	this->localSearchImprovements = 0;
	this->globalImprovements = 0;

	this->tspLibEud2DPtr = NULL;
	this->testCaseObjPtr = NULL;

	this->distTablePtr = NULL;
	this->floatDistTablePtr = NULL;

	this->graphPtr = NULL;

	this->customerList = new FrogObjectCol();
	this->depotList = new FrogObjectCol();
	this->vehiclePairList = new FrogObjectCol();
	this->ptrBestSolution = NULL;

	this->globalVehicleId = 0;	
}

FrogLeapController::~FrogLeapController()
{

	delete this->vehiclePairList;
	delete this->depotList;
	delete this->customerList;

	this->deleteArray(this->customerArray, this->getNumberOfCustomers());

	this->deleteArray(this->depotArray, this->getNumberOfDepots());

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

long int FrogLeapController::getNumberOfIterations()
{
	return 150000;
}

float FrogLeapController::getMinCostValue()
{
	return this->minCostValue;
}

void FrogLeapController::setMinCostValue(float cost)
{
	this->minCostValue = cost;
}

void FrogLeapController::setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution)
{
	DecodedFrogLeapSolution * oldSolution = this->ptrBestSolution;
	this->ptrBestSolution = ptrSolution;
	delete oldSolution;
	oldSolution = NULL;
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
	float newCost = this->ptrBestSolution->applyLocalSearch(this);
	this->setMinCostValue(newCost);
}

void FrogLeapController::printCtrl()
{
	printf("\n \n SHOWING DATA OF FROGLEAPING CONTROLLER \n");
	if(this->ptrBestSolution != NULL)
	{
		this->ptrBestSolution->printFrogObj();
	}
	else
	{
		printf("\n NO FEASIBLE SOLUTION FOUND: ptrBestSolution IS NULL \n");
	}
	
	printf("\n Summary of Best Found Solution \n");
	printf("	Time Seed used %lld \n", (long long)this->timeSeedUsed);
	printf("	Number of success attempts: %d \n", this->successAttempts);
	printf("	Number of fail attempts: %d \n", this->failAttempts);
	printf("	Number of TOTAL Improvements: %d \n", this->getTotalImprovements());
	printf("	Number of Global Search Improvements: %d \n", this->globalImprovements);
	printf("	Number of Local Search Improvements: %d \n", this->localSearchImprovements);
	printf("	Evaluation of best found solution is: %.3f \n \n", this->getMinCostValue());
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

			// Loading coordinates (we load the node Id, x_coord and y_coord)
			this->loadCoordinates(filePtr, tspLibEuc2DPtrAux);

			// Loading demands (we load the node Id, demand). The Id is the same as the previous one
			this->loadDemand(filePtr, tspLibEuc2DPtrAux);

			this->loadDepots(filePtr, tspLibEuc2DPtrAux);

			this->tspLibEud2DPtr = tspLibEuc2DPtrAux;
			fclose(filePtr);
		}
		else
		{
			printf("Error reading file \n");
			fclose(filePtr);
		}		
	}
	else
	{
		printf("Error found opening file");
	}
}

DecodedFrogLeapSolution * FrogLeapController::loadTestCaseData(char * fileName)
{
	FILE * filePtr;
	char * sectionTag = new char[50], *separatorChar = new char[1], buf[LINE_MAX];
	string ctrlSectionTagStr, ctrlSeparatorCharStr, sectionTagStr, separatorCharStr;

	TestCaseObj * testCaseObjPtr = new TestCaseObj();

	ctrlSeparatorCharStr = string(":");

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
				return NULL;
			}

			testCaseObjPtr->setName(name);
		}
		else
		{
			printf("Error reading file \n");
			return NULL;
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
				return NULL;
			}

			testCaseObjPtr->setComment(comment);
		}
		else
		{
			printf("Error reading file \n");
			return NULL;
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
				return NULL;
			}

			testCaseObjPtr->setDimension(dimension);
		}
		else
		{
			printf("Error reading file \n");
			return NULL;
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
				return NULL;
			}

			testCaseObjPtr->setType(type);
		}
		else
		{
			printf("Error reading file \n");
			return NULL;
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
				return NULL;
			}

			testCaseObjPtr->setCapacity(capacity);
		}
		else
		{
			printf("Error reading file \n");
			return NULL;
		}

		// reading Assignation Section
		char * assignationSection = new char[50];;
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%s ", assignationSection);
			printf("Section: %s \n", assignationSection);

			sectionTagStr = assignationSection;

			ctrlSectionTagStr = string("ASSIGNATION");
			if (sectionTagStr.compare(ctrlSectionTagStr) != 0)
			{
				printf("Error in file format \n");
				return NULL;
			}

			DecodedFrogLeapSolution * dfls = NULL;
			FrogLeapSolution * fls = NULL;

			// Loading assignations (customers to vehicles)
			//dfls = this->loadAssignations2(filePtr, testCaseObjPtr);
			fls = this->loadAssignations3(filePtr, testCaseObjPtr);
			//dfls = fls->decodeFrogLeapSolution(this);
			dfls = fls->decodeSolutionWithAngularCriteria(this);
			float evaluation = dfls->evalSolution();
			printf("Showing test evaluation: %.3f", evaluation);
			fclose(filePtr);
			return dfls;
		}
		else
		{
			printf("Error reading file \n");
			fclose(filePtr);

			return NULL;
		}
	}
}

void FrogLeapController::loadAssignations(FILE * filePtr, TestCaseObj * testCaseObjPtr)
{
	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
	int nodeLabelId = 0, depot_capacity = 0, customer_load = 0, v_dimension = testCaseObjPtr->getDimension();
	char buf[LINE_MAX];
	Pair * currPair;

	while(stopLoop == false)
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			if(vehicleDataLoaded == false)
			{
				sscanf(buf, "%d %d %d", &nodeLabelId, &depot_capacity, &customer_load);
				printf("Depot data: %d %d %d \n", nodeLabelId, depot_capacity, customer_load);

				currPair = new Pair(PairType::IntVsInt, nodeLabelId);
				currPair->set_i_IntValue(depot_capacity);
				currPair->set_j_IntValue(customer_load);
				currPair->setId(nodeLabelId);
				currPair->setValue(nodeLabelId);

				testCaseObjPtr->AddVehicleItem(currPair);
				vehicleDataLoaded = true;
				assignationBlockLoaded = false;
			}
			else
			{
				int customerLabelId;
				if(assignationBlockLoaded == false)
				{					
					sscanf(buf, "%d ", &customerLabelId);
					printf("Customer Label Id : %d \n", customerLabelId);
					
					if(customerLabelId == -1)
					{
						assignationBlockLoaded = true;
						vehicleDataLoaded = false;
					}
					else
					{
						if(customerLabelId == -2)
						{
							stopLoop = true;
						}
						else
						{
							currPair = new Pair(PairType::IntVsInt, customerLabelId);
							currPair->set_i_IntValue(customerLabelId);
							currPair->set_j_IntValue(nodeLabelId);
							currPair->setId(customerLabelId);
							currPair->setValue(customerLabelId);

							testCaseObjPtr->AddCustomerItem(currPair);
						}
					}
				}
			}
		}
		else
		{
			printf("Error reading file: Section Node Coordinates \n");
			return;
		}
	}
}

// This method creates an already decoded solution
DecodedFrogLeapSolution * FrogLeapController::loadAssignations2(FILE * filePtr, TestCaseObj * testCaseObjPtr)
{
	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
	int depotLabelId = 0, vehicle_cost = 0, vehicle_load = 0, v_dimension = testCaseObjPtr->getDimension();
	char buf[LINE_MAX];
	Pair * currPair;
	float globalCounter = 0;
	int depotIndex;

	DecodedFrogLeapSolution * decodedSolution = new DecodedFrogLeapSolution(this->getNumberOfDepots(), this);
	Vehicle * veh = NULL;
	int count;
	Pair * customerPair = NULL;

	int prevDepotLabelId = -1;

	while (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		char* tok = strtok(buf, " ");
			
		// read data of the depot vehicle
		count = 0;
			
		// Loading the first three data of the vehicle depot
		while (tok != NULL && count < 3) // Correct logic to use to stop looping.
		{
			if(count == 0)
			{
				depotLabelId = atoi(tok);
				cout << depotLabelId << endl;  // Print the current token before getting the next token.
			}				

			if(count == 1)
			{
				vehicle_cost = atoi(tok);
				cout << vehicle_cost << endl;  // Print the current token before getting the next token.
			}

			if(count == 2)
			{
				vehicle_load = atoi(tok);
				cout << vehicle_load << endl;  // Print the current token before getting the next token.
			}
								
			tok = strtok(NULL, " ");
			count++;
		}

		veh = new Vehicle(this->getGlobalVehicleId(), this);
		veh->setDepotId(depotLabelId);
		depotIndex = this->getDepotIndexByLabelId(depotLabelId);
		veh->setDepotIndex(depotIndex);

		decodedSolution->addVehicle(depotIndex, veh);

		count = 0;

		int customerLabelId, customerIndex;
		while (tok != NULL) 
		{
			customerLabelId = atoi(tok);
			customerIndex = this->getCustomerIndexByLabelId(customerLabelId);
			float fvalue = depotIndex + (globalCounter / 1000);
			customerPair = new Pair(PairType::IntVsFloat);
			customerPair->set_i_IntValue(customerIndex);
			customerPair->set_j_FloatValue(fvalue);
			customerPair->setValue(fvalue);
			customerPair->setId(customerIndex);
				
			veh->addLastCustomerPair(customerPair);

			tok = strtok(NULL, " ");

			globalCounter = globalCounter + 1;
		}

		globalCounter = 0;
		prevDepotLabelId = depotLabelId;
	}

	return decodedSolution;
}


FrogLeapSolution * FrogLeapController::loadAssignations3(FILE * filePtr, TestCaseObj * testCaseObjPtr)
{
	bool stopLoop = false, vehicleDataLoaded = false, assignationBlockLoaded = false;
	int depotLabelId = 0, vehicle_cost = 0, vehicle_load = 0, v_dimension = testCaseObjPtr->getDimension();
	char buf[LINE_MAX];
	Pair * currPair;
	float globalCounter = 0, fvalue;
	int depotIndex, customerLabelId, customerIndex;
	FrogLeapSolution * frogLeapSolution = new FrogLeapSolution(SolutionGenerationType::FrogLeaping, this->getSourceType(), this->getNumberOfCustomers(), this->getNumberOfDepots(), 0);
		
	int count;
	Pair * customerPair = NULL;
		
	while (fgets(buf, sizeof buf, filePtr) != NULL)
	{
		char* tok = strtok(buf, " ");

		// read data of the depot vehicle
		count = 0;

		// Loading the first three data of the vehicle depot
		while (tok != NULL && count < 3) // Correct logic to use to stop looping.
		{
			if (count == 0)
			{
				depotLabelId = atoi(tok);
				cout << depotLabelId << endl;  // Print the current token before getting the next token.
			}

			if (count == 1)
			{
				vehicle_cost = atoi(tok);
				cout << vehicle_cost << endl;  // Print the current token before getting the next token.
			}

			if (count == 2)
			{
				vehicle_load = atoi(tok);
				cout << vehicle_load << endl;  // Print the current token before getting the next token.
			}

			tok = strtok(NULL, " ");
			count++;
		}

		depotIndex = this->getDepotIndexByLabelId(depotLabelId);
		count = 0;

		while (tok != NULL)
		{
			customerLabelId = atoi(tok);
			customerIndex = this->getCustomerIndexByLabelId(customerLabelId);
			fvalue = depotIndex + (globalCounter / 1000);
			frogLeapSolution->setFLValue(customerIndex, fvalue);

			tok = strtok(NULL, " ");

			globalCounter = globalCounter + 1;
		}		
	}

	return frogLeapSolution;
}


void FrogLeapController::loadCoordinates(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr)
{
	bool stopLoop = false;
	int nodeId = 0, x_coord = 0, y_coord = 0, v_dimension = tspLibEuc2DPtr->getDimension();
	char buf[LINE_MAX];

	for(int i=0; i < v_dimension;i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%d %d %d", &nodeId, &x_coord, &y_coord);
			printf("Coordinate: %d %d %d \n", nodeId, x_coord, y_coord);

			Pair * currPair = new Pair(PairType::IntVsInt, nodeId);

			currPair->set_i_IntValue(x_coord);
			currPair->set_j_IntValue(y_coord);
			currPair->setId(nodeId);
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

	int dimension = tspLibEuc2DPtr->getDimension();

	for (int i = 0; i < dimension; i++)
	{
		if (fgets(buf, sizeof buf, filePtr) != NULL)
		{
			sscanf(buf, "%d %d", &nodeId, &demand);
			printf("Demand: %d %d \n", nodeId, demand);

	
			Pair * currPair = new Pair(PairType::IntVsInt, nodeId);

			currPair->set_i_IntValue(nodeId);
			currPair->set_j_IntValue(demand);
			currPair->setId(nodeId);
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

DistanceTable * FrogLeapController::loadDistanceTable()
{
	int dimension = this->tspLibEud2DPtr->getDimension();
	float floatDistance;

	DistanceTable * fdt = new DistanceTable(dimension);

	for(int i = 0; i < dimension; i++)
	{
		for(int j = i + 1; j < dimension; j++)
		{
			floatDistance = this->tspLibEud2DPtr->getEucDistance(i, j);			

			// we add two edges (a[u][v] and a[v][u])
			fdt->addEdge(i, j, floatDistance);			

			//if (i == 54 && j == 260)
			//{
			//	printf("Testing distance table: dt[%d, %d] = %f", i, j, fdt->getEdge(i,j));
			//}

		}
	}

	for (int k = 0; k < dimension; k++)
	{
		fdt->addDiagEdge(k, 0);
	}

	this->distTablePtr = fdt;

	return fdt;
}

void FrogLeapController::setDistanceTable(DistanceTable * t)
{
	this->distTablePtr = t;
}

DistanceTable * FrogLeapController::getDistanceTable()
{
	return this->distTablePtr;
}

void FrogLeapController::setFloatDistanceTable(FloatDistanceTable * t)
{
	this->floatDistTablePtr = t;
}

FloatDistanceTable * FrogLeapController::getFloatDistanceTable()
{
	return this->floatDistTablePtr;
}

int FrogLeapController::getNumberOfDepots()
{
	if(this->source_t == SourceType::Graph)
	{
		return this->depotList->getSize();
	}
	else
	{
		return this->tspLibEud2DPtr->getNumberOfDepots();
	}	
}

Pair * FrogLeapController::getDepotPairByIndex(int position)
{
	return this->depotArray[position];
}


Pair * FrogLeapController::getCustomerPairByIndex(int position)
{
	return this->customerArray[position];
}

Pair * FrogLeapController::getPairByInternalId(int internalId)
{
	return (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(internalId);	
}

void FrogLeapController::setAngularValues(Pair * veh_customerPair, int customerInternalId, int depotInternalId)
{
	float theta = this->tspLibEud2DPtr->getAngularTheta(customerInternalId, depotInternalId);
	float rho = this->tspLibEud2DPtr->getAngularRho(customerInternalId, depotInternalId);

	veh_customerPair->setValue(theta);
	veh_customerPair->setValue2(rho);
}

void FrogLeapController::setUpVehiclesPerDepot()
{
	int numOfDepots = this->depotList->getSize();
	Pair * depotPair = NULL;
	int depotDemand, depotId;

	this->vehiclePairList = new FrogObjectCol();

	for (int i = 0; i < numOfDepots; i++)
	{
		depotPair = this->depotArray[i];
		depotId = depotPair->get_i_IntValue();
		depotDemand = depotPair->get_j_IntValue();

		assignVehiclesToDepots(depotId, depotDemand);
	}

	setUpVehiclePairList();
}

void FrogLeapController::assignVehiclesToDepots(int depotId, int depotDemand)
{
	int remainingDemand = depotDemand;
	Pair * vehiclePair = NULL;
	int currentId = this->vehiclePairList->getSize();
	
	while (remainingDemand > 0)
	{
		vehiclePair = new Pair(PairType::IntVsInt);
		vehiclePair->setId(currentId);		

		vehiclePair->set_i_IntValue(this->getVehicleCapacity());
		vehiclePair->set_j_IntValue(depotId);
		this->vehiclePairList->addFrogObjectOrdered(vehiclePair);

		if(remainingDemand >= this->getVehicleCapacity())
		{
			remainingDemand = remainingDemand - this->getVehicleCapacity();
		}
		else
		{
			remainingDemand = 0;
		}
	}
}

int FrogLeapController::getNumberOfCustomers()
{
	if (this->source_t == SourceType::Graph)
	{
		return this->customerList->getSize();
	}
	else
	{
		return this->tspLibEud2DPtr->getNumberOfCustomers();
	}
}

void FrogLeapController::setGraph(Graph * gPtr)
{
	this->graphPtr = gPtr;
}

Graph * FrogLeapController::getGraph()
{
	return this->graphPtr;
}

void FrogLeapController::setSourceType(SourceType source)
{
	this->source_t = source;
}

SourceType FrogLeapController::getSourceType()
{
	return this->source_t;
}

void FrogLeapController::setSolutionGenerationType(SolutionGenerationType v_sgt)
{
	this->sgt = v_sgt;
}

SolutionGenerationType FrogLeapController::getSolutionGenerationType()
{
	return this->sgt;
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
	int auxShortInt;

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

void FrogLeapController::setAsCustomer(int customerInternalId, int demand)
{
	Pair * customerPair = new Pair(PairType::IntVsInt);
	customerPair->set_i_IntValue(customerInternalId);
	customerPair->set_j_IntValue(demand);
	customerPair->setValue(customerInternalId);
	customerPair->setId(customerInternalId);

	this->customerList->addFrogObjectOrdered(customerPair);
}

void FrogLeapController::setAsDepot(int depotInternalId, int capacity)
{

	Pair * depotPair = new Pair(PairType::IntVsInt);
	depotPair->set_i_IntValue(capacity);
	depotPair->set_j_IntValue(capacity);
	depotPair->setValue(depotInternalId);
	depotPair->setId(depotInternalId);

	this->depotList->addFrogObjectOrdered(depotPair);
}

void FrogLeapController::setUpCustomerList()
{
	int n_customers = this->getNumberOfCustomers();

	this->customerArray = new Pair *[n_customers];

	for (int i = 0; i < n_customers; i++)
	{
		this->customerArray[i] = (Pair *) this->customerList->getFrogObject(i);
	}
}

void FrogLeapController::setUpDepotList()
{
	int n_depots = this->getNumberOfDepots();

	this->depotArray = new Pair *[n_depots];

	for (int i = 0; i < n_depots; i++)
	{
		depotArray[i] = (Pair *)this->depotList->getFrogObject(i);
	}
}

void FrogLeapController::loadCustomerAndDepotList()
{
	int size = this->tspLibEud2DPtr->getDimension(), demandOrCapacity;

	IndexList * depotListSection = this->tspLibEud2DPtr->getDepotSection();

	// i is the internal id of the node in the nodeCoordSection collection
	for (int i = 0; i < size; i++)
	{			
		Pair * nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(i);

		int nodeIdLabel = nodeCoord->getId();

		Pair * demandPair = (Pair *) this->tspLibEud2DPtr->getDemandSection()->getFrogObjectById(nodeIdLabel);

		if(demandPair != NULL)
		{
			demandOrCapacity = demandPair->get_j_IntValue();
		}		

		//if does not exist then it is a customer
		if (depotListSection->getItemById(nodeIdLabel) == -1)
		{				
			this->setAsCustomer(i, demandOrCapacity);
		}
		else //is a depot
		{
			this->setAsDepot(i, demandOrCapacity);
		}
	}
}

int FrogLeapController::getLabel(int internalId)
{
	if(this->source_t == SourceType::Graph)
	{
		return this->graphPtr->getVertexIdByPosition(internalId);
	}
	else
	{
		return this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(internalId)->getId();
	}
	
}

int FrogLeapController::getDepotListIndexByInternal(int depotInternalId)
{

	for (int i = 0; i < this->depotList->getSize(); i++)
	{
		if (this->depotArray[i]->getId() == depotInternalId)
		{			
			return i;
		}
	}

	return -1;
}

int FrogLeapController::getCustomerListIndexByInternal(int customerInternalId)
{

	for (int i = 0; i < this->customerList->getSize(); i++)
	{
		if (this->customerArray[i]->getId() == customerInternalId)
		{
			return i;
		}
	}

	return -1;
}

int FrogLeapController::getDepotIndexByLabelId(int depotLabelId)
{
	
	int depotInternalIndex = -1;
	Pair * depotPair = NULL;
	Pair * nodeCoord = NULL;

	for(int i = 0; i < this->getNumberOfDepots(); i++)
	{
		depotPair = (Pair *)this->depotArray[i];

		if(depotPair != NULL)
		{
			depotInternalIndex = depotPair->getId();
			nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(depotInternalIndex);
			if(nodeCoord != NULL)
			{
				int nodeIdLabel = nodeCoord->getId();
				if(nodeIdLabel == depotLabelId)
				{
					return i;
				}
			}
		}		
	}

	return -1;
}

int FrogLeapController::getCustomerIndexByLabelId(int customerLabelId)
{
	int customerInternalIndex = -1;
	Pair * customerPair = NULL;
	Pair * nodeCoord = NULL;

	for (int i = 0; i < this->getNumberOfCustomers(); i++)
	{
		customerPair = (Pair *)this->customerArray[i];

		if (customerPair != NULL)
		{
			customerInternalIndex = customerPair->getId();
			nodeCoord = (Pair *) this->tspLibEud2DPtr->getNodeCoordSection()->getFrogObject(customerInternalIndex);
			if (nodeCoord != NULL)
			{
				int nodeIdLabel = nodeCoord->getId();
				if (nodeIdLabel == customerLabelId)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

FrogObjectCol * FrogLeapController::getTestCustomerSectionList()
{
	return this->testCaseObjPtr->getCustomerSection();
}

void FrogLeapController::setUpCustomerAndDepotLists()
{
	if(this->getSourceType() == SourceType::Tsp2DEuc)
	{
		loadCustomerAndDepotList();		
	}

	setUpCustomerList();
	setUpDepotList();
}

void FrogLeapController::setUpVehicleCapacity()
{
	this->vehicle_capacity = this->tspLibEud2DPtr->getCapacity();
}

long int FrogLeapController::getVehicleCapacity()
{
	return this->vehicle_capacity;
}

void FrogLeapController::setUpVehiclePairList()
{
	int n_vehiclePairs = this->vehiclePairList->getSize();

	this->vehiclePairArray = new Pair *[n_vehiclePairs];

	for (int i = 0; i < n_vehiclePairs; i++)
	{
		vehiclePairArray[i] = (Pair *)this->vehiclePairList->getFrogObject(i);
	}
}

int FrogLeapController::getNumberOfVehicles()
{
	return this->vehiclePairList->getSize();
}

int FrogLeapController::getCustomerInternalId(int position)
{
	return this->customerArray[position]->getId();
}


int FrogLeapController::getCustomerDemandByIndex(int position)
{
	return this->customerArray[position]->get_j_IntValue();
}

int FrogLeapController::getDepotInternalId(int position)
{
	
	return this->depotArray[position]->getId();
}

int  FrogLeapController::getDepotCapacityByIndex(int position)
{
	return this->depotArray[position]->get_i_IntValue();
}

int  FrogLeapController::getDepotRemainingCapacityByIndex(int position)
{
	return this->depotArray[position]->get_j_IntValue();
}

void FrogLeapController::decRemainingDepotCapacity(int position, int capacity_to_dec)
{
	int oldValue = this->depotArray[position]->get_j_IntValue();
	this->depotArray[position]->set_j_IntValue(oldValue - capacity_to_dec);
}

void  FrogLeapController::setDepotRemainingCapacityByIndex(int position, int remaining_capacity)
{
	this->depotArray[position]->set_j_IntValue(remaining_capacity);
}

FrogLeapSolution * FrogLeapController::genRandomFrogLeapSolution(FrogLeapController * controller)
{
	FrogLeapSolution * result = new FrogLeapSolution(this->sgt, this->source_t, this->getNumberOfCustomers(), this->getNumberOfDepots(), 0);

	result->genRandomSolution(controller);
	return result;
}

long int FrogLeapController::getTope()
{
	return TOPE_ITERATIONS;
}

FrogObjectCol * FrogLeapController::createDepotListOrderedByCapacity()
{
	FrogObjectCol * localDepotCol = new FrogObjectCol();
	Pair * current = NULL;

	for(int i = 0; i < this->getNumberOfDepots(); i++)
	{
		current = this->depotArray[i];
		localDepotCol->addFrogObjectOrdered(current);
	}

	return localDepotCol;
}

// create a list ordered by demand in descendant order
FrogObjectCol * FrogLeapController::createCustomerListOrderedByDemand()
{
	FrogObjectCol * localCustomerCol = new FrogObjectCol();
	Pair * current = NULL;

	for (int i = 0; i < this->getNumberOfCustomers(); i++)
	{
		current = this->customerArray[i];
		localCustomerCol->addFrogObjectDescOrdered(current);
	}

	return localCustomerCol;
}

void FrogLeapController::resetDepotRemainingCapacities()
{
	for (int i = 0; i < this->getNumberOfDepots(); i++)
	{		
		resetCapacityOrDemand(this->depotArray[i]);
	}
}

void FrogLeapController::resetCustomerRemainingDemands()
{
	for (int i = 0; i < this->getNumberOfCustomers(); i++)
	{
		resetCapacityOrDemand(this->customerArray[i]);
	}
}

void FrogLeapController::resetCapacityOrDemand(Pair * depotPair)
{
	
	int depotCap = depotPair->get_i_IntValue();
	depotPair->set_j_IntValue(depotCap);
	depotPair->setValue(depotCap);
}

void FrogLeapController::deleteArray(Pair ** arrayPtr, int v_size) {
	int size = v_size;

	for (int i = 0; i < size; i++)
	{
		//delete arrayPtr[i];
		arrayPtr[i] = NULL;
	}

	delete[] arrayPtr;
}

long long int FrogLeapController::getGlobalVehicleId()
{
	long long int result = this->globalVehicleId;

	this->globalVehicleId++;

	return result;
}

int FrogLeapController::getCloserIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localNodeCol)
{
	float closerDistance = FLT_MAX;
	int closerNodeIndex = INT_MAX;

	for (int i = lowBoundIndex; i < topBoundIndex; i++)
	{
		Pair * currentPair = (Pair *)localNodeCol->getFrogObject(i);
		Pair * depotPair = (Pair *) this->depotArray[depotIndex];
		int nodeInternalId = currentPair->getId();
		int depotInternalId = depotPair->getId();
		DistanceTable * dt = this->getDistanceTable();
		float currentDistance = dt->getEdge(nodeInternalId, depotInternalId);
		if (currentDistance < closerDistance)
		{
			closerDistance = currentDistance;
			closerNodeIndex = i;
		}
	}

	return closerNodeIndex;
}

// returns the index in the local collection passed as parameter
int FrogLeapController::getClosestCustomerLocalIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol)
{
	float closerDistance = FLT_MAX;
	int closerNodeIndex = INT_MAX;

	for (int i = lowBoundIndex; i < topBoundIndex; i++)
	{
		Pair * customerIndexPair = (Pair *)localCustomerIndexesCol->getFrogObject(i);
		Pair * depotPair = (Pair *) this->depotArray[depotIndex];
		int customerIndex = customerIndexPair->getId();
		int customerInternalId = this->getCustomerInternalId(customerIndex);
		int depotInternalId = depotPair->getId();
		DistanceTable * dt = this->getDistanceTable();

		float currentDistance = dt->getEdge(customerInternalId, depotInternalId);
		if (currentDistance < closerDistance)
		{
			closerDistance = currentDistance;
			closerNodeIndex = i;
		}
	}

	return closerNodeIndex;
}

// returns the index in the local collection passed as parameter
int FrogLeapController::getClosestCustomerLocalIndexToCustomer(int targetCustomerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol)
{
	float closerDistance = FLT_MAX;
	int closerNodeIndex = INT_MAX;

	for (int i = lowBoundIndex; i < topBoundIndex; i++)
	{
		Pair * customerIndexPair = (Pair *)localCustomerIndexesCol->getFrogObject(i);
		Pair * targetCustomerPair = (Pair *) this->customerArray[targetCustomerIndex];
		int customerIndex = customerIndexPair->getId();
		int customerInternalId = this->getCustomerInternalId(customerIndex);
		int targetCustomerInternalId = targetCustomerPair->getId();
		DistanceTable * dt = this->getDistanceTable();

		float currentDistance = dt->getEdge(customerInternalId, targetCustomerInternalId);
		if (currentDistance < closerDistance)
		{
			closerDistance = currentDistance;
			closerNodeIndex = i;
		}
	}

	return closerNodeIndex;
}

bool FrogLeapController::existInLocalDepotList(int assignedDepotIndex, FrogObjectCol * localDepotCol, int low, int top)
{
	for(int i = low; i < top; i++)
	{
		Pair * currentPair = (Pair *)localDepotCol->getFrogObject(i);
		int depotInternalId = currentPair->getId();
		int depotIndex = this->getDepotListIndexByInternal(depotInternalId);
		
		if(assignedDepotIndex == depotIndex)
		{
			return true;
		}		
	}

	return false;	
}

int FrogLeapController::getClosestDepotIndexOfAssignedCustomers (int targetCustomerIndex, FrogObjectCol * localDepotCol, int low, int top, float & distanceToCustomer)
{
	float closestDistance = FLT_MAX, currentDistance;
	int result = -1;
	Pair * customerPair = NULL;
	int assignedDepotIndex;
	int customerInternalId;
	Pair * targetCustomerPair;
	int targetCustomerInternalId;
	DistanceTable * dt = NULL;

	for(int i = 0; i < this->getNumberOfCustomers(); i++)
	{
		customerPair = this->customerArray[i];

		assignedDepotIndex = customerPair->getAssignedDepotIndex();

		if(assignedDepotIndex != -1)
		{
			if(existInLocalDepotList(assignedDepotIndex, localDepotCol, low, top) == true)
			{
				customerInternalId = customerPair->getId();
				targetCustomerPair = (Pair *)this->customerArray[targetCustomerIndex];
				targetCustomerInternalId = targetCustomerPair->getId();
				dt = this->getDistanceTable();

				currentDistance = dt->getEdge(targetCustomerInternalId, customerInternalId);

				if(currentDistance < closestDistance)
				{
					closestDistance = currentDistance;
					result = customerPair->getAssignedDepotIndex();
					distanceToCustomer = closestDistance;
				}
			}
		}
	} //end for

	return result;
}

void FrogLeapController::setCustomerPairAsAssigned(int customerIndex, int depotIndex)
{
	Pair * customerPair = this->customerArray[customerIndex];

	customerPair->setAssignedDepotIndex(depotIndex);
}

// Set every pair in customerArray as not assigned
void FrogLeapController::resetCustomersAsNotAssigned()
{
	for(int i = 0; i < this->getNumberOfCustomers(); i++)
	{
		Pair * customerPair = this->customerArray[i];
		customerPair->setAssignedDepotIndex(-1);
	}
}

int FrogLeapController::getClosestLocalDepotIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol, float & distance)
{
	float closerDistance = FLT_MAX;
	int closerNodeIndex = INT_MAX;

	for(int i = lowBoundIndex; i < topBoundIndex; i++ )
	{
		Pair * currentDepotPair = (Pair *)localDepotCol->getFrogObject(i);
		Pair * customerPair = (Pair *) this->customerArray[customerIndex];
		int depotInternalId = currentDepotPair->getId();
		int customerInternalId = customerPair->getId();
		DistanceTable * dt = this->getDistanceTable();
		float currentDistance = dt->getEdge(depotInternalId, customerInternalId);
		if(currentDistance < closerDistance)
		{
			closerDistance = currentDistance;
			closerNodeIndex = i;
		}
	}

	distance = closerDistance;

	return closerNodeIndex;	
}

float FrogLeapController::genRandomFloatingNumber(float a, float b)
{
	float randNumber = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	
	float result = a + diff*randNumber;
		 
	this->writeRandomInfo(a, b, result);
		
	return result;
}

//void FrogLeapController::setEngine(std::default_random_engine * generator)
//{
//	this->engine = generator;
//}

//std::default_random_engine * FrogLeapController::getEngine()
//{
//	return this->engine;
//}

void FrogLeapController::openOutPutFile()
{
	outPutFileName = "outPutFL.txt";
	pFile = fopen(outPutFileName, "w");

	if(pFile != NULL)
	{
		fputs("MDVRP ALGORITHM OUTPUT \n", pFile);
	}
}

void FrogLeapController::closeOutPutFile()
{
	fclose(this->pFile);
}

void FrogLeapController::writeSeed()
{
	char buffer[256] = { 0 };

	sprintf(buffer, "SEED USED: ; %lld \n", this->timeSeedUsed);

	fputs(buffer, this->pFile);
}

void FrogLeapController::writeFrogLeapSolution(FrogLeapSolution * fls)
{ 
	//fputs("FrogLeapSolution \n", this->pFile);
	
	fputs("FLS Customer Index: ;", this->pFile);

	for(int i = 0; i < fls->getSize(); i++)
	{
		fprintf(this->pFile, "%d ; ", i);
	}

	fprintf(this->pFile, "\n");

	fputs("FLS Depot Index: ;", this->pFile);

	for (int i = 0; i < fls->getSize(); i++)
	{
		fprintf(this->pFile, "%.3f ;", fls->getFLValue(i));
	}

	fprintf(this->pFile, "\n");
}

void FrogLeapController::writeIterationInfo(long long int i, float currentValue)
{
	char buffer[300] = { 0 };

	printf("\n\n\n Iteration Number i = %lld ; MinCostValue = %.3f ; CurrentCostValue = %.3f \n\n\n", i, this->getMinCostValue(), currentValue);
	sprintf(buffer, "Iteration Number i = ; %lld ; MinCostValue = ; %.3f ; CurrentCostValue = ; %.3f \n", i, this->getMinCostValue(), currentValue);
	fputs(buffer, this->pFile);	
}

void FrogLeapController::writeRandomInfo(float a, float b, float finalRandom)
{
	char buffer[300] = { 0 };

	printf("Random Info a = %.3f b = %.3f finalRandom = %.3f \n", a, b, finalRandom);
	sprintf(buffer, "Random Info a = ; %.3f ; b = ; %.3f m = ; %.3f finalRandom = ; %.3f \n", a, b, finalRandom);
	fputs(buffer, this->pFile);
}

void FrogLeapController::writeExecutionInfo()
{
	char buffer[300] = { 0 };

	sprintf(buffer, "\n \n SHOWING DATA OF FROGLEAPING CONTROLLER \n");
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);

	if (this->ptrBestSolution != NULL)
	{
		this->ptrBestSolution->printFrogObj();
	}
	else
	{
		sprintf(buffer,"\n NO FEASIBLE SOLUTION FOUND: ptrBestSolution IS NULL \n");
		buffer[300] = { 0 };
	}

	sprintf(buffer, "\n Summary of Best Found Solution \n");
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Time Seed used %lld \n", (long long)this->timeSeedUsed);
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Number of success attempts: %d \n", this->successAttempts);
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Number of fail attempts: %d \n", this->failAttempts);
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Number of TOTAL Improvements: %d \n", this->getTotalImprovements());
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Number of Global Search Improvements: %d \n", this->globalImprovements);
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Number of Local Search Improvements: %d \n", this->localSearchImprovements);
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
	sprintf(buffer, "	Evaluation of best found solution is: %.3f \n \n", this->getMinCostValue());
	buffer[300] = { 0 };
	fputs(buffer, this->pFile);
}

