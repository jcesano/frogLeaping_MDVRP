#ifndef INDEXLIST_H_   /* Include guard */
#define INDEXLIST_H_

class IndexListNode;

class IndexList
{
	private:

		IndexListNode * head;

		int size;

	public:

		IndexList(); // Constructor

		~IndexList();


		void addIndex(int index);

		void removeIndex(int index);

		int getSize();

		int getItem(int position);

		int getItemById(int itemId);
};

#endif