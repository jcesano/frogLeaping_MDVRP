#include "stdafx.h"
#include "FloatDistanceTable.h"
#include "DistVect.h"
#include "Graph.h"

// Allocates memory for adjacency list
FloatDistanceTable::FloatDistanceTable(int vertexCount)
{
	int i;

	this->V = vertexCount;

	a = new float*[V];

	for (i = 0; i < V; i++) {
		a[i] = new float[V];
	};

	for (i = 0; i < V; i++) {

		for (int j = i + 1; j < V; j++) {
			a[i][j] = NO_ADJ;
			a[j][i] = NO_ADJ;
		}
	}

	for (i = 0; i < V; i++)
	{
		a[i][i] = 0;
	}
}

FloatDistanceTable::~FloatDistanceTable()
{
	for (int i = 0; i < this->V; i++)
	{
		delete a[i];
	}

	delete[] a;
}

void FloatDistanceTable::addEdge(int u, int v, float w)
{
	a[u][v] = w;
	a[v][u] = w;
}

void FloatDistanceTable::addDiagEdge(int u, float w)
{
	a[u][u] = w;
}

float FloatDistanceTable::getEdge(int u, int v)
{
	return this->a[u][v];
}

// load the table with the minimum distance among all vertexes
void FloatDistanceTable::loadMinDistanceTable(DistVect * dv)
{
	for (int i = 0; i < this->V; i++)
	{
		for (short j = 0; j < this->V; j++)
		{
			loadMinDistanceEdge(dv, i, j);
		}
	}
}

void FloatDistanceTable::loadMinDistanceEdge(DistVect * dv, int i, int j)
{
	int min_dist = dv->getDistanceBtwn(i, j);

	this->a[i][j] = min_dist;
	this->a[j][i] = min_dist;
}

void FloatDistanceTable::fillDistanceTable(DistVect * dv, Graph * g)
{
	bool stop = false;
	int nextSrc = -1;

	do
	{
		fillDistanceTableFromPrevVertex(dv, g);

		//this->fillFromPath(dv, g);

		// If all edges were completed then return -1
		nextSrc = this->getNextSourceForDijkstra();

		if (nextSrc != -1)
		{
			// delete dv
			dv = g->dijkstra(nextSrc);
		}
	} while (nextSrc != -1);
	// If all edges were completed then nextSrc = -1
}

void FloatDistanceTable::fillDistanceTableFromPrevVertex(DistVect * dv, Graph * g)
{
	for (int v = 0; v < this->V; v++)
	{
		fillFromPrevVertex(dv, g, v);
	}
}

void FloatDistanceTable::fillFromPrevVertex(DistVect * dv, Graph * g, int v)
{
	int currentVertex = v, prevVertex;
	int edgeValue = -1, acumEdgeValue = 0;

	while (currentVertex != -1)
	{
		prevVertex = dv->getPrevIndex(currentVertex);

		if (prevVertex != -1)
		{
			edgeValue = g->getEdgeValue(currentVertex, prevVertex);
			acumEdgeValue += edgeValue;

			// if not egde previously added
			if (this->getEdge(currentVertex, prevVertex) == NO_ADJ)
			{
				this->addEdge(currentVertex, prevVertex, edgeValue);
			}

			// this is to add an edgge from the origin vertex V. This ocurrs only once so we do not have 
			// to check the edge was previously added
			if (currentVertex != v)
			{
				this->addEdge(v, prevVertex, acumEdgeValue);
			}

		} // end if(prevVertex != -1)

		currentVertex = prevVertex;
	}
}

void FloatDistanceTable::fillFromPath(DistVect * dv, Graph * g)
{
	int currentVertex = dv->getLastMarkedVertex(), prevVertex;
	int edgeValue = -1, acumEdgeValue = 0;

	while (currentVertex != -1)
	{
		prevVertex = dv->getPrevPathIndex(currentVertex);

		if (prevVertex != -1)
		{
			edgeValue = g->getEdgeValue(currentVertex, prevVertex);

			// if not egde previously added
			if (this->getEdge(currentVertex, prevVertex) == NO_ADJ)
			{
				this->addEdge(currentVertex, prevVertex, edgeValue);
			}
		}

		currentVertex = prevVertex;
	}
}

int FloatDistanceTable::getNextSourceForDijkstra()
{
	for (int i = 0; i < this->V; i++)
	{
		for (int j = i; j < this->V; j++)
		{
			if (this->a[i][j] == NO_ADJ)
			{
				return i;
			}
		}
	}

	return -1;
}

bool FloatDistanceTable::allEdgesFilled()
{
	for (int u = 0; u < V; u++) {

		for (int v = 0; v < V; v++) {
			if (a[u][v] == NO_ADJ)
			{
				return false;
			}
		}
	}

	return true;
}

void FloatDistanceTable::printDistanceTable()
{
	printf("Printing Distance Table \n");

	for (int i = 0; i < this->V; i++)
	{
		for (int j = i + 1; j < this->V; j++)
		{
			printf("(%d, %d) = %d ", i, j, this->a[i][j]);
		}

		printf(" \n");
	}
}
