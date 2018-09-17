#ifndef FLOATDISTANCETABLE_H_   /* Include guard */
#define FLOATDISTANCETABLE_H_

class DistVect;
class Graph;

class FloatDistanceTable
{
	int  V;    // No. of vertices
	float ** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	
public:
	int const NO_ADJ = -1;

	FloatDistanceTable(int V);  // Constructor

	~FloatDistanceTable();

	void addEdge(int u, int v, float w); // function to add an edge to graph

	void addDiagEdge(int u, float w);

	float getEdge(int u, int v);

	void loadMinDistanceTable(DistVect * dv); // load the table with the minimum distance among all vertexes

	void loadMinDistanceEdge(DistVect * dv, int i, int j); // load minimum distance between i and j

	void fillDistanceTable(DistVect * dv, Graph * g); // fill the distance table with the minimum distance between each pair of vertexes

	void printDistanceTable();

	void fillDistanceTableFromPrevVertex(DistVect * dv, Graph * g);

	void fillFromPrevVertex(DistVect * dv, Graph * g, int v);

	void fillFromPath(DistVect * dv, Graph * g);

	int getNextSourceForDijkstra();

	bool allEdgesFilled();
};

#endif

