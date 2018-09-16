#include "stdafx.h"
#include "FrogLeapSolution.h"
#include "FrogLeapController.h"
#include "DecodedFrogLeapSolution.h"
//#include "FrogObjectCol.h"
//#include "IndexList.h"
#include "FeasibleSolution.h"
//#include "DistanceTable.h"
#include "Graph.h"
#include "FeasibleSolCol.h"
#include "DistanceTable.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <string>

using std::string;

using namespace std;

void setDepot(FrogLeapController *controller, Graph * g, short int vertIdLabel, short int capacity)
{
	short int vertexIndex = g->getPositionVertexById(vertIdLabel);

	if (vertexIndex != -1)
	{
		controller->setAsDepot(vertexIndex, capacity);
	}
}

void setCustomer(FrogLeapController *controller, Graph * g, short int vertIdLabel, short int capacity)
{
	short int vertexIndex = g->getPositionVertexById(vertIdLabel);

	if (vertexIndex != -1)
	{
		controller->setAsCustomer(vertexIndex, capacity);
	}
}


int main()
{
    
	auto start_time = std::chrono::high_resolution_clock::now();

	// create the graph given in above fugure
	
	short int V = 9;
	
	FrogLeapController * controller = new FrogLeapController();

	char * fileName = "casog01.vrp";

	controller->setSourceType(SourceType::Tsp2DEuc);

	if(controller->getSourceType() == SourceType::Graph)
	{
		Graph * g = new Graph(V);

		g->addEdge(0, 1, 4);
		g->addEdge(0, 7, 8);
		g->addEdge(1, 2, 8);
		g->addEdge(1, 7, 11);
		g->addEdge(2, 3, 7);
		g->addEdge(2, 8, 2);
		g->addEdge(2, 5, 4);
		g->addEdge(3, 4, 9);
		g->addEdge(3, 5, 14);
		g->addEdge(4, 5, 10);
		g->addEdge(5, 6, 2);
		g->addEdge(6, 7, 1);
		g->addEdge(6, 8, 6);
		g->addEdge(7, 8, 7);

		short int vertexIndex = g->getPositionVertexById(0);
		DistVect * dv = NULL;

		if(vertexIndex != -1)
		{
			dv = g->dijkstra(vertexIndex);
		}		
		
		/* main to test Dijkstra algorithm */
		
		setDepot(controller, g, 0, 12);
		setDepot(controller, g, 6, 14);

		setCustomer(controller, g, 1, 3);
		setCustomer(controller, g, 2, 3);
		setCustomer(controller, g, 3, 3);
		setCustomer(controller, g, 4, 3);
		setCustomer(controller, g, 7, 3);
		setCustomer(controller, g, 8, 3);

		/* main to fill the Distance Table */
		DistanceTable * dt = new DistanceTable(V);

		dt->fillDistanceTable(dv, g);

		dt->printDistanceTable();

		g->setDistanceTable(dt);

		controller->setGraph(g);

		controller->setDistanceTable(dt);

		dt = NULL;

		controller->setUpCustomerAndDepotLists();
	} 
	else
	{
		controller->loadTSPEUC2D_Data(fileName);
		controller->setUpCustomerAndDepotLists();
		controller->loadDistanceTable();
	}

	//controller->setUpVehiclesPerDepot();	
	
	/* Main to test all permutations of distance = 1 and distance = 2 

	FeasibleSolution * fs;
	FeasibleSolCol * fscol;

	fs = new FeasibleSolution(V);
	*/

	/* setting indexes as values in the FeasibleSolution	
	for(int i = 0; i<V;i++)
	{
		fs->setSolFactValue(i, i);
	}
		
	int distance;
	distance = 1;
	fscol = fs->genPermutations(distance,NULL, controller);
	fscol->printFeasSolCol();
	*/

	/* main to test random vector (FeasibleSolution) 
	fs = new FeasibleSolution(V);

	fs->setRandomSolution();

	fs->printFeasibleSolution();
	*/

	/* main to test the random solution generator 
	//FeasibleSolution * fs = new FeasibleSolution(V);
	fs->setRandomSolution();
	fscol = fs->genRandomFeasibleSolCol();

	fscol->printFeasSolCol(); 
	*/

	
	
	/* main test frogSolution */
	short int nDepots = controller->getNumberOfDepots();
	short int nCustomers = controller->getNumberOfCustomers();

	FrogLeapSolution * fls = new FrogLeapSolution(SolutionGenerationType::FrogLeaping, controller->getSourceType(), nCustomers, nDepots, 0);

	DecodedFrogLeapSolution * dfls_1 = NULL;
	int evalSol;	
	const int itNumber = controller->getNumberOfIterations();

	for(int i=0; i < itNumber; i++)
	{
		printf("ITERATION NUMBER %d", i);

		if (i == 49) {
			printf("\n STOP BUG HERE \n");

		}
		fls->genRandomSolution();

		fls->printFrogObj();

		dfls_1 = fls->decodeSolution(controller);

		if (dfls_1->getIsFeasibleSolution() == true) 
		{
			controller->incSuccessAttempts();
			evalSol = dfls_1->evalSolution();
			printf("Evaluation of frogLeapingSolution is = %d   ", evalSol);

			if(evalSol < controller->getMinCostValue())
			{
				controller->incGlobalSearchImprovements();
				controller->setBestDecodedFrogLeapSolution(dfls_1);
				controller->setMinCostValue(evalSol);
				//apply local search
				controller->applyLocalSearch();
			}
			else
			{
				dfls_1->printFrogObj();
				delete dfls_1;
			}
		}
		else
		{
			dfls_1->printFrogObj();
			controller->incFailAttempts();
			delete dfls_1;
		}		
	}
	
	controller->printCtrl();
	
	//delete g;
	delete fls;
	delete controller;

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	std::cout << "FrogLeaping took " <<
		std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " to run.\n";

	return 0;
}

 