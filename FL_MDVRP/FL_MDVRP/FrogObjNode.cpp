#include "stdafx.h"
#include "FrogObjNode.h"
#include "FrogObject.h"

FrogObjNode::FrogObjNode(FrogObject * fs, FrogObjNode * fsnodeptr)
{
	frogItem = fs;
	next = fsnodeptr;
}

FrogObjNode::~FrogObjNode()
{
	delete this->frogItem;
}

void FrogObjNode::printNodeItems()
{
	if (this->frogItem != NULL)
	{
		this->frogItem->printFrogObj();
	}

	FrogObjNode * tempNodePtr = next;
	while (tempNodePtr != NULL)
	{
		tempNodePtr->frogItem->printFrogObj();
		tempNodePtr = tempNodePtr->next;
	};
}

FrogObject * FrogObjNode::getFrogItem()
{
	return this->frogItem;
}

FrogObjNode * FrogObjNode::getNextFrogObjNode()
{
	return this->next;
}

void FrogObjNode::setNextFrogObjNode(FrogObjNode * node)
{
	this->next = node;
}
