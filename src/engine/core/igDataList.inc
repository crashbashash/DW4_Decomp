void * igDataList_Create(int pool) {
    igDataList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586788), (igMemoryPoolView *)pool));
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

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igDataList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDataList_Register);
}

void *igDataList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        g_igDataList_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igDataList_GetMetaObjectFunction,
        igDataList_className,
        0x14,
        igDataList_GetVTable,
        igDataList_InitFields,
        0,
        0
    );
}

void igDataList_GetMetaObjectFunction(void) {
    igDataList_GetMetaObject();
}

void igDataList_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igDataList_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igDataList_ctorTable[0], 3);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igDataList_fieldTable[0], (igMetaField ***)&g_igDataList_fieldDescriptors[0], &g_igDataList_fieldOffsets[0], base);
}

