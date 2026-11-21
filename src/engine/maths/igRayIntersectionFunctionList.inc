igMetaObject *g_igRayIntersectionFunctionList_metaObject;

OpTable *FUN_00189420(int arg0) {
    igRayIntersectionFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igRayIntersectionFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igRayIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayIntersectionFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRayIntersectionFunctionList_EnsureRegistered();
    return g_igRayIntersectionFunctionList_metaObject;
}

int igRayIntersectionFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRayIntersectionFunctionList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igRayIntersectionFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRayIntersectionFunctionList_Register);
}

CallbackArray *igRayIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRayIntersectionFunctionList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igRayIntersectionFunctionList_GetMetaObjectFunction,
        "igRayIntersectionFunctionList",
        0x14, /* instance size */
        igRayIntersectionFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igRayIntersectionFunctionList_GetMetaObjectFunction(void) {
    igRayIntersectionFunctionList_GetMetaObject();
}

