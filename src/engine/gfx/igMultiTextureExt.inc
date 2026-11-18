igMetaObject *g_igMultiTextureExt_metaObject;

igMetaObject *igMultiTextureExt_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiTextureExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMultiTextureExt_EnsureRegistered();
    return g_igMultiTextureExt_metaObject;
}

void igMultiTextureExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMultiTextureExt_Register);
}

CallbackArray *igMultiTextureExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igMultiTextureExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        igMultiTextureExt_GetMetaObjectFunction,
        "igMultiTextureExt",
        0x14, /* instance size */
        0,
        igMultiTextureExt_InitFields_0014d650,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMultiTextureExt_GetMetaObjectFunction(void) {
    igMultiTextureExt_GetMetaObject();
}

