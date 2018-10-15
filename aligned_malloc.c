#include <stdio.h>
#include <stdint.h>

void *aligned_malloc(uint32_t bytes,uint8_t alignment);
void aligned_free(void *ptr);

int main()
{
    void *ptr  =  aligned_malloc(12,8); //12 bytes to be allocated on 64-bit machine.
    void *ptr2 = aligned_malloc(8,4);   //8  bytes to be allocated on 32-bit machine.

    if(NULL == ptr || NULL == ptr2)
    {
        printf("Failed to allocate memory, please try again! \n");
        return -1;
    }

    aligned_free(ptr);
    aligned_free(ptr2);

    return 0;
}

void *aligned_malloc(uint32_t bytes,uint8_t alignment)
{
    void *result = malloc(bytes + alignment + sizeof(void *));
    if(NULL == result)
    {
        return NULL;
    }
    printf("Address returned after malloc = %p\n",result);
    
    void *free_addr  = result;
    void *start_addr = (void *) ((size_t)result + (alignment - (size_t) result % alignment));
    start_addr--;
    *(size_t *)start_addr = free_addr;
    start_addr++;
    
    printf("Aligned address = %p\n",start_addr);
    return start_addr;
}

void aligned_free(void *ptr)
{
    ptr--;
    printf("Address of initial allocation = %p\n",*(size_t *)ptr);
    
    free(* (size_t *) ptr);
}
