#include <cstdio>
#include <stdio.h>
#include "list.h"

bool cmp(void* e1, void* e2) {
	return (*(int*)e1) < (*(int*)e2);
}

void print(void* val) {
	printf("%d, ", *(int*)val);
}

int main(void) {
	SortedLinkedList* sLL = initSortedLinkedList(&cmp);
	int six9 = 69;
	sLL->insert(sLL, &six9);
	int two = 2;
	sLL->insert(sLL, &two);
	int four = 4;
	sLL->insert(sLL, &four);
	int neg4 = -4;
	sLL->insert(sLL, &neg4);
	printf("=======================\n");
	printf("%d\n", *(int *)sLL->get(sLL, 0));
	printf("%d\n", *(int *)sLL->get(sLL, 1));
	printf("%d\n", *(int *)sLL->get(sLL, 2));
	printf("%d\n", *(int *)sLL->get(sLL, 3));
	printf("=======================\n");

	sLL->remove(sLL, 2);
	printf("%d\n", *(int *)sLL->get(sLL, 0));
	printf("%d\n", *(int *)sLL->get(sLL, 1));
	printf("%d\n", *(int *)sLL->get(sLL, 2));

	printSortedLinkedList(sLL, &print);
}
