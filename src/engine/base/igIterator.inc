igMetaObject *g_igIterator_metaObject;

igMetaObject *igIterator_GetMetaObject(void)
{
    igMetaObject *g = g_igIterator_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002273d0();
    return g_igIterator_metaObject;
}

void FUN_002273d0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igIterator_Register);
}

CallbackArray *igIterator_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igIterator_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igIterator_GetMetaObjectFunction,
        "igIterator",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igIterator_GetMetaObjectFunction(void) {
    igIterator_GetMetaObject();
}

igMetaObject *igIterator_GetPublishedMetaObject(void) {
    return g_igIterator_metaObject;
}

