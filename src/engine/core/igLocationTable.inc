igMetaObject *g_igLocationTable_metaObject;
igMetaField *g_igLocationTable_capacityMetaField;
igMetaField *g_igLocationTable_hashCapacityMetaField;
igMetaField *g_igLocationTable_locationsMetaField;
igMetaField *g_igLocationTable_hashIndexMetaField;
igMetaField *g_igLocationTable_symbolNamesMetaField;
igMetaField *g_igLocationTable_sourceFileNamesMetaField;

igMetaObject *igLocationTable_GetOrCreateMetaObject(void) {
    if (g_igLocationTable_metaObject == 0) {
        g_igLocationTable_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLocationTable_metaObject;
}

igMetaObject *igLocationTable_GetMetaObject(void)
{
    igMetaObject *g = g_igLocationTable_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLocationTable_EnsureRegistered();
    return g_igLocationTable_metaObject;
}

int igLocationTable_GetVTable(void) {
    igLocationTable o;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader((igObject *)&o);
    o._vtable = (int)&g_igLocationTable_vtable[0];
    p16 = &o._locations;
    *p16 = 0;
    p17 = &o._hashIndex;
    *p17 = 0;
    p18 = &o._symbolNames;
    *p18 = 0;
    o._sourceFileNames = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igLocationTable_vtable[0];
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&o._sourceFileNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)p18, -1);
    igSmartPointer_igIntListNoClean_Destruct((void **)p17, -1);
    igSmartPointer_igUnsignedIntListNoClean_Destruct((igSmartPointer<igObject> *)p16, -1);
    return r;
}

void igLocationTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLocationTable_Register);
}

static igMetaObjectCallback g_igLocationTable_callbackList[] = { igUnsignedIntListNoClean_EnsureRegistered, igIntListNoClean_EnsureRegistered, igStringTable_EnsureRegistered, 0 };

CallbackArray *igLocationTable_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igLocationTable_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igLocationTable_GetMetaObjectFunction,
        "igLocationTable",
        0x20,
        igLocationTable_GetVTable,
        igLocationTable_InitFields,
        0,
        g_igLocationTable_callbackList
    );
}

void igLocationTable_GetMetaObjectFunction(void) {
    igLocationTable_GetMetaObject();
}

static FieldFactory g_igLocationTable_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLocationTable_fieldTable[] = {
    "_capacity",
    "_hashCapacity",
    "_locations",
    "_hashIndex",
    "_symbolNames",
    "_sourceFileNames",
};
static igMetaField **g_igLocationTable_fieldDescriptors[] = {
    &g_igLocationTable_capacityMetaField,
    &g_igLocationTable_hashCapacityMetaField,
    &g_igLocationTable_locationsMetaField,
    &g_igLocationTable_hashIndexMetaField,
    &g_igLocationTable_symbolNamesMetaField,
    &g_igLocationTable_sourceFileNamesMetaField,
};
static int g_igLocationTable_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igLocationTable_InitFields(void) {
    int base;
    void *locationsField;
    void *hashIndexField;
    void *symbolNamesField;
    void *sourceFileNamesField;
    void *meta;

    meta = (void *)g_igLocationTable_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igLocationTable_ctorTable, 6);
    locationsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)locationsField)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)locationsField)->_construct = 1;
    hashIndexField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)hashIndexField)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)hashIndexField)->_construct = 1;
    symbolNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)symbolNamesField)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)symbolNamesField)->_construct = 1;
    sourceFileNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((igObjectRefMetaField *)sourceFileNamesField)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)sourceFileNamesField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igLocationTable_fieldTable, g_igLocationTable_fieldDescriptors, g_igLocationTable_fieldOffsets, base);
}

