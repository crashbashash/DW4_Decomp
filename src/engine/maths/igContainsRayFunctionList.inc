igMetaObject *g_igContainsRayFunctionList_metaObject;

OpTable *FUN_00189160(int arg0) {
    igContainsRayFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igContainsRayFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igContainsRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsRayFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContainsRayFunctionList_EnsureRegistered();
    return g_igContainsRayFunctionList_metaObject;
}

int igContainsRayFunctionList_GetVTable(void) {
    union U4 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igContainsRayFunctionList_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igContainsRayFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContainsRayFunctionList_Register);
}

CallbackArray *igContainsRayFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igContainsRayFunctionList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igContainsRayFunctionList_GetMetaObjectFunction,
        "igContainsRayFunctionList",
        0x14, /* instance size */
        igContainsRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igContainsRayFunctionList_GetMetaObjectFunction(void) {
    igContainsRayFunctionList_GetMetaObject();
}

