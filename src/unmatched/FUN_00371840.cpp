extern "C" {
void FUN_0036e160(void);
void *Memory_AllocateBufferDirect(unsigned int size, void *pool);
void FUN_002ed4c0(void *ptr, void *pool);
extern void *DAT_0056de30;
}

struct PoolAllocated {
    static void *operator new(unsigned int size, void *pool) { return Memory_AllocateBufferDirect(size, pool); }
    static void operator delete(void *ptr, void *) { FUN_002ed4c0(ptr, DAT_0056de30); }
};

struct PooledNode : PoolAllocated {
    char body[92];
    PooledNode();
};

extern "C" PooledNode *FUN_00371840(void);

PooledNode *FUN_00371840(void) {
    FUN_0036e160();
    return new (DAT_0056de30) PooledNode;
}
