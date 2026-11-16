igMetaObject *g_igContainsRayFunctionList_metaObject;

OpTable *FUN_00189160(int arg0) {
    igContainsRayFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((int)g_igContainsRayFunctionList_metaObject, arg0);
}

igMetaObject *igContainsRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsRayFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContainsRayFunctionList_EnsureRegistered();
    return g_igContainsRayFunctionList_metaObject;
}

int igContainsRayFunctionList_GetVTable(void) {
    union U4 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igContainsRayFunctionList_vtable[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void igContainsRayFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContainsRayFunctionList_Register);
}

void igContainsRayFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igContainsRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsRayFunctionList_GetMetaObject,
        "igContainsRayFunctionList",
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

