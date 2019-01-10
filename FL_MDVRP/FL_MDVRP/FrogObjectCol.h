#ifndef FROGOBJECTCOL_H_   /* Include guard */
#define FROGOBJECTCOL_H_

//=================================
// forward declared dependencies
class FrogObjNode;
class FrogObject;

class FrogObjectCol
{
	FrogObjNode * head;

	int colSize;

public:

	FrogObjectCol();

	~FrogObjectCol();

	void destroy(FrogObjNode * itemNode);

	int getFrogObjectPositionById(int id);

	void addFrogObject(FrogObject * fs);

	void addLastFrogObject(FrogObject * fs);

	void addFrogObjectOrdered(FrogObject * fs);

	void addFrogObjectDescOrdered(FrogObject * fs);

	void addFrogObjectDoubleOrdered(FrogObject * fs);
	
	void printFrogObjCol();

	int getSize();

	FrogObject * getFrogObject(int i);

	FrogObject * getFrogObjectById(int objid);

	FrogObject * getMaxValueFrogObject();

	void removeFrogObjects(FrogObjectCol * sourceSolutionCol);

	void removeFrogObject(FrogObject * fs);

	FrogObjectCol * removeRepetedItems();

	int areThereRepetedItems();

	int frogObjectExists(FrogObject * fs);

	int frogObjectExists(int id);

	void ConcatCol(FrogObjectCol * fs);

	FrogObject * getFirstUpperValueFrogObject(float searchedValue);

	FrogObject * getFirstUpperValueFrogObjectIndex(float searchedValue, int &frogObjectValue);

	void reorderFrogObject(FrogObject * fs);

	void removeAllLowerValueFrogObject(int value, FrogObjectCol * deletedFrogObjects);

	void addAllFrogObjects(FrogObjectCol * elementsToAdd);

	void unReferenceFrogObjectCol();
};


#endif