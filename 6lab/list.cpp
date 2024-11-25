#include "list.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>

struct LinkedListNode* initLinkedListNode(void* value) {
	struct LinkedListNode* node = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
	node->next = NULL;
	node->value = value;
	return node;
}

void SortedLinkedList_insert(SortedLinkedList* list, void* data) {
	if (list == NULL) return;
	list->size++;
	if (list->first == NULL) {
		list->first = initLinkedListNode(data);
		return;
	}
	struct LinkedListNode* next = list->first;
	struct LinkedListNode* last = NULL;
	while (next && list->cmp(next->value, data)) {
		last = next;
		next = next->next;
	}
	struct LinkedListNode* newNode = initLinkedListNode(data);
	newNode->next = next;

	if (last == NULL) list->first = newNode;
	else last->next = newNode;
}

void SortedLinkedList_remove(SortedLinkedList* list, int index) {
	if (list == NULL) return;
	if (list->first == NULL) return;
	list->size--;
	if (index == 0) {
		struct LinkedListNode* next = list->first->next;
		free(list->first);
		list->first = next;
		return;
	}
	struct LinkedListNode* next = list->first;
	struct LinkedListNode* last = NULL;
	int idx = 0;
	while (next && idx < index) {
		last = next;
		next = next->next;
		idx++;
	}
	if (next != NULL && next->next != NULL) {
		struct LinkedListNode* temp = next->next;
		free(last->next);
		last->next = temp;
	} else {
		free(last->next);
		last->next = NULL;
	}
}

void* SortedLinkedList_get(SortedLinkedList* list, int index) {
	if (list == NULL) return NULL;
	int idx = 0;
	struct LinkedListNode* node = list->first;
	while (node && idx < index) {
		idx++;
		node = node->next;
	}
	if (node == NULL) return NULL;
	return node->value;
}

void printSortedLinkedList(SortedLinkedList* list, void (*printElem)(void*)) {
	for (size_t i = 0; i < list->size; i++) {
		printElem(list->get(list, i));
	}
}

void Iterator_next(Iterator* it) {
	if (it->private_val == NULL) {
		it->valid = false;
	} else {
		it->private_val = it->private_val->next;
	}

	if (it->private_val == NULL) {
		it->valid = false;
	}
}

void* Iterator_get(Iterator* it) {
	if (it->valid == false) return NULL;
	return it->private_val;
}

void freeIterator(Iterator* itter) {
	free(itter);
}

Iterator* initIterator(struct LinkedListNode* first) {
	Iterator* it = (Iterator*)malloc(sizeof(Iterator));
	it->private_val = first;
	it->next = &Iterator_next;
	it->get = &Iterator_get;
	return it;
}

Iterator* SortedLinkedList_getIterator(SortedLinkedList* linkedList) {
	return initIterator(linkedList->first);
}

// cmp is a func that says elem1 < elem2
SortedLinkedList* initSortedLinkedList(bool (*cmp) (void*, void*)) {
	SortedLinkedList* sLL = (SortedLinkedList*)malloc(sizeof(SortedLinkedList));
	sLL->first = NULL;
	sLL->size = 0;
	sLL->insert = &SortedLinkedList_insert;
	sLL->remove = &SortedLinkedList_remove;
	sLL->get = &SortedLinkedList_get;
	sLL->cmp = cmp;
	return sLL;
}

void freeSortedLinkedList(SortedLinkedList* sortedLinkedList) {
	LinkedListNode* lastNode = NULL;
	LinkedListNode* node = sortedLinkedList->first;
	while(node) {
		free(lastNode);
		lastNode = node;
		node = node->next;
	}
	free(node);
	free(sortedLinkedList);
}
