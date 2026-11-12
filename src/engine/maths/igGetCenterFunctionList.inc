OpTable *FUN_00188920(int arg0) {
    FUN_001889f0();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561018, arg0);
}

igMetaObject *igGetCenterFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igGetCenterFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001889f0();
    return g_igGetCenterFunctionList_metaObject[0];
}

int igGetCenterFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527e50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001889f0(void)
{
    igMetaObject_RunStaticInit(igGetCenterFunctionList_Register);
}

void igGetCenterFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGetCenterFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igGetCenterFunctionList_GetMetaObject,
        igGetCenterFunctionList_className,
        0x14, /* instance size */
        igGetCenterFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGetCenterFunctionList_GetMetaObject(void) {
    igGetCenterFunctionList_GetMetaObject();
}

