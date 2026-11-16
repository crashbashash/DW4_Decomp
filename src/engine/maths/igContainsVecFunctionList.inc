igMetaObject *g_igContainsVecFunctionList_metaObject;

OpTable *FUN_00188ea0(int arg0) {
    igContainsVecFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igContainsVecFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igContainsVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsVecFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContainsVecFunctionList_EnsureRegistered();
    return g_igContainsVecFunctionList_metaObject;
}

int igContainsVecFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igContainsVecFunctionList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igContainsVecFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContainsVecFunctionList_Register);
}

CallbackArray *igContainsVecFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igContainsVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsVecFunctionList_GetMetaObject,
        "igContainsVecFunctionList",
        0x14, /* instance size */
        igContainsVecFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igContainsVecFunctionList_GetMetaObject(void) {
    igContainsVecFunctionList_GetMetaObject();
}

