void FUN_002cfe10(int arg0) {
    FUN_002cff30();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586D48), (MemoryPool *)arg0);
}

igMetaObject *FUN_002cfe50(void) {
    if (g_igPsx2IopRpcConnection_metaObject[0] == 0) {
        g_igPsx2IopRpcConnection_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igPsx2IopRpcConnection_metaObject[0];
}

igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IopRpcConnection_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cff30();
    return g_igPsx2IopRpcConnection_metaObject[0];
}

int igPsx2IopRpcConnection_GetVTable(void) {
    union U_2cfef0 u;
    igObject_InitHeader((ObjectHeader *)u.b);
    u.vt = (int)&DAT_0052db30[0];
    return *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
}

void FUN_002cff30(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2IopRpcConnection_Register);
}

void igPsx2IopRpcConnection_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2IopRpcConnection_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPsx2IopRpcConnection_GetMetaObject,
        igPsx2IopRpcConnection_className,
        0x14, /* instance size */
        igPsx2IopRpcConnection_GetVTable,
        &igPsx2IopRpcConnection_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPsx2IopRpcConnection_GetMetaObject(void) {
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

