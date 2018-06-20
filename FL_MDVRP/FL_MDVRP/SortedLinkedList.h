#ifndef SORTEDLINKEDLIST_H_   /* Include guard */
#define SORTEDLINKEDLIST_H_

#include <iostream>
#include <time.h>

class FrogObject
{
	private:
		float value;

	public:

		FrogObject();

		float getValue();

		void setValue(float valueV);

		virtual void printFrogObj() = 0;

		virtual bool isTheSame(FrogObject * fs) = 0;
};

class FrogObjNode
{
	FrogObject * FrogItem;

	FrogObjNode * next;

	public:
		FrogObjNode(FrogObject * fs, FrogObjNode * fsnodeptr);

		void printNodeItems();
		
		FrogObject * getFrogItem();

		FrogObjNode * getNextFrogObjNode();

		void setNextFrogObjNode(FrogObjNode * node);
};


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