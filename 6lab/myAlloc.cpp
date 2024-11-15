#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include "myAlloc.hpp"

struct memStruct {
	unsigned char* mem;
	std::list<allocation_ticket> memInfo;
};

struct memStruct Mem;

allocation_ticket make_allocation_ticket(int low, int high, int exp, void* spot) {
	return std::pair(std::pair(low, high), std::pair(spot, exp));
}

// returns -1 if too big otherwise the begaining
int find_optimal_mem_loc(size_t size) {
	
}

void insertTicket(std::list<allocation_ticket> list, allocation_ticket ticket) {
	list.push_back(ticket);
	std::sort(list.begin(), list.end(), [](allocation_ticket a1, allocation_ticket a2){return a1.first.first < a2.first.first;});
}

unsigned char* myMalloc(size_t size, int exp) {
	if (size<= 0) return NULL;
	int start = find_optimal_mem_loc(size);
	if (start == -1) return NULL;
	insertTicket(Mem.memInfo, make_allocation_ticket(start, start + size, exp, &Mem.mem[start]));
	return &Mem.mem[start];
}

unsigned char* myCalloc(size_t size_bytes, int exp) {
	if (size_bytes <= 0) return NULL;
	unsigned char* mem = myMalloc(size_bytes, exp);
	memset(mem, '\0', size_bytes);
	return mem;
}
