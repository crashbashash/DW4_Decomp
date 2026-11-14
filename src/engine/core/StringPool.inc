StringPool *StringPool_Construct(StringPool *pool) {
    int allocator;
    StringTable *table;
    StringChunk *chunk;

    pool->table = 0;
    pool->chunks = 0;
    pool->chunkSize = 0x4000;
    pool->pool = 0;
    allocator = pool->pool;
    allocator = g_useOwnerAllocator != 0 ? allocator : (int)((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
    pool->pool = allocator;
    if (pool->pool == 0) {
        pool->pool = ((int)Memory_GetDefaultAllocator());
    }
    table = (StringTable *)StringTable_AllocateObject(0x18, (igMemoryPoolView *)pool->pool);
    if (table != 0) {
        table = StringTable_Construct(table, pool, 0x400);
    }
    pool->table = table;
    chunk = (StringChunk *)StringChunk_AllocateObject(0x24, (igMemoryPoolView *)pool->pool);
    if (chunk != 0) {
        chunk = StringChunk_Construct(chunk, 0, pool->table, pool->chunkSize);
    }
    pool->chunks = chunk;
    return pool;
}

StringPool *StringPool_Destroy(StringPool *self, long long delete_flag) {
    if (self != 0) {
        StringPool_DestroyChunks(self);
        StringTable_Destroy(self->table, 1);
        if ((short)delete_flag > 0) {
            FUN_002eb050((int)self);
        }
    }
    return self;
}

void StringPool_DestroyChunks(StringPool *pool) {
    StringChunk *c = pool->chunks;
    while (c != 0) {
        StringChunk *t = c;
        c = c->next;
        StringChunk_Destroy(t, 1);
    }
}

int StringPool_Intern(StringPool *pool, const char *name)
{
    int token;
    StringChunk *chunk;
    int copy, size;

    if (name == 0) {
        return 0;
    }
    token = 0;
    copy = StringTable_Find(pool->table, (int)name);
    if (copy == 0) {
        chunk = 0;
        size = strlen(name) + 1;
        copy = StringChunk_AllocateToken(pool->chunks, size, &chunk, &token);
        memcpy((void *)copy, name, size);
        StringTable_Register(pool->table, (StringTokenHeader *)token, chunk, copy);
    }
    return copy;
}

void * StringPool_Allocate(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    return ((igMemoryPoolView *)temp_v0)->Allocate(arg0);
}

void FUN_002eb050(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    ((igMemoryPoolView *)(temp_v0))->Free((void *)arg0);
}

void FUN_002eb090(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

