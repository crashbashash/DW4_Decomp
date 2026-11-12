OpTable *FUN_00188ea0(int arg0) {
    FUN_00188f70();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561038, arg0);
}

igMetaObject *igContainsVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsVecFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188f70();
    return g_igContainsVecFunctionList_metaObject[0];
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
        g_igContainsVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsVecFunctionList_GetMetaObject,
        igContainsVecFunctionList_className,
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

