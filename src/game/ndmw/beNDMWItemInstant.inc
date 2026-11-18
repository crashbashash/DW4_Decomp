igMetaObject *g_beNDMWItemInstant_metaObject;
igMetaField *g_beNDMWItemInstant_valueMetaField;

beNDMWItemInstant *beNDMWItemInstant_Create(int allocator) {
    beNDMWItemInstant_EnsureRegistered();
    return (beNDMWItemInstant *)igMetaObject_CreateInstance(g_beNDMWItemInstant_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWItemInstant_GetReadyMetaObject(void) {
    if (g_beNDMWItemInstant_metaObject == 0 || !isValid(g_beNDMWItemInstant_metaObject)) beNDMWItemInstant_EnsureRegistered();
    return g_beNDMWItemInstant_metaObject;
}

int beNDMWItemInstant_GetVTable(void) {
    beNDMWItemInstant obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemInstant_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWItemInstant_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemInstant_Register);
}

CallbackArray *beNDMWItemInstant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemInstant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemInstant_GetMetaObject,
        "beNDMWItemInstant",
        0x18, /* instance size */
        beNDMWItemInstant_GetVTable,
        beNDMWItemInstant_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemInstant_GetMetaObject(void)
{
    beNDMWItemInstant_GetReadyMetaObject();
}

static FieldFactory g_beNDMWItemInstant_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemInstant_fieldTable[] = {
    "_value",
};
static igMetaField **g_beNDMWItemInstant_fieldHandles[] = {
    &g_beNDMWItemInstant_valueMetaField,
};
static int g_beNDMWItemInstant_fieldOffsets[] = {
    20,
};

void beNDMWItemInstant_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWItemInstant_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWItemInstant_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWItemInstant_fieldTable, g_beNDMWItemInstant_fieldHandles, g_beNDMWItemInstant_fieldOffsets, base);
}

