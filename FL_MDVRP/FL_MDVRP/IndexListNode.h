#ifndef INDEXLISTNODE_H_   /* Include guard */
#define INDEXLISTNODE_H_

class IndexListNode
{
	short int index;
	IndexListNode * next;
public:
	IndexListNode(short int index, IndexListNode * nextPtr); // Constructor

	~IndexListNode();

	short int getIndex();

	IndexListNode * getNextPtr();

	void setIndex(short int index);

	void setNextPtr(IndexListNode * nextPtr);

};

#endif
