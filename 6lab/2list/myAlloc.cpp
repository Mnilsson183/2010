// Copyright 2024 Morgan Nilsson
#include <_strings.h>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <stdio.h>
#include "myAlloc.hpp"

extern size_t clock_tick;

void getMem(size_t size, int exp);
void cleanExpired(int tick);

allocation_ticket make_allocation_ticket(size_t low, size_t high, int exp) {
	return allocation_ticket{{low, high}, exp};
}

struct Allocator* initAllocator(int maxAdder) {
	struct Allocator* myAlloc = (struct Allocator*)malloc(sizeof(struct Allocator));
	myAlloc->free.push_back(make_allocation_ticket(0, MEMORY_SIZE, -1));
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
	return &myAlloc->allocated.at(index);
}

void printAllocationTicket(void* rawTicket) {
	if (myAlloc->allocated.size() == 0) return;
	allocation_ticket* ticket = (allocation_ticket*) rawTicket;
	printf("Allocation: range [%d, %d] with expire %d\n", ticket->first.first, ticket->first.second, ticket->second);
}

void printfAllocationTickets() {
	for (size_t i = 0; i < myAlloc->allocated.size(); i++) {
		printAllocationTicket(getAllocationTicket(i));
	}
}

void printFreeSpace() {
	for (size_t i = 0; i < myAlloc->free.size(); i++) {
		printf("Free ");
		printAllocationTicket(&myAlloc->free[i]);
	}

}

// returns -1 if too big otherwise the begaining
// basic first fit
int find_optimal_mem_loc(int size) {
	if (myAlloc->allocated.size() == 0) {
		myAlloc->free[0].first.first += size + 1;
		return 0;
	}
	for (size_t i = 0; i < myAlloc->free.size(); i++) {
		allocation_ticket space = myAlloc->free[i];
		if (space.first.second - space.first.first >= size) {
			int val = space.first.first;
			myAlloc->free[i].first.first += size + 1;
			return val;
		}
	}
	return -1;
}

size_t findInsertLoc(allocation_ticket ticket) {
	if (myAlloc->allocated.size() == 0) return 0;
	int start = ticket.first.first;
	if (start < getAllocationTicket(0)->first.first) return 0;
	for (size_t i = 1; i < myAlloc->allocated.size(); i++) {
		if (getAllocationTicket(i)->first.first > start) return i;
	}
	return myAlloc->allocated.size();
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
	printFreeSpace();
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
	allocation_ticket ticket = make_allocation_ticket(start, start + size, clock_tick + exp);
	size_t inserLoc = findInsertLoc(ticket);
	myAlloc->allocated.insert(myAlloc->allocated.begin() + inserLoc, ticket);
	myAlloc->requests_satisfied++;
	#if DEBUG
	printf("\n\n");
	#endif
	return;
}

bool cmp (allocation_ticket a1, allocation_ticket a2) {
	return a1.first.first < a2.first.first;
}

void condenseFreeList() {
	std::sort(myAlloc->free.begin(), myAlloc->free.end(), &cmp);
	for (size_t i = 0; i < myAlloc->free.size()-1; i++) {
		if (myAlloc->free[i].first.second == myAlloc->free[i+1].first.first - 1) {
			myAlloc->free[i].first.second = myAlloc->free[i+1].first.second;
			myAlloc->free.erase(myAlloc->free.begin()+i+1);
		}
	}
}

void cleanExpired(size_t tick) {
	for (size_t i = 0; i < myAlloc->allocated.size(); i++) {
		size_t expires = getAllocationTicket(i)->second;
		if (tick >= expires) {
			#if DEBUG
			printf("TICK: %lu | Removing ticket #%lu with exp %lu\n", tick, i, expires);
			#endif
			allocation_ticket expTicket = myAlloc->allocated[i];
			myAlloc->free.push_back(make_allocation_ticket(expTicket.first.first, expTicket.first.second, -1));
			myAlloc->allocated.erase(myAlloc->allocated.begin() + i);
			i--;
		}
	}
	condenseFreeList();
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
}
