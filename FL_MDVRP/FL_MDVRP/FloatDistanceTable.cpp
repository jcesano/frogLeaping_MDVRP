#include "stdafx.h"
#include "FloatDistanceTable.h"
#include "DistVect.h"
#include "Graph.h"

// Allocates memory for adjacency list
FloatDistanceTable::FloatDistanceTable(short int vertexCount)
{
	short int i;

	this->V = vertexCount;

	a = new float*[V];

	for (i = 0; i < V; i++) {
		a[i] = new float[V];
	};

	for (i = 0; i < V; i++) {

		for (short int j = i + 1; j < V; j++) {
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
	for (short int i = 0; i < this->V; i++)
	{
		delete a[i];
	}

	delete[] a;
}

void FloatDistanceTable::addEdge(short int u, short int v, float w)
{
	a[u][v] = w;
	a[v][u] = w;
}

void FloatDistanceTable::addDiagEdge(short int u, float w)
{
	a[u][u] = w;
}

float FloatDistanceTable::getEdge(short int u, short int v)
{
	return this->a[u][v];
}

// load the table with the minimum distance among all vertexes
void FloatDistanceTable::loadMinDistanceTable(DistVect * dv)
{
	for (short int i = 0; i < this->V; i++)
	{
		for (short j = 0; j < this->V; j++)
		{
			loadMinDistanceEdge(dv, i, j);
		}
	}
}

void FloatDistanceTable::loadMinDistanceEdge(DistVect * dv, short int i, short int j)
{
	short int min_dist = dv->getDistanceBtwn(i, j);

	this->a[i][j] = min_dist;
	this->a[j][i] = min_dist;
}

void FloatDistanceTable::fillDistanceTable(DistVect * dv, Graph * g)
{
	bool stop = false;
	short int nextSrc = -1;

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
	for (short int v = 0; v < this->V; v++)
	{
		fillFromPrevVertex(dv, g, v);
	}
}

void FloatDistanceTable::fillFromPrevVertex(DistVect * dv, Graph * g, short int v)
{
	short int currentVertex = v, prevVertex;
	short int edgeValue = -1, acumEdgeValue = 0;

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
	short int currentVertex = dv->getLastMarkedVertex(), prevVertex;
	short int edgeValue = -1, acumEdgeValue = 0;

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

short int FloatDistanceTable::getNextSourceForDijkstra()
{
	for (short int i = 0; i < this->V; i++)
	{
		for (short int j = i; j < this->V; j++)
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
	for (short int u = 0; u < V; u++) {

		for (short int v = 0; v < V; v++) {
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

	for (short int i = 0; i < this->V; i++)
	{
		for (short int j = i + 1; j < this->V; j++)
		{
			printf("(%d, %d) = %d ", i, j, this->a[i][j]);
		}

		printf(" \n");
	}
}
