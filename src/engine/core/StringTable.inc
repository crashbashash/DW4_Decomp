StringTable *StringTable_Construct(StringTable *table, StringPool *pool, int capacity) {
    table->pool = pool;
    table->count = 0;
    table->step = 0;
    table->capacity = capacity;
    table->entries = (StringTokenHeader **)((igMemoryPoolView *)pool->pool)->Allocate(capacity * 4);
    table->emptyChunks = 0;
    return table;
}

/* Table destructor: frees the element array (`data`) and, for a positive 16-bit `delete_flag`,
 * deletes the table object. */
void *StringTable_Destroy(StringTable *self, long long delete_flag) {
    if (self != 0) {
        Memory_FreeBuffer(self->entries);
        if ((short)delete_flag > 0) {
            StringTable_DeleteObject((int)self);
        }
    }
    return self;
}

void *g_stringTableSemaphore;

void StringTable_SetSynchronization(int enable) {
    int pool;
    igSemaphoreView *semaphore;
    igObject *held;
    if (enable != 0) {
        if (g_stringTableSemaphore == 0) {
            pool = ((int)Memory_GetCurrentAllocator());
pool = g_useOwnerAllocator != 0 ? pool : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
            semaphore = (igSemaphoreView *)igSemaphore_Create(pool);
            semaphore->Create();
            g_stringTableSemaphore = semaphore;
        }
    } else {
        held = (igObject *)g_stringTableSemaphore;
        if (held != 0) {
            g_stringTableSemaphore = 0;
            held->_refCount = (int)held->_refCount - 1;
            if (((unsigned long long)(long long)(int)held->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(held);
            }
        }
    }
}

int StringTable_Find(StringTable *table, int string) {
    int index;
    int found;
    igResult waitResult;
    igResult signalResult;

    index = 0;
    found = 0;
    if (g_stringTableSemaphore != 0) {
        waitResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Wait(1);
    }
    StringTable_SearchRetained(table, string, &found, (unsigned int *)&index);
    if (g_stringTableSemaphore != 0) {
        signalResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Signal();
    }
    return found;
}

StringTokenHeader *StringTable_Register(StringTable *table, StringTokenHeader *header, StringChunk *chunk, int string) {
    int index;
    int found;
    igResult waitResult;
    igResult signalResult;

    if (g_stringTableSemaphore != 0) {
        waitResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Wait(1);
    }
    header->owner = (int)chunk;
    header->refCount = 1;
    index = 0;
    found = 0;
    StringTable_SearchRetained(table, string, &found, (unsigned int *)&index);
    StringTable_InsertAt(table, (int)header, index);
    if (g_stringTableSemaphore != 0) {
        signalResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Signal();
    }
    return header;
}

void StringTable_RemoveHeader(StringTable *table, int header) {
    int index;
    int found;
    igResult waitResult;
    igResult signalResult;

    if (g_stringTableSemaphore != 0) {
        waitResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Wait(1);
    }
    index = 0;
    found = 0;
    StringTable_SearchRetained(table, header + 8, &found, (unsigned int *)&index);
    StringTable_EraseAt(table, index);
    if (g_stringTableSemaphore != 0) {
        signalResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Signal();
    }
}

/* An emptied chunk is unlinked from the pool's chain and destroyed once an empty chunk has already
 * been seen; the first one is only counted and kept. */
void StringTable_NotifyEmptyChunk(StringTable *table, StringChunk *chunk) {
    igResult waitResult;
    igResult signalResult;
    int seen;
    StringChunk **chain;
    StringChunk *head;
    StringChunk *next;
    StringChunk *previous;

    if (g_stringTableSemaphore != 0) {
        waitResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Wait(1);
    }
    seen = table->emptyChunks;
    if (seen > 0) {
        chain = &table->pool->chunks;
        head = *chain;
        if (chunk == head) {
            *chain = head->next;
        } else {
            previous = chunk->previous;
            previous->next = chunk->next;
            next = previous->next;
            if (next != 0) {
                next->previous = previous;
            }
        }
        StringChunk_Destroy(chunk, 1);
    } else {
        table->emptyChunks = seen + 1;
    }
    if (g_stringTableSemaphore != 0) {
        signalResult = ((igSemaphoreView *)(g_stringTableSemaphore))->Signal();
    }
}

int StringTable_SearchRetained(StringTable *table, int string, int *outString, unsigned int *outIndex) {
    unsigned int lo;
    unsigned int n;
    unsigned int mid;
    StringTokenHeader *e;
    int s;
    int r;
    lo = 0;
    for (n = table->step; n != 0; n >>= 1) {
        mid = lo + n;
        if (table->count >= mid) {
            e = table->entries[mid - 1];
            s = (int)e + 8;
            r = strcmp(string, s);
            if (r == 0) {
                e->refCount = e->refCount + 1;
                *outString = s;
                *outIndex = mid - 1;
                return 1;
            }
            if (r > 0) {
                lo = mid;
            }
        }
    }
    *outIndex = lo;
    return 0;
}

/* Remove the element at `index` from the array by sliding the following elements down one slot,
 * then halve `step` when the count drops below it. */
void StringTable_EraseAt(StringTable *self, unsigned index) {
    StringTokenHeader **slot = self->entries + index;
    --self->count;
    memmove(slot, slot + 1, (self->count - index) * 4);
    if (self->count < self->step) self->step >>= 1;
}

/* Insert `header` at `index`, doubling the slot array when full, then double `step` once the count
 * reaches twice it. */
void StringTable_InsertAt(StringTable *table, int header, int index) {
    unsigned int capacity;
    StringTokenHeader **slot;
    unsigned int grown;
    unsigned int step;
    unsigned int doubled;

    capacity = table->capacity;
    if (table->count == capacity) {
        grown = capacity * 2;
        table->entries = (StringTokenHeader **)Memory_ReallocateBuffer(table->entries, grown * 4);
        table->capacity = grown;
    }
    slot = table->entries + index;
    memmove(slot + 1, slot, (table->count - index) * 4);
    table->entries[index] = (StringTokenHeader *)header;
    table->count = table->count + 1;
    step = table->step;
    doubled = step * 2;
    if (doubled <= table->count) {
        doubled = (step != 0) ? doubled : 1;
        table->step = doubled;
    }
}

void *StringTable_AllocateObject(unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

int StringTable_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA((void *)object);
}

/* Chunk constructor. The cache starts unknown (-1) and the chunk empty; storage is then allocated
 * by StringChunk_InitializeStorage. */
StringChunk *StringChunk_Construct(StringChunk *chunk, StringChunk *previous, StringTable *table, int capacity) {
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

/* Chunk destructor; releases the storage and deletes the object when the signed low 16 bits of
 * deleteFlags are positive. */
StringChunk *StringChunk_Destroy(StringChunk *chunk, long long deleteFlags) {
    if (chunk != 0) {
        StringChunk_FreeStorage(chunk);
        if ((short)deleteFlags > 0) {
            StringChunk_DeleteObject((int)chunk);
        }
    }
    return chunk;
}

/* Carve a block for `size` text bytes plus the 8-byte token header from the first chunk that has
 * room, appending a chunk (at least the head's capacity) when none has. Returns the text address;
 * the block start and its chunk go to the out parameters. */
int StringChunk_AllocateToken(StringChunk *head, int size, StringChunk **chunkOut, int *headerOut) {
    unsigned int bytes;
    int block;
    StringChunk *fresh;
    StringChunk *chunk;
    unsigned int capacity;

    bytes = ((size + 3) & ~3) + 8;
    block = 0;
    chunk = head;
    for (;;) {
        int largest = chunk->largestFree;
        if (!(largest >= 0 && bytes > (unsigned int) largest)) {
            block = (int)StringChunk_TakeBlock(chunk, bytes);
        }
        if (block != 0) break;
        if (chunk->next == 0) {
            capacity = head->capacity;
            if (capacity < bytes) {
                capacity = bytes;
            }
            fresh = (StringChunk *)StringChunk_AllocateObject(0x24, (igMemoryPoolView *)head->table->pool->pool);
            if (fresh != 0) {
                fresh = StringChunk_Construct(fresh, chunk, head->table, capacity);
            }
            chunk->next = fresh;
        }
        chunk = chunk->next;
    }
    *chunkOut = chunk;
    chunk->isEmpty = 0;
    *headerOut = block;
    return block + 8;
}

/* Give a string's block back to its chunk. `header` is the block start; the NUL-terminated text
 * lives at header + 8, so the block is 8 header bytes + strlen + NUL. If the chunk becomes empty
 * its owner is told so it can drop the chunk. */
void StringChunk_ReleaseHeader(StringChunk *self, int header) {
    StringTable_RemoveHeader(self->table, header);
    StringChunk_ReturnBlock(self, (char *)header, strlen(header + 8) + 9);
    if (self->isEmpty != 0) {
        StringTable_NotifyEmptyChunk(self->table, self);
    }
}

void StringChunk_InitializeStorage(StringChunk *chunk) {
    igMemoryPoolView *pool = (igMemoryPoolView *)chunk->table->pool->pool;
    chunk->storage=(char *)pool->Allocate(chunk->capacity);
    chunk->freeHead=chunk->storage+chunk->capacity;
    chunk->storageEnd=chunk->storage+chunk->capacity;
    {
        unsigned short *footer_end=(unsigned short *)chunk->freeHead;
        footer_end[-1]=((unsigned)chunk->capacity)>>2;
        footer_end[-2]=0;
    }
}

int StringChunk_FreeStorage(StringChunk *chunk)
{
    return Memory_FreeBuffer(chunk->storage);
}

char *StringChunk_TakeBlock(StringChunk *self, unsigned int bytes) {
 unsigned short want;
 unsigned short largest;
 unsigned short sz;
 char *prev;
 char *blk;
 unsigned short next;
 StringBlockHeader *h;
 char *r;
 blk = self->freeHead; want = (bytes >> 2) & 0xFFFF; largest = 0; prev = 0;
 while (blk != 0) {
  h = (StringBlockHeader *)(blk - 4);
  sz = h->size; next = h->next;
  if (sz > largest) { largest = sz; }
  if (!(want > sz)) {
   r = blk - sz * 4;
   if (want == sz) {
    if (prev != 0) {
     h = (StringBlockHeader *)(prev - 4);
     if (next == 0) { h->next = 0; } else { h->next += next; }
    }
    if (blk == self->freeHead) {
     if (next != 0) { self->freeHead = self->freeHead + next * 4; } else { self->freeHead = 0; }
    }
   } else { h->size -= want; }
   self->largestFree = -1;
   return r;
  }
  prev = blk;
  if (next == 0) { blk = 0; } else { blk = blk + next * 4; }
 }
 self->largestFree = largest * 4;
 return 0;
}

/* Absorb free block `left` into the adjacent free block `right` (and extend `previous`'s link past
 * it). Free-list references are block ends; each end carries two halfwords, the distance to the
 * next free end (-4 bytes) and the block length (-2 bytes), both in 4-byte units. Returns the
 * merged length in bytes. */
int StringChunk_MergeBlocks(StringChunk *chunk, unsigned short *previous,
                unsigned short *left, unsigned short *right) {
    if ((char *)left == chunk->freeHead) {
        chunk->freeHead = (char *)right;
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

/* Give `bytes` at `block` back to the free list, which is kept in address order, and merge the
 * block with free neighbours on either side. */
void StringChunk_ReturnBlock(StringChunk *self, char *block, unsigned int bytes) {
    unsigned short units = (bytes + 3) >> 2;
    int size = units * 4;
    char *end = block + size;
    char *previous = 0;
    char *next = self->freeHead;
    char *beforePrevious = 0;
    if (next == 0 || end < next) {
        self->freeHead = end;
    } else {
        unsigned short link;
        for (next = self->freeHead; next < end; next += link * 4) {
            link = ((StringBlockHeader *)(next - 4))->next;
            beforePrevious = previous;
            previous = next;
            if (link == 0) {
                next = 0;
                break;
            }
        }
    }
    StringBlockHeader *footer = (StringBlockHeader *)(end - 4);
    footer->size = units;
    footer->next = next == 0 ? 0 : (next - end) >> 2;
    if (previous != 0) {
        ((StringBlockHeader *)(previous - 4))->next = (end - previous) >> 2;
        if (end - size == previous) {
            size = StringChunk_MergeBlocks(self, (unsigned short *)beforePrevious, (unsigned short *)previous, (unsigned short *)end);
            previous = beforePrevious;
        }
    }
    if (next != 0 && next - ((StringBlockHeader *)(next - 4))->size * 4 == end) {
        size = StringChunk_MergeBlocks(self, (unsigned short *)previous, (unsigned short *)end, (unsigned short *)next);
    }
    if (0 <= self->largestFree && self->largestFree < size) {
        self->largestFree = size;
    }
    if (size == self->capacity) {
        self->isEmpty = 1;
    }
}

void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

/* Delete wrapper, same target as StringTable_DeleteObject. */
int StringChunk_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA((void *)object);
}

