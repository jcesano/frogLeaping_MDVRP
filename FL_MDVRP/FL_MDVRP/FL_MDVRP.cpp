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
	const int infVal = 300000;
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

	int allMarked();

};

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	// Create a priority queue to store vertices that
	// are being preprocessed. This is weird syntax in C++.
	// Refer below link for details of this syntax
	// http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF) except the origin that is initialized with 0
		
	


	
	
	/* Looping till priority queue becomes empty (or all
	distances are not finalized) */
	int stop = 0
	while (!stop)
	{
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int u = pq.top().second;
		pq.pop();

		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent
			// of u.
			int v = (*i).first;
			int weight = (*i).second;

			//  If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	// Print shortest distances stored in dist[]
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
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

	// setting the default "random" minInd
	if (v == 0 || v == countV)
		minInd = 1;
	else
	{
		minInd = origin + 1;
	};

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
	int min = INT_MAX, minIndex = -1;
		
	for (int i = 0; i < countV; i++) 
	{
		if(dv[i].isUnmarkedVertex() && dv[i].getDistance < min)
		{
			min = dv[i].getDistance();
			minInd = i;
		}
	}

	return minIndex;
}

int DistVect::allMarked()
{
	int stop = 0,i=0, result = 1;

	while (stop==0 && i < countV)
	{
		if (marked[i] == 0)
		{
			stop = 1;
			result = 0;
		};
	};//end while

	return result;
}

int DistVect::GetMin()
{
	return dv[minInd];
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
	if (marked == 0)
		return 1;
	else
		return 0;
	
}

int Vertex::getPrevIndex()
{
	return prevIndex;
}

void Vertex::setPrevIndex(int prevIndexV)
{
	prevIndex = prevIndexV;
}
