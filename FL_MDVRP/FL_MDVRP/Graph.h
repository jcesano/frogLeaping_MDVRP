#ifndef GRAPH_H_   /* Include guard */
#define GRAPH_H_

class DistVect;
class IndexList;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	short int V;    // No. of vertices
	short int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge

	IndexList * custormerList;
	IndexList * depotList;

	short int origin;

	short int nVehiclesPerDepot;

public:
	short int const NO_ADJ = -1;

	Graph(short int V);  // Constructor

	void setOrigin(short int v);

	short int getOrigin();

	// function to add an edge to graph
	void addEdge(short int u, short int v, short int w);

	void setAsCustomer(short int v);

	void setAsDepot(short int v);

	void setNumberOfVehiclesPerDepot(short int nVehiclesPerDepot);

	short int getNumberOfVehiclesPerDepot();

	DistVect * dijkstra(short int src);

	short int getNextClosestVertex(short int v, short int * prevPathVertex, DistVect * dvptr); // returns the next unmarked closest adjascent vertex to v	

	short int getCustomerCount();

	short int getCustomerId(short int position);
};

#endif
