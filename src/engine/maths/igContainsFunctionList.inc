OpTable *FUN_00189580(int arg0) {
    FUN_00189650();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561060, arg0);
}

igMetaObject *igContainsFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189650();
    return g_igContainsFunctionList_metaObject[0];
}

int igContainsFunctionList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00527af0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_00189650(void)
{
    igMetaObject_RunStaticInit(igContainsFunctionList_Register);
}

void igContainsFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContainsFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsFunctionList_GetMetaObject,
        igContainsFunctionList_className,
        0x14, /* instance size */
        igContainsFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igContainsFunctionList_GetMetaObject(void) {
    igContainsFunctionList_GetMetaObject();
}

