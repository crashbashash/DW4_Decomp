void * FUN_002c8450(int arg0) {
    igDataList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586788), (MemoryPool *)arg0));
}

/* Created with allocation only when missing. */
int igDataList_GetOrCreateMetaObject(void) {
    if (((int *)g_igDataList_metaObject)[0] == 0) {
        ((int *)g_igDataList_metaObject)[0] = (int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return ((int *)g_igDataList_metaObject)[0];
}

igMetaObject *igDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataList_EnsureRegistered();
    return g_igDataList_metaObject[0];
}

int igDataList_GetVTable(void) {
    igDataList list;

    igObject_InitHeader((struct ObjectHeader *)&list);
    list._vtable = (int)&DAT_005309b0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDataList_Register);
}

void *igDataList_Register(void) {
    FUN_002b5d50();
    return ((void *)igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDataList_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataList_GetMetaObject,
        igDataList_className,
        0x14, /* instance size */
        igDataList_GetVTable,
        &igDataList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    ));
}

void thunk_igDataList_GetMetaObject(void) {
    igDataList_GetMetaObject();
}

void igDataList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDataList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igDataList_ctorTable[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igDataList_fieldTable[0], (igMetaField ***)&DAT_004c13a0[0], &DAT_004c13b0[0], temp_s2);
}

