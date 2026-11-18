igMetaObject *g_igMemoryImage_metaObject;

igMetaObject *igMemoryImage_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryImage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryImage_EnsureRegistered();
    return g_igMemoryImage_metaObject;
}

void igMemoryImage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryImage_Register);
}

CallbackArray *igMemoryImage_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igMemoryImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        igMemoryImage_GetMetaObjectFunction,
        "igMemoryImage",
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMemoryImage_GetMetaObjectFunction(void) {
    igMemoryImage_GetMetaObject();
}

igMetaObject *FUN_0014de90(void) {
    return g_igImage_metaObject;
}

