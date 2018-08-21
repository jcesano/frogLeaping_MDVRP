#include "stdafx.h"
#include "DistVect.h"
#include "Vertex.h"
#include "Graph.h"

DistVect::DistVect(short int v, short int v_origin)
{
	dv = new Vertex[v];
	ptr = new Vertex*[v];

	this->lastMarked = -1;

	for (short int i = 0; i < v; i++) {
		dv[i].setDistance(infVal);
		dv[i].setId(i);
		dv[i].setPrevIndex(-1);
		dv[i].unmarkVertex();
		ptr[i] = &dv[i];
	}

	//setting the origin of the graph with distance equals to 0
	this->origin = v_origin;
	dv[origin].setDistance(0);

	countV = v;
}

DistVect::~DistVect()
{
	delete [] this->ptr;
	delete[] this->ptrCustomers;
	delete [] this->dv;	
}

void DistVect::setMinDist(int v, int dist)
{
	dv[v].setDistance(dist);
}

void DistVect::markVert(int v)
{
	dv[v].markVertex();
	this->setLastMarkedVertex(v);
}

void DistVect::unmarkVert(int v)
{
	dv[v].unmarkVertex();
}

int DistVect::getMinDist(int v)
{
	return dv[v].getDistance();

}

int DistVect::allMarked()
{
	int stop = 0, i = 0, result = 1;

	while (stop == 0 && i < countV)
	{
		if (dv[i].isUnmarkedVertex())
		{
			stop = 1;
			result = 0;
		};

		i++;

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

void DistVect::setPrevPathIndex(int currIndexV, int v)
{
	this->dv[currIndexV].setPrevPathIndex(v);
}

int DistVect::getPrevPathIndex(int currIndexV)
{
	return this->dv[currIndexV].getPrevPathIndex();
}

int DistVect::isUnmarkedVertex(int v)
{
	return dv[v].isUnmarkedVertex();
}

void DistVect::sortSolution()
{
	Vertex * temp;

	for (int i = 0; i < countV; i++)
	{
		for (int j = 0; j<countV - i - 1; j++)
		{
			if (this->ptr[j]->getDistance() > this->ptr[j + 1]->getDistance())
			{
				temp = ptr[j]; // assigning memory address
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = temp;
			}
		}
	}
}

void DistVect::printSolution()
{
	printf("Vertex |  Previous Vertex | Distance from source: %d \n", this->origin);

	for (int i = 0; i < countV; i++)
	{
		printf("%d      |    %d      |        %d  \n", ptr[i]->getId(), ptr[i]->getPrevPathIndex(), ptr[i]->getDistance());
	}
}

short int DistVect::getDistanceBtwn(short int i, short int j)
{
	short int v_origin, v_end;

	if (i < j)
	{
		v_origin = i;
		v_end = j;
	}
	else
	{
		v_origin = j;
		v_end = i;
	};

	short int prevDistance, currentDistance, currentDiffDistance;

	prevDistance = 0;
	currentDistance = ptr[v_origin]->getDistance();
	currentDiffDistance = 0;

	for (short int w = v_origin + 1; w <= v_end; w++)
	{
		prevDistance = currentDistance;
		currentDistance = ptr[w]->getDistance();
		currentDiffDistance = currentDiffDistance + (currentDistance - prevDistance);
	}

	return currentDiffDistance;
}

short int DistVect::getCustomerCount()
{
	short int custCnt = 0;

	for (int i = 0; i< this->countV; i++)
	{
		switch (this->dv[i].getVertexType())
		{
		case Customer:
			custCnt++;
			break;
		default:
			break;
		}
	}

	return custCnt;
}

void DistVect::importCustomers(Graph * g)
{
	short int custId;

	for (short int i = 0; i < g->getNumberOfCustomers(); i++)
	{
		custId = g->getCustomerId(i);
		this->dv[custId].setVertexType(VertexType::Customer);
	}
}

void DistVect::pointCustomers()
{
	short int customerCount = 0;

	customerCount = this->getCustomerCount();

	this->ptrCustomers = new Vertex*[customerCount];

	customerCount = 0;

	for (int i = 0; i < this->countV; i++)
	{
		switch (this->dv[i].getVertexType())
		{
		case Customer:
			ptrCustomers[customerCount] = &dv[i];
			break;
		default:
			break;
		}
	}
}


short int DistVect::getLastMarkedVertex()
{
	return this->lastMarked;
}

void DistVect::setLastMarkedVertex(short int v)
{
	this->lastMarked = v;
}
