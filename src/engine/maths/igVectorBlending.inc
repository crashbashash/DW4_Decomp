igMetaObject *g_igVectorBlending_metaObject;

igMetaObject *igVectorBlending_GetMetaObject(void)
{
    igMetaObject *meta = g_igVectorBlending_metaObject;
    if (!meta || ((meta->_validity & 4) != 0) == false)
        igVectorBlending_EnsureRegistered();
    return g_igVectorBlending_metaObject;
}

int igVectorBlending_GetVTable(void) {
    struct Obj3 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVectorBlending_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVectorBlending_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVectorBlending_Register);
}

CallbackArray *igVectorBlending_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVectorBlending_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        (igMetaObjectCallback)thunk_igVectorBlending_GetMetaObject_00186ff0,
        "igVectorBlending",
        8, /* instance size */
        igVectorBlending_GetVTable,
        0,
        igVectorBlending_StaticInitCallback, /* static-initializer callback item (appended on fresh configuration) */
        0                                    /* 0-terminated dependency-callback list */
    );
}

void igVectorBlending_GetMetaObjectFunction(void) {
    igVectorBlending_GetMetaObject();
}

void igVectorBlending_StaticInitCallback(void) {
    igVectorBlending_InstallFunctions();
}

