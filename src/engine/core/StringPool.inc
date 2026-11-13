struct S_2eadf0 *StringPool_Construct(struct S_2eadf0 *arg0) {
    int var_v0;
    int var_v0_2;
    int var_v0_3;

    arg0->f0 = 0;
    arg0->f4 = 0;
    arg0->f8 = 0x4000;
    arg0->f12 = 0;
    var_v0 = arg0->f12;
    var_v0 = g_useOwnerAllocator != 0 ? var_v0 : (int)((void **)Memory_GetAllocatorBySelector(DAT_00587048[0]));
    arg0->f12 = var_v0;
    if (arg0->f12 == 0) {
        arg0->f12 = ((int)Memory_GetDefaultAllocator());
    }
    var_v0_2 = ((int)StringTable_AllocateObject(0x18, (igMemoryPoolView *)arg0->f12));
    if (var_v0_2 != 0) {
        var_v0_2 = ((int)StringTable_Construct((void *)var_v0_2, (void *)arg0, 0x400));
    }
    arg0->f0 = var_v0_2;
    var_v0_3 = ((int)StringChunk_AllocateObject(0x24, (igMemoryPoolView *)arg0->f12));
    if (var_v0_3 != 0) {
        var_v0_3 = ((int)StringChunk_Construct((StringChunk *)var_v0_3, 0, arg0->f0, arg0->f8));
    }
    arg0->f4 = var_v0_3;
    return arg0;
}

int *StringPool_Destroy(int *self, long long delete_flag) {
    if (self != 0) {
        StringPool_DestroyChunks((struct P_2eadf0 *)self);
        StringTable_Destroy((StringTableLayout *)((void *)*self), 1);
        if ((short)delete_flag > 0) {
            FUN_002eb050((int)self);
        }
    }
    return self;
}

void StringPool_DestroyChunks(struct P_2eadf0 *arg0) {
    struct C_2eadf0 *c = arg0->head;
    while (c != 0) {
        struct C_2eadf0 *t = c;
        c = c->next;
        StringChunk_Destroy((StringChunk *)t, 1);
    }
}

int StringPool_Intern(StringPool *pool, const char *name)
{
    int token, hash;
    int copy, size;

    if (name == 0) {
        return 0;
    }
    token = 0;
    copy = StringTable_Find(pool->table, (int)name);
    if (copy == 0) {
        hash = 0;
        size = strlen(name) + 1;
        copy = StringChunk_AllocateToken((struct StringChunkTokenView *)pool->chunks, size, (struct StringChunkTokenView **)&hash, &token);
        memcpy((void *)copy, name, size);
        StringTable_Register(pool->table, (void *)token, hash, copy);
    }
    return copy;
}

void * StringPool_Allocate(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(DAT_00587048[0])));
    return (void *)(((DW4VC_216_1 *)(temp_v0))->vX((int)(arg0)));
}

void FUN_002eb050(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(DAT_00587048[0])));
    ((DW4VC_264_1 *)(temp_v0))->vX((int)(arg0));
}

void FUN_002eb090(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

