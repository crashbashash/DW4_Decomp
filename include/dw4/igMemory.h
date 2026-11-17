#ifndef DW4_IGMEMORY_H
#define DW4_IGMEMORY_H

/* Raw memory blocks from a pool: allocation with a given or the default allocator, and freeing back to the block's owner.
 * The Aligned16 calls take an allocator selector (a kIGMemoryPoolHandle* value) and align to 16 bytes. */
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
void *Memory_AllocateDefaultBuffer(unsigned int size);
void *Memory_AllocateBufferDirect(unsigned int size, struct igMemoryPoolView *pool);
void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned short alignment, struct igMemoryPoolView *pool);
void Memory_FreeBufferWithAllocator(void *block, struct igMemoryPoolView *pool);
int Memory_FreeBuffer(void *buffer);
int Memory_FreeBufferAliasA(void *buffer);
void Memory_FreeBufferAliasB(void *buffer);
unsigned int Memory_GetBufferSize(void *buffer);
void *Memory_ReallocateAligned(void *buffer, unsigned int size, unsigned short alignment);
void *Memory_ReallocateBufferAlias(void *buffer, unsigned int size);
void *Memory_ReallocateAlignedAlias(void *buffer, unsigned int size, unsigned short alignment);
struct igMemoryPoolView *Memory_FindBufferOwner(void *buffer);
struct igMemoryPoolView *Memory_GetDefaultHandleAllocator(void);
struct igMemoryPoolView *Memory_GetAllocatorByName(const char *name);
void *Memory_AllocateAligned16(unsigned int size, int selector);
void Memory_FreeToSelector(void *block, int selector);
void *Memory_ReallocateAligned16(void *block, unsigned int size, int selector);
#ifdef __cplusplus
}
#endif

#endif
