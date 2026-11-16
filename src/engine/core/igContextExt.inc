igMetaObject *g_igContextExt_metaObject;

igMetaObject *igContextExt_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExt_EnsureRegistered();
    return g_igContextExt_metaObject;
}

void igContextExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContextExt_Register);
}

CallbackArray *igContextExt_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igContextExt_metaObject,
        igContext_Register,
        (igMetaObjectGetFunction)igContext_GetPublishedMetaObject,
        igContextExt_GetMetaObjectFunction,
        "igContextExt",
        0x14,
        0,
        0,
        0,
        0
    );
}

void igContextExt_GetMetaObjectFunction(void) {
    igContextExt_GetMetaObject();
}

