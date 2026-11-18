igMetaObject *g_igDisableExt_metaObject;

igMetaObject *igDisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igDisableExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDisableExt_EnsureRegistered();
    return g_igDisableExt_metaObject;
}

void igDisableExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDisableExt_Register);
}

CallbackArray *igDisableExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igDisableExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        igDisableExt_GetMetaObjectFunction,
        "igDisableExt",
        0x14, /* instance size */
        0,
        igDisableExt_SetAbstractProxy_0014f8a0,   /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igDisableExt_GetMetaObjectFunction(void) {
    igDisableExt_GetMetaObject();
}

