igMetaObject *igFileImage_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014def0();
    return g_igFileImage_metaObject[0];
}

void FUN_0014def0(void)
{
    igMetaObject_RunStaticInit(igFileImage_Register);
}

void igFileImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFileImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        thunk_igFileImage_GetMetaObject,
        igFileImage_className,
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFileImage_GetMetaObject(void) {
    igFileImage_GetMetaObject();
}

