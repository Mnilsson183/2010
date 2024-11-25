// Copyright 2024 Morgan Nilsson
#include <cstddef>
struct LinkedListNode;
typedef struct SortedLinkedList SortedLinkedList;
typedef struct Iterator Iterator;

struct Iterator;

struct SortedLinkedList{
	struct LinkedListNode* first;
	size_t size;
	void (*insert) (SortedLinkedList*, void*);
	void (*remove) (SortedLinkedList*, int);
	void* (*get) (SortedLinkedList*, int);
	bool (*cmp) (void*, void*);
	Iterator* (*getIterator)(SortedLinkedList*);
} ;

struct LinkedListNode {
	struct LinkedListNode* next;
	void* value;
};

struct Iterator {
	struct LinkedListNode* private_val;
	bool valid;
	void (*next)(Iterator*);
	void* (*get)(Iterator*);
};

void freeIterator(Iterator* itter);
void freeSortedLinkedList(SortedLinkedList* sortedLinkedList);

SortedLinkedList* initSortedLinkedList(bool (*cmp) (void*, void*));
void printSortedLinkedList(SortedLinkedList* list, void (*printElem)(void*));
