/* Use the caller allocator in direct mode, otherwise resolve the selector. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern unsigned char GPR_00554c14;
int Memory_GetAllocatorBySelector(int);
int Memory_SelectAllocator_003e9370(const int *selector, int fallback)
{
    if(GPR_00554c14)
        return fallback;
    else
        return Memory_GetAllocatorBySelector(*selector);
}
} /* extern "C" */
