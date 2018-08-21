#ifndef FROGOBJNODE_H_   /* Include guard */
#define FROGOBJNODE_H_

//=================================
// forward declared dependencies
class FrogObject;

class FrogObjNode
{
	FrogObject * frogItem;

	FrogObjNode * next;

public:
	FrogObjNode(FrogObject * fs, FrogObjNode * fsnodeptr);

	~FrogObjNode();

	void printNodeItems();

	FrogObject * getFrogItem();

	FrogObjNode * getNextFrogObjNode();

	void setNextFrogObjNode(FrogObjNode * node);
};

#endif