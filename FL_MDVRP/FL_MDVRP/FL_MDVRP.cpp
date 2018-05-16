// FL_MDVRP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


using namespace std;

class FeasSolNode; //forward declaration
class FeasibleSolution; //forward declaration

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

	void removeFeasibleSolutions(FeasibleSolCol * sourceSolutionCol);

	void removeFeasibleSolution(FeasibleSolution * fs);
};

FeasSolNode::FeasSolNode(FeasibleSolution * fs, FeasSolNode * fsnodeptr)
{
	feasibleSol = fs;
	next = fsnodeptr;
}

class FeasibleSolution
{
	int * solVect;

	int size;

	bool isFeasible;

public:
	FeasibleSolution(int n);

	FeasibleSolution(FeasibleSolution * fs);

	void setSolFactValue(int pos, int val);

	int getSolFactValue(int pos);

	FeasibleSolution * swapItems(int pos1, int pos2);

	FeasibleSolCol * genOneSwapPermutations();

	FeasibleSolCol * genPermutations(int distance, FeasibleSolCol * sourceSolutionCol);

	int isTheSame(FeasibleSolution * fs);

	void printFeasibleSolution();
};


FeasibleSolution::FeasibleSolution(int n)
{
	solVect = new int[n];
	size = n;
	isFeasible = true;
}

FeasibleSolution::FeasibleSolution(FeasibleSolution * fs)
{
	solVect = new int[fs->size];
	size = fs->size	;
	isFeasible = true;

	for(int i = 0; i<this->size;i++)
	{
		this->solVect[i] = fs->getSolFactValue(i);
	}
}

void FeasibleSolution::setSolFactValue(int pos, int val)
{
	solVect[pos] = val;
};

int FeasibleSolution::getSolFactValue(int pos)
{
	return this->solVect[pos];
}

// Swap elements i and j: return a new FeasibleSolution containing in position i, the element of position j and viceversa
FeasibleSolution * FeasibleSolution::swapItems(int pos1, int pos2)
{
	int tempValue;

	tempValue = this->getSolFactValue(pos1); //store value of position pos1

	// in position pos1, set element of position pos2
	this->setSolFactValue(pos1, this->getSolFactValue(pos2));

	// in position pos2, set element of position pos1
	this->setSolFactValue(pos2, tempValue);

	return this;
};

int FeasibleSolution::isTheSame(FeasibleSolution * fs)
{
	int result = 1, i = 0;


	if(this->size != fs->size)
	{
		return 0;
	};

	while(result == 1 && i < this->size)
	{
		if(this->solVect[i] != fs->solVect[i])
		{
			result = 0;
		}

		i++;
	};

	return result;
}

void FeasibleSolution::printFeasibleSolution()
{
	for(int i = 0; i < this->size;i++)
	{
		printf("%d ", this->solVect[i]);
	}

	printf("\n");
}

FeasibleSolCol * FeasibleSolution::genPermutations(int distance, FeasibleSolCol * sourceSolutionCol)
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

			for(int i=0; i < this->size;i++)
			{
				for(int j = i+1; j < this->size;j++)
				{
					colptr_i_j = new FeasibleSolution(this);

					colptr_i_j->swapItems(i, j);

					colptr->AddFeasibleSol(colptr_i_j);
				}//end for j
			}//end for i
		}// end else

	return colptr;
};


class Vertex
{
	int distance;
	int marked;
	int index;		// index of vertex in graph. Is the id of the vertex.
	int prevIndex; // index of previous vertex in the shortest path from origin
	int prevPathIndex; // index of previous vertex in the marking vertex path

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
	void setPrevIndex(int prevInd);
	int getPrevPathIndex();
	void setPrevPathIndex(int v);
};

Vertex::Vertex()
{
	this->distance = -1;
	this->index = -1;
	this->marked = 0;
	this->prevIndex = -2;
	this->prevPathIndex = -2;
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


// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int V;    // No. of vertices
	int** a;
	// In a weighted graph, we need to store vertex
	// and weight pair for every edge



public:
	int const NO_ADJ = -1;

	Graph(int V);  // Constructor

				   // function to add an edge to graph
	void addEdge(int u, int v, int w);

	void dijkstra(int src);

	int getNextClosestVertex(int v, int * prevPathVertex, DistVect * dvptr); // returns the next unmarked closest adjascent vertex to v	
};

// Allocates memory for adjacency list
Graph::Graph(int vertexCount)
{
	this->V = vertexCount;

	a = new int*[V];

	for (int i = 0; i < V; i++) {
		a[i] = new int[V];
	};

	for (int u = 0; u < V; u++) {

		for (int v = 0; v < V; v++) {
			a[u][v] = NO_ADJ;
		}
	}
}

void Graph::addEdge(int u, int v, int w)
{
	a[u][v] = w;
	a[v][u] = w;
}

// Prints shortest paths from src to all other vertices
void Graph::dijkstra(int src)
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

	int currentPathVertex = src, prevPathVertex = -1;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		//int u = minDistance(dist, sptSet);
		int currDistance = dvptr->getMinDist(currentPathVertex);

		// Mark the picked vertex as processed
		//sptSet[u] = true;
		dvptr->markVert(currentPathVertex);
		dvptr->setPrevPathIndex(currentPathVertex, prevPathVertex);

		int curr_closestVertDistance = INT_MAX; // is the closest distance to u from all adj vertexes
		int curr_closestVert = -1;              // is the closest index to u from all adj vertexes

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)
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
}

int Graph::getNextClosestVertex(int v, int * prevPathVertex, DistVect* dvptr)
{	
	int minDistVertex = INT_MAX;
	int minDistVertexInd = -1;

	for(int i=0;i < V;i++)
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
	int V = 5;
	//Graph g(V);

	//  making above shown graph
	//g.addEdge(0, 1, 4);
	//g.addEdge(0, 7, 8);
	//g.addEdge(1, 2, 8);
	//g.addEdge(1, 7, 11);
	//g.addEdge(2, 3, 7);
	//g.addEdge(2, 8, 2);
	//g.addEdge(2, 5, 4);
	//g.addEdge(3, 4, 9);
	//g.addEdge(3, 5, 14);
	//g.addEdge(4, 5, 10);
	//g.addEdge(5, 6, 2);
	//g.addEdge(6, 7, 1);
	//g.addEdge(6, 8, 6);
	//g.addEdge(7, 8, 7);

	//g.dijkstra(0);

	FeasibleSolution * fs;
	FeasibleSolCol * fscol;

	fs = new FeasibleSolution(V);

	for(int i = 0; i<V;i++)
	{
		fs->setSolFactValue(i, i);
	}

	int distance;
	distance = 2;
	fscol = fs->genPermutations(distance,NULL);


	fscol->printFeasSolCol();

	return 0;
}

void FeasSolNode::printNodeItems()
{
	this->feasibleSol->printFeasibleSolution();

	if(next != NULL)
	{
		this->next->printNodeItems();
	}	
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
