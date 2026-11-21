igMetaObject *g_igCustomState_metaObject;

igMetaObject *igCustomState_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCustomState_EnsureRegistered();
    return g_igCustomState_metaObject;
}

void igCustomState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCustomState_Register);
}

CallbackArray *igCustomState_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igCustomState_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igCustomState_GetMetaObjectFunction,
        "igCustomState",
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCustomState_GetMetaObjectFunction(void) {
    igCustomState_GetMetaObject();
}

