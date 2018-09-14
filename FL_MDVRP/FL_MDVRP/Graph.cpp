#include "stdafx.h"
#include "Graph.h"
#include "DistVect.h"
#include "IndexList.h"
#include "DecodedFrogLeapSolution.h"
#include "Vehicle.h"
#include "FrogLeapSolution.h"
#include "Pair.h"
#include "DistanceTable.h"
#include "FrogObjectCol.h"

#include <stdlib.h>
#include <stdio.h>

// Allocates memory for adjacency list
Graph::Graph(short int vertexCount)
{
	this->V = vertexCount;
	this->vertexCol = new FrogObjectCol();

	a = new short int*[V];

	for (short int i = 0; i < V; i++) {
		a[i] = new short int[V];
	};

	for (short int u = 0; u < V; u++) {

		for (short int v = 0; v < V; v++) {
			a[u][v] = NO_ADJ;
		}
	}

	this->origin = -1;
}

Graph::~Graph()
{
	if(this->distanceTable != NULL)
	{
		delete this->distanceTable;
	}	
}

void Graph::setOrigin(short int v)
{
	short int v_index = this->vertexCol->getFrogObjectPositionById(v);

	if(v_index != -1)
	{
		this->origin = v_index;
	}	
}

short int Graph::getOrigin()
{
	return this->origin;
}

short int Graph::getPositionVertexById(short int vertexId)
{
	return this->vertexCol->getFrogObjectPositionById(vertexId);
}

short int Graph::getVertexIdByPosition(short int internalId)
{
	Pair * v_pair = (Pair *) this->vertexCol->getFrogObject(internalId);

	return v_pair->get_j_IntValue();
}

short int Graph::getPositionOrAddVertexById(short int vertexId)
{
	short int u_vertexIndex = this->vertexCol->getFrogObjectPositionById(vertexId);
	Pair * u_vertexPair;

	if (u_vertexIndex == -1)
	{
		u_vertexPair = new Pair(PairType::IntVsInt);
		u_vertexPair->setId(vertexId);
		u_vertexPair->setValue(vertexId);
		short int lastPosition = this->vertexCol->getSize();
		u_vertexPair->set_i_IntValue(lastPosition);
		u_vertexPair->set_j_IntValue(vertexId);
		this->vertexCol->AddLastFrogObject(u_vertexPair);
		return lastPosition;
	}
	else
	{
		return u_vertexIndex;
	}	
}

void Graph::addEdge(short int u, short int v, short int w)
{
	short int u_index, v_index;

	u_index = this->getPositionOrAddVertexById(u);
	v_index = this->getPositionOrAddVertexById(v);
	a[u_index][v_index] = w;
	a[v_index][u_index] = w;
}

// Prints shortest paths from src to all other vertices
DistVect * Graph::dijkstra(short int src)
{
	// The output array.  dist[i] will hold the shortest
	// distance from src to i
	DistVect * dvptr = new DistVect(V, src);

	//bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	//for (int i = 0; i < V; i++)
	//dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	//dist[src] = 0;

	short int currentPathVertex = src, prevPathVertex = -1;

	// Find shortest path for all vertices
	for (short int count = 0; count < V; count++)
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

		currentPathVertex = getNextClosestVertex(dvptr);

	} //end for(int count = 0; count < V - 1; count++)

	dvptr->sortSolution();

	// print the constructed distance array
	dvptr->printSolution();

	return dvptr;
}

short int Graph::getNextClosestVertex(DistVect* dvptr)
{
	short int minDistVertex = SHRT_MAX;
	short int minDistVertexInd = -1;
	
	if(dvptr->allMarked())
	{
		return -1;
	}

	for (short int i = 0; i < V; i++)
	{
		if (dvptr->getMinDist(i) < minDistVertex && dvptr->isUnmarkedVertex(i))
		{
			minDistVertex = dvptr->getMinDist(i);
			minDistVertexInd = i;
		}
	}

	return minDistVertexInd;
}

//short int Graph::getNextClosestVertex(short int v, short int * prevPathVertex, DistVect* dvptr, short int src)
//{
//	short int minDistVertex = SHRT_MAX;
//	short int minDistVertexInd = -1;
//
//	if(dvptr->allMarked())
//	{
//		return -1;
//	}
//
//	for (short int i = 0; i < V; i++)
//	{
//		if (a[v][i] != NO_ADJ && i != v && a[v][i] < minDistVertex && dvptr->isUnmarkedVertex(i))
//		{
//			minDistVertex = a[v][i];
//			minDistVertexInd = i;
//		}
//	}
//
//	if (minDistVertexInd == -1)
//	{
//		return this->getNextClosestVertex(dvptr->getPrevPathIndex(v), prevPathVertex, dvptr, src);
//	}
//	else 
//	{
//		(*prevPathVertex) = v;
//		
//		if(minDistVertexInd == 3)
//		{
//			printf("debug");
//		}
//
//		return minDistVertexInd;
//	}
//}

FrogLeapSolution * Graph::genRandomFrogLeapSolution()
{
	return nullptr;
}

void Graph::setDistanceTable(DistanceTable * t)
{
	distanceTable = t;
}

DistanceTable * Graph::getDistanceTable()
{
	return this->distanceTable;
}

short int Graph::getEdgeValue(short int origin, short int destiny)
{
	return this->a[origin][destiny];
}
