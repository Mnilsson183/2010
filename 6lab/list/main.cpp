#include "myAlloc.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
size_t clock = 0;

int main(void) {
	srand(0);
	setMaxMemSize(MEMORY_SIZE);


	do {
		cleanExpired(clock);
		if (clock % REQUEST_INTERVAL == 0) {
			size_t size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
			size_t expiry = rand() % (MAX_LEASE - MIN_LEASE + 1) + MIN_LEASE;
			#if DEBUG
			printf("TICK: %lu | Making allocation of %lu bytes with an expiry of %lu\n", clock, size, expiry);
			#endif
			getMem(size, expiry);
		}
		clock++;
	} while(clock != TIME_LIMIT);
	myAllocClean();
}
