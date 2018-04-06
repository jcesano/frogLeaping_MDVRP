// FL_MDVRP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


using namespace std;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int V;    // No. of vertices
	int** a;
			  // In a weighted graph, we need to store vertex
			  // and weight pair for every edge
	

public:
	Graph(int V);  // Constructor

				   // function to add an edge to graph
	void addEdge(int u, int v, int w);

	void dijkstra(int src);

	// prints shortest path from s
	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	a = new int*[V];

	for (int i = 0; i < V; i++) {
		a[i] = new int[V];
	};
}

void Graph::addEdge(int u, int v, int w)
{
	a[u][v] = w;
}

class Vertex
{
	int distance;
	int marked;
	int prevIndex; // index of previous vertex in the shortest path from origin
public:
	Vertex(); //Constructor
	int getDistance();
	void setDistance(int distanceV);
	void markVertex();
	void unmarkVertex();
	int isUnmarkedVertex();
	int getPrevIndex();
	void setPrevIndex(int prevInd);
};

class DistVect
{
	const int infVal = INT_MAX;
	int countV;
	Vertex* dv;
	int minInd; // Index of the closest unmarked verted
	int minVal; // Distance of the closest unmarked vertex

public:
	DistVect(int v, int origin); //Constructor

	void setMinDist(int v, int dist); 

	void markVert(int v);

	void unmarkVert(int v);

	int getMinInd();

	int getMinDist();

	int allMarked();

	void setPrevIndex(int currIndexV, int prevIndexV);

	int getPrevIndex(int v);

};

// Prints shortest paths from src to all other vertices
void Graph::dijkstra(int src)
{
	// The output array.  dist[i] will hold the shortest
	// distance from src to i
	DistVect dv = new DistVect(src, V);

	//bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

					// Initialize all distances as INFINITE and stpSet[] as false
	//for (int i = 0; i < V; i++)
		//dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	//dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		//int u = minDistance(dist, sptSet);
		int u = dv.getMinDist();

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist, V);
}


int main()
{
    
	// create the graph given in above fugure
	int V = 9;
	Graph g(V);

	//  making above shown graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.shortestPath(0);

	return 0;
}

DistVect::DistVect(int v, int origin)
{
	dv = new Vertex[v];

	for (int i = 0; i < v; i++) {
		dv[i].setDistance(infVal);
		dv[i].setPrevIndex(-1);
		dv[i].unmarkVertex();
	}

	//setting the origin of the graph with distance equals to 0
	dv[origin].setDistance(0);

	minInd = origin;

	minVal = dv[minInd].getDistance();
}

void DistVect::setMinDist(int v, int dist)
{
	dv[v].setDistance(dist);
}

void DistVect:: markVert(int v)
{
	dv[v].markVertex();	
}

void DistVect::unmarkVert(int v)
{
	dv[v].unmarkVertex();
}

int DistVect::getMinInd()
{
	int min = INT_MAX;
		
	for (int i = 0; i < countV; i++) 
	{
		if(dv[i].isUnmarkedVertex() && dv[i].getDistance < min)
		{
			min = dv[i].getDistance();
			minInd = i;
		}
	}

	return minInd;
}

int DistVect::getMinDist()
{
	return dv[minInd].getDistance();
	
}

int DistVect::allMarked()
{
	int stop = 0,i=0, result = 1;

	while (stop==0 && i < countV)
	{
		if (dv[i].isUnmarkedVertex())
		{
			stop = 1;
			result = 0;
		};
	};//end while

	return result;
}

void DistVect::setPrevIndex(int currIndexV, int prevIndexV)
{
	dv[currIndexV].setPrevIndex(prevIndexV);
}

int DistVect::getPrevIndex(int v) 
{
	return dv[v].getPrevIndex();

}

int Vertex::getDistance()
{
	return distance;
}

void Vertex::setDistance(int distanceV)
{
	distance = distanceV;
}

void Vertex::markVertex()
{
	marked = 1;
}

void Vertex::unmarkVertex()
{
	marked = 0;
}

int Vertex::isUnmarkedVertex()
{
	return (marked == 0);
}

int Vertex::getPrevIndex()
{
	return prevIndex;
}

void Vertex::setPrevIndex(int prevIndexV)
{
	prevIndex = prevIndexV;
}
