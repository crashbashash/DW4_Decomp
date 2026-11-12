OpTable *FUN_00189160(int arg0) {
    FUN_00189230();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561048, arg0);
}

igMetaObject *igContainsRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsRayFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189230();
    return g_igContainsRayFunctionList_metaObject[0];
}

int igContainsRayFunctionList_GetVTable(void) {
    union U4 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527c10[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_00189230(void)
{
    igMetaObject_RunStaticInit(igContainsRayFunctionList_Register);
}

void igContainsRayFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContainsRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsRayFunctionList_GetMetaObject,
        igContainsRayFunctionList_className,
        0x14, /* instance size */
        igContainsRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igContainsRayFunctionList_GetMetaObject(void) {
    igContainsRayFunctionList_GetMetaObject();
}

