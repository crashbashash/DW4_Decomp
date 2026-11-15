igMetaObject *g_beNDMWItemRevisionBase_metaObject;
igMetaField *g_beNDMWItemRevisionBase_revisionMetaField;

void *beNDMWItemRevisionBase_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemRevisionBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c8fd0();
    }
    return g_beNDMWItemRevisionBase_metaObject;
}

void FUN_003c8fd0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionBase_Register);
}

void *beNDMWItemRevisionBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWItemRevisionBase_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemRevisionBase_GetMetaObject,
        "beNDMWItemRevisionBase",
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

static FieldFactory g_beNDMWItemRevisionBase_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemRevisionBase_fieldTable[] = {
    "_revision",
};
static igMetaField **g_beNDMWItemRevisionBase_fieldHandles[] = {
    &g_beNDMWItemRevisionBase_revisionMetaField,
};
static int g_beNDMWItemRevisionBase_fieldOffsets[] = {
    20,
};

void beNDMWItemRevisionBase_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWItemRevisionBase_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWItemRevisionBase_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWItemRevisionBase_fieldTable, g_beNDMWItemRevisionBase_fieldHandles, g_beNDMWItemRevisionBase_fieldOffsets, temp_s1);
}

