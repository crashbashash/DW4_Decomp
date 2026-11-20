igMetaObject *g_beSvPs2McImage128k_metaObject;
igMetaField *g_beSvPs2McImage128k_dataSizeMetaField;
igMetaField *g_beSvPs2McImage128k_dataMetaField;

void *beSvPs2McImage128k_GetMetaObject(void) {
    igMetaObject *g = g_beSvPs2McImage128k_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPs2McImage128k_EnsureRegistered();
    }
    return g_beSvPs2McImage128k_metaObject;
}

int beSvPs2McImage128k_GetVTable(void) {
    beSvPs2McImage128k obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvPs2McImage128k_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beSvPs2McImage128k_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPs2McImage128k_Register);
}

CallbackArray *beSvPs2McImage128k_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPs2McImage128k_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beSvPs2McImage128k_GetMetaObjectFunction,
        "beSvPs2McImage128k",
        0x10, /* instance size */
        beSvPs2McImage128k_GetVTable,
        beSvPs2McImage128k_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPs2McImage128k_GetMetaObjectFunction(void)
{
    beSvPs2McImage128k_GetMetaObject();
}

static FieldFactory g_beSvPs2McImage128k_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beSvPs2McImage128k_fieldTable[] = {
    "_dataSize",
    "_data",
};
static igMetaField **g_beSvPs2McImage128k_fieldHandles[] = {
    &g_beSvPs2McImage128k_dataSizeMetaField,
    &g_beSvPs2McImage128k_dataMetaField,
};
static int g_beSvPs2McImage128k_fieldOffsets[] = {
    12,
    8,
};

void beSvPs2McImage128k_InitFields(void) {
    int base;
    void *data;
    igMetaObject *meta;

    meta = g_beSvPs2McImage128k_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvPs2McImage128k_ctorTable, 2);
    data = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)data)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    igMetaObject_NameFields(meta, g_beSvPs2McImage128k_fieldTable, g_beSvPs2McImage128k_fieldHandles, g_beSvPs2McImage128k_fieldOffsets, base);
}

