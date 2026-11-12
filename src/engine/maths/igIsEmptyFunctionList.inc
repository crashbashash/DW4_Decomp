OpTable *FUN_00188a80(int arg0) {
    FUN_00188b50();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561020, arg0);
}

igMetaObject *igIsEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIsEmptyFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188b50();
    return g_igIsEmptyFunctionList_metaObject[0];
}

int igIsEmptyFunctionList_GetVTable(void) {
    union U3 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00527df0[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_00188b50(void)
{
    igMetaObject_RunStaticInit(igIsEmptyFunctionList_Register);
}

void igIsEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIsEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIsEmptyFunctionList_GetMetaObject,
        igIsEmptyFunctionList_className,
        0x14, /* instance size */
        igIsEmptyFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIsEmptyFunctionList_GetMetaObject(void) {
    igIsEmptyFunctionList_GetMetaObject();
}

