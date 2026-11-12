OpTable *FUN_001892c0(int arg0) {
    FUN_00189390();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561050, arg0);
}

igMetaObject *igExtendByRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByRayFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189390();
    return g_igExtendByRayFunctionList_metaObject[0];
}

int igExtendByRayFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527bb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00189390(void)
{
    igMetaObject_RunStaticInit(igExtendByRayFunctionList_Register);
}

void igExtendByRayFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByRayFunctionList_GetMetaObject,
        igExtendByRayFunctionList_className,
        0x14, /* instance size */
        igExtendByRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByRayFunctionList_GetMetaObject(void) {
    igExtendByRayFunctionList_GetMetaObject();
}

