#include "SortedLinkedList.h"


float FrogObject::getValue()
{
	return this->value;
};

void FrogObject::setValue(float valueV)
{
	this->value = valueV;
}

FrogObjNode::FrogObjNode(FrogObject * fs, FrogObjNode * fsnodeptr)
{
	feasibleSol = fs;
	next = fsnodeptr;
}

void FrogObjNode::printNodeItems()
{
	if (this->FrogItem != NULL)
	{
		this->FrogItem->printFrogObj();
	}

	FrogObjNode * tempNodePtr = next;
	while (tempNodePtr != NULL)
	{
		tempNodePtr->FrogItem->printFrogObj();
		tempNodePtr = tempNodePtr->next;
	};
}

FrogObject * FrogObjNode::getFrogItem()
{
	return this->FrogItem
}

FrogObjNode * FrogObjNode::getNextFrogObjNode()
{
	return this->next;
}

void FrogObjNode::setNextFrogObjNode(FrogObjNode * node)
{
	this->next = node;
}

FrogObjectCol::FrogObjectCol()
{
	head = NULL;

	this->colSize = 0;
}


void FrogObjectCol::addFrogObject(FrogObject * fs)
{
	FrogObjNode * ptr;

	ptr = new FrogObjNode(fs, head);

	head = ptr;

	this->colSize = this->colSize + 1;
}

void FrogObjectCol::printFrogObjCol()
{
	printf("Printing frog objects \n");

	if (head != NULL)
	{
		head->printNodeItems();
	}
}

int FrogObjectCol::getSize()
{
	return this->colSize;
}

FrogObject * FrogObjectCol::getFrogObject(int i)
{
	// assign the first element
	FrogObjNode * result = head;

	if (this->head != NULL)
	{
		// if i == 1 then for is not executed, otherwise we start from i = 2 
		// cause result is pointing to the first Node already 
		for (int j = 2; j <= i; j++)
		{
			result = result->getNextFrogObjNode();
		}
	}

	if (result != NULL)
	{
		return result->getFrogItem();
	}

	return NULL;
}

void FrogObjectCol::removeFrogObjects(FrogObjectCol * sourceSolutionCol)
{
	if (sourceSolutionCol != NULL)
	{
		for (int i = 1; i <= sourceSolutionCol->colSize; i++)
		{
			FrogObject * fs = sourceSolutionCol->getFrogObject(i);
			if (this->frogObjectExists(fs) == 1)
			{
				this->removeFrogObject(fs);
			}
		}
	}
}

void FrogObjectCol::removeFrogObject(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	if (fs != NULL)
	{
		while (nodePtr != NULL)
		{
			if (nodePtr->getFrogItem() != NULL)
			{
				if (nodePtr->getFrogItem()->isTheSame(fs) == 1)
				{

					// if the element is located at the begining of the list
					if (head == nodePtr)
					{
						nodePtrTemp = head;
						head = head->getNextFrogObjNode();
						nodePtr = head;
						// add a delete nodePtrTemp
						this->colSize--;
					}
					else {
						nodePtrTemp = nodePtr;
						nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFeasSolNode());
						nodePtr = nodePtrTemp->getNextFrogObjNode();
						// add a delete nodePtrTemp
						this->colSize--;
					}
				}
				else {
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} // end if (nodePtr->getFrogItem() != NULL)
		} // end while (nodePtr != NULL)
	} // end if(fs != NULL)
}