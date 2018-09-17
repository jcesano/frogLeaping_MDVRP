#ifndef INDEXLISTNODE_H_   /* Include guard */
#define INDEXLISTNODE_H_

class IndexListNode
{
	int index;
	IndexListNode * next;
public:
	IndexListNode(int index, IndexListNode * nextPtr); // Constructor

	~IndexListNode();

	int getIndex();

	IndexListNode * getNextPtr();

	void setIndex(int index);

	void setNextPtr(IndexListNode * nextPtr);

};

#endif
