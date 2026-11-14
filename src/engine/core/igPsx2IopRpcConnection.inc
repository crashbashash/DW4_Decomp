void igPsx2IopRpcConnection_Create(int arg0) {
    igPsx2IopRpcConnection_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586D48), (igMemoryPoolView *)arg0);
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
    connection._vtable = (int)&DAT_0052db30[0];
    return *(int *)((char *)&connection + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPsx2IopRpcConnection_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2IopRpcConnection_Register);
}

void igPsx2IopRpcConnection_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2IopRpcConnection_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igPsx2IopRpcConnection_GetMetaObjectFunction,
        igPsx2IopRpcConnection_className,
        0x14, /* instance size */
        igPsx2IopRpcConnection_GetVTable,
        &igPsx2IopRpcConnection_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPsx2IopRpcConnection_GetMetaObjectFunction(void) {
    igPsx2IopRpcConnection_GetMetaObject();
}

void igPsx2IopRpcConnection_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2IopRpcConnection_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igPsx2IopRpcConnection_ctorTable[0], 3);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igPsx2IopRpcConnection_fieldTable[0], (igMetaField ***)&DAT_004c1df0[0], &DAT_004c1e00[0], temp_s1);
}

