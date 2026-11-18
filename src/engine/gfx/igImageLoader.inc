igMetaObject *g_igImageLoader_metaObject;

igMetaObject *igImageLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igImageLoader_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igImageLoader_EnsureRegistered();
    return g_igImageLoader_metaObject;
}

void igImageLoader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igImageLoader_Register);
}

CallbackArray *igImageLoader_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igImageLoader_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        igImageLoader_GetMetaObjectFunction,
        "igImageLoader",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igImageLoader_GetMetaObjectFunction(void) {
    igImageLoader_GetMetaObject();
}

igMetaObject *igImageUtils_GetPublishedMetaObject(void) {
    return g_igImageUtils_metaObject;
}

