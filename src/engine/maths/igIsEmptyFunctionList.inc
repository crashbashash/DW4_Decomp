igMetaObject *g_igIsEmptyFunctionList_metaObject;

OpTable *FUN_00188a80(int arg0) {
    igIsEmptyFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igIsEmptyFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igIsEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIsEmptyFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIsEmptyFunctionList_EnsureRegistered();
    return g_igIsEmptyFunctionList_metaObject;
}

int igIsEmptyFunctionList_GetVTable(void) {
    union U3 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igIsEmptyFunctionList_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igIsEmptyFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIsEmptyFunctionList_Register);
}

CallbackArray *igIsEmptyFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIsEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIsEmptyFunctionList_GetMetaObject,
        "igIsEmptyFunctionList",
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

