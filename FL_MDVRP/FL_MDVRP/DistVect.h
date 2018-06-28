#ifndef DISTVECT_H_   /* Include guard */
#define DISTVECT_H_

#include <iostream>


class Graph;
class Vertex;

class DistVect
{
	const int infVal = INT_MAX;
	int countV;
	Vertex* dv;
	Vertex** ptr;
	Vertex** ptrCustomers;
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

	void pointCustomers();

	short int getCustomerCount();

	void importCustomers(Graph * g);
};


#endif
