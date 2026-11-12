OpTable *FUN_001896e0(int arg0) {
    FUN_001897b0();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561068, arg0);
}

igMetaObject *igExtendByFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001897b0();
    return g_igExtendByFunctionList_metaObject[0];
}

int igExtendByFunctionList_GetVTable(void) {
    Obj8 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00527a90[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001897b0(void)
{
    igMetaObject_RunStaticInit(igExtendByFunctionList_Register);
}

void igExtendByFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByFunctionList_GetMetaObject,
        igExtendByFunctionList_className,
        0x14, /* instance size */
        igExtendByFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByFunctionList_GetMetaObject(void) {
    igExtendByFunctionList_GetMetaObject();
}

