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

	void AddLastFrogObject(FrogObject * fs);

	void addFrogObjectOrdered(FrogObject * fs);
	
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

	void reorderFrogObject(FrogObject * fs);
};


#endif