#include "stdafx.h"

#include "FrogLeapSolution.h"
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

using namespace std;

int main()
{
    
	// create the graph given in above fugure
	
	short int V = 9;
	short int nVehiclesPerDepot = 2;

	Graph * g = new Graph (V);

	//  making above shown graph
	/* main to test Dijkstra algorithm */
	g->setAsDepot(0);
	g->setAsDepot(6);

	g->setNumberOfVehiclesPerDepot(nVehiclesPerDepot);

	g->setAsCustomer(1);
	g->setAsCustomer(2);
	g->setAsCustomer(3);
	g->setAsCustomer(4);
	g->setAsCustomer(7);
	g->setAsCustomer(8);
	
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
	
	g->setUpCustomerAndDepotLists();

	DistVect * dv = g->dijkstra(0); 
	

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
	fscol = fs->genPermutations(distance,NULL);
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

	/* main to fill the Distance Table */
	DistanceTable * dt = new DistanceTable(V);

	dt->fillDistanceTable(dv);

	dt->printDistanceTable(); 

	g->setDistanceTable(dt);
	

	/* main test frogSolution */
	short int nDepots = g->getNumberOfDepots();
	short int nCustomers = g->getNumberOfCustomers();

	FrogLeapSolution * fls = new FrogLeapSolution(nCustomers, nVehiclesPerDepot * nDepots, nDepots, 0);

	fls->genRandomSolution();

	fls->printFrogObj();

	DecodedFrogLeapSolution * dfls_1 = fls->decodeFrogLeapSolution(g);

	int evalSol = dfls_1->evalSolution(g);
	
	printf("Evaluation of frogLeapingSolution is = %d", evalSol);

	return 0;
}

