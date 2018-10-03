#include "stdafx.h"
#include "TestCaseObj.h"
#include "TspLibEuc2D.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>  
#include "FrogObjectCol.h"
#include "IndexList.h"
#include "Pair.h"
#include <math.h>

TestCaseObj::TestCaseObj() :FrogObject()
{
	this->name = NULL;
	this->comment = NULL;
	this->edge_weight_type = NULL;
	this->capacity = 0;
	this->vehicleTestCol = new FrogObjectCol();
	this->customer_section = new FrogObjectCol();
	this->depot_section = new FrogObjectCol();
}

TestCaseObj::~TestCaseObj()
{

}

void TestCaseObj::setName(char * v_name)
{
	this->name = v_name;
}

char * TestCaseObj::getName()
{
	return this->name;
}

void TestCaseObj::setComment(char * v_comment)
{
	this->comment = v_comment;
}

char * TestCaseObj::getComment()
{
	return this->comment;
}

void TestCaseObj::setType(char * v_type)
{
	this->type = v_type;
}

char * TestCaseObj::getType()
{
	return this->type;
}

void TestCaseObj::setDimension(int v_dimension)
{
	this->dimension = v_dimension;
}

int TestCaseObj::getDimension()
{
	return this->dimension;
}

void TestCaseObj::setEdgeWeightType(char * v_EdgeWeightType)
{
	this->edge_weight_type = v_EdgeWeightType;
}

char * TestCaseObj::getEdgeWeightType()
{
	return this->edge_weight_type;
}

void TestCaseObj::setCapacity(int v_capacity)
{
	this->capacity = v_capacity;
}

int TestCaseObj::getCapacity()
{
	return this->capacity;
}

void TestCaseObj::AddVehicleItem(Pair * v_pair_coord)
{
	this->vehicleTestCol->addLastFrogObject(v_pair_coord);
}

void TestCaseObj::AddCustomerItem(Pair * v_pair_demand)
{
	this->customer_section->addLastFrogObject(v_pair_demand);
}

float TestCaseObj::getEucDistance(int u, int v)
{

	float result = 0;
	Pair * coordinateOrigin = NULL, *coordinateDestination = NULL;

	coordinateOrigin = (Pair *)vehicleTestCol->getFrogObject(u);
	coordinateDestination = (Pair *)vehicleTestCol->getFrogObject(v);

	result = calcEuc2D(coordinateOrigin, coordinateDestination);

	return result;
}

float TestCaseObj::calcEuc2D(Pair * origin, Pair * destination)
{
	float result = 0, a, b;
	short x, y, w, z;
	x = origin->get_i_IntValue();
	y = origin->get_j_IntValue();

	w = destination->get_i_IntValue();
	z = destination->get_j_IntValue();

	a = pow((x - w), 2);
	b = pow((y - z), 2);

	result = sqrt(a + b);

	return result;
}

int TestCaseObj::getNumberOfDepots()
{
	return this->depot_section->getSize();
}

int TestCaseObj::getNumberOfCustomers()
{
	return (this->customer_section->getSize());
}

FrogObjectCol * TestCaseObj::getCustomerSection()
{
	return this->customer_section;
}

FrogObjectCol * TestCaseObj::getDemandSection()
{
	return this->customer_section;
}


void TestCaseObj::printFrogObj()
{
	printf("printing TestCaseObj data \n");
}

bool TestCaseObj::isTheSame(FrogObject * fs)
{
	return (this == fs);
}





