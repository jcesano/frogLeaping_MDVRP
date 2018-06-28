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

	void addFrogObject(FrogObject * fs);

	void printFrogObjCol();

	int getSize();

	FrogObject * getFrogObject(short int i);

	FrogObject * getFrogObjectById(short int objid);

	void removeFrogObjects(FrogObjectCol * sourceSolutionCol);

	void removeFrogObject(FrogObject * fs);

	FrogObjectCol * removeRepetedItems();

	int areThereRepetedItems();

	int frogObjectExists(FrogObject * fs);

	int frogObjectExists(short int id);

	void ConcatCol(FrogObjectCol * fs);
};


#endif