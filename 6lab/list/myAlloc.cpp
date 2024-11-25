// Copyright 2024 Morgan Nilsson
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <stdio.h>
#include "myAlloc.hpp"

extern size_t clock;

void getMem(size_t size, int exp);
void cleanExpired(int tick);

bool cmp(void* e1, void* e2) {
	int ev1 = ((allocation_ticket*)e1)->first.first;
	int ev2 = ((allocation_ticket*)e2)->first.first;
	return ev1 < ev2;
}

struct Allocator* initAllocator(int maxAdder) {
	struct Allocator* myAlloc = (struct Allocator*)malloc(sizeof(struct Allocator));
	myAlloc->allocs = initSortedLinkedList(&cmp);
	myAlloc->maxAdder = maxAdder;

	myAlloc->number_of_requests = 0;
	myAlloc->requests_satisfied = 0;
	myAlloc->requests_unsatisfied = 0;

	myAlloc->smallest_size_request = 1000000;
	myAlloc->largest_size_request = 0;
	myAlloc->total_size_requested = 0;

	myAlloc->shortest_exp_requested = 10000;
	myAlloc->longest_exp_requested = 0;
	myAlloc->total_exp_requested = 0;

	return  myAlloc;
}

struct Allocator* myAlloc = initAllocator(DEFAULT_MAX_ADDRESS);

allocation_ticket* getAllocationTicket(size_t index) {
	return (allocation_ticket*)(myAlloc->allocs->get(myAlloc->allocs, index));
}

void printAllocationTicket(void* rawTicket) {
	allocation_ticket* ticket = (allocation_ticket*) rawTicket;
	printf("Allocation: range [%lu, %lu] with expire %lu\n", ticket->first.first, ticket->first.second, ticket->second);
}

void printfAllocationTickets() {
	printSortedLinkedList(myAlloc->allocs, &printAllocationTicket);
}

void printFreeSpace() {
	allocation_ticket* t1 = getAllocationTicket(0);
	allocation_ticket* t2 = NULL;
	if (t1->first.first != 0) printf("Free space [0, %lu] : %lu\n", t1->first.first-1, t1->first.first);
	for (size_t i = 1; i < myAlloc->allocs->size; i++) {
		t1 = getAllocationTicket(i-1);
		t2 = getAllocationTicket(i);
		if ((t1->first.second+1) - (t2->first.first) != 0) printf("Free space [%lu, %lu] : %lu\n", t1->first.second+1, t2->first.first-1, (t2->first.first - t1->first.second - 1));
	}
	t1 = getAllocationTicket(myAlloc->allocs->size-1);
	if (t1->first.second - MEMORY_SIZE != 0) printf("Free space [%lu, %d] : %lu\n", t1->first.second+1, MEMORY_SIZE, MEMORY_SIZE - t1->first.second - 1);
}

allocation_ticket* make_allocation_ticket(size_t low, size_t high, size_t exp) {
	return new allocation_ticket{{low, high}, exp};
}

// returns -1 if too big otherwise the begaining
// basic first fit
int find_optimal_mem_loc(size_t size) {
	if (size <= 0) return -1;
	allocation_ticket* a1;
	allocation_ticket* a2;
	if (myAlloc->allocs->size == 0) return 0;
	if (getAllocationTicket(0)->first.first - 0 >= size) return 0;
	for (size_t i = 0; i < myAlloc->allocs->size - 1; i++) {
		a1 = getAllocationTicket(i);
		a2 = getAllocationTicket(i + 1);
		if (a2->first.first - a1->first.second >= size) return a1->first.second + 1;
	}
	// between the last alloc and the end
	allocation_ticket* last = getAllocationTicket(myAlloc->allocs->size-1);
	if (last == NULL) return -1;
	if (myAlloc->maxAdder - last->first.second >= size) return last->first.second + 1;
	return -1;
}

void getMem(size_t size, size_t exp) {
	myAlloc->number_of_requests++;

	if (size > myAlloc->largest_size_request) myAlloc->largest_size_request = size;
	if (size < myAlloc->smallest_size_request) myAlloc->smallest_size_request = size;
	myAlloc->total_size_requested += size;

	if (exp > myAlloc->longest_exp_requested) myAlloc->longest_exp_requested = exp;
	if (exp < myAlloc->shortest_exp_requested) myAlloc->shortest_exp_requested = exp;
	myAlloc->total_exp_requested += exp;

	#if DEBUG
	printfAllocationTickets();
	#endif
	if (size <= 0) {
		myAlloc->requests_unsatisfied++;
		return;
	}
	if (size > myAlloc->maxAdder) return;
	int start = find_optimal_mem_loc(size);
	if (start == -1) {
		myAlloc->requests_unsatisfied++;
		#if DEBUG
		printf("Was unable to find a spot for memory size %lu\n", size);
		#endif
		return;
	}
	#if DEBUG
	printf("TICK: idx| Found open spot [%d, %lu]\n", start, start + size);
	#endif
	allocation_ticket* ticket = make_allocation_ticket(start, start + size, clock + exp);
	myAlloc->allocs->insert(myAlloc->allocs, ticket);
	myAlloc->requests_satisfied++;
	return;
}

void cleanExpired(size_t tick) {
	for (size_t i = 0; i < myAlloc->allocs->size; i++) {
		size_t expires = getAllocationTicket(i)->second;
		if (tick >= expires) {
			#if DEBUG
			printf("TICK: %lu | Removing ticket #%lu with exp %lu\n", tick, i, expires);
			#endif
			myAlloc->allocs->remove(myAlloc->allocs, i);
			i--;
		}
	}
}

int setMaxMemSize(size_t size) {
	// larger resizes are always okay
	if (size > myAlloc->maxAdder) {
		myAlloc->maxAdder = size;
		return 0;
	// if there are no current allocations
	} else if (myAlloc->allocs->size == 0) {
		myAlloc->maxAdder = size;
		return 0;
	// if the end of the last allocation is smaller than the new size
	} else if (((allocation_ticket*)myAlloc->allocs->get(myAlloc->allocs, myAlloc->allocs->size-1))->first.second <= size){
		myAlloc->maxAdder = size;
		return 0;
	// new size failed
	} else return 1;
}

void myAllocClean() {
	printf("Total requests %d\nTotal satisfied: %d (%lf%%)\nTotal unsatisfied: %d (%lf%%)\n", 
		myAlloc->number_of_requests, myAlloc->requests_satisfied, 100.0 * myAlloc->requests_satisfied / myAlloc->number_of_requests, myAlloc->requests_unsatisfied, 100.0 * myAlloc->requests_unsatisfied / myAlloc->number_of_requests);
	printf("Smallest size request %lu\nLargest size request %lu\nAverage size of request: %Lf\n", 
		myAlloc->smallest_size_request, myAlloc->largest_size_request, 1.0L * myAlloc->total_size_requested / myAlloc->number_of_requests);
	printf("Smallest lease duration request %lu\nLargest lease duration request %lu\nAverage lease duration of request: %Lf\n", 
		myAlloc->shortest_exp_requested, myAlloc->longest_exp_requested, 1.0L * myAlloc->total_exp_requested/ myAlloc->number_of_requests);
	printf("State of allocations\n");
	printfAllocationTickets();
	printf("State of free memory\n");
	printFreeSpace();
	freeSortedLinkedList(myAlloc->allocs);
	free(myAlloc);
}
