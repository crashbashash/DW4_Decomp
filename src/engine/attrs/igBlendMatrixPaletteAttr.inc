igMetaObject *g_igBlendMatrixPaletteAttr_metaObject;
igMetaField *g_igBlendMatrixPaletteAttr_matrixCacheMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_matrixIndicesMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_currentMatrixCountMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_capacityMetaField;

igBlendMatrixPaletteAttr *igBlendMatrixPaletteAttr_Create(igMemoryPoolView *pool) {
    igBlendMatrixPaletteAttr_EnsureRegistered();
    return (igBlendMatrixPaletteAttr *)igMetaObject_CreateInstance(g_igBlendMatrixPaletteAttr_metaObject, pool);
}

igMetaObject *igBlendMatrixPaletteAttr_GetOrCreateMetaObject(void) {
    if (g_igBlendMatrixPaletteAttr_metaObject == 0) {
        g_igBlendMatrixPaletteAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendMatrixPaletteAttr_metaObject;
}

igMetaObject *igBlendMatrixPaletteAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendMatrixPaletteAttr_EnsureRegistered();
    return g_igBlendMatrixPaletteAttr_metaObject;
}

int igBlendMatrixPaletteAttr_GetVTable(void) {
    union U_139a70 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igBlendMatrixPaletteAttr_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igBlendMatrixPaletteAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixPaletteAttr_Register);
}

CallbackArray *igBlendMatrixPaletteAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatrixPaletteAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igBlendMatrixPaletteAttr_GetMetaObjectFunction,
        "igBlendMatrixPaletteAttr",
        0x1C, /* instance size */
        igBlendMatrixPaletteAttr_GetVTable,
        &igBlendMatrixPaletteAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBlendMatrixPaletteAttr_GetMetaObjectFunction(void) {
    igBlendMatrixPaletteAttr_GetMetaObject();
}

static FieldFactory g_igBlendMatrixPaletteAttr_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igBlendMatrixPaletteAttr_fieldTable[] = {
    "_matrixCache",
    "_matrixIndices",
    "_currentMatrixCount",
    "_capacity",
};
static igMetaField **g_igBlendMatrixPaletteAttr_fieldHandles[] = {
    &g_igBlendMatrixPaletteAttr_matrixCacheMetaField,
    &g_igBlendMatrixPaletteAttr_matrixIndicesMetaField,
    &g_igBlendMatrixPaletteAttr_currentMatrixCountMetaField,
    &g_igBlendMatrixPaletteAttr_capacityMetaField,
};
static int g_igBlendMatrixPaletteAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igBlendMatrixPaletteAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igBlendMatrixPaletteAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igBlendMatrixPaletteAttr_ctorTable, 4);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)field2)->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    ((igRefMetaField *)field2)->_destruct = 1;
    ((igMemoryRefMetaField *)field2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field2)->_releaseOnReset = 1;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igUnsignedIntMetaField::getMetaField();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields(meta, g_igBlendMatrixPaletteAttr_fieldTable, g_igBlendMatrixPaletteAttr_fieldHandles, g_igBlendMatrixPaletteAttr_fieldOffsets, base);
}

