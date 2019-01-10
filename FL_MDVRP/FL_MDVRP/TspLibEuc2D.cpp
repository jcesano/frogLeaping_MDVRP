#include "stdafx.h"
#include "TspLibEuc2D.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>  
#include "FrogObjectCol.h"
#include "IndexList.h"
#include "Pair.h"
#include <math.h>

TspLibEuc2D::TspLibEuc2D():FrogObject()
{
	this->name = NULL;
	this->comment = NULL;
	this->edge_weight_type = NULL;
	this->capacity = 0;
	this->nodeCoordSection = new FrogObjectCol();
	this->demand_section = new FrogObjectCol();
	this->depot_section = new IndexList();	
}

TspLibEuc2D::~TspLibEuc2D()
{

}

void TspLibEuc2D::setName(char * v_name)
{
	this->name = v_name;
}

char * TspLibEuc2D::getName()
{
	return this->name ;
}

void TspLibEuc2D::setComment(char * v_comment)
{
	this->comment = v_comment;
}

char * TspLibEuc2D::getComment()
{
	return this->comment;
}

void TspLibEuc2D::setType(char * v_type)
{
	this->type = v_type;
}

char * TspLibEuc2D::getType()
{
	return this->type;
}

void TspLibEuc2D::setDimension(int v_dimension)
{
	this->dimension = v_dimension;
}

int TspLibEuc2D::getDimension()
{
	return this->dimension;
}

void TspLibEuc2D::setEdgeWeightType(char * v_EdgeWeightType)
{
	this->edge_weight_type = v_EdgeWeightType;
}

char * TspLibEuc2D::getEdgeWeightType()
{
	return this->edge_weight_type;
}

void TspLibEuc2D::setCapacity(int v_capacity)
{
	this->capacity = v_capacity;
}

int TspLibEuc2D::getCapacity()
{
	return this->capacity;
}

void TspLibEuc2D::AddNodeCoordItem(Pair * v_pair_coord)
{
	this->nodeCoordSection->addFrogObjectOrdered(v_pair_coord);
}

void TspLibEuc2D::AddDemandItem(Pair * v_pair_demand)
{
	this->demand_section->addFrogObjectOrdered(v_pair_demand);
}

void TspLibEuc2D::AddDepotItem(int depotId)
{
	this->depot_section->addIndex(depotId);
}

float TspLibEuc2D::getEucDistance(int u, int v)
{
	
	float result = 0;
	Pair * coordinateOrigin = NULL, * coordinateDestination = NULL;

	coordinateOrigin		= (Pair *)nodeCoordSection->getFrogObject(u);
	coordinateDestination	= (Pair *)nodeCoordSection->getFrogObject(v);

	result = calcEuc2D(coordinateOrigin, coordinateDestination);

	return result;
}

float TspLibEuc2D::calcEuc2D(Pair * origin, Pair * destination)
{
	float result = 0, a ,b;
	short x , y, w, z;
	x = origin->get_i_IntValue();
	y = origin->get_j_IntValue();

	w = destination->get_i_IntValue();
	z = destination->get_j_IntValue();

	a = pow((x - w), 2);
	b = pow((y - z), 2);

	result = sqrt(a + b);

	return result;	
}

int TspLibEuc2D::getNumberOfDepots()
{
	return this->depot_section->getSize();
}

int TspLibEuc2D::getNumberOfCustomers()
{
	return (this->getDimension() - this->getDepotSection()->getSize());
}

FrogObjectCol * TspLibEuc2D::getNodeCoordSection()
{
	return this->nodeCoordSection;
}

FrogObjectCol * TspLibEuc2D::getDemandSection()
{
	return this->demand_section;
}

IndexList * TspLibEuc2D::getDepotSection()
{
	return this->depot_section;
}

double TspLibEuc2D::getAngularTheta(int customerInternalId, int depotInternalId)
{
	
	float const pi = 3.14159265;

	Pair * customerPair = (Pair *) this->nodeCoordSection->getFrogObject(customerInternalId);

	Pair * depotPair = (Pair *) this->nodeCoordSection->getFrogObject(depotInternalId);

	double x = (customerPair->get_i_IntValue() - depotPair->get_i_IntValue());
	double y = (customerPair->get_j_IntValue() - depotPair->get_j_IntValue());

	double result = atan2(y, x);

	return result;	
}

double TspLibEuc2D::getAngularRho(int customerInternalId, int depotInternalId)
{
	double result;

	Pair * customerPair = (Pair *) this->nodeCoordSection->getFrogObject(customerInternalId);

	Pair * depotPair = (Pair *) this->nodeCoordSection->getFrogObject(depotInternalId);

	double a = (customerPair->get_i_IntValue() - depotPair->get_i_IntValue());
	double b = (customerPair->get_j_IntValue() - depotPair->get_j_IntValue());


	result = sqrt(a*a + b*b);

	return result;
}

void TspLibEuc2D::printFrogObj()
{
	printf("printing TspLibEuc2D data \n");
}

bool TspLibEuc2D::isTheSame(FrogObject * fs)
{
	return (this == fs);
}




