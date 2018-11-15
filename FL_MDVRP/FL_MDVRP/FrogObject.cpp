#include "stdafx.h"
#include "FrogObject.h"



FrogObject::FrogObject()
{
	this->value = 0;
}

FrogObject::~FrogObject()
{
	//printf("Destroying FrogObject:START AND END \n");
}

FrogObject::FrogObject(int id_v)
{
	this->id = id_v;
	this->value = 0;
}

float FrogObject::getValue()
{
	return this->value;
}
float FrogObject::getValue2()
{
	return this->value2;
}
int FrogObject::getId()
{
	return this->id;
}

void FrogObject::setId(int id_v)
{
	this->id = id_v;
}

void FrogObject::setValue(float valueV)
{
	this->value = valueV;
}

void FrogObject::setValue2(float valueV)
{
	this->value2 = valueV;
}

bool FrogObject::isTheSame(int objid)
{
	return (this->id == objid);
}