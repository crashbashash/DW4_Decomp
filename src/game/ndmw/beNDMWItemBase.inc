igMetaObject *g_beNDMWItemBase_metaObject;
igMetaField *g_beNDMWItemBase_kindNoMetaField;
igMetaField *g_beNDMWItemBase_recNoMetaField;
igMetaField *g_beNDMWItemBase_isEquipMetaField;

igMetaObject *beNDMWItemBase_GetOrCreateMetaObject(void) {
    if (g_beNDMWItemBase_metaObject == 0) {
        g_beNDMWItemBase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWItemBase_metaObject;
}

void *beNDMWItemBase_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemBase_EnsureRegistered();
    }
    return g_beNDMWItemBase_metaObject;
}

void beNDMWItemBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBase_Register);
}

CallbackArray *beNDMWItemBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWItemBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWItemBase_GetMetaObject,
        "beNDMWItemBase",
        0x14, /* instance size */
        0,
        beNDMWItemBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemBase_GetMetaObject(void)
{
    beNDMWItemBase_ResolveMetaObject();
}

static FieldFactory g_beNDMWItemBase_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWItemBase_fieldTable[] = {
    "_kindNo",
    "_recNo",
    "_isEquip",
};
static igMetaField **g_beNDMWItemBase_fieldHandles[] = {
    &g_beNDMWItemBase_kindNoMetaField,
    &g_beNDMWItemBase_recNoMetaField,
    &g_beNDMWItemBase_isEquipMetaField,
};
static int g_beNDMWItemBase_fieldOffsets[] = {
    8,
    12,
    16,
};

void beNDMWItemBase_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWItemBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWItemBase_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beNDMWItemBase_fieldTable, g_beNDMWItemBase_fieldHandles, g_beNDMWItemBase_fieldOffsets, base);
}

