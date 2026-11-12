igMetaObject *igItemBase_GetMetaObject(void)
{
    igMetaObject *g = g_igItemBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228950();
    return g_igItemBase_metaObject[0];
}

void FUN_00228950(void)
{
    igMetaObject_RunStaticInit(igItemBase_Register);
}

void igItemBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igItemBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igItemBase_GetMetaObject,
        igItemBase_className,
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igItemBase_GetMetaObject(void) {
    igItemBase_GetMetaObject();
}

