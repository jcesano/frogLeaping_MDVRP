#ifndef DISTVECT_H_   /* Include guard */
#define DISTVECT_H_

#include <iostream>


class Graph;
class Vertex;
class FrogLeapController;

class DistVect
{
	const int infVal = INT_MAX;
	int countV;
	Vertex* dv;
	Vertex** ptr;
	Vertex** ptrCustomers;
	int origin; // Index of the closest unmarked verted	

	int lastMarked;

public:
	DistVect(int v, int v_origin); //Constructor

	~DistVect();

	void setMinDist(int v, int dist);

	void markVert(int v);

	void unmarkVert(int v);

	int getLastMarkedVertex();

	void setLastMarkedVertex(int v);

	int getMinDist(int v);

	int allMarked();

	void setPrevIndex(int currIndexV, int prevIndexV);

	int getPrevIndex(int v);

	void setPrevPathIndex(int currIndexV, int v);

	int getPrevPathIndex(int currIndexV);

	int isUnmarkedVertex(int v);

	void sortSolution();

	void printSolution();

	int getDistanceBtwn(int i, int j);

	void pointCustomers();

	int getCustomerCount();

	void importCustomers(FrogLeapController * controller);
};


#endif
