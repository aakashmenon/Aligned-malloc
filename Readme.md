---------------------------------------------------------------------------------

# **Aligned Malloc**

Malloc (void *malloc(size_t size)) and free (void free(void *ptr)) are part of stdlib library which allows user to dynamically allocate and free memory from the heap.

Malloc returns a pointer to a valid address if allocation was successful and a NULL pointer if it failed to allocate memory.
Free will free up this dynamically allocated memory back to the heap.

The memory allocated by malloc is typically random and may cause multiple read/write cycles if unaligned.

For example, if the memory layout is as follows:

ADDR: 0    1    2    3

ADDR: 4    5    6    7

ADDR: 8    9    10   11

...

If we want to allocate 4 bytes of memory and malloc returns starting address of 3, assumming 8 bits can be stored at each location, 4 bytes will be stored from address location 3 to 6.
On a 32-bit machine it is possible to read/write 4 bytes at a time on even addresses (0,4,8,12,16...), so to read/write to the addresses 3,4,5,6 it will require 2 read/write cycles since the newly allocated memory is not 4-byte aligned in this case.

To optimize read/write cycles we can write our own aligned_malloc and aligned_free functions.

We allocate extra bytes to handle alignment and store the starting address to be freed.
If X1, X2, X3, X4, X5, X6, X7, X8, X9, X10 are the memory locations allocated and X1 is the address returned by malloc and X4 is the aligned address, we will store address of X1 at X3 location.
So for read/write operations we are only concered with X4 as the starting address and while freeing memory will free the address stored at X3 memory location.

The drawback of this approach is that more memory needs to be allocated than requested, so there is a tradeoff between memory and speed of read/write and this choice depends on the application at hand.

Note: This program may have to be run multiple times with different inputs to aligned_malloc function to observe proper alignment.
