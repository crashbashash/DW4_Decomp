igMetaObject *g_beNDMWItemRevisionPocketBase_metaObject;
igMetaField *g_beNDMWItemRevisionPocketBase_pocketMetaField;

void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemRevisionPocketBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemRevisionPocketBase_EnsureRegistered();
    }
    return g_beNDMWItemRevisionPocketBase_metaObject;
}

void beNDMWItemRevisionPocketBase_EnsureRegistered(void)
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
    int base;
    igMetaObject *meta;

    meta = g_beNDMWItemRevisionPocketBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWItemRevisionPocketBase_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWItemRevisionPocketBase_fieldTable, g_beNDMWItemRevisionPocketBase_fieldHandles, g_beNDMWItemRevisionPocketBase_fieldOffsets, base);
}

