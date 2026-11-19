igMetaObject *g_igVectorMorphing_metaObject;

igMetaObject *igVectorMorphing_GetMetaObject(void)
{
    igMetaObject *meta = g_igVectorMorphing_metaObject;
    if (!meta || ((meta->_validity & 4) != 0) == false)
        igVectorMorphing_EnsureRegistered();
    return g_igVectorMorphing_metaObject;
}

int igVectorMorphing_GetVTable(void) {
    struct Obj2 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVectorMorphing_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVectorMorphing_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVectorMorphing_Register);
}

CallbackArray *igVectorMorphing_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVectorMorphing_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        (igMetaObjectCallback)thunk_igVectorMorphing_GetMetaObject_00186ec0,
        "igVectorMorphing",
        8, /* instance size */
        igVectorMorphing_GetVTable,
        0,
        igVectorMorphing_StaticInitCallback, /* static-initializer callback item (appended on fresh configuration) */
        0                                    /* 0-terminated dependency-callback list */
    );
}

void igVectorMorphing_GetMetaObjectFunction(void) {
    igVectorMorphing_GetMetaObject();
}

void igVectorMorphing_StaticInitCallback(void) {
    igVectorMorphing_InstallFunctions();
}

