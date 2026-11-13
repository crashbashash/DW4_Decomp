void * FUN_002bc0d0(int arg0) {
    FUN_002bc1b0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585AA8), (MemoryPool *)arg0));
}

igMetaObject *FUN_002bc110(void) {
    if (g_igQueue_metaObject[0] == 0) {
        g_igQueue_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igQueue_metaObject[0];
}

igMetaObject *igQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc1b0();
    return g_igQueue_metaObject[0];
}

void FUN_002bc1b0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igQueue_Register);
}

void igQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igQueue_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igQueue_GetMetaObject,
        igQueue_className,
        0xC, /* instance size */
        0,
        &igQueue_InitFields,
        0, /* extra callback item */
        g_igQueue_callbackList /* callback list */
    );
}

void thunk_igQueue_GetMetaObject(void) {
    igQueue_GetMetaObject();
}

void igQueue_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(((void * *)g_igQueue_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igQueue_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_002b8390();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igQueue_fieldTable[0], (igMetaField ***)&DAT_004bf9c8[0], &DAT_004bf9d0[0], temp_s2);
    *(int *)((char *)(((void * *)g_igQueue_metaObject)[0]) + 60) = (int)thunk_igStandardQueue_GetMetaObject;
}

