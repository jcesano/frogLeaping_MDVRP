#include "stdafx.h"
#include "DistanceTable.h"
#include "DistVect.h"
#include "Graph.h"

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

short int DistanceTable::getEdge(short int u, short int v)
{
	return this->a[u][v];
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

void DistanceTable::fillDistanceTable(DistVect * dv, Graph * g)
{
	bool stop = false;
	
	do 
	{
		fillDistanceTableFromPrevVertex(dv, g);

		fillDistanceTableFromPrevPath(dv, g);		
		
	} while (!allEdgesFilled());
}

void DistanceTable::fillDistanceTableFromPrevVertex(DistVect * dv, Graph * g)
{
	for(int v = 0; v <= this->V; v++)
	{
		fillFromPrevVertex(dv, g, v);
	}

}

void DistanceTable::fillFromPrevVertex(DistVect * dv, Graph * g, short int v)
{
	short int currentVertex = v, prevVertex;
	int edgeValue = -1, acumEdgeValue = 0;

	while (currentVertex != -1)
	{
		prevVertex = dv->getPrevIndex(currentVertex);

		if(prevVertex != -1)
		{
			edgeValue = g->getEdgeValue(currentVertex, prevVertex);
			acumEdgeValue += edgeValue;

			if(this->getEdge(currentVertex, prevVertex) == NO_ADJ)
			{
				this->addEdge(currentVertex, prevVertex, edgeValue);
			}			

			if(currentVertex != v)
			{
				if (this->getEdge(v, prevVertex) == NO_ADJ)
				{
					this->addEdge(v, prevVertex, acumEdgeValue);
				}				
			}			
		}

		currentVertex = prevVertex;
	}
}

void DistanceTable::fillDistanceTableFromPrevPath(DistVect * dv, Graph * g)
{

}

bool DistanceTable::allEdgesFilled()
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
