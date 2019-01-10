#include "stdafx.h"
#include "FrogObjectCol.h"
#include "FrogObject.h"
#include "FrogObjNode.h"


FrogObjectCol::FrogObjectCol()
{
	head = NULL;

	this->colSize = 0;
}

FrogObjectCol::~FrogObjectCol()
{
	
	//printf("Destroying FrogObjectCol:STARTED \n");

	//destroy(this->head);
	FrogObjNode * itemNode = this->head, *old;

	this->head = NULL;

	while (itemNode != NULL)
	{
		old = itemNode;
		itemNode = itemNode->getNextFrogObjNode();
		delete old;
		old = NULL;
	}

	
	//---------------------------
	//FrogObjNode * temp;

	//temp = head;

	//while(this->head != NULL)
	//{
	//	temp = temp->getNextFrogObjNode();
	//	delete head;
	//	head = temp;
	//}
	//---------------------------

	//printf("Destroying FrogObjectCol:FINISHED \n");
}

void FrogObjectCol::destroy(FrogObjNode * itemNode)
{
	//printf("Destroying FrogObjectCol: STARTED \n");

	while(itemNode != NULL)
	{
		FrogObjNode * old = itemNode;
		itemNode = itemNode->getNextFrogObjNode();
		delete old;
	}
	
	//if(itemNode != NULL)
	//{
	//	delete itemNode;
	//}

	//printf("Destroying FrogObjectCol: FINISHED \n");
}

void FrogObjectCol::addFrogObject(FrogObject * fs)
{
	FrogObjNode * ptr;

	ptr = new FrogObjNode(fs, head);

	head = ptr;

	this->colSize++;
}

int FrogObjectCol::getFrogObjectPositionById(int id)
{
	int result = -1, i;

	bool found = false;
	
	FrogObjNode * nodePtr;
	FrogObject * solPtr;

	i = 0;

	nodePtr = this->head;

	while (found == false && i < this->getSize() && nodePtr != NULL)
	{
		solPtr = nodePtr->getFrogItem();

		found = (solPtr->getId() == id);

		if (found == false) 
		{
			nodePtr = nodePtr->getNextFrogObjNode();
			i++;
		}
		else
		{
			result = i;
		}			
	}

	return result;
}

void FrogObjectCol::addLastFrogObject(FrogObject * fs) 
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != NULL)
	{
		if (head == NULL)
		{
			head = new FrogObjNode(fs, NULL);
			this->colSize++;
		}
		else
		{			
			do
			{
				nodePtrPrev = nodePtr;
				nodePtr = nodePtr->getNextFrogObjNode();
			} while (nodePtr != NULL);

			//if I am in the end of the list
			if (nodePtr == NULL)
			{
				nodePtr = new FrogObjNode(fs, NULL);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == NULL)
	}// end if(fs != NULL)
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
			this->colSize++;
		}
		else
		{
			stopLoop = false;
			
			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() <= nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == NULL then i am in the begining of the list
					if(nodePtrPrev != NULL)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}
					
					this->colSize++;
					stopLoop = true;
				}
				else //keep looking
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} while (!stopLoop && nodePtr != NULL);

			//if I am in the end of the list
			if (nodePtr == NULL)
			{
				nodePtr = new FrogObjNode(fs, NULL);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == NULL)
	}// end if(fs != NULL)
}

void FrogObjectCol::addFrogObjectDoubleOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != NULL)
	{
		if (head == NULL)
		{
			head = new FrogObjNode(fs, NULL);
			this->colSize++;
		}
		else
		{
			stopLoop = false;

			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() < nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == NULL then i am in the begining of the list
					if (nodePtrPrev != NULL)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}

					this->colSize++;
					stopLoop = true;
				}
				else 
				{
					// If it is equal then check second value
					if(fs->getValue() == nodePtr->getFrogItem()->getValue())
					{	// order by Value2
						if (fs->getValue2() <= nodePtr->getFrogItem()->getValue2())
						{
							nodePtrTemp = new FrogObjNode(fs, nodePtr);

							// if nodePtrPrev == NULL then i am in the begining of the list
							if (nodePtrPrev != NULL)
							{
								nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
							}
							else
							{
								head = nodePtrTemp;
							}

							this->colSize++;
							stopLoop = true;
						}
						else // keep looking
						{
							nodePtrPrev = nodePtr;
							nodePtr = nodePtr->getNextFrogObjNode();
						}
					}
					else //keep looking
					{
						nodePtrPrev = nodePtr;
						nodePtr = nodePtr->getNextFrogObjNode();
					}
				}
			} while (!stopLoop && nodePtr != NULL);

			//if I am in the end of the list
			if (nodePtr == NULL)
			{
				nodePtr = new FrogObjNode(fs, NULL);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
		}//end else (head == NULL)
	}// end if(fs != NULL)
}

void FrogObjectCol::addFrogObjectDescOrdered(FrogObject * fs)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;
	bool stopLoop = false;

	if (fs != NULL)
	{
		if (head == NULL)
		{
			head = new FrogObjNode(fs, NULL);
			this->colSize++;
		}
		else
		{
			stopLoop = false;

			do
			{
				//if the new value is lower than current item => add new value before
				if (fs->getValue() >= nodePtr->getFrogItem()->getValue())
				{
					nodePtrTemp = new FrogObjNode(fs, nodePtr);

					// if nodePtrPrev == NULL then i am in the begining of the list
					if (nodePtrPrev != NULL)
					{
						nodePtrPrev->setNextFrogObjNode(nodePtrTemp);
					}
					else
					{
						head = nodePtrTemp;
					}

					this->colSize++;
					stopLoop = true;
				}
				else //keep looking
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} while (!stopLoop && nodePtr != NULL);

			//if I am in the end of the list
			if (nodePtr == NULL)
			{
				nodePtr = new FrogObjNode(fs, NULL);
				nodePtrPrev->setNextFrogObjNode(nodePtr);
				this->colSize++;
			}
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

FrogObject * FrogObjectCol::getFrogObject(int position)
{
	// assign the first element
	FrogObjNode * currentNode = head;
	FrogObject * result = NULL;

	if ((this->head != NULL) && (position < this->getSize()) && (position >= 0))
	{
		// if i == 0 then for is not executed, otherwise we start from i = 1
		// cause result is pointing to the first Node already (first node is in position = 0)
		for (int j = 0; j < position; j++)
		{			
			currentNode = currentNode->getNextFrogObjNode();
		}

		result = currentNode->getFrogItem();
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
				if (nodePtr->getFrogItem()->isTheSame(fs))
				{

					// if the element is located at the begining of the list
					if (head == nodePtr)
					{
						nodePtrTemp = head;						
						head = head->getNextFrogObjNode();
						nodePtr = head;

						nodePtrTemp->setFrogItem(NULL);
						delete nodePtrTemp;
						nodePtrTemp = NULL;
						
						this->colSize--;
					}
					else 
					{
						nodePtrTemp = nodePtr;
						nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFrogObjNode());
						nodePtr = nodePtrTemp->getNextFrogObjNode();						

						nodePtrTemp->setFrogItem(NULL);
						delete nodePtrTemp;
						nodePtrTemp = NULL;

						this->colSize--;
					}
				}
				else 
				{
					nodePtrPrev = nodePtr;
					nodePtr = nodePtr->getNextFrogObjNode();
				}
			} // end if (nodePtr->getFrogItem() != NULL)
		} // end while (nodePtr != NULL)

		nodePtrPrev = NULL;

	} // end if(fs != NULL)
}

void FrogObjectCol::reorderFrogObject(FrogObject * fs)
{
	this->removeFrogObject(fs);
	this->addFrogObjectOrdered(fs);
}

void FrogObjectCol::removeAllLowerValueFrogObject(int value, FrogObjectCol * deletedFrogObjects)
{
	FrogObjNode * nodePtr = this->head, *nodePtrPrev = NULL, *nodePtrTemp;

	while (nodePtr != NULL)
	{
		if (nodePtr->getFrogItem() != NULL)
		{
			float currValue = nodePtr->getFrogItem()->getValue();

			if (nodePtr->getFrogItem()->getValue() < value)
			{

				// if the element is located at the begining of the list
				if (head == nodePtr)
				{
					nodePtrTemp = head;
					deletedFrogObjects->addLastFrogObject(nodePtrTemp->getFrogItem());

					head = head->getNextFrogObjNode();
					nodePtr = head;

					nodePtrTemp->setFrogItem(NULL);
					delete nodePtrTemp;
					nodePtrTemp = NULL;

					this->colSize--;
				}
				else
				{
					nodePtrTemp = nodePtr;
					deletedFrogObjects->addLastFrogObject(nodePtrTemp->getFrogItem());
					nodePtrPrev->setNextFrogObjNode(nodePtr->getNextFrogObjNode());
					nodePtr = nodePtrTemp->getNextFrogObjNode();

					nodePtrTemp->setFrogItem(NULL);
					delete nodePtrTemp;
					nodePtrTemp = NULL;

					this->colSize--;
				}
			}
			else {
				nodePtrPrev = nodePtr;
				nodePtr = nodePtr->getNextFrogObjNode();
			}
		} // end if (nodePtr->getFrogItem() != NULL)
	} // end while (nodePtr != NULL)

	nodePtrPrev = NULL;
}

void FrogObjectCol ::addAllFrogObjects(FrogObjectCol * elementsToAdd)
{
	int size = elementsToAdd->getSize();

	for(int i = 0; i < size; i++)
	{
		this->addFrogObject(elementsToAdd->getFrogObject(i));
	}
}

void FrogObjectCol::unReferenceFrogObjectCol()
{
	//printf("Unreferencing FrogObjectCol: STARTED \n");

	FrogObjNode * itemNode = this->head;

	while (itemNode != NULL)
	{
		FrogObjNode * old = itemNode;
		old->setFrogItem(NULL);
		itemNode = itemNode->getNextFrogObjNode();		
	}

	//printf("Unreferencing FrogObjectCol: FINISHED \n");
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

int FrogObjectCol::frogObjectExists(int objid)
{
	bool found = false;
	int i;

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

FrogObject * FrogObjectCol::getFrogObjectById(int objid)
{
	bool found = false;
	int i;
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

FrogObject * FrogObjectCol::getMaxValueFrogObject()
{
	FrogObject * result = NULL, * currentFrogObject = NULL;

	result = this->getFrogObject(0);
	
	for (int i = 1; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() > result->getValue())
		{
			result = currentFrogObject;
		}
	}

	return result;
}

FrogObject * FrogObjectCol::getFirstUpperValueFrogObject(float searchedValue)
{
	FrogObject * result = NULL, *currentFrogObject = NULL;

	for (int i = 0; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() >= searchedValue)
		{
			result = currentFrogObject;
			return result;
		}
	}

	return result;
}

FrogObject * FrogObjectCol::getFirstUpperValueFrogObjectIndex(float searchedValue, int & frogObjectIndex)
{	
	FrogObject * currentFrogObject = NULL, * result = NULL;

	for (int i = 0; i < this->getSize(); i++)
	{
		currentFrogObject = this->getFrogObject(i);
		if (currentFrogObject->getValue() >= searchedValue)
		{
			result = currentFrogObject;
			frogObjectIndex = i;  
			return result;
		}
	}

	frogObjectIndex = -1;
	return result;
}

void FrogObjectCol::ConcatCol(FrogObjectCol * fs)
{
}







