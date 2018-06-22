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

	FrogObject * getFrogObject(int i);

	void removeFrogObjects(FrogObjectCol * sourceSolutionCol);

	void removeFrogObject(FrogObject * fs);

	FrogObjectCol * removeRepetedItems();

	int areThereRepetedItems();

	int frogObjectExists(FrogObject * fs);

	void ConcatCol(FrogObjectCol * fs);
};


#endif