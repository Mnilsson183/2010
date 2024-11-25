For this assignment I want you to write a program that will simulate memory allocation. This simulation will consist of generating memory block requests at regular intervals and trying to satisfy this from a list of free memory blocks. To create the illusion of a process holding on to its memory block for a period of time, an expiry time will be added to each satisfied block request. When that request expires, the block is returned to the free list where possible merging of small memory blocks will take place.

Your program must maintain 2 lists : one that contains a list of all the memory holes ( free list ) currently available and another that contains a list of satisfied requests. Both lists will make use of the following basic structure.

using range = std::pair<int,int>;
range r;
/* the first /second attributes are :
    int start;        // the starting address of the range
    int size;        // size of the range
*/
auto [start,size] = r;

The first list should hold elements of the  type range and the  list of satisfied requests should hold elements of the type :

 using alloc = std::pair<range,int>;
 alloc a;
 /* the first/second attribute are :
     range allocated;    //  the range of memory currently allocated from freelist
    int leaseExpiry;     // time at which this block will be returned to free list
 */
auto [allocated,leaseExpiry] = a;

To make some of the tasks that you will be asked to do easier I would suggest that the lists above be kept in sorted order. The list of of holes should be sorted according to the location of the hole in memory. This will make the task of merging adjacent holes easy. The list of allocated blocks, on the other hand, should be sorted based on the lease expiration time.

Your main program should have the following structure

int main () {
   long int clock = 0;
   repeat
      /* generate a memory request */
      /* see if lease has expired  */
   until ( ++clock == TIME_LIMIT);
}

The variable clock is used to simulate a clock. One iteration of the loop will increase the clock by one tick. Memory requests are to be generated at regular intervals : one every REQUEST_INTERVAL clock ticks. If the clock indicates that a memory request needs to be generated your program should generate two values : the first will be the size of the block and the second will be the duration of the lease. The size of the block will lie between MIN_SIZE and MAX_SIZE. The C expression rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE will do this. The duration of the lease will be a value between MIN_LEASE and MAX_LEASE. A statement similar to the one just given will work. Note that the lease expiration time is equal to the current clock time plus the lease duration. Once a block size has been determined, your program must search the free list and allocate a block of the appropriate size. The criterion used to select a block will be the first-fit allocation scheme where the first hole that satisfies the size request is used.

At each clock tick, your program should check to see if a lease on a memory block has expired. Note that this test is easily performed if your allocated block list is sorted as described earlier. If a lease has expired, the block is returned to the free list. The merging of adjacent holes is not done immediately; instead, the program will wait for a memory request to fail before merging and retrying the request again if needed.

After the simulation has ended, your program shall report the results of the simulation. The statistics that I want to see include:

total number of requests, number of satisfied and unsatisfied requests
smallest, largest, and average block size requested.
shortest, longest and average lease duration and number of times that merging was performed
the state of free list and allocated list at end of simulation

For this program use the following values for your simulation parameters

MIN_LEASE = 40
MAX_LEASE = 70
MIN_SIZE = 50
MAX_SIZE = 350
TIME_LIMIT = 1000
REQUEST_INTERVAL = 10
MEMORY_SIZE = 1000


The last parameter represents the total amount of memory available for requests. Structure your program as a collection of .cpp and .h files. Your main.cpp should contain only the main function. All constants, type definitions and function declarations should be in a properly-constructed header file. I will have more to say on this in the lab. Submit the assignment as either a zip file or github repository.

