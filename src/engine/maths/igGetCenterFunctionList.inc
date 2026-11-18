igMetaObject *g_igGetCenterFunctionList_metaObject;

OpTable *FUN_00188920(int arg0) {
    igGetCenterFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igGetCenterFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igGetCenterFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igGetCenterFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGetCenterFunctionList_EnsureRegistered();
    return g_igGetCenterFunctionList_metaObject;
}

int igGetCenterFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGetCenterFunctionList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igGetCenterFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGetCenterFunctionList_Register);
}

CallbackArray *igGetCenterFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGetCenterFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igGetCenterFunctionList_GetMetaObject,
        "igGetCenterFunctionList",
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

