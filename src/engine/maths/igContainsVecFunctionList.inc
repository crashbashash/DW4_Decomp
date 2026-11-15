igMetaObject *g_igContainsVecFunctionList_metaObject;

OpTable *FUN_00188ea0(int arg0) {
    FUN_00188f70();
    return (OpTable *)igMetaObject_CreateInstance((int)g_igContainsVecFunctionList_metaObject, arg0);
}

igMetaObject *igContainsVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsVecFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188f70();
    return g_igContainsVecFunctionList_metaObject;
}

int igContainsVecFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527cd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00188f70(void)
{
    igMetaObject_RunStaticInit(igContainsVecFunctionList_Register);
}

void igContainsVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
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

