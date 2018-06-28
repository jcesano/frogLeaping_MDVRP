#include "stdafx.h"
#include "IndexList.h"
#include "IndexListNode.h"


IndexList::IndexList()
{
	this->head = NULL;
	this->size = 0;
}

void IndexList::addIndex(short int index)
{
	IndexListNode * node = new IndexListNode(index, head);

	head = node;

	this->size++;
}

void IndexList::removeIndex(short int index)
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

short int IndexList::getSize()
{
	return this->size;
}

short int IndexList::getItem(short int position)
{
	short int currentPos = 0;
	IndexListNode * currPtr;

	currPtr = this->head;

	while (currPtr != NULL) 
	{
		if(currentPos == position)
		{
			return currPtr->getIndex();
		}
		else
		{
			currentPos++;
			currPtr = currPtr->getNextPtr();
		};		
	}	

	return -1;
}
