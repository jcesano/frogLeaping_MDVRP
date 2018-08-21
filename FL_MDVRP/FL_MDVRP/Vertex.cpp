#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex()
{
	this->distance = -1;
	this->id = -1;
	this->marked = 0;
	this->prevIndex = -2;
	this->prevPathIndex = -2;
	this->v_type = SimpleNode;
}

Vertex::~Vertex()
{
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

int Vertex::getId()
{
	return id;
}

void Vertex::setId(int v)
{
	id = v;
}

int Vertex::getPrevIndex()
{
	return prevIndex;
}

VertexType Vertex::getVertexType()
{
	return this->v_type;
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

void Vertex::setVertexType(VertexType v_Type_V)
{
	this->v_type = v_Type_V;
}

