OpTable *FUN_00188be0(int arg0) {
    FUN_00188cb0();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561028, arg0);
}

igMetaObject *igEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igEmptyFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188cb0();
    return g_igEmptyFunctionList_metaObject[0];
}

int igEmptyFunctionList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00527d90[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00188cb0(void)
{
    igMetaObject_RunStaticInit(igEmptyFunctionList_Register);
}

void igEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igEmptyFunctionList_GetMetaObject,
        igEmptyFunctionList_className,
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

