#ifndef _5LAB_MYALLOC_HPP_
#define _5LAB_MYALLOC_HPP_

#include <cstddef>
#include <utility>
#include <vector>

#define DEFAULT_MAX_ADDRESS 1000

#define MIN_LEASE 40
#define MAX_LEASE 70
#define MIN_SIZE 50
#define MAX_SIZE 350
#define TIME_LIMIT 100
#define REQUEST_INTERVAL 10
#define MEMORY_SIZE 1000

#define DEBUG 0

typedef std::pair<int , int> range;
typedef std::pair<range, int> allocation_ticket;

struct Allocator {
	std::vector<range> free;
	std::vector<allocation_ticket> allocated;
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

	size_t number_of_merges;
};

void getMem(size_t size, size_t exp);
void cleanExpired(size_t tick);

// 0 for okay
// 1 for fail
int setMaxMemSize(size_t size);
void myAllocClean();

#endif
