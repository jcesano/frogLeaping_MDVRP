#include "stdafx.h"
#include "DistanceTable.h"
#include "DistVect.h"

// Allocates memory for adjacency list
DistanceTable::DistanceTable(short int vertexCount)
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
}

void DistanceTable::addEdge(short int u, short int v, short int w)
{
	a[u][v] = w;
	a[v][u] = w;
}

void DistanceTable::addDiagEdge(short int u, short int w)
{
	a[u][u] = w;
}

// load the table with the minimum distance among all vertexes
void DistanceTable::loadMinDistanceTable(DistVect * dv)
{
	for (short int i = 0; i < this->V; i++)
	{
		for (short j = 0; j < this->V; j++)
		{
			loadMinDistanceEdge(dv, i, j);
		}
	}
}

void DistanceTable::loadMinDistanceEdge(DistVect * dv, short int i, short int j)
{
	short int min_dist = dv->getDistanceBtwn(i, j);

	this->a[i][j] = min_dist;
	this->a[j][i] = min_dist;
}

void DistanceTable::fillDistanceTable(DistVect * dv)
{
	int i, dist_i_j;

	for (i = 0; i < this->V; i++)
	{
		for (int j = 0; j < i; j++)
		{
			dist_i_j = dv->getDistanceBtwn(i, j);
			this->addEdge(i, j, dist_i_j);
		}
	}

	for (i = 0; i < this->V; i++)
	{
		this->addDiagEdge(i, 0);
	}
}

void DistanceTable::printDistanceTable()
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
