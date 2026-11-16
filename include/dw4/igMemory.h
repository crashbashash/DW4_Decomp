#ifndef DW4_IGMEMORY_H
#define DW4_IGMEMORY_H

/* Raw memory blocks from a pool: allocation with a given or the default allocator, and freeing back to the block's owner. */
class igMemoryPoolView;

extern "C" {
void *Memory_AllocateDefaultBuffer(unsigned int size);
void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPoolView *pool);
void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned short alignment, igMemoryPoolView *pool);
void Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool);
int Memory_FreeBuffer(void *buffer);
int Memory_FreeBufferAliasA(void *buffer);
unsigned int Memory_GetBufferSize(void *buffer);
}

#endif
