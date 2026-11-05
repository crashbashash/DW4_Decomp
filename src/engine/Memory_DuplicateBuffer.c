/* 0x002ed530 — Memory_DuplicateBuffer.
 * Clone a heap buffer: ask its owning allocator for the size, allocate that
 * many bytes from the same owner, and copy the contents over.  The size is
 * queried a second time for the copy length, after the allocation, and the new
 * block is not checked for failure; both match retail
 * (docs/engine/memory-field-copy.md, finding #891). */
int memcpy();
int Memory_AllocateBufferViaSharedTail();
int Memory_GetBufferSize();
int Memory_FindBufferOwner();

int Memory_DuplicateBuffer(int source) {
    int copy;
    int size;

    size = Memory_GetBufferSize(source);
    copy = Memory_AllocateBufferViaSharedTail(size, Memory_FindBufferOwner(source));
    memcpy(copy, source, Memory_GetBufferSize(source));
    return copy;
}
