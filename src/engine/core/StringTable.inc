void *StringTable_Construct(void *arg0, void *arg1, int arg2) {
    *(int *)((char *)(arg0) + 0) = (int)(arg1);
    *(int *)((char *)(arg0) + 4) = 0;
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 12) = arg2;
    *(int *)((char *)(arg0) + 16) = (int)(*(igMemoryPoolView **)((char *)arg1 + 12))->Allocate(arg2 * 4);
    *(int *)((char *)(arg0) + 20) = 0;
    return arg0;
}

/* Table destructor: frees the element array (`data`) and, for a positive 16-bit `delete_flag`,
 * deletes the table object. */
void *StringTable_Destroy(StringTableLayout *self, long long delete_flag) {
    if (self != 0) {
        Memory_FreeBuffer((void *)((int)self->data));
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
            var_v0 = ((int)FUN_002f8a20());
var_v0 = g_useOwnerAllocator != 0 ? var_v0 : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
            o = (igSemaphoreView *)FUN_002ba650(var_v0);
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

int StringTable_Find(int arg0, int arg1) {
    int sp3C;
    int sp38;
    igResult sp34;
    igResult sp30;

    sp3C = 0;
    sp38 = 0;
    if (DAT_005871c8[0] != 0) {
        sp34 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg1, &sp38, (unsigned int *)&sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
    return sp38;
}

void *StringTable_Register(int arg0, void *arg1, int arg2, int arg3) {
    int sp5C;
    int sp58;
    igResult sp54;
    igResult sp50;

    if (DAT_005871c8[0] != 0) {
        sp54 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    *(int *)((char *)(arg1) + 0) = arg2;
    *(int *)((char *)(arg1) + 4) = 1;
    sp5C = 0;
    sp58 = 0;
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg3, &sp58, (unsigned int *)&sp5C);
    StringTable_InsertAt((struct StringTableInsertView *)arg0, (int)arg1, sp5C);
    if (DAT_005871c8[0] != 0) {
        sp50 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
    return arg1;
}

void StringTable_RemoveHeader(int arg0, int arg1) {
    int sp3C;
    int sp38;
    igResult sp34;
    igResult sp30;

    if (DAT_005871c8[0] != 0) {
        sp34 = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    sp3C = 0;
    sp38 = 0;
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg1 + 8, &sp38, (unsigned int *)&sp3C);
    StringTable_EraseAt((StringTableLayout *)arg0, sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
}

void StringTable_NotifyEmptyChunk(StringTableChunkList *arg0, void *arg1) {
    igResult sp3C;
    igResult sp38;
    int temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1_2;

    if (DAT_005871c8[0] != 0) {
        sp3C = ((igSemaphoreView *)(DAT_005871c8[0]))->wait(1);
    }
    temp_v1 = arg0->cnt;
    if (temp_v1 > 0) {
        temp_v0 = (void *)(arg0->first);
        temp_v0_2 = (void *)(*(int *)((char *)(temp_v0) + 4));
        if (arg1 == temp_v0_2) {
            *(int *)((char *)(temp_v0) + 4) = (int)((int) *(int *)((char *)(temp_v0_2) + 4));
        } else {
            temp_v1_2 = (void *)(*(int *)((char *)(arg1) + 8));
            *(int *)((char *)(temp_v1_2) + 4) = (int)((int) *(int *)((char *)(arg1) + 4));
            temp_v0_3 = (void *)(*(int *)((char *)(temp_v1_2) + 4));
            if (temp_v0_3 != 0) {
                *(int *)((char *)(temp_v0_3) + 8) = (int)(temp_v1_2);
            }
        }
        StringChunk_Destroy((StringChunk *)arg1, 1);
    } else {
        arg0->cnt = temp_v1 + 1;
    }
    if (DAT_005871c8[0] != 0) {
        sp38 = ((igSemaphoreView *)(DAT_005871c8[0]))->signal();
    }
}

int StringTable_SearchRetained(struct StringTableSearchView *arg0, int arg1, int *arg2, unsigned int *arg3) {
    unsigned int lo;
    unsigned int n;
    unsigned int mid;
    StringTokenHeader *e;
    int s;
    int r;
    lo = 0;
    for (n = arg0->n; n != 0; n >>= 1) {
        mid = lo + n;
        if (arg0->cnt >= mid) {
            e = (StringTokenHeader *)arg0->tab[mid - 1];
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
void StringTable_EraseAt(StringTableLayout *self, unsigned index) {
    void **slot = self->data + index;
    --self->count;
    memmove(slot, slot + 1, (self->count - index) * 4);
    if (self->count < self->step) self->step >>= 1;
}

void StringTable_InsertAt(struct StringTableInsertView *arg0, int arg1, int arg2) {
    int temp_v1;
    char *temp_a1;
    int temp_s0;
    unsigned int temp_a1_2;
    unsigned int var_a0;

    temp_v1 = arg0->f12;
    if (arg0->cnt == temp_v1) {
        int nc = temp_v1 * 2;
        arg0->f16 = (char *)Memory_ReallocateBuffer(arg0->f16, nc * 4);
        arg0->f12 = nc;
    }
    temp_s0 = arg2 * 4;
    temp_a1 = arg0->f16 + temp_s0;
    memmove(temp_a1 + 4, temp_a1, (arg0->cnt - arg2) * 4);
    *(int *)(arg0->f16 + temp_s0) = arg1;
    arg0->cnt = arg0->cnt + 1;
    temp_a1_2 = arg0->f8;
    var_a0 = temp_a1_2 * 2;
    if (var_a0 <= arg0->cnt) {
        var_a0 = (temp_a1_2 != 0) ? var_a0 : 1;
        arg0->f8 = var_a0;
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

int StringChunk_AllocateToken(struct StringChunkTokenView *arg0, int arg1, struct StringChunkTokenView **arg2, int *arg3) {
    unsigned int temp_s3;
    int var_s2;
    void *var_v0;
    struct StringChunkTokenView *var_s1;
    unsigned int var_s0;

    temp_s3 = ((arg1 + 3) & ~3) + 8;
    var_s2 = 0;
    var_s1 = arg0;
    for (;;) {
        int temp_v0 = var_s1->f28;
        if (!(temp_v0 >= 0 && temp_s3 > (unsigned int) temp_v0)) {
            var_s2 = (int)StringChunk_TakeBlock((StringChunkState *)var_s1, temp_s3);
        }
        if (var_s2 != 0) break;
        if (var_s1->next == 0) {
            var_s0 = arg0->f12;
            if (var_s0 < temp_s3) {
                var_s0 = temp_s3;
            }
            var_v0 = StringChunk_AllocateObject(0x24, (igMemoryPoolView *)arg0->f0->f0->f12);
            if (var_v0 != 0) {
                var_v0 = StringChunk_Construct((StringChunk *)var_v0, (int)var_s1, (int)arg0->f0, var_s0);
            }
            var_s1->next = (struct StringChunkTokenView *)var_v0;
        }
        var_s1 = var_s1->next;
    }
    *arg2 = var_s1;
    var_s1->f32 = 0;
    *arg3 = var_s2;
    return var_s2 + 8;
}

/* Give a string's block back to its chunk. `header` is the block start; the NUL-terminated text
 * lives at header + 8, so the block is 8 header bytes + strlen + NUL. If the chunk becomes empty
 * its owner is told so it can drop the chunk. */
void StringChunk_ReleaseHeader(StringChunkOwnerView *self, int header) {
    StringTable_RemoveHeader(self->owner, header);
    StringChunk_ReturnBlock(self, header, strlen(header + 8) + 9);
    if (self->is_empty != 0) {
        StringTable_NotifyEmptyChunk((StringTableChunkList *)self->owner, self);
    }
}

void StringChunk_InitializeStorage(StringChunk *chunk) {
    igMemoryPoolView *pool = (igMemoryPoolView *)*(int *)((char *)*(int *)chunk->table+12);
    chunk->storage=(int)pool->Allocate(chunk->capacity);
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
    return Memory_FreeBuffer((void *)chunk->storage);
}

char *StringChunk_TakeBlock(StringChunkState *self, unsigned int bytes) {
 unsigned short want;
 unsigned short largest;
 unsigned short sz;
 char *prev;
 char *blk;
 unsigned short next;
 StringBlockHeader *h;
 char *r;
 blk = self->free; want = (bytes >> 2) & 0xFFFF; largest = 0; prev = 0;
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
    if (blk == self->free) {
     if (next != 0) { self->free = self->free + next * 4; } else { self->free = 0; }
    }
   } else { h->size -= want; }
   self->largest = -1;
   return r;
  }
  prev = blk;
  if (next == 0) { blk = 0; } else { blk = blk + next * 4; }
 }
 self->largest = largest * 4;
 return 0;
}

/* Absorb free block `left` into the adjacent free block `right` (and extend `previous`'s link past
 * it). Free-list references are block ends; each end carries two halfwords, the distance to the
 * next free end (-4 bytes) and the block length (-2 bytes), both in 4-byte units. Returns the
 * merged length in bytes. */
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

void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool)
{
    return pool->Allocate(size);
}

/* Delete wrapper, same target as StringTable_DeleteObject. */
int StringChunk_DeleteObject(int object)
{
    return Memory_FreeBufferAliasA((void *)object);
}

