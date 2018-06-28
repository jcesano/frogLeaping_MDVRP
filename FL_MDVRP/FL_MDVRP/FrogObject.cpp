#include "stdafx.h"
#include "FrogObject.h"



FrogObject::FrogObject()
{
	this->value = 0;
}

FrogObject::FrogObject(short int id_v)
{
	this->id = id_v;
}

float FrogObject::getValue()
{
	return this->value;
}
short int FrogObject::getId()
{
	return this->id;
}

void FrogObject::setId(short int id_v)
{
	this->id = id_v;
}

void FrogObject::setValue(float valueV)
{
	this->value = valueV;
}

bool FrogObject::isTheSame(short int objid)
{
	return (this->id == objid);
}