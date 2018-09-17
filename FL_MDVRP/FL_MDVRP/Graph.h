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
	int V;    // No. of vertices
	short int** a;

	int origin;

	FrogObjectCol * vertexCol;

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	DistanceTable * distanceTable;

public:
	int const NO_ADJ = -1;

	Graph(int V);  // Constructor

	~Graph();	// destructor 

	void setOrigin(int v);

	int getOrigin();

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	int getEdgeValue(int origin, int destiny);

	DistVect * dijkstra(int src);

	int getNextClosestVertex(DistVect * dvptr); // returns the next unmarked closest adjascent vertex to v	
	
	//int getNextClosestVertex(int v, int * prevPathVertex, DistVect * dvptr, int src); // returns the next unmarked closest adjascent vertex to v	
	
	int getPositionVertexById(int vertexId);

	int getVertexIdByPosition(int internalId);

	int getPositionOrAddVertexById(int vertexId);

	FrogLeapSolution * genRandomFrogLeapSolution();

	void setDistanceTable(DistanceTable * t);

	DistanceTable * getDistanceTable();	
};

#endif
