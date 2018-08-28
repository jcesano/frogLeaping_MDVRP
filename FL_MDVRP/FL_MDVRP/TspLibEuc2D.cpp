#include "stdafx.h"
#include "TspLibEuc2D.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>  
#include "FrogObjectCol.h"
#include "IndexList.h"
#include "Pair.h"


TspLibEuc2D::TspLibEuc2D():FrogObject()
{
	this->name = NULL;
	this->comment = NULL;
	this->edge_weight_type = NULL;
	this->capacity = 0;
	this->nodeCoordSection = NULL;
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

void TspLibEuc2D::setDimension(short int v_dimension)
{
	this->dimension = v_dimension;
}

short int TspLibEuc2D::getDimension()
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

void TspLibEuc2D::setCapacity(short int v_capacity)
{
	this->capacity = v_capacity;
}

short int TspLibEuc2D::getCapacity()
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

void TspLibEuc2D::AddDepotItem(short int depotId)
{
	this->depot_section->addIndex(depotId);
}

void TspLibEuc2D::printFrogObj()
{
	printf("printing TspLibEuc2D data \n");
}

bool TspLibEuc2D::isTheSame(FrogObject * fs)
{
	return true;
}



