#include "stdafx.h"
#include "IndexListNode.h"

IndexListNode::IndexListNode(int v_index, IndexListNode * nextPtr)
{
	this->index = v_index;
	this->next = nextPtr;
}

IndexListNode::~IndexListNode()
{
}

int IndexListNode::getIndex()
{
	return this->index;
}

IndexListNode * IndexListNode::getNextPtr()
{
	return this->next;
}

void IndexListNode::setIndex(int v_index)
{
	this->index = v_index;
}

void IndexListNode::setNextPtr(IndexListNode * nextPtr)
{
	this->next = nextPtr;
}

