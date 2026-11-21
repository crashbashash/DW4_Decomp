igMetaObject *g_igScissorExt_metaObject;

igMetaObject *igScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igScissorExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igScissorExt_EnsureRegistered();
    return g_igScissorExt_metaObject;
}

void igScissorExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igScissorExt_Register);
}

CallbackArray *igScissorExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igScissorExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        igScissorExt_GetMetaObjectFunction,
        "igScissorExt",
        0x14, /* instance size */
        0,
        igScissorExt_InitFields_0014bdb0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igScissorExt_GetMetaObjectFunction(void) {
    igScissorExt_GetMetaObject();
}

