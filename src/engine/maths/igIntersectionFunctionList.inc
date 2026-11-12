OpTable *FUN_00189840(int arg0) {
    FUN_00189910();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561070, arg0);
}

igMetaObject *igIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectionFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189910();
    return g_igIntersectionFunctionList_metaObject[0];
}

int igIntersectionFunctionList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00527a30[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00189910(void)
{
    igMetaObject_RunStaticInit(igIntersectionFunctionList_Register);
}

void igIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntersectionFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIntersectionFunctionList_GetMetaObject,
        igIntersectionFunctionList_className,
        0x14, /* instance size */
        igIntersectionFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIntersectionFunctionList_GetMetaObject(void) {
    igIntersectionFunctionList_GetMetaObject();
}

