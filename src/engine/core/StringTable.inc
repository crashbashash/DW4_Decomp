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

void StringTable_SetSynchronization(int arg0) {
    int var_v0;
    igSemaphoreView *o;
    igObject *p;
    if (arg0 != 0) {
        if (DAT_005871c8[0] == 0) {
            var_v0 = ((int)Memory_GetCurrentAllocator());
var_v0 = g_useOwnerAllocator != 0 ? var_v0 : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
            o = (igSemaphoreView *)igSemaphore_Create(var_v0);
            o->create();
            DAT_005871c8[0] = o;
        }
    } else {
        p = (igObject *)DAT_005871c8[0];
        if (p != 0) {
            DAT_005871c8[0] = 0;
            p->_refCount = (int)p->_refCount - 1;
            if (((unsigned long long)(long long)(int)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
        }
    }
}

int StringTable_Find(StringTable *arg0, int arg1) {
    int sp3C;
    int sp38;
    igResult sp34;
    igResult sp30;

    sp3C = 0;
    sp38 = 0;
    if (DAT_005871c8[0] != 0) {
        sp34 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    StringTable_SearchRetained(arg0, arg1, &sp38, (unsigned int *)&sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
    return sp38;
}

StringTokenHeader *StringTable_Register(StringTable *arg0, StringTokenHeader *arg1, StringChunk *arg2, int arg3) {
    int sp5C;
    int sp58;
    igResult sp54;
    igResult sp50;

    if (DAT_005871c8[0] != 0) {
        sp54 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    arg1->owner = (int)arg2;
    arg1->refCount = 1;
    sp5C = 0;
    sp58 = 0;
    StringTable_SearchRetained(arg0, arg3, &sp58, (unsigned int *)&sp5C);
    StringTable_InsertAt(arg0, (int)arg1, sp5C);
    if (DAT_005871c8[0] != 0) {
        sp50 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
    return arg1;
}

void StringTable_RemoveHeader(StringTable *arg0, int arg1) {
    int sp3C;
    int sp38;
    igResult sp34;
    igResult sp30;

    if (DAT_005871c8[0] != 0) {
        sp34 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    sp3C = 0;
    sp38 = 0;
    StringTable_SearchRetained(arg0, arg1 + 8, &sp38, (unsigned int *)&sp3C);
    StringTable_EraseAt(arg0, sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
}

/* An emptied chunk is unlinked from the pool's chain and destroyed once an empty chunk has already
 * been seen; the first one is only counted and kept. */
void StringTable_NotifyEmptyChunk(StringTable *table, StringChunk *chunk) {
    igResult sp3C;
    igResult sp38;
    int seen;
    StringChunk **chain;
    StringChunk *head;
    StringChunk *next;
    StringChunk *previous;

    if (DAT_005871c8[0] != 0) {
        sp3C = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
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
    if (DAT_005871c8[0] != 0) {
        sp38 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
}

int StringTable_SearchRetained(StringTable *arg0, int arg1, int *arg2, unsigned int *arg3) {
    unsigned int lo;
    unsigned int n;
    unsigned int mid;
    StringTokenHeader *e;
    int s;
    int r;
    lo = 0;
    for (n = arg0->step; n != 0; n >>= 1) {
        mid = lo + n;
        if (arg0->count >= mid) {
            e = arg0->entries[mid - 1];
            s = (int)e + 8;
            r = strcmp(arg1, s);
            if (r == 0) {
                e->refCount = e->refCount + 1;
                *arg2 = s;
                *arg3 = mid - 1;
                return 1;
            }
            if (r > 0) {
                lo = mid;
            }
        }
    }
    *arg3 = lo;
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
    StringChunk_ReturnBlock(self, header, strlen(header + 8) + 9);
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

void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

/* Delete wrapper, same target as StringTable_DeleteObject. */
int StringChunk_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA((void *)object);
}

