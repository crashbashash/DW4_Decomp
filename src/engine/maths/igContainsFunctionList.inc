igMetaObject *g_igContainsFunctionList_metaObject;

OpTable *FUN_00189580(int arg0) {
    igContainsFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((int)g_igContainsFunctionList_metaObject, arg0);
}

igMetaObject *igContainsFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContainsFunctionList_EnsureRegistered();
    return g_igContainsFunctionList_metaObject;
}

int igContainsFunctionList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&g_igContainsFunctionList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void igContainsFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContainsFunctionList_Register);
}

void igContainsFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igContainsFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsFunctionList_GetMetaObject,
        "igContainsFunctionList",
        0x14, /* instance size */
        igContainsFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igContainsFunctionList_GetMetaObject(void) {
    igContainsFunctionList_GetMetaObject();
}

