int StringPool_DestroyChunks();
int FUN_002eb050(int *);
void *StringTable_Destroy();
int Memory_FreeBuffer(int);
int StringTable_DeleteObject(void *);
int strlen();
int StringTable_RemoveHeader();
int StringTable_NotifyEmptyChunk();
int StringChunk_ReturnBlock();

/* 24-byte target ABI view. Field labels do not assert the original C++ member spelling. */
typedef struct {
    int pool;
    unsigned count, step, capacity;
    void **data;
    int cleanup;
} StringTableLayout;
typedef char StringTableLayoutSize[(sizeof(StringTableLayout) == 24) ? 1 : -1];
/* memmove(destination, source, byte_count): the erase below slides the tail of the array down by
 * one element. The parameter list stays unspecified so the call compiles as in retail. */
int memmove();

/* A string chunk: a block of string storage owned by a pool, kept in a doubly linked list. Field
 * labels do not assert the original member spelling. */
typedef struct StringChunkLayout {
    int owner;                  /* +0  the pool that owns the chunk */
    struct StringChunkLayout *next; /* +4 */
    struct StringChunkLayout *prev; /* +8 */
    unsigned capacity;          /* +12 storage size in bytes */
    char pad16[16];             /* +16 storage pointers, not used here */
    unsigned char is_empty;     /* +32 set at construction, cleared by StringChunk_AllocateToken */
} StringChunkLayout;
typedef char StringChunkLayoutSize[(sizeof(StringChunkLayout) == 36) ? 1 : -1];

/* Pool destructor. Frees the chunk list and the table that is the pool's first member;
 * `delete_flag` is the compiler-generated destructor flag, and a positive value (tested as a
 * 16-bit quantity) also releases the pool object itself. */
int *StringPool_Destroy(int *self, long long delete_flag) {
    if (self != 0) {
        StringPool_DestroyChunks(self);
        StringTable_Destroy((void *)*self, 1);
        if ((short)delete_flag > 0) {
            FUN_002eb050(self);
        }
    }
    return self;
}

/* Table destructor: frees the element array (`data`) and, for a positive 16-bit `delete_flag`,
 * deletes the table object. */
void *StringTable_Destroy(StringTableLayout *self, long long delete_flag) {
    if (self != 0) {
        Memory_FreeBuffer((int)self->data);
        if ((short)delete_flag > 0) {
            StringTable_DeleteObject(self);
        }
    }
    return self;
}

/* Remove the element at `index` from the array by sliding the following elements down one slot,
 * then halve `step` when the count drops below it. */
void StringTable_EraseAt(StringTableLayout *self, unsigned index) {
    void **slot = self->data + index;
    --self->count;
    memmove(slot, slot + 1, (self->count - index) * 4);
    if (self->count < self->step) self->step >>= 1;
}

/* Give a string's block back to its chunk. `header` is the block start; the NUL-terminated text
 * lives at header + 8, so the block is 8 header bytes + strlen + NUL. If the chunk becomes empty
 * its owner is told so it can drop the chunk. */
void StringChunk_ReleaseHeader(StringChunkLayout *self, int header) {
    StringTable_RemoveHeader(self->owner, header);
    StringChunk_ReturnBlock(self, header, strlen(header + 8) + 9);
    if (self->is_empty != 0) {
        StringTable_NotifyEmptyChunk(self->owner, self);
    }
}
