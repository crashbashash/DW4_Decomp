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
}
