#ifndef _5LAB_MYALLOC_HPP_
#define _5LAB_MYALLOC_HPP_

#include <cstddef>
#include <utility>

typedef std::pair<int, int> range;
typedef std::pair<range, std::pair<void*, int>> allocation_ticket;


unsigned char* myMalloc(size_t size, int exp);
unsigned char* myCalloc(size_t size, int exp);
unsigned char* myRealloc(void* orgin, size_t size, int exp);

void myFree(void* mem);

#endif
