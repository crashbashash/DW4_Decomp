OpTable *FUN_00189000(int arg0) {
    FUN_001890d0();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561040, arg0);
}

igMetaObject *igExtendByVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByVecFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001890d0();
    return g_igExtendByVecFunctionList_metaObject[0];
}

int igExtendByVecFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527c70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001890d0(void)
{
    igMetaObject_RunStaticInit(igExtendByVecFunctionList_Register);
}

void igExtendByVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByVecFunctionList_GetMetaObject,
        igExtendByVecFunctionList_className,
        0x14, /* instance size */
        igExtendByVecFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByVecFunctionList_GetMetaObject(void) {
    igExtendByVecFunctionList_GetMetaObject();
}

