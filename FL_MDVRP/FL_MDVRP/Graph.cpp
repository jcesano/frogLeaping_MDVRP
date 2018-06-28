#include "stdafx.h"
#include "Graph.h"
#include "DistVect.h"
#include "IndexList.h"

// Allocates memory for adjacency list
Graph::Graph(short int vertexCount)
{
	this->V = vertexCount;

	a = new short int*[V];

	for (short int i = 0; i < V; i++) {
		a[i] = new short int[V];
	};

	for (short int u = 0; u < V; u++) {

		for (short int v = 0; v < V; v++) {
			a[u][v] = NO_ADJ;
		}
	}

	this->custormerList = new IndexList();
	this->depotList = new IndexList();

	this->origin = -1;
}

void Graph::setOrigin(short int v)
{
	this->origin = v;
}

short int Graph::getOrigin()
{
	return this->origin;
}

void Graph::addEdge(short int u, short int v, short int w)
{
	a[u][v] = w;
	a[v][u] = w;
}

void Graph::setAsCustomer(short int v)
{
	this->custormerList->addIndex(v);
}

void Graph::setAsDepot(short int v)
{
	this->depotList->addIndex(v);
}

// Prints shortest paths from src to all other vertices
DistVect * Graph::dijkstra(short int src)
{
	// The output array.  dist[i] will hold the shortest
	// distance from src to i
	DistVect * dvptr = new DistVect(V, src);

	//bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	//for (int i = 0; i < V; i++)
	//dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	//dist[src] = 0;

	short int currentPathVertex = src, prevPathVertex = -1;

	// Find shortest path for all vertices
	for (short int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		//int u = minDistance(dist, sptSet);
		short int currDistance = dvptr->getMinDist(currentPathVertex);

		// Mark the picked vertex as processed
		//sptSet[u] = true;
		dvptr->markVert(currentPathVertex);
		dvptr->setPrevPathIndex(currentPathVertex, prevPathVertex);

		short int curr_closestVertDistance = INT_MAX; // is the closest distance to u from all adj vertexes
		short int curr_closestVert = -1;              // is the closest index to u from all adj vertexes

													  // Update dist value of the adjacent vertices of the picked vertex.
		for (short int v = 0; v < V; v++)
		{


			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (a[currentPathVertex][v] != NO_ADJ && dvptr->getMinDist(currentPathVertex) + a[currentPathVertex][v] < dvptr->getMinDist(v))
			{
				dvptr->setMinDist(v, dvptr->getMinDist(currentPathVertex) + a[currentPathVertex][v]);
				dvptr->setPrevIndex(v, currentPathVertex);

				if (dvptr->getMinDist(v) < curr_closestVertDistance)
				{
					curr_closestVertDistance = dvptr->getMinDist(v);
					curr_closestVert = v;
				}
			}
		}

		currentPathVertex = getNextClosestVertex(currentPathVertex, &prevPathVertex, dvptr);

	} //end for(int count = 0; count < V - 1; count++)

	dvptr->sortSolution();

	// print the constructed distance array
	dvptr->printSolution();

	return dvptr;
}

short int Graph::getNextClosestVertex(short int v, short int * prevPathVertex, DistVect* dvptr)
{
	short int minDistVertex = SHRT_MAX;
	short int minDistVertexInd = -1;

	for (short int i = 0; i < V; i++)
	{
		if (a[v][i] != NO_ADJ && i != v && a[v][i] < minDistVertex && dvptr->isUnmarkedVertex(i))
		{
			minDistVertex = a[v][i];
			minDistVertexInd = i;
		}
	}

	if (minDistVertexInd == -1)
	{
		return this->getNextClosestVertex(dvptr->getPrevPathIndex(v), prevPathVertex, dvptr);
	}
	else {
		(*prevPathVertex) = v;
		return minDistVertexInd;
	}
}

short int Graph::getCustomerCount()
{
	return this->custormerList->getSize();
}

short int Graph::getCustomerId(short int position)
{
	return this->custormerList->getItem(position);
}