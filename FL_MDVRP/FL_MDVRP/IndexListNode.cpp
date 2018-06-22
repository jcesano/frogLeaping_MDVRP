#include "stdafx.h"
#include "IndexListNode.h"

IndexListNode::IndexListNode(short int v_index, IndexListNode * nextPtr)
{
	this->index = v_index;
	this->next = nextPtr;
}

short int IndexListNode::getIndex()
{
	return this->index;
}

IndexListNode * IndexListNode::getNextPtr()
{
	return this->next;
}

void IndexListNode::setIndex(short int v_index)
{
	this->index = v_index;
}

void IndexListNode::setNextPtr(IndexListNode * nextPtr)
{
	this->next = nextPtr;
}

