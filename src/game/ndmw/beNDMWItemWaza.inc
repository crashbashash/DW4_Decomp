igMetaObject *g_beNDMWItemWaza_metaObject;
igMetaField *g_beNDMWItemWaza_baseNoMetaField;

beNDMWItemWaza *beNDMWItemWaza_Create(int allocator) {
    beNDMWItemWaza_EnsureRegistered();
    return (beNDMWItemWaza *)igMetaObject_CreateInstance(g_beNDMWItemWaza_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWItemWaza_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemWaza_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWItemWaza_EnsureRegistered();
    return g_beNDMWItemWaza_metaObject;
}

int beNDMWItemWaza_GetVTable(void) {
    int obj[8];

    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_beNDMWItemWaza_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)(char *)g_objectSystem + 916));
}

void beNDMWItemWaza_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWaza_Register);
}

CallbackArray *beNDMWItemWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemWaza_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemWaza_GetMetaObject,
        "beNDMWItemWaza",
        0x18, /* instance size */
        beNDMWItemWaza_GetVTable,
        beNDMWItemWaza_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemWaza_GetMetaObject(void)
{
    beNDMWItemWaza_GetReadyMetaObject();
}

igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void) {
    return g_beNDMWItemBase_metaObject;
}

static FieldFactory g_beNDMWItemWaza_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemWaza_fieldTable[] = {
    "_baseNo",
};
static igMetaField **g_beNDMWItemWaza_fieldHandles[] = {
    &g_beNDMWItemWaza_baseNoMetaField,
};
static int g_beNDMWItemWaza_fieldOffsets[] = {
    20,
};

void beNDMWItemWaza_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWItemWaza_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWItemWaza_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWItemWaza_fieldTable, g_beNDMWItemWaza_fieldHandles, g_beNDMWItemWaza_fieldOffsets, base);
}

