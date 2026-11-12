OpTable *FUN_00189420(int arg0) {
    FUN_001894f0();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561058, arg0);
}

igMetaObject *igRayIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayIntersectionFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001894f0();
    return g_igRayIntersectionFunctionList_metaObject[0];
}

int igRayIntersectionFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527b50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001894f0(void)
{
    igMetaObject_RunStaticInit(igRayIntersectionFunctionList_Register);
}

void igRayIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRayIntersectionFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igRayIntersectionFunctionList_GetMetaObject,
        igRayIntersectionFunctionList_className,
        0x14, /* instance size */
        igRayIntersectionFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRayIntersectionFunctionList_GetMetaObject(void) {
    igRayIntersectionFunctionList_GetMetaObject();
}

