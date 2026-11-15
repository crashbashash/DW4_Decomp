igMetaObject *g_igItemBase_metaObject;

igMetaObject *igItemBase_GetMetaObject(void)
{
    igMetaObject *g = g_igItemBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228950();
    return g_igItemBase_metaObject;
}

void FUN_00228950(void)
{
    igMetaObject_RunStaticInit(igItemBase_Register);
}

void igItemBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igItemBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igItemBase_GetMetaObject,
        "igItemBase",
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

