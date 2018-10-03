#ifndef TESTCASEOBJ_H_   /* Include guard */
#define TESTCASEOBJ_H_

#include "FrogObject.h"

class FrogObjectCol;
class IndexList;
class Pair;


class TestCaseObj : public FrogObject
{
private:
	long int totalCapacityOfDepots;
	long int totalCustomerLoad;
	float totalPathCost;

	char * name;
	char * comment;
	char * type;
	int dimension;
	char * edge_weight_type;
	int capacity;
	FrogObjectCol * vehicleTestCol;
	FrogObjectCol * customer_section;
	FrogObjectCol * depot_section;

public:
	TestCaseObj();

	virtual ~TestCaseObj();

	void setName(char * v_name);

	char * getName();

	void setComment(char * v_comment);
	char *getComment();

	void setType(char * v_type);
	char * getType();

	void setDimension(int v_dimension);
	int getDimension();

	void setEdgeWeightType(char * v_EdgeWeightType);
	char * getEdgeWeightType();

	void setCapacity(int v_capacity);
	int getCapacity();

	void AddVehicleItem(Pair * v_pair_coord);

	void AddCustomerItem(Pair * v_pair_demand);	

	float getEucDistance(int u, int v);

	float calcEuc2D(Pair * origin, Pair * destination);

	int getNumberOfDepots();

	int getNumberOfCustomers();

	FrogObjectCol * getCustomerSection();

	FrogObjectCol * getDemandSection();
	

	// abstract methods
	void printFrogObj();

	bool isTheSame(FrogObject * fs);
};
#endif
