void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPool_2ed1c0 *pool)
{
    return FUN_002ed1e0(1, size, pool);
}

void *FUN_002ed1e0(int, unsigned int size, igMemoryPool_2ed1c0 *pool)
{
    return pool->Allocate(size);
}

void *Memory_AllocateDefaultBuffer(unsigned int size)
{
    igMemoryPool_2ed1c0 *allocator = ((igMemoryPool_2ed1c0 *)Memory_GetDefaultAllocator());
    return allocator->Allocate(size);
}

void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPool_2ed1c0 *pool)
{
    return pool->Allocate(size);
}

void *FUN_002ed260(unsigned int size, unsigned int alignment)
{
    igMemoryPool_2ed1c0 *allocator = ((igMemoryPool_2ed1c0 *)Memory_GetDefaultAllocator());
    return allocator->AllocateAligned(size, alignment);
}

void *FUN_002ed2b0(unsigned int size, unsigned int alignment, igMemoryPool_2ed1c0 *pool)
{
    return pool->AllocateAligned(size, alignment);
}

void *FUN_002ed2e0(unsigned int size, unsigned int alignment)
{
    igMemoryPool_2ed1c0 *allocator = ((igMemoryPool_2ed1c0 *)Memory_GetDefaultAllocator());
    return allocator->vfunc_54(size, alignment);
}

void *Memory_ReallocateBuffer(void *buffer, unsigned int size)
{
    igMemoryPool_2ed1c0 *owner;

    if (buffer == 0) {
        return Memory_AllocateDefaultBuffer(size);
    }
    owner = ((igMemoryPool_2ed1c0 *)Memory_FindOwningAllocator((int)buffer));
    if (owner != 0) {
        return owner->Reallocate(buffer, size);
    }
    return 0;
}

void *FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment)
{
    igMemoryPool_2ed1c0 *owner;

    if (buffer == 0) {
        return FUN_002ed260(size, alignment);
    }
    owner = ((igMemoryPool_2ed1c0 *)Memory_FindOwningAllocator((int)buffer));
    if (owner != 0) {
        return owner->ReallocateAligned(buffer, size, alignment);
    }
    return 0;
}

void *thunk_Memory_ReallocateBuffer(void *buffer, unsigned int size)
{
    return Memory_ReallocateBuffer(buffer, size);
}

void *thunk_FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment)
{
    return FUN_002ed3b0(buffer, size, alignment);
}

int Memory_FreeBuffer(void *buffer)
{
    igMemoryPool_2ed1c0 *allocator;

    if (buffer != 0) {
        allocator = ((igMemoryPool_2ed1c0 *)Memory_FindOwningAllocator((int)buffer));
        if (allocator != 0) {
            allocator->Free(buffer);
        }
    }
}

int Memory_FreeBufferAliasA(void *buffer)
{
    return Memory_FreeBuffer(buffer);
}

void Memory_FreeBufferWithAllocator(void *block, igMemoryPool_2ed1c0 *pool)
{
    pool->Free(block);
}

unsigned int Memory_GetBufferSize(void *buffer)
{
    igMemoryPool_2ed1c0 *owner = ((igMemoryPool_2ed1c0 *)Memory_FindOwningAllocator((int)buffer));
    return owner->GetSize(buffer);
}

igMemoryPool_2ed1c0 *Memory_FindBufferOwner(void *buffer)
{
    return ((igMemoryPool_2ed1c0 *)Memory_FindOwningAllocator((int)buffer));
}

void *Memory_DuplicateBuffer(void *source)
{
    void *copy;
    unsigned int size;

    size = Memory_GetBufferSize(source);
    copy = Memory_AllocateBufferViaSharedTail(size, Memory_FindBufferOwner(source));
    memcpy(copy, source, Memory_GetBufferSize(source));
    return copy;
}

int FUN_002ed5a0(void *block, igMemoryPool_2ed1c0 *pool)
{
    return pool->vfunc_58(block);
}

void Memory_FreeBufferAliasB(void *buffer)
{
    Memory_FreeBuffer(buffer);
}

void Memory_FreeOwnedBufferUnchecked(void *buffer)
{
    igMemoryPool_2ed1c0 *owner = Memory_FindBufferOwner(buffer);
    owner->Free(buffer);
}

void *FUN_002ee430(unsigned int size)
{
    if (DAT_00587218[0] == 0) {
        FUN_0032f300();
    }
    if (DAT_00587218[0] != 0) {
        return DAT_00587218[0]->Allocate(size);
    }
    return ((void *)malloc(size));
}

void FUN_002ee4a0(void *block)
{
    if (DAT_00587218[0] == 0) {
        FUN_0032f300();
    }
    if (DAT_00587218[0] != 0) {
        DAT_00587218[0]->Free(block);
        return;
    }
    free(block);
}

