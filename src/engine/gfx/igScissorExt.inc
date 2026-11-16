igMetaObject *g_igScissorExt_metaObject;

igMetaObject *igScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igScissorExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014bd20();
    return g_igScissorExt_metaObject;
}

void FUN_0014bd20(void)
{
    igMetaObject_RunStaticInit(igScissorExt_Register);
}

CallbackArray *igScissorExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igScissorExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igScissorExt_GetMetaObject,
        "igScissorExt",
        0x14, /* instance size */
        0,
        igScissorExt_InitFields_0014bdb0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igScissorExt_GetMetaObject(void) {
    igScissorExt_GetMetaObject();
}

