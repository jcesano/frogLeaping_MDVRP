#ifndef INDEXLIST_H_   /* Include guard */
#define INDEXLIST_H_

class IndexListNode;

class IndexList
{
	IndexListNode * head;

	short int size;

public:

	IndexList(); // Constructor

	void addIndex(short int index);

	void removeIndex(short int index);

	short int getSize();

	short int getItem(short int position);
};

#endif