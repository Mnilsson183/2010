#ifndef _5LAB_MYALLOC_HPP_
#define _5LAB_MYALLOC_HPP_

#include <cstddef>
#include <utility>
#include "list.h"

#define DEFAULT_MAX_ADDRESS 1000

#define MIN_LEASE 40
#define MAX_LEASE 70
#define MIN_SIZE 50
#define MAX_SIZE 350
#define TIME_LIMIT 100 //1000
#define REQUEST_INTERVAL 10
#define MEMORY_SIZE 1000

#define DEBUG 0

typedef std::pair<size_t, size_t> range;
typedef std::pair<range, size_t> allocation_ticket;

struct Allocator {
	SortedLinkedList* allocs;
	size_t maxAdder;

	int number_of_requests;
	int requests_satisfied;
	int requests_unsatisfied;

	size_t smallest_size_request;
	size_t largest_size_request;
	size_t total_size_requested;

	size_t shortest_exp_requested;
	size_t longest_exp_requested;
	size_t total_exp_requested;
};

void getMem(size_t size, size_t exp);
void cleanExpired(size_t tick);

// 0 for okay
// 1 for fail
int setMaxMemSize(size_t size);
void myAllocClean();

#endif
