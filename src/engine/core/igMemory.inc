void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPoolView *pool)
{
    return FUN_002ed1e0(1, size, pool);
}

void *FUN_002ed1e0(int, unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

void *Memory_AllocateDefaultBuffer(unsigned int size)
{
    igMemoryPoolView *allocator = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    return allocator->Allocate(size);
}

void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

void *FUN_002ed260(unsigned int size, unsigned int alignment)
{
    igMemoryPoolView *allocator = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    return allocator->AllocateAligned(size, alignment);
}

void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned int alignment, igMemoryPoolView *pool)
{
    return pool->AllocateAligned(size, alignment);
}

void *FUN_002ed2e0(unsigned int size, unsigned int alignment)
{
    igMemoryPoolView *allocator = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    return allocator->vfunc_56(size, alignment);
}

void *Memory_ReallocateBuffer(void *buffer, unsigned int size)
{
    igMemoryPoolView *owner;

    if (buffer == 0) {
        return Memory_AllocateDefaultBuffer(size);
    }
    owner = ((igMemoryPoolView *)Memory_FindOwningAllocator((int)buffer));
    if (owner != 0) {
        return owner->Reallocate(buffer, size);
    }
    return 0;
}

void *FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment)
{
    igMemoryPoolView *owner;

    if (buffer == 0) {
        return FUN_002ed260(size, alignment);
    }
    owner = ((igMemoryPoolView *)Memory_FindOwningAllocator((int)buffer));
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
    igMemoryPoolView *allocator;

    if (buffer != 0) {
        allocator = ((igMemoryPoolView *)Memory_FindOwningAllocator((int)buffer));
        if (allocator != 0) {
            allocator->Free(buffer);
        }
    }
}

int Memory_FreeBufferAliasA(void *buffer)
{
    return Memory_FreeBuffer(buffer);
}

void Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool)
{
    pool->Free(block);
}

unsigned int Memory_GetBufferSize(void *buffer)
{
    igMemoryPoolView *owner = ((igMemoryPoolView *)Memory_FindOwningAllocator((int)buffer));
    return owner->GetAllocationSize(buffer);
}

igMemoryPoolView *Memory_FindBufferOwner(void *buffer)
{
    return ((igMemoryPoolView *)Memory_FindOwningAllocator((int)buffer));
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

int FUN_002ed5a0(void *block, igMemoryPoolView *pool)
{
    return pool->vfunc_58(block);
}

void Memory_FreeBufferAliasB(void *buffer)
{
    Memory_FreeBuffer(buffer);
}

void Memory_FreeOwnedBufferUnchecked(void *buffer)
{
    igMemoryPoolView *owner = Memory_FindBufferOwner(buffer);
    owner->Free(buffer);
}

/* Hex dump of memory: `size` bytes (1..8) per value, `perLine` values per line, each line headed by
 * its address printed in `digits` hex digits when `digits` is nonzero. The text goes to the file
 * `name` when one is given (and opens), otherwise to the console. */
#define DUMP_CASE(N, FMT, VALUE) \
        mask = (1 << (digits * 4)) - 1; \
        while (more) { \
            if (showAddr) { \
                if (digits < 8) { EMIT(text_0x_0_x, digits, addr & mask); } \
                else { EMIT(text_0x_08x_2, addr); } \
            } \
            for (i = 0; i < perLine; i++) { \
                EMIT(FMT, VALUE); \
                addr = addr + N; \
                if ((unsigned long long)addr >= end) { more = 0; break; } \
            } \
            EMIT(DAT_004f95c8); \
        } \
        break;
void FUN_002ed610(unsigned int size, unsigned int perLine, unsigned int digits,
                  unsigned int addr, long long length, const char *name)
{
    bool showAddr = digits;
    unsigned char more = 1;
    DumpFile *file = 0;
    unsigned long long end;
    if (!size) size = 1;
    else if (size > 8) size = 8;
    if (0 != name) {
        int alloc;
        if (g_useOwnerAllocator) alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent);
        else alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        file = (DumpFile *)igFile_Create(alloc);
        if (0 == file->Open(name, (const char *)DAT_004f92f0)) goto done;
    }
    {
        unsigned int mask;
        end = (unsigned long long)addr + length;
        unsigned int i;
        switch (size) {
        case 1: DUMP_CASE(1, text_02x, *(unsigned char *)addr)
        case 2: DUMP_CASE(2, text_04x, *(unsigned short *)addr)
        case 3: DUMP_CASE(3, text_06x, *(unsigned int *)addr & 0xFFFFFF)
        case 4: DUMP_CASE(4, text_08x, *(unsigned int *)addr)
        case 5: DUMP_CASE(5, text_010lx, *(unsigned long long *)addr & 0xFFFFFFFFFFULL)
        case 6: DUMP_CASE(6, text_012lx, *(unsigned long long *)addr & 0xFFFFFFFFFFFFULL)
        case 7: DUMP_CASE(7, text_014lx, *(unsigned long long *)addr & 0xFFFFFFFFFFFFFFULL)
        default: DUMP_CASE(8, text_016lx, *(unsigned long long *)addr)
        }
    }
    if (file) {
        file->Close();
        if (--file->refs, 0 == (0x7FFFFF & file->refs)) igObject_Destroy(file);
    }
done:;
}
#undef DUMP_CASE

void *FUN_002ee430(unsigned int size)
{
    if (g_activeSystemAllocator[0] == 0) {
        FUN_0032f300();
    }
    if (g_activeSystemAllocator[0] != 0) {
        return g_activeSystemAllocator[0]->Allocate(size);
    }
    return ((void *)malloc(size));
}

void FUN_002ee4a0(void *block)
{
    if (g_activeSystemAllocator[0] == 0) {
        FUN_0032f300();
    }
    if (g_activeSystemAllocator[0] != 0) {
        g_activeSystemAllocator[0]->Free(block);
        return;
    }
    free(block);
}

