igMetaObject *g_beNDMWItemRevisionPocketBase_metaObject;
igMetaField *g_beNDMWItemRevisionPocketBase_pocketMetaField;

void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemRevisionPocketBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c8e60();
    }
    return g_beNDMWItemRevisionPocketBase_metaObject;
}

void FUN_003c8e60(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionPocketBase_Register);
}

void *beNDMWItemRevisionPocketBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWItemRevisionPocketBase_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemRevisionPocketBase_GetMetaObject,
        "beNDMWItemRevisionPocketBase",
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

static FieldFactory g_beNDMWItemRevisionPocketBase_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemRevisionPocketBase_fieldTable[] = {
    "_pocket",
};
static igMetaField **g_beNDMWItemRevisionPocketBase_fieldHandles[] = {
    &g_beNDMWItemRevisionPocketBase_pocketMetaField,
};
static int g_beNDMWItemRevisionPocketBase_fieldOffsets[] = {
    24,
};

void beNDMWItemRevisionPocketBase_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWItemRevisionPocketBase_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWItemRevisionPocketBase_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWItemRevisionPocketBase_fieldTable, g_beNDMWItemRevisionPocketBase_fieldHandles, g_beNDMWItemRevisionPocketBase_fieldOffsets, temp_s1);
}

