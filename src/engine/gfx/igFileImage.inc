igMetaObject *g_igFileImage_metaObject;

igMetaObject *igFileImage_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFileImage_EnsureRegistered();
    return g_igFileImage_metaObject;
}

void igFileImage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFileImage_Register);
}

CallbackArray *igFileImage_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igFileImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        igFileImage_GetMetaObjectFunction,
        "igFileImage",
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igFileImage_GetMetaObjectFunction(void) {
    igFileImage_GetMetaObject();
}

