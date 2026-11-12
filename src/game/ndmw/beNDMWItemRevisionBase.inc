void *beNDMWItemRevisionBase_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemRevisionBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c8fd0();
    }
    return g_beNDMWItemRevisionBase_metaObject[0];
}

void FUN_003c8fd0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionBase_Register);
}

void *beNDMWItemRevisionBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemRevisionBase_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemRevisionBase_GetMetaObject,
        beNDMWItemRevisionBase_className,
        0x18, /* instance size */
        0,
        beNDMWItemRevisionBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemRevisionBase_GetMetaObject(void)
{
    beNDMWItemRevisionBase_GetReadyMetaObject();
}

void beNDMWItemRevisionBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemRevisionBase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc108[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc110[0], &DAT_004cc118[0], &DAT_004cc120[0], temp_s1);
}

