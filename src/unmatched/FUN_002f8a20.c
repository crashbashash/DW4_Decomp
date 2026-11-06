int Memory_GetAllocatorBySelector(int);

void FUN_002f8a20(void) {
    if (Memory_GetAllocatorBySelector(2) == 0) {
        Memory_GetAllocatorBySelector(0);
    }
}
