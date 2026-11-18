igMetaObject *g_igExtendByVecFunctionList_metaObject;

OpTable *FUN_00189000(int arg0) {
    igExtendByVecFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igExtendByVecFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igExtendByVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByVecFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExtendByVecFunctionList_EnsureRegistered();
    return g_igExtendByVecFunctionList_metaObject;
}

int igExtendByVecFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igExtendByVecFunctionList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igExtendByVecFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExtendByVecFunctionList_Register);
}

CallbackArray *igExtendByVecFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igExtendByVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByVecFunctionList_GetMetaObject,
        "igExtendByVecFunctionList",
        0x14, /* instance size */
        igExtendByVecFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByVecFunctionList_GetMetaObject(void) {
    igExtendByVecFunctionList_GetMetaObject();
}

