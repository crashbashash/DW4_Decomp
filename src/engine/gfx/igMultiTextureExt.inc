igMetaObject *g_igMultiTextureExt_metaObject;

igMetaObject *igMultiTextureExt_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiTextureExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014d5c0();
    return g_igMultiTextureExt_metaObject;
}

void FUN_0014d5c0(void)
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
        thunk_igMultiTextureExt_GetMetaObject,
        "igMultiTextureExt",
        0x14, /* instance size */
        0,
        igMultiTextureExt_InitFields_0014d650,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMultiTextureExt_GetMetaObject(void) {
    igMultiTextureExt_GetMetaObject();
}

