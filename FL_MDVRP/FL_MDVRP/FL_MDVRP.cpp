// FL_MDVRP.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "SortedLinkedList.h"
#include "FrogLeapSolution.h"
#include <iostream>
#include <time.h>




using namespace std;


class FeasSolNode; //forward declaration
class FeasibleSolution; //forward declaration

class Permutation
{
	int i;
	int j;

public:
	Permutation();

	int get_i_Value();
	int get_j_Value();
};

Permutation::Permutation()
{
	i = -1;
	j = -1;
}

int Permutation::get_i_Value()
{
	return i;
}

int Permutation::get_j_Value()
{
	return j;
}

class FeasibleSolCol
{
	FeasSolNode * head;

	int colSize;

public:
	FeasibleSolCol();

	void AddFeasibleSol(FeasibleSolution * fs);

	void printFeasSolCol();

	int getSize();

	FeasibleSolution * getFeasibleSolution(int i);
	
	void removeFeasibleSolutions(FeasibleSolCol * sourceSolutionCol);

	void removeFeasibleSolution(FeasibleSolution * fs);

	FeasibleSolCol * removeRepetedItems();

	int areThereRepetedItems();

	int feasibleSolExists(FeasibleSolution * fs);

	void ConcatCol(FeasibleSolCol * fs);
};

FeasibleSolCol::FeasibleSolCol()
{
	head = NULL;

	this->colSize = 0;
}

class FeasSolNode
{
	FeasibleSolution * feasibleSol;

	FeasSolNode * next;

public:

	FeasSolNode(FeasibleSolution * fs, FeasSolNode * fsnodeptr);

	void printNodeItems();

	FeasibleSolution * getSolution();

	FeasSolNode * getNextFeasSolNode();

	void setNextFeasSolNode(FeasSolNode * node);
};

FeasSolNode::FeasSolNode(FeasibleSolution * fs, FeasSolNode * fsnodeptr)
{
	feasibleSol = fs;
	next = fsnodeptr;
}

class FeasibleSolution
{
	short int * solVect;

	short int size;

	bool isFeasible;

	time_t timeSeedUsed;

public:
	FeasibleSolution(short int n);

	FeasibleSolution(FeasibleSolution * fs);

	void setSolFactValue(short int pos, short int val);

	int getSolFactValue(short int pos);

	FeasibleSolution * swapItems(short int pos1, short int pos2);

	FeasibleSolCol * genOneSwapPermutations();

	FeasibleSolCol * genPermutations(short int distance, FeasibleSolCol * sourceSolutionCol);

	bool isTheSame(FeasibleSolution * fs);

	void printFeasibleSolution();

	FeasibleSolution * genRandomSwapSolution(short int bottom, short int top);

	FeasibleSolCol * genRandomFeasibleSolCol();
	
	void setRandomSolution();

	void setIndexesAsValues();

	void removeValue(short int position);

	short int popRandomValue();

	int factorial(short int n);
};


FeasibleSolution::FeasibleSolution(short int n)
{
	solVect = new short int[n];
	size = n;
	isFeasible = true;

	// initialize random seed
	timeSeedUsed = time(NULL);

	srand(timeSeedUsed);

}

FeasibleSolution::FeasibleSolution(FeasibleSolution * fs)
{
	solVect = new short int[fs->size];
	size = fs->size	;
	isFeasible = true;

	for(short int i = 0; i<this->size;i++)
	{
		this->solVect[i] = fs->getSolFactValue(i);
	}

	// initialize random seed
	timeSeedUsed = time(NULL);

	srand(timeSeedUsed);

}

void FeasibleSolution::setSolFactValue(short int pos, short int val)
{
	solVect[pos] = val;
};

int FeasibleSolution::getSolFactValue(short int pos)
{
	return this->solVect[pos];
}

// Swap elements i and j: return a new FeasibleSolution containing in position i, the element of position j and viceversa
FeasibleSolution * FeasibleSolution::swapItems(short int pos1, short int pos2)
{
	short int tempValue;

	tempValue = this->getSolFactValue(pos1); //store value of position pos1

	// in position pos1, set element of position pos2
	this->setSolFactValue(pos1, this->getSolFactValue(pos2));

	// in position pos2, set element of position pos1
	this->setSolFactValue(pos2, tempValue);

	return this;
};

bool FeasibleSolution::isTheSame(FeasibleSolution * fs)
{
	bool result = true;
	short int i = 0;
	
	if(this->size != fs->size)
	{
		return 0;
	};

	while(result == true && i < this->size)
	{
		if(this->solVect[i] != fs->solVect[i])
		{
			result = false;
		}

		i++;
	};

	return result;
}

void FeasibleSolution::printFeasibleSolution()
{
	for(short int i = 0; i < this->size;i++)
	{
		printf("%d ", this->solVect[i]);
	}

	printf("\n");
}

FeasibleSolution * FeasibleSolution::genRandomSwapSolution(short int bottom, short int top)
{
	short int randomValue;

	FeasibleSolution * randomFs = new FeasibleSolution(this);

	if(top - bottom == 1)
	{
		randomFs->swapItems(bottom, top);
	}
	else{
			
			do
			{
				randomValue = (rand() % (top + 1 - bottom)) + bottom;
			} while (randomValue == bottom);
			
			randomFs->swapItems(bottom, randomValue);
		}		

	return randomFs;
}

FeasibleSolCol * FeasibleSolution::genRandomFeasibleSolCol()
{
	FeasibleSolCol * randomFsCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	randomFsCol->AddFeasibleSol(this);

	fs = this;
	for(short int i = 0; i < this->size-1; i++)
	{
		fs = fs->genRandomSwapSolution(i, this->size - 1);

		randomFsCol->AddFeasibleSol(fs);
	}

	return randomFsCol;
}

void FeasibleSolution::setRandomSolution()
{
	FeasibleSolution * fsIndex = new FeasibleSolution(this->size);

	fsIndex->setIndexesAsValues();

	for(short int i = 0; i <= this->size-1; i++)
	{
		short int randValue = fsIndex->popRandomValue();

		this->setSolFactValue(i, randValue);
	}	

	delete fsIndex;
}

FeasibleSolCol * FeasibleSolution::genPermutations(short int distance, FeasibleSolCol * sourceSolutionCol)
{
	if (distance == 1)
	{
		FeasibleSolCol * fscol = this->genOneSwapPermutations();

		if(sourceSolutionCol == NULL)
		{
			return fscol;
		}
		else{
				fscol->removeFeasibleSolutions(sourceSolutionCol);
				return fscol;
			}		
	}
	else{
			FeasibleSolCol * tempCol = this->genOneSwapPermutations(), * tempCol_i = NULL, * fullCol = new FeasibleSolCol();
			FeasibleSolution * fs_i;			

			
			if (sourceSolutionCol == NULL)
			{
				sourceSolutionCol = new FeasibleSolCol();
			}

			sourceSolutionCol->AddFeasibleSol(this);

			for(int i = 1; i <= tempCol->getSize();i++)
			{
				fs_i = tempCol->getFeasibleSolution(i);

				sourceSolutionCol->AddFeasibleSol(fs_i);

				tempCol_i = fs_i->genPermutations(distance - 1, sourceSolutionCol);

				fullCol->ConcatCol(tempCol_i);
			}

			//sourceSolutionCol->AddFeasibleSol(this);

			//fullCol->removeFeasibleSolutions(sourceSolutionCol);

			return fullCol;
		}
}

FeasibleSolCol * FeasibleSolution::genOneSwapPermutations()
{
	FeasibleSolCol * colptr = NULL;
	
	if (this->size == 1) 
	{
		return NULL;
	}// end if
	
	if (this->size == 2)
	{
		colptr = new FeasibleSolCol();	
		
		// swap first and second and generate a new FeasibleSolution
		colptr->AddFeasibleSol(this->swapItems(0, 1));
	}
	else
		{
			FeasibleSolution * colptr_i_j;
			colptr = new FeasibleSolCol();

			for(short int i=0; i < this->size;i++)
			{
				for(short int j = i+1; j < this->size;j++)
				{
					colptr_i_j = new FeasibleSolution(this);

					colptr_i_j->swapItems(i, j);

					colptr->AddFeasibleSol(colptr_i_j);
				}//end for j
			}//end for i
		}// end else

	return colptr;
};


void FeasibleSolution::setIndexesAsValues()
{
	for (short int i = 0; i < this->size; i++)
	{
		this->setSolFactValue(i, i);
	};
}

void FeasibleSolution::removeValue(short int position)
{
	for(int i = position; i < this->size-1; i++)
	{
		this->setSolFactValue(i, this->getSolFactValue(i + 1));
	}

	this->size--;
}

short int FeasibleSolution::popRandomValue()
{
	short int randomIndex = rand() % ( this->size); // random number between 0 and size-1

	short int randomValue = this->getSolFactValue(randomIndex);

	this->removeValue(randomIndex);

	return randomValue;
}

int FeasibleSolution::factorial(short int n)
{
	long int result = 1;

	if(n == 0)
	{
		return 1;
	};

	for(int i = 1; i <= n; i++)
	{
		result = result * i;
	};

	return result;
}

class Vertex
{
	int distance;
	int marked;
	int index;		// index of vertex in graph. Is the id of the vertex.
	int prevIndex; // index of previous vertex in the shortest path from origin
	int prevPathIndex; // index of previous vertex in the marking vertex path
	
	short int vertexType; // type of vertex: 0 = "simple node"; 1 = "Customer Node"; 2 = "Depot"

public:
	Vertex(); //Constructor
	int getDistance();
	void setDistance(int distanceV);
	void markVertex();
	void unmarkVertex();
	int isUnmarkedVertex();
	int getIndex();
	void setIndex(int v);
	int getPrevIndex();
	int getVertexType();
	void setPrevIndex(int prevInd);
	int getPrevPathIndex();
	void setPrevPathIndex(int v);
	void setVertexType(short int vertexType);
};

Vertex::Vertex()
{
	this->distance = -1;
	this->index = -1;
	this->marked = 0;
	this->prevIndex = -2;
	this->prevPathIndex = -2;
	this->vertexType = 0;
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

int Vertex::getIndex()
{
	return index;
}

void Vertex::setIndex(int v)
{
	index = v;
}

int Vertex::getPrevIndex()
{
	return prevIndex;
}

int Vertex::getVertexType()
{
	return this->vertexType;
}

void Vertex::setPrevIndex(int prevIndexV)
{
	prevIndex = prevIndexV;
}

int Vertex::getPrevPathIndex()
{
	return this->prevPathIndex;
}

void Vertex::setPrevPathIndex(int v)
{
	this->prevPathIndex = v;
}

void Vertex::setVertexType(short int v_Type)
{
	this->vertexType = v_Type;
}

class DistVect
{
	const int infVal = INT_MAX;
	int countV;
	Vertex* dv;
	Vertex** ptr;
	int origin; // Index of the closest unmarked verted	

public:
	DistVect(int v, int v_origin); //Constructor

	void setMinDist(int v, int dist); 

	void markVert(int v);

	void unmarkVert(int v);

	int getMinDist(int v);

	int allMarked();

	void setPrevIndex(int currIndexV, int prevIndexV);

	int getPrevIndex(int v);

	void setPrevPathIndex(int currIndexV, int v);

	int getPrevPathIndex(int currIndexV);
	
	int isUnmarkedVertex(int v);

	void sortSolution();

	void printSolution();

	short int getDistanceBtwn(short int i, short int j);

};


DistVect::DistVect(int v, int v_origin)
{
	dv = new Vertex[v];
	ptr = new Vertex*[v];

	for (int i = 0; i < v; i++) {
		dv[i].setDistance(infVal);
		dv[i].setIndex(i);
		dv[i].setPrevIndex(-1);
		dv[i].unmarkVertex();
		ptr[i] = &dv[i];
	}

	//setting the origin of the graph with distance equals to 0
	this->origin = v_origin;
	dv[origin].setDistance(0);

	countV = v;
}

void DistVect::setMinDist(int v, int dist)
{
	dv[v].setDistance(dist);
}

void DistVect::markVert(int v)
{
	dv[v].markVertex();
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
	printf("Vertex | Distance from source: %d \n", this->origin);

	for (int i = 0; i < countV; i++)
	{
		printf("%d      |          %d  \n", i, ptr[i]->getDistance());
	}
}

short int DistVect::getDistanceBtwn(short int i, short int j)
{
	short int v_origin, v_end;

	if(i < j)
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

	for(short int w = v_origin + 1; w <= v_end; w++)
	{
		prevDistance = currentDistance;
		currentDistance = ptr[w]->getDistance();
		currentDiffDistance = currentDiffDistance + (currentDistance - prevDistance);
	}

	return currentDiffDistance;
}


class DistanceTable
{
	short int V;    // No. of vertices
	short int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge

public:
	short int const NO_ADJ = -1;

	DistanceTable(short int V);  // Constructor

								 // function to add an edge to graph
	void addEdge(short int u, short int v, short int w);

	void addDiagEdge(short int u, short int w);

	void loadMinDistanceTable(DistVect * dv); // load the table with the minimum distance among all vertexes

	void loadMinDistanceEdge(DistVect * dv, short int i, short int j); // load minimum distance between i and j

	void fillDistanceTable(DistVect * dv); // fill the distance table with the minimum distance between each pair of vertexes

	void printDistanceTable();
};

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

	for( i = 0; i < this->V; i++)
	{
		for (int j = 0; j < i; j++)
		{
			dist_i_j = dv->getDistanceBtwn(i, j);
			this->addEdge(i, j, dist_i_j);
		}
	}

	for(i = 0; i < this->V; i++)
	{
		this->addDiagEdge(i, 0);
	}
}

void DistanceTable::printDistanceTable()
{
	printf("Printing Distance Table \n");

	for(short int i = 0; i < this->V; i++)
	{
		for(short int j = i+1; j < this->V; j++)
		{
			printf("(%d, %d) = %d ", i, j, this->a[i][j]);
		}

		printf(" \n");
	}	
}

class IndexListNode
{
	short int index;
	IndexListNode * next;
public:
	IndexListNode(short int index, IndexListNode * nextPtr); // Constructor

	short int getIndex();

	IndexListNode * getNextPtr();

	void setIndex(short int index);

	void setNextPtr(IndexListNode * nextPtr);

};

IndexListNode::IndexListNode(short int v_index, IndexListNode * nextPtr)
{
	this->index = v_index;
	this->next = nextPtr;
}

short int IndexListNode::getIndex()
{
	return this->index;
}

IndexListNode * IndexListNode::getNextPtr()
{
	return this->next;
}

void IndexListNode::setIndex(short int v_index)
{
	this->index = v_index;
}

void IndexListNode::setNextPtr(IndexListNode * nextPtr)
{
	this->next = nextPtr;
}

class IndexList 
{
	IndexListNode * head;

	short int size;

public:

	IndexList(); // Constructor
	
	void addIndex(short int index);

	void removeIndex(short int index);
};

IndexList::IndexList()
{
	this->head = NULL;
	this->size = 0;
}

void IndexList::addIndex(short int index)
{
	IndexListNode * node = new IndexListNode(index, head);

	head = node;

	this->size++;
}

void IndexList::removeIndex(short int index)
{
	IndexListNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	while (nodePtr != NULL)
	{
		if (nodePtr->getIndex() == index)
		{
			// if the element is located at the begining of the list
			if (head == nodePtr)
			{
				nodePtrTemp = head;
				head = head->getNextPtr();
				nodePtr = head;
				
				// add a delete nodePtrTemp
				this->size--;
			}
			else {
					nodePtrTemp = nodePtr;
					nodePtrPrev->setNextPtr(nodePtr->getNextPtr());
					nodePtr = nodePtrTemp->getNextPtr();
					
					// add a delete nodePtrTemp
					this->size--;
				 }
		} // if (nodePtr->getIndex == index)
		else {
				nodePtrPrev = nodePtr;
				nodePtr = nodePtr->getNextPtr();
			 }
		
	} // end while (nodePtr != NULL)
}

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	short int V;    // No. of vertices
	short int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	
	IndexList * custormerList;
	IndexList * depotList;

	short int origin;

public:
	short int const NO_ADJ = -1;

	Graph(short int V);  // Constructor

	void setOrigin(short int v);

	short int getOrigin();

				   // function to add an edge to graph
	void addEdge(short int u, short int v, short int w);

	void setAsCustomer(short int v);

	void setAsDepot(short int v);

	DistVect * dijkstra(short int src);

	short int getNextClosestVertex(short int v, short int * prevPathVertex, DistVect * dvptr); // returns the next unmarked closest adjascent vertex to v	
};

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

				if(dvptr->getMinDist(v) < curr_closestVertDistance)
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

	for(short int i=0;i < V;i++)
	{
		if(a[v][i] != NO_ADJ && i != v && a[v][i] < minDistVertex && dvptr->isUnmarkedVertex(i))
		{
			minDistVertex = a[v][i];
			minDistVertexInd = i;
		}
	}

	if(minDistVertexInd == -1)
	{
		return this->getNextClosestVertex(dvptr->getPrevPathIndex(v), prevPathVertex, dvptr);
	}
	else{
			(*prevPathVertex) = v;
			return minDistVertexInd;
		}		
}

int main()
{
    
	// create the graph given in above fugure
	int V = 9;
	Graph g(V);

	//  making above shown graph
	/* main to test Dijkstra algorithm 
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

	DistVect * dv = g.dijkstra(0); */
	
	
	/* Main to test all permutations of distance = 1 and distance = 2 
	FeasibleSolution * fs;
	FeasibleSolCol * fscol;

	fs = new FeasibleSolution(V);

	// setting indexes as values in the FeasibleSolution	
	for(int i = 0; i<V;i++)
	{
		fs->setSolFactValue(i, i);
	}
		
	int distance;
	distance = 1;
	fscol = fs->genPermutations(distance,NULL);
	fscol->printFeasSolCol();
	*/

	/* main to test random vector (FeasibleSolution)
	FeasibleSolution * fs = new FeasibleSolution(V);

	fs->setRandomSolution();

	fs->printFeasibleSolution();
	*/

	/* main to test the random solution generator 
	FeasibleSolution * fs = new FeasibleSolution(V);
	fs->setRandomSolution();
	FeasibleSolCol * fscol = fs->genRandomFeasibleSolCol();

	fscol->printFeasSolCol();
	*/

	/* main to fill the Distance Table 
	DistanceTable dt(V);

	dt.fillDistanceTable(dv);

	dt.printDistanceTable(); */

	short int size = 5;
	FrogLeapSolution * fls = new FrogLeapSolution(size);

	


	return 0;
}

void FeasSolNode::printNodeItems()
{
	if(this->feasibleSol != NULL)
	{
		this->feasibleSol->printFeasibleSolution();
	}

	FeasSolNode * tempNodePtr = next;
	while (tempNodePtr != NULL)
	{
		tempNodePtr->feasibleSol->printFeasibleSolution();
		tempNodePtr = tempNodePtr->next;
	};
}

FeasibleSolution * FeasSolNode::getSolution()
{
	return this->feasibleSol;
}

FeasSolNode * FeasSolNode::getNextFeasSolNode()
{
	return this->next;
}


void FeasSolNode::setNextFeasSolNode(FeasSolNode * node)
{
	this->next = node;
}

void FeasibleSolCol::AddFeasibleSol(FeasibleSolution * fs)
{
	FeasSolNode * ptr;

	ptr = new FeasSolNode(fs, head);

	head = ptr;

	this->colSize = this->colSize + 1;
};

void FeasibleSolCol::printFeasSolCol()
{
	printf("Printing permutations \n");

	if (head != NULL)
	{
		head->printNodeItems();
	}
}

int FeasibleSolCol::getSize()
{
	return this->colSize;
}

//returns the solution in position i in the list, first position is 1.
FeasibleSolution * FeasibleSolCol::getFeasibleSolution(int i)
{
	// assign the first element
	FeasSolNode * result = head;

	if(this->head != NULL)
	{
		// if i == 1 then for is not executed, otherwise we start from i = 2 
		// cause result is pointing to the first Node already 
		for(int j = 2; j <= i; j++)
		{
			result = result->getNextFeasSolNode();
		}
	}

	if (result != NULL)
	{
		return result->getSolution();
	}
	
	return NULL;	
}

void FeasibleSolCol::removeFeasibleSolutions(FeasibleSolCol * sourceSolutionCol)
{
	if (sourceSolutionCol != NULL)
	{
		for (int i = 1; i <= sourceSolutionCol->colSize; i++)
		{
			FeasibleSolution * fs = sourceSolutionCol->getFeasibleSolution(i);
			if (this->feasibleSolExists(fs) == 1)
			{
				this->removeFeasibleSolution(fs);
			}
		}
	}

}

void FeasibleSolCol::removeFeasibleSolution(FeasibleSolution * fs)
{
	FeasSolNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	if(fs != NULL)
	{
		while (nodePtr != NULL)
		{
			if (nodePtr->getSolution() != NULL)
			{
				if (nodePtr->getSolution()->isTheSame(fs) == 1)
				{

					// if the element is located at the begining of the list
					if (head == nodePtr)
					{
						nodePtrTemp = head;
						head = head->getNextFeasSolNode();
						nodePtr = head;
						// add a delete nodePtrTemp
						this->colSize--;
					}
					else{
							nodePtrTemp = nodePtr;
							nodePtrPrev->setNextFeasSolNode(nodePtr->getNextFeasSolNode());
							nodePtr = nodePtrTemp->getNextFeasSolNode();
							// add a delete nodePtrTemp
							this->colSize--;
						}
				}
				else{
						nodePtrPrev = nodePtr;
						nodePtr = nodePtr->getNextFeasSolNode();
					}
			} // end if (nodePtr->getSolution() != NULL)
		} // end while (nodePtr != NULL)
	} // end if(fs != NULL)
}

FeasibleSolCol * FeasibleSolCol::removeRepetedItems()
{
	FeasibleSolCol * remRepItemsCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	for(int i = 1; i <= this->getSize(); i++)
	{
		fs = this->getFeasibleSolution(i);

		if(remRepItemsCol->feasibleSolExists(fs) == 0)
		{
			remRepItemsCol->AddFeasibleSol(fs);
		}		
	}

	return remRepItemsCol;
}

// It returns the position of the first repeated item. Otherwise returns 0.
int FeasibleSolCol::areThereRepetedItems()
{
	int repeated = 0, i = 1;
	FeasibleSolCol * auxCol = new FeasibleSolCol();
	FeasibleSolution * fs = NULL;

	while (i <= this->getSize() && repeated == 0)
	{
		fs = this->getFeasibleSolution(i);
		if (auxCol->feasibleSolExists(fs) == 0)
		{
			repeated = i;
		}
	}

	return repeated;
}

int FeasibleSolCol::feasibleSolExists(FeasibleSolution * fs)
{
	int found = 0, i;

	if(this != NULL)
	{
		FeasSolNode * nodePtr;
		FeasibleSolution * solPtr;

		i = 1;

		nodePtr = this->head;

		while (found == 0 && i <= this->getSize() && nodePtr != NULL)
		{
			solPtr = nodePtr->getSolution();

			found = solPtr->isTheSame(fs);

			nodePtr = nodePtr->getNextFeasSolNode();
			i = i + 1;
		}		
	}
	
	return found;
}

void FeasibleSolCol::ConcatCol(FeasibleSolCol * fscol)
{
	FeasSolNode * tmp;
	FeasibleSolution * fs;

	for(int i = 1; i <= fscol->getSize();i++)
	{
		fs = fscol->getFeasibleSolution(i);
		this->AddFeasibleSol(fs);
	}
}
