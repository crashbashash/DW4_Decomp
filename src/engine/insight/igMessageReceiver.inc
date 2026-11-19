igMetaObject *g_igMessageReceiver_metaObject;

igMetaObject *igMessageReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessageReceiver_EnsureRegistered();
    return g_igMessageReceiver_metaObject;
}

void igMessageReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessageReceiver_Register);
}

CallbackArray *igMessageReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igMessageReceiver_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igMessageReceiver_GetMetaObjectFunction,
        "igMessageReceiver",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMessageReceiver_GetMetaObjectFunction(void) {
    igMessageReceiver_GetMetaObject();
}

