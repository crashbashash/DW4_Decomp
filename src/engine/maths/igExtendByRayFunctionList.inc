igMetaObject *g_igExtendByRayFunctionList_metaObject;

OpTable *FUN_001892c0(int arg0) {
    igExtendByRayFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igExtendByRayFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igExtendByRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByRayFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExtendByRayFunctionList_EnsureRegistered();
    return g_igExtendByRayFunctionList_metaObject;
}

int igExtendByRayFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igExtendByRayFunctionList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igExtendByRayFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExtendByRayFunctionList_Register);
}

CallbackArray *igExtendByRayFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igExtendByRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByRayFunctionList_GetMetaObject,
        "igExtendByRayFunctionList",
        0x14, /* instance size */
        igExtendByRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByRayFunctionList_GetMetaObject(void) {
    igExtendByRayFunctionList_GetMetaObject();
}

