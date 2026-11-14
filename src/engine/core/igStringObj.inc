void * igStringObj_Create(int pool) {
    igStringObj_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858F0), (igMemoryPoolView *)pool));
}

igMetaObject *igStringObj_GetOrCreateMetaObject(void) {
    if (g_igStringObj_metaObject[0] == 0) {
        g_igStringObj_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringObj_metaObject[0];
}

igMetaObject *igStringObj_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObj_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringObj_EnsureRegistered();
    return g_igStringObj_metaObject[0];
}

int igStringObj_GetVTable(void) {
    igStringObj string;

    igObject_InitHeader((igObject *)&string);
    string._vtable = (int)(&g_igStringObj_vtable[0]);
    return *(int *)((char *)&string + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igStringObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringObj_Register);
}

void igStringObj_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringObj_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igStringObj_GetMetaObjectFunction,
        igStringObj_className,
        0x10,
        igStringObj_GetVTable,
        igStringObj_InitFields,
        0,
        0
    );
}

void igStringObj_GetMetaObjectFunction(void) {
    igStringObj_GetMetaObject();
}

void igStringObj_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g_igStringObj_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igStringObj_ctorTable[0], 2);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igStringObj_fieldTable[0], (igMetaField ***)&g_igStringObj_fieldDescriptors[0], &g_igStringObj_fieldOffsets[0], first);
}

