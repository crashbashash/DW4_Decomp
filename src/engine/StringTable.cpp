/* ABI declarations below describe only observed fields and vtable position. Reserved slots are not
 * recovered method names; never instantiate these views. */
class igMemoryPoolView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *Allocate(unsigned int size);
    virtual void *vfunc_53(unsigned int size, unsigned int alignment);
    virtual void d54(); virtual void d55();
    virtual void *Reallocate(void *block, unsigned int size);
    virtual void d57();
    virtual int vfunc_58(void *block);
    virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void Free(void *block);
};

/* MWCC reserves two leading slots, so 52 preceding methods place allocate at byte 216. */
class AllocatorSlot216 {
public:
    virtual void reserved0(); virtual void reserved1(); virtual void reserved2(); virtual void reserved3();
    virtual void reserved4(); virtual void reserved5(); virtual void reserved6(); virtual void reserved7();
    virtual void reserved8(); virtual void reserved9(); virtual void reserved10(); virtual void reserved11();
    virtual void reserved12(); virtual void reserved13(); virtual void reserved14(); virtual void reserved15();
    virtual void reserved16(); virtual void reserved17(); virtual void reserved18(); virtual void reserved19();
    virtual void reserved20(); virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
    virtual void reserved24(); virtual void reserved25(); virtual void reserved26(); virtual void reserved27();
    virtual void reserved28(); virtual void reserved29(); virtual void reserved30(); virtual void reserved31();
    virtual void reserved32(); virtual void reserved33(); virtual void reserved34(); virtual void reserved35();
    virtual void reserved36(); virtual void reserved37(); virtual void reserved38(); virtual void reserved39();
    virtual void reserved40(); virtual void reserved41(); virtual void reserved42(); virtual void reserved43();
    virtual void reserved44(); virtual void reserved45(); virtual void reserved46(); virtual void reserved47();
    virtual void reserved48(); virtual void reserved49(); virtual void reserved50(); virtual void reserved51();
    virtual int allocate_bytes(int);
};
struct DW4SR4 { int w0; };
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };

/* 24-byte target ABI view. Field labels do not assert the original C++ member spelling. */
typedef struct {
    int pool;
    unsigned count, step, capacity;
    void **data;
    int cleanup;
} StringTableLayout;
typedef char StringTableLayoutSize[(sizeof(StringTableLayout) == 24) ? 1 : -1];

struct StringTableEntry { int pad4; int rc; };
struct StringTableSearchView { int pad[1]; unsigned int cnt; unsigned int n; int pad12; int *tab; };
struct StringTableInsertView { char pad[4]; unsigned cnt; unsigned f8; int f12; char *f16; };
struct StringTableChunkList { int first; int pad[4]; int cnt; };

/* 36-byte string chunk. References are 4-byte values in this ABI. */
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

struct StringChunkStorageView {
    int table, next, previous, size, storage, end, head, largest;
    unsigned char empty;
};
typedef char StringChunkSizeCheck[sizeof(StringChunkStorageView)==36 ? 1 : -1];

/* A string chunk as its release path sees it. Field labels do not assert the original member
 * spelling. */
typedef struct StringChunkOwnerView {
    int owner;                  /* +0  the pool that owns the chunk */
    struct StringChunkOwnerView *next; /* +4 */
    struct StringChunkOwnerView *prev; /* +8 */
    unsigned capacity;          /* +12 storage size in bytes */
    char pad16[16];             /* +16 storage pointers, not used here */
    unsigned char is_empty;     /* +32 set at construction, cleared by StringChunk_AllocateToken */
} StringChunkOwnerView;
typedef char StringChunkOwnerViewSize[(sizeof(StringChunkOwnerView) == 36) ? 1 : -1];

struct StringChunkPool { struct StringChunkPool *f0; int f4; int f8; int f12; };
struct StringChunkTokenView { struct StringChunkPool *f0; struct StringChunkTokenView *next; int f8; unsigned f12; int p16[3]; int f28; char f32; };

typedef struct StringBlockHeader { unsigned short next; unsigned short size; } StringBlockHeader;
typedef struct StringChunkState { char pad[24]; char *free; int largest; } StringChunkState;

struct SyncResult { int v; SyncResult() {} };
class SyncLockView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual SyncResult vX(); };
struct SyncLockRef { int word0; int references; };

extern "C" {
void **FUN_002ba650(...);
int FUN_002f8a20(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int Memory_FreeBuffer(int);
int Memory_FreeBufferAliasA(int);
int Memory_ReallocateBuffer(...);
int memmove(...);
int strcmp(...);
int strlen(...);
extern int DAT_00587038[4];
extern void *DAT_005871c8[4];
extern unsigned char GPR_00554c14;

void *StringTable_Construct(void *arg0, void *arg1, int arg2);
void *StringTable_Destroy(StringTableLayout *self, long long delete_flag);
void StringTable_SetSynchronization(int arg0);
int StringTable_Find(int arg0, int arg1);
void *StringTable_Register(int arg0, void *arg1, int arg2, int arg3);
void StringTable_RemoveHeader(int arg0, int arg1);
void StringTable_NotifyEmptyChunk(StringTableChunkList *arg0, void *arg1);
int StringTable_SearchRetained(struct StringTableSearchView *arg0, int arg1, int *arg2, unsigned int *arg3);
void StringTable_EraseAt(StringTableLayout *self, unsigned index);
void StringTable_InsertAt(struct StringTableInsertView *arg0, int arg1, int arg2);
void *StringTable_AllocateObject(unsigned int size, igMemoryPoolView *pool);
int StringTable_DeleteObject(int object);
void *StringChunk_Construct(StringChunk *chunk, int previous, int table, int capacity);
StringChunk *StringChunk_Destroy(StringChunk *chunk, long long deleteFlags);
int StringChunk_AllocateToken(struct StringChunkTokenView *arg0, int arg1, struct StringChunkTokenView **arg2, int *arg3);
void StringChunk_ReleaseHeader(StringChunkOwnerView *self, int header);
void StringChunk_InitializeStorage(StringChunkStorageView *chunk);
int StringChunk_FreeStorage(StringChunk *chunk);
char *StringChunk_TakeBlock(StringChunkState *self, unsigned int bytes);
int StringChunk_MergeBlocks(StringChunk *chunk, unsigned short *previous, unsigned short *left, unsigned short *right);
int StringChunk_ReturnBlock(...);
void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool);
int StringChunk_DeleteObject(int object);
}

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
        Memory_FreeBuffer((int)self->data);
        if ((short)delete_flag > 0) {
            StringTable_DeleteObject((int)self);
        }
    }
    return self;
}

void StringTable_SetSynchronization(int arg0) {
    int var_v0;
    SyncLockView *o;
    SyncLockRef *p;
    if (arg0 != 0) {
        if (DAT_005871c8[0] == 0) {
            var_v0 = FUN_002f8a20();
var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587038[0]);
            o = (SyncLockView *)FUN_002ba650(var_v0);
            o->vX();
            DAT_005871c8[0] = o;
        }
    } else {
        p = (SyncLockRef *)DAT_005871c8[0];
        if (p != 0) {
            DAT_005871c8[0] = 0;
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
        }
    }
}

int StringTable_Find(int arg0, int arg1) {
    int sp3C;
    int sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;

    sp3C = 0;
    sp38 = 0;
    if (DAT_005871c8[0] != 0) {
        sp34 = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
    }
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg1, &sp38, (unsigned int *)&sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
    return sp38;
}

void *StringTable_Register(int arg0, void *arg1, int arg2, int arg3) {
    int sp5C;
    int sp58;
    DW4SR4 sp54;
    DW4SR4 sp50;

    if (DAT_005871c8[0] != 0) {
        sp54 = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
    }
    *(int *)((char *)(arg1) + 0) = arg2;
    *(int *)((char *)(arg1) + 4) = 1;
    sp5C = 0;
    sp58 = 0;
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg3, &sp58, (unsigned int *)&sp5C);
    StringTable_InsertAt((struct StringTableInsertView *)arg0, (int)arg1, sp5C);
    if (DAT_005871c8[0] != 0) {
        sp50 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
    return arg1;
}

void StringTable_RemoveHeader(int arg0, int arg1) {
    int sp3C;
    int sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;

    if (DAT_005871c8[0] != 0) {
        sp34 = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
    }
    sp3C = 0;
    sp38 = 0;
    StringTable_SearchRetained((struct StringTableSearchView *)arg0, arg1 + 8, &sp38, (unsigned int *)&sp3C);
    StringTable_EraseAt((StringTableLayout *)arg0, sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
}

void StringTable_NotifyEmptyChunk(StringTableChunkList *arg0, void *arg1) {
    DW4SR4 sp3C;
    DW4SR4 sp38;
    int temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1_2;

    if (DAT_005871c8[0] != 0) {
        sp3C = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
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
        sp38 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
}

int StringTable_SearchRetained(struct StringTableSearchView *arg0, int arg1, int *arg2, unsigned int *arg3) {
    unsigned int lo;
    unsigned int n;
    unsigned int mid;
    struct StringTableEntry *e;
    int s;
    int r;
    lo = 0;
    for (n = arg0->n; n != 0; n >>= 1) {
        mid = lo + n;
        if (arg0->cnt >= mid) {
            e = (struct StringTableEntry *)arg0->tab[mid - 1];
            s = (int)e + 8;
            r = strcmp(arg1, s);
            if (r == 0) {
                e->rc = e->rc + 1;
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
    return Memory_FreeBufferAliasA(object);
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
    StringChunk_InitializeStorage((StringChunkStorageView *)chunk);
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

void StringChunk_InitializeStorage(StringChunkStorageView *chunk) {
    chunk->storage=((AllocatorSlot216 *)*(int *)((char *)*(int *)chunk->table+12))->allocate_bytes(chunk->size);
    chunk->head=chunk->storage+chunk->size;
    chunk->end=chunk->storage+chunk->size;
    {
        unsigned short *footer_end=(unsigned short *)chunk->head;
        footer_end[-1]=((unsigned)chunk->size)>>2;
        footer_end[-2]=0;
    }
}

int StringChunk_FreeStorage(StringChunk *chunk)
{
    return Memory_FreeBuffer(chunk->storage);
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
    return Memory_FreeBufferAliasA(object);
}
