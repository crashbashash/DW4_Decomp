int FUN_0014db20(int arg0) {
    FUN_0014dbb0();
    return igMetaObject_CreateInstance(*(int *)0x55FD60, arg0);
}

igMetaObject *igImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igImageConvert_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014dbb0();
    return g_igImageConvert_metaObject[0];
}

void FUN_0014dbb0(void)
{
    igMetaObject_RunStaticInit(igImageConvert_Register);
}

void igImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageConvert_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        thunk_igImageConvert_GetMetaObject,
        igImageConvert_className,
        8, /* instance size */
        0,
        &igImageConvert_SetAbstractProxy_0014dc40[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igImageConvert_GetMetaObject(void) {
    igImageConvert_GetMetaObject();
}

