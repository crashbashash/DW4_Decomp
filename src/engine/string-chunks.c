/* src/engine/string-chunks.c — packed string-chunk primitive matches
 *
 * One translation unit: 6 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

/* 36-byte string chunk (docs/engine/string-chunks.md, finding #866).  Only
 * the free-list head is used by the merge below; the other fields are written
 * by the constructor.  References are 4-byte values in this ABI. */
typedef struct StringChunk {
    int table;          /* +0   owning string pool */
    int next;           /* +4   next chunk in the chain */
    int previous;       /* +8   previous chunk in the chain */
    int capacity;       /* +12  storage size in bytes */
    int storage;        /* +16  allocator-provided storage base */
    int storageEnd;     /* +20  end of the storage */
    int freeHead;       /* +24  end address of the first free block */
    int largestFree;    /* +28  cached largest free size, -1 = unknown */
    char isEmpty;       /* +32  no strings live in the chunk */
} StringChunk;

void StringChunk_InitializeStorage(void *);
int StringChunk_FreeStorage(StringChunk *);
int StringChunk_DeleteObject(int);

/* 0x0030c760: delete wrapper, forwards to the delete service at 0x002ed4b0. */
int StringTable_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA(object);
}

/* 0x0030c770: chunk constructor.  The cache starts unknown (-1) and the chunk
 * empty; storage is then allocated by StringChunk_InitializeStorage. */
void *StringChunk_Construct(StringChunk *chunk, int previous, int table, int capacity) {
    chunk->table = table;
    chunk->next = 0;
    chunk->previous = previous;
    chunk->capacity = capacity;
    chunk->storage = 0;
    chunk->storageEnd = 0;
    chunk->freeHead = 0;
    chunk->largestFree = -1;
    chunk->isEmpty = 1;
    StringChunk_InitializeStorage(chunk);
    return chunk;
}

/* 0x0030c7d0: chunk destructor; releases the storage and deletes the object
 * when the signed low 16 bits of deleteFlags are positive. */
StringChunk *StringChunk_Destroy(StringChunk *chunk, long long deleteFlags) {
    if (chunk != 0) {
        StringChunk_FreeStorage(chunk);
        if ((short)deleteFlags > 0) {
            StringChunk_DeleteObject((int)chunk);
        }
    }
    return chunk;
}

/* 0x0030ca30: release the chunk's storage (service at 0x002ed460). */
int StringChunk_FreeStorage(StringChunk *chunk)
{
    return Memory_FreeBuffer(chunk->storage);
}

/* 0x0030cb30: absorb free block `left` into the adjacent free block `right`
 * (and extend `previous`'s link past it).  Free-list references are block
 * ends; each end carries two halfwords, the distance to the next free end
 * (-4 bytes) and the block length (-2 bytes), both in 4-byte units.  Returns
 * the merged length in bytes. */
int StringChunk_MergeBlocks(StringChunk *chunk, unsigned short *previous,
                unsigned short *left, unsigned short *right) {
    if ((int)left == chunk->freeHead) {
        chunk->freeHead = (int)right;
    }
    {
        unsigned short *leftFooter = left - 2;  /* [0] distance to next free end, [1] length */
        if (previous) {
            previous[-2] += leftFooter[0];
        }
        right[-1] += leftFooter[1];
        return right[-1] * 4;
    }
}

/* 0x0030cd00: delete wrapper, same target as StringTable_DeleteObject. */
int StringChunk_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA(object);
}
