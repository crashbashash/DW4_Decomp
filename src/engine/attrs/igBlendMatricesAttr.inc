igMetaObject *g_igBlendMatricesAttr_metaObject;
igMetaField *g_igBlendMatricesAttr_matrixCacheMetaField;
igMetaField *g_igBlendMatricesAttr_currentMatrixCountMetaField;
igMetaField *g_igBlendMatricesAttr_matrixCacheCapacityMetaField;

igBlendMatricesAttr *igBlendMatricesAttr_Create(igMemoryPoolView *pool) {
    igBlendMatricesAttr_EnsureRegistered();
    return (igBlendMatricesAttr *)igMetaObject_CreateInstance(g_igBlendMatricesAttr_metaObject, pool);
}

igMetaObject *igBlendMatricesAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendMatricesAttr_EnsureRegistered();
    return g_igBlendMatricesAttr_metaObject;
}

int igBlendMatricesAttr_GetVTable(void) {
    struct Obj_139ca0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igBlendMatricesAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igBlendMatricesAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatricesAttr_Register);
}

CallbackArray *igBlendMatricesAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatricesAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igBlendMatricesAttr_GetMetaObjectFunction,
        "igBlendMatricesAttr",
        0x18, /* instance size */
        igBlendMatricesAttr_GetVTable,
        &igBlendMatricesAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBlendMatricesAttr_GetMetaObjectFunction(void) {
    igBlendMatricesAttr_GetMetaObject();
}

static FieldFactory g_igBlendMatricesAttr_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igBlendMatricesAttr_fieldTable[] = {
    "_matrixCache",
    "_currentMatrixCount",
    "_matrixCacheCapacity",
};
static igMetaField **g_igBlendMatricesAttr_fieldHandles[] = {
    &g_igBlendMatricesAttr_matrixCacheMetaField,
    &g_igBlendMatricesAttr_currentMatrixCountMetaField,
    &g_igBlendMatricesAttr_matrixCacheCapacityMetaField,
};
static int g_igBlendMatricesAttr_fieldOffsets[] = {
    12,
    16,
    20,
};

void igBlendMatricesAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igBlendMatricesAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igBlendMatricesAttr_ctorTable, 3);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)field)->_memType = FUN_001888e0();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields(meta, g_igBlendMatricesAttr_fieldTable, g_igBlendMatricesAttr_fieldHandles, g_igBlendMatricesAttr_fieldOffsets, base);
}

