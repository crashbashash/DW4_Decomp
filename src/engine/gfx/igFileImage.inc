igMetaObject *g_igFileImage_metaObject;

igMetaObject *igFileImage_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014def0();
    return g_igFileImage_metaObject;
}

void FUN_0014def0(void)
{
    igMetaObject_RunStaticInit(igFileImage_Register);
}

CallbackArray *igFileImage_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igFileImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        thunk_igFileImage_GetMetaObject,
        "igFileImage",
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

