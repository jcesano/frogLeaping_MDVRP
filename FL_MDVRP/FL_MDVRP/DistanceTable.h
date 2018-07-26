#ifndef DISTANCETABLE_H_   /* Include guard */
#define DISTANCETABLE_H_

class DistVect;
class Graph;

class DistanceTable
{
	short int V;    // No. of vertices
	short int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge

public:
	short int const NO_ADJ = -1;

	DistanceTable(short int V);  // Constructor
								 
	void addEdge(short int u, short int v, short int w); // function to add an edge to graph

	void addDiagEdge(short int u, short int w);

	short int getEdge(short int u, short int v);

	void loadMinDistanceTable(DistVect * dv); // load the table with the minimum distance among all vertexes

	void loadMinDistanceEdge(DistVect * dv, short int i, short int j); // load minimum distance between i and j

	void fillDistanceTable(DistVect * dv, Graph * g); // fill the distance table with the minimum distance between each pair of vertexes

	void printDistanceTable();

	void fillDistanceTableFromPrevVertex(DistVect * dv, Graph * g);

	void fillFromPrevVertex(DistVect * dv, Graph * g, short int v);

	void fillDistanceTableFromPrevPath(DistVect * dv, Graph * g);

	bool allEdgesFilled();
};

#endif
