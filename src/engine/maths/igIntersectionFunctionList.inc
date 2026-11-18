igMetaObject *g_igIntersectionFunctionList_metaObject;

OpTable *FUN_00189840(int arg0) {
    igIntersectionFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igIntersectionFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectionFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntersectionFunctionList_EnsureRegistered();
    return g_igIntersectionFunctionList_metaObject;
}

int igIntersectionFunctionList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igIntersectionFunctionList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igIntersectionFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntersectionFunctionList_Register);
}

CallbackArray *igIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIntersectionFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIntersectionFunctionList_GetMetaObject,
        "igIntersectionFunctionList",
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

