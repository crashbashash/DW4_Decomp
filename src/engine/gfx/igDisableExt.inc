igMetaObject *igDisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igDisableExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f810();
    return g_igDisableExt_metaObject[0];
}

void FUN_0014f810(void)
{
    igMetaObject_RunStaticInit(igDisableExt_Register);
}

void igDisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDisableExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igDisableExt_GetMetaObject,
        igDisableExt_className,
        0x14, /* instance size */
        0,
        &igDisableExt_SetAbstractProxy_0014f8a0[0],   /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDisableExt_GetMetaObject(void) {
    igDisableExt_GetMetaObject();
}

