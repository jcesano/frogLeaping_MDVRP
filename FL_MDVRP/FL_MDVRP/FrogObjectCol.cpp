#include "stdafx.h"
#include "FrogObjectCol.h"
#include "FrogObject.h"
#include "FrogObjNode.h"


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

	this->colSize++;
}

void FrogObjectCol::addFrogObjectOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;
	bool stopLoop = false;


	if (fs != NULL)
	{
		if (head == NULL)
		{
			head = new FrogObjNode(fs, NULL);
		}
		else
		{
			stopLoop = false;
			nodePtrPrev = nodePtr;
			nodePtr = nodePtr->getNextFrogObjNode();

			while (!stopLoop && nodePtr != NULL)
			{

				//if the new value is lower than first => add new value before
				if (fs->getValue() <= nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);
					nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					this->colSize++;
					stopLoop = true;
				}
				else //keep looking
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			}// end while

			//if I am in the end of the list
			if (nodePtr == NULL)
			{
				nodePtr = new FrogObjNode(fs, NULL);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			};
		}//end else (head == NULL)
	}// end if(fs != NULL)
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

FrogObject * FrogObjectCol::getFrogObject(short int i)
{
	// assign the first element
	FrogObjNode * currentNode = head;
	FrogObject * result = NULL;

	if ((this->head != NULL) && (i <= this->getSize()))
	{
		// if i == 1 then for is not executed, otherwise we start from i = 2 
		// cause result is pointing to the first Node already 
		for (int j = 1; j <= i; j++)
		{
			result = currentNode->getFrogItem();
			currentNode = currentNode->getNextFrogObjNode();
		}
	}
	else
	{
		return NULL;
	}
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
					else 
					{
						nodePtrTemp = nodePtr;
						nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFrogObjNode());
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

FrogObjectCol * FrogObjectCol::removeRepetedItems()
{
	return nullptr;
}

int FrogObjectCol::areThereRepetedItems()
{
	return 0;
}

int FrogObjectCol::frogObjectExists(FrogObject * fs)
{
	return 0;
}

int FrogObjectCol::frogObjectExists(short int objid)
{
	bool found = false, i;

	if (this != NULL)
	{
		FrogObjNode * nodePtr;
		FrogObject * solPtr;

		i = 1;

		nodePtr = this->head;

		while (found == false && i <= this->getSize() && nodePtr != NULL)
		{
			solPtr = nodePtr->getFrogItem();

			found = solPtr->isTheSame(objid);

			nodePtr = nodePtr->getNextFrogObjNode();
			i = i + 1;
		}
	}

	return found;

}

FrogObject * FrogObjectCol::getFrogObjectById(short int objid)
{
	bool found = false, i;
	FrogObject * result = NULL;

	if (this != NULL)
	{
		FrogObjNode * nodePtr;
		FrogObject * solPtr;

		i = 1;

		nodePtr = this->head;

		while (found == false && i <= this->getSize() && nodePtr != NULL)
		{
			solPtr = nodePtr->getFrogItem();

			found = solPtr->isTheSame(objid);

			if(found == true)
			{
				result = solPtr;
			}
			else
			{
				nodePtr = nodePtr->getNextFrogObjNode();
				i = i + 1;					
			}
		}
	}

	return result;
}

void FrogObjectCol::ConcatCol(FrogObjectCol * fs)
{
}






