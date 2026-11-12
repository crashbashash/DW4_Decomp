igMetaObject *igMemoryImage_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryImage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014de10();
    return g_igMemoryImage_metaObject[0];
}

void FUN_0014de10(void)
{
    igMetaObject_RunStaticInit(igMemoryImage_Register);
}

void igMemoryImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMemoryImage_metaObject,
        igImage_Register,
        igImage_GetPublishedMetaObject,
        thunk_igMemoryImage_GetMetaObject,
        igMemoryImage_className,
        0x5C, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryImage_GetMetaObject(void) {
    igMemoryImage_GetMetaObject();
}

igMetaObject *FUN_0014de90(void) {
    return g_igImage_metaObject[0];
}

