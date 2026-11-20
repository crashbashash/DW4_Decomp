igMetaObject *g_igGeometryAttr_metaObject;
igMetaField *g_igGeometryAttr_vertexArrayMetaField;
igMetaField *g_igGeometryAttr_indexArrayMetaField;
igMetaField *g_igGeometryAttr_primTypeMetaField;
igMetaField *g_igGeometryAttr_numPrimsMetaField;
igMetaField *g_igGeometryAttr_offsetMetaField;
igMetaField *g_igGeometryAttr_primLengthsMetaField;
igMetaField *g_igGeometryAttr_handleMetaField;
igMetaField *g_igGeometryAttr_dPdsMetaField;
igMetaField *g_igGeometryAttr_dPdtMetaField;

igGeometryAttr *igGeometryAttr_Create(int allocator) {
    igGeometryAttr_EnsureRegistered();
    return (igGeometryAttr *)igMetaObject_CreateInstance(g_igGeometryAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igGeometryAttr_GetOrCreateMetaObject(void) {
    if (g_igGeometryAttr_metaObject == 0) {
        g_igGeometryAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGeometryAttr_metaObject;
}

igMetaObject *igGeometryAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryAttr_EnsureRegistered();
    return g_igGeometryAttr_metaObject;
}

void igGeometryAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryAttr_Register);
}

static igMetaObjectCallback g_igGeometryAttr_callbackList[] = { igVertexArray_EnsureRegistered, igIndexArray_EnsureRegistered, igUnsignedIntList_EnsureRegistered, igVec3fList_EnsureRegistered, 0 };

CallbackArray *igGeometryAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igGeometryAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igGeometryAttr_GetMetaObjectFunction,
        "igGeometryAttr",
        0x30, /* instance size */
        0,
        &igGeometryAttr_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr_callbackList /* callback list */
    );
}

void igGeometryAttr_GetMetaObjectFunction(void) {
    igGeometryAttr_GetMetaObject();
}

static FieldFactory g_igGeometryAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igGeometryAttr_fieldTable[] = {
    "_vertexArray",
    "_indexArray",
    "_primType",
    "_numPrims",
    "_offset",
    "_primLengths",
    "_handle",
    "_dPds",
    "_dPdt",
};
static igMetaField **g_igGeometryAttr_fieldHandles[] = {
    &g_igGeometryAttr_vertexArrayMetaField,
    &g_igGeometryAttr_indexArrayMetaField,
    &g_igGeometryAttr_primTypeMetaField,
    &g_igGeometryAttr_numPrimsMetaField,
    &g_igGeometryAttr_offsetMetaField,
    &g_igGeometryAttr_primLengthsMetaField,
    &g_igGeometryAttr_handleMetaField,
    &g_igGeometryAttr_dPdsMetaField,
    &g_igGeometryAttr_dPdtMetaField,
};
static int g_igGeometryAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void igGeometryAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    void *field5;
    void *field6;
    igMetaObject *meta;

    meta = g_igGeometryAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igGeometryAttr_ctorTable, 9);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igIndexArray_GetOrCreateMetaObject();
    field6 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((Gap::Core::igEnumMetaField *)field6)->setDefault(0);
    ((igEnumMetaField *)field6)->_getMetaEnumFunction = (int)(&IG_GFX_DRAW_GetMetaEnum);
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    field5 = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)field5)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igGeometryAttr_fieldTable, g_igGeometryAttr_fieldHandles, g_igGeometryAttr_fieldOffsets, base);
    *(int *)((char *)(g_igGeometryAttr_metaObject) + 60) = (int)igGeometryAttr1_5_GetMetaObjectFunction;
}

