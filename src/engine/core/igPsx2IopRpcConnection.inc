void igPsx2IopRpcConnection_Create(int pool) {
    igPsx2IopRpcConnection_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586D48), (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2IopRpcConnection_GetOrCreateMetaObject(void) {
    if (g_igPsx2IopRpcConnection_metaObject[0] == 0) {
        g_igPsx2IopRpcConnection_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPsx2IopRpcConnection_metaObject[0];
}

igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IopRpcConnection_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2IopRpcConnection_EnsureRegistered();
    return g_igPsx2IopRpcConnection_metaObject[0];
}

int igPsx2IopRpcConnection_GetVTable(void) {
    igPsx2IopRpcConnection connection;
    igObject_InitHeader((igObject *)&connection);
    connection._vtable = (int)&g_igPsx2IopRpcConnection_vtable[0];
    return *(int *)((char *)&connection + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPsx2IopRpcConnection_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2IopRpcConnection_Register);
}

void igPsx2IopRpcConnection_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPsx2IopRpcConnection_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igPsx2IopRpcConnection_GetMetaObjectFunction,
        igPsx2IopRpcConnection_className,
        0x14,
        igPsx2IopRpcConnection_GetVTable,
        igPsx2IopRpcConnection_InitFields,
        0,
        0
    );
}

void igPsx2IopRpcConnection_GetMetaObjectFunction(void) {
    igPsx2IopRpcConnection_GetMetaObject();
}

void igPsx2IopRpcConnection_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igPsx2IopRpcConnection_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igPsx2IopRpcConnection_ctorTable[0], 3);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igPsx2IopRpcConnection_fieldTable[0], (igMetaField ***)&g_igPsx2IopRpcConnection_fieldDescriptors[0], &g_igPsx2IopRpcConnection_fieldOffsets[0], first);
}

