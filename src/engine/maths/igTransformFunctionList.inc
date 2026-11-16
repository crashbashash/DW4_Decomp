igMetaObject *g_igTransformFunctionList_metaObject;

OpTable *FUN_00188d40(int arg0) {
    igTransformFunctionList_EnsureRegistered();
    return (OpTable *)igMetaObject_CreateInstance((igMetaObject *)g_igTransformFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igTransformFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformFunctionList_EnsureRegistered();
    return g_igTransformFunctionList_metaObject;
}

int igTransformFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTransformFunctionList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igTransformFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformFunctionList_Register);
}

CallbackArray *igTransformFunctionList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTransformFunctionList_GetMetaObject,
        "igTransformFunctionList",
        0x14, /* instance size */
        igTransformFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTransformFunctionList_GetMetaObject(void) {
    igTransformFunctionList_GetMetaObject();
}

