igMetaObject *g_igEmptyFunctionList_metaObject;

OpTable *FUN_00188be0(int arg0) {
    igEmptyFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((int)g_igEmptyFunctionList_metaObject, arg0);
}

igMetaObject *igEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igEmptyFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEmptyFunctionList_EnsureRegistered();
    return g_igEmptyFunctionList_metaObject;
}

int igEmptyFunctionList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&g_igEmptyFunctionList_vtable[0];
    off = *(int *)((char *)(g_objectSystem[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igEmptyFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEmptyFunctionList_Register);
}

void igEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igEmptyFunctionList_GetMetaObject,
        "igEmptyFunctionList",
        0x14, /* instance size */
        igEmptyFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEmptyFunctionList_GetMetaObject(void) {
    igEmptyFunctionList_GetMetaObject();
}

