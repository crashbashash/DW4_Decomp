igMetaObject *g_igExtendByFunctionList_metaObject;

OpTable *FUN_001896e0(int arg0) {
    igExtendByFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igExtendByFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igExtendByFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExtendByFunctionList_EnsureRegistered();
    return g_igExtendByFunctionList_metaObject;
}

int igExtendByFunctionList_GetVTable(void) {
    Obj8 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igExtendByFunctionList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igExtendByFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExtendByFunctionList_Register);
}

CallbackArray *igExtendByFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igExtendByFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByFunctionList_GetMetaObject,
        "igExtendByFunctionList",
        0x14, /* instance size */
        igExtendByFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igExtendByFunctionList_GetMetaObject(void) {
    igExtendByFunctionList_GetMetaObject();
}

