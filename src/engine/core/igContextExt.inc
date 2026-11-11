igMetaObject *igContextExt_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb980();
    return g_igContextExt_metaObject[0];
}

void FUN_002cb980(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExt_Register);
}

void igContextExt_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igContextExt_metaObject),
        igContext_Register,
        igContext_GetPublishedMetaObject,
        thunk_igContextExt_GetMetaObject,
        igContextExt_className,
        0x14, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igContextExt_GetMetaObject(void) {
    igContextExt_GetMetaObject();
}

