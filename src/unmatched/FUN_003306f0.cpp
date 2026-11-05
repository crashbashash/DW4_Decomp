extern "C" int Memory_GetAllocatorBySelector();
extern "C" int Memory_GetDefaultAllocator();
extern "C" int FUN_003306f0(void) {
    int r = Memory_GetAllocatorBySelector();
    if (r != 0) return r;
    return Memory_GetDefaultAllocator();
}
