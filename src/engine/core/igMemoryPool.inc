int FUN_002c04a0(void) {
    if (DAT_00585ea0[0] == 0) {
        DAT_00585ea0[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585ea0[0];
}

igMetaObject *igMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0540();
    return g_igMemoryPool_metaObject[0];
}

void FUN_002c0540(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPool_Register);
}

void igMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igMemoryPool_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMemoryPool_GetMetaObject,
        igMemoryPool_className,
        0x70, /* instance size */
        0,
        &igMemoryPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryPool_GetMetaObject(void) {
    igMemoryPool_GetMetaObject();
}

void igMemoryPool_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(((void * *)DAT_00585ea0)[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0190[0], 0xE);
    FUN_002d3890((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)), 1);
    FUN_002d3890((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c01d0[0], (igMetaField ***)&DAT_004c0210[0], &DAT_004c0250[0], temp_s1);
    *(int *)((char *)(((void * *)DAT_00585ea0)[0]) + 60) = (int)thunk_igArenaMemoryPool_GetMetaObject;
}

