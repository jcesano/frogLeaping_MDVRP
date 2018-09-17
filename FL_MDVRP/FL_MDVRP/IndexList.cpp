#include "stdafx.h"
#include "IndexList.h"
#include "IndexListNode.h"


IndexList::IndexList()
{
	this->head = NULL;
	this->size = 0;
}

IndexList::~IndexList()
{
	IndexListNode * temp = head;

	while (this->head != NULL)
	{
		temp = temp->getNextPtr();
		delete head;
		head = temp;
	}
}

void IndexList::addIndex(int index)
{
	IndexListNode * node = new IndexListNode(index, head);

	head = node;

	this->size++;
}

void IndexList::removeIndex(int index)
{
	IndexListNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	while (nodePtr != NULL)
	{
		if (nodePtr->getIndex() == index)
		{
			// if the element is located at the begining of the list
			if (head == nodePtr)
			{
				nodePtrTemp = head;
				head = head->getNextPtr();
				nodePtr = head;

				// add a delete nodePtrTemp
				this->size--;
			}
			else {
				nodePtrTemp = nodePtr;
				nodePtrPrev->setNextPtr(nodePtr->getNextPtr());
				nodePtr = nodePtrTemp->getNextPtr();

				// add a delete nodePtrTemp
				this->size--;
			}
		} // if (nodePtr->getIndex == index)
		else {
			nodePtrPrev = nodePtr;
			nodePtr = nodePtr->getNextPtr();
		}

	} // end while (nodePtr != NULL)
}

int IndexList::getSize()
{
	return this->size;
}

int IndexList::getItem(int position)
{
	IndexListNode * currPtr;

	currPtr = this->head;

	if ((currPtr != NULL) && (position >= 0) && (position < this->getSize()))
	{
		for(int i = 0; i < position;i++)
		{
			currPtr = currPtr->getNextPtr();
		}

		return currPtr->getIndex();			
	}	

	return -1;
}

int IndexList::getItemById(int itemId)
{
	int result = -1, i;

	bool found = false;
	
	if (this != NULL)
	{
		IndexListNode * nodePtr;
		int solPtr;

		i = 1;

		nodePtr = this->head;

		while (found == false && i <= this->getSize() && nodePtr != NULL)
		{
			solPtr = nodePtr->getIndex();

			found = (solPtr == itemId);

			if (found == true)
			{
				result = solPtr;
			}
			else
			{
				nodePtr = nodePtr->getNextPtr();
				i = i + 1;
			}
		}
	}

	return result;
}
