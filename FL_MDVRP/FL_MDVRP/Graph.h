#ifndef GRAPH_H_   /* Include guard */
#define GRAPH_H_

class DistVect;
class IndexList;
class DecodedFrogLeapSolution;
class DistanceTable;
class FrogLeapSolution;
class Pair;
class FrogObjectCol;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	short int V;    // No. of vertices
	short int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge

	FrogObjectCol * custormerList;

	FrogObjectCol * depotList;

	Pair * * customerArray;

	Pair * * depotArray;

	short int origin;

	short int nVehiclesPerDepot;

	DistanceTable * distanceTable;

public:
	short int const NO_ADJ = -1;

	Graph(short int V);  // Constructor

	~Graph();	// destructor 

	void setOrigin(short int v);

	short int getOrigin();

	// function to add an edge to graph
	void addEdge(short int u, short int v, short int w);

	short int getEdgeValue(short int origin, short int destiny);

	void setAsCustomer(short int customerIndex, int demand);

	void setAsDepot(short int depotId, int capacity);

	short int getNumberOfDepots();

	void setNumberOfVehiclesPerDepot(short int nVehiclesPerDepot);

	short int getNumberOfVehiclesPerDepot();

	short int getNumberOfVehicles();

	void setUpCustomerList();

	void setUpDepotList();

	void setUpCustomerAndDepotLists();
	
	DistVect * dijkstra(short int src);

	short int getNextClosestVertex(DistVect * dvptr); // returns the next unmarked closest adjascent vertex to v	
	
	//short int getNextClosestVertex(short int v, short int * prevPathVertex, DistVect * dvptr, short int src); // returns the next unmarked closest adjascent vertex to v	

	short int getNumberOfCustomers();

	short int getCustomerId(short int position);

	int getCustomerDemandByIndex(short int position);

	short int getDepotId(short int position);

	int getDepotCapacityByIndex(short int position);

	FrogLeapSolution * genRandomFrogLeapSolution();

	void setDistanceTable(DistanceTable * t);

	DistanceTable * getDistanceTable();

	void deleteArray(Pair ** arrayPtr, short int v_size);	
};

#endif
