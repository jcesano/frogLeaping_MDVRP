#include "stdafx.h"
#include "FrogObject.h"



FrogObject::FrogObject()
{
	this->value = 0;
}

float FrogObject::getValue()
{
	return this->value;
};

void FrogObject::setValue(float valueV)
{
	this->value = valueV;
}
