igMetaObject *igImageLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igImageLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014da90();
    return g_igImageLoader_metaObject[0];
}

void FUN_0014da90(void)
{
    igMetaObject_RunStaticInit(igImageLoader_Register);
}

void igImageLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageLoader_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        thunk_igImageLoader_GetMetaObject,
        igImageLoader_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igImageLoader_GetMetaObject(void) {
    igImageLoader_GetMetaObject();
}

int FUN_0014db10(void) {
    return DAT_0055fd68[0];
}

