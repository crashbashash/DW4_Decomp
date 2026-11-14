void * igQueue_Create(int arg0) {
    igQueue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AA8), (igMemoryPoolView *)arg0));
}

igMetaObject *igQueue_GetOrCreateMetaObject(void) {
    if (g_igQueue_metaObject[0] == 0) {
        g_igQueue_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igQueue_metaObject[0];
}

igMetaObject *igQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igQueue_EnsureRegistered();
    return g_igQueue_metaObject[0];
}

void igQueue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igQueue_Register);
}

void igQueue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igQueue_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igQueue_GetMetaObjectFunction,
        igQueue_className,
        0xC, /* instance size */
        0,
        &igQueue_InitFields,
        0, /* extra callback item */
        g_igQueue_callbackList /* callback list */
    );
}

void igQueue_GetMetaObjectFunction(void) {
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
    *(int *)((char *)(temp_s1) + 56) = (int)igThreadList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igQueue_fieldTable[0], (igMetaField ***)&DAT_004bf9c8[0], &DAT_004bf9d0[0], temp_s2);
    *(int *)((char *)(((void * *)g_igQueue_metaObject)[0]) + 60) = (int)igStandardQueue_GetMetaObjectFunction;
}

