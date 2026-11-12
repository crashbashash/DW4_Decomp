void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemRevisionPocketBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c8e60();
    }
    return g_beNDMWItemRevisionPocketBase_metaObject[0];
}

void FUN_003c8e60(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionPocketBase_Register);
}

void *beNDMWItemRevisionPocketBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemRevisionPocketBase_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemRevisionPocketBase_GetMetaObject,
        beNDMWItemRevisionPocketBase_className,
        0x1c, /* instance size */
        0,
        beNDMWItemRevisionPocketBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemRevisionPocketBase_GetMetaObject(void)
{
    beNDMWItemRevisionPocketBase_GetReadyMetaObject();
}

void beNDMWItemRevisionPocketBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemRevisionPocketBase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc0e8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc0f0[0], &DAT_004cc0f8[0], &DAT_004cc100[0], temp_s1);
}

