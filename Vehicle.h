#ifndef VEHICLE_H_   /* Include guard */
#define VEHICLE_H_

class Vehicle
{
	FrogObjNode * head;

	int colSize;

public:

	Vehicle();

	void addCustomer(FrogObject * fs);

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
