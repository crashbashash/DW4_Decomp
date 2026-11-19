int FUN_00198b60(int arg0) {
    igShaderProcessor_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igShaderProcessor_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igShaderProcessor_metaObject;

igMetaObject *igShaderProcessor_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderProcessor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShaderProcessor_EnsureRegistered();
    return g_igShaderProcessor_metaObject;
}

int igShaderProcessor_GetVTable(void) {
    struct Obj_198bf0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igShaderProcessor_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igShaderProcessor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShaderProcessor_Register);
}

CallbackArray *igShaderProcessor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShaderProcessor_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igShaderProcessor_GetMetaObjectFunction,
        "igShaderProcessor",
        8, /* instance size */
        igShaderProcessor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igShaderProcessor_GetMetaObjectFunction(void) {
    igShaderProcessor_GetMetaObject();
}

