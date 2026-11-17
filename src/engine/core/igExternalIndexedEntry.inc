igMetaObject *g_igExternalIndexedEntry_metaObject;
igMetaField *g_igExternalIndexedEntry_directoryIndexMetaField;
igMetaField *g_igExternalIndexedEntry_entryIndexMetaField;
igMetaField *g_igExternalIndexedEntry_entryTypeMetaField;
igMetaField *g_igExternalIndexedEntry_entryTypeIndexMetaField;
igMetaField *g_igExternalIndexedEntry_objectTypeMetaField;
igMetaField *g_igExternalIndexedEntry_objectTypeIndexMetaField;

igMetaObject *igExternalIndexedEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalIndexedEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalIndexedEntry_EnsureRegistered();
    return g_igExternalIndexedEntry_metaObject;
}

int igExternalIndexedEntry_GetVTable(void) {
    igExternalIndexedEntry entry;
    int vtable;

    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)(&g_igExternalIndexedEntry_vtable[0]);
    entry._entryType = 0;
    entry._objectType = 0;
    vtable = *(int *)((char *)&entry + g_objectSystem->vtableProbeOffset);
    entry._vtable = (int)(&g_igExternalIndexedEntry_vtable[0]);
    igSmartPointer_igMetaObject_Destruct((igSmartPointer<igObject> *)&entry._objectType, -1);
    igSmartPointer_igMetaObject_Destruct((igSmartPointer<igObject> *)&entry._entryType, -1);
    igDirEntry_Destroy((igDirEntry *)&entry, 0);
    return vtable;
}

void igExternalIndexedEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExternalIndexedEntry_Register);
}

static igMetaObjectCallback g_igExternalIndexedEntry_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igExternalIndexedEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igExternalIndexedEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalIndexedEntry_GetMetaObjectFunction,
        "igExternalIndexedEntry",
        0x34,
        igExternalIndexedEntry_GetVTable,
        igExternalIndexedEntry_InitFields,
        0,
        g_igExternalIndexedEntry_callbackList
    );
}

void igExternalIndexedEntry_GetMetaObjectFunction(void) {
    igExternalIndexedEntry_GetMetaObject();
}

static FieldFactory g_igExternalIndexedEntry_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igExternalIndexedEntry_fieldTable[] = {
    "_directoryIndex",
    "_entryIndex",
    "_entryType",
    "_entryTypeIndex",
    "_objectType",
    "_objectTypeIndex",
};
static igMetaField **g_igExternalIndexedEntry_fieldDescriptors[] = {
    &g_igExternalIndexedEntry_directoryIndexMetaField,
    &g_igExternalIndexedEntry_entryIndexMetaField,
    &g_igExternalIndexedEntry_entryTypeMetaField,
    &g_igExternalIndexedEntry_entryTypeIndexMetaField,
    &g_igExternalIndexedEntry_objectTypeMetaField,
    &g_igExternalIndexedEntry_objectTypeIndexMetaField,
};
static int g_igExternalIndexedEntry_fieldOffsets[] = {
    28,
    32,
    36,
    40,
    44,
    48,
};

void igExternalIndexedEntry_InitFields(void) {
    int first;
    void *objectTypeField;
    void *entryTypeField;
    void *meta;

    meta = (void *)g_igExternalIndexedEntry_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igExternalIndexedEntry_ctorTable, 6);
    entryTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)entryTypeField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igMetaField *)entryTypeField)->_persistent = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3), -1);
    objectTypeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4)));
    ((igObjectRefMetaField *)objectTypeField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igMetaField *)objectTypeField)->_persistent = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 5), -1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igExternalIndexedEntry_fieldTable, g_igExternalIndexedEntry_fieldDescriptors, g_igExternalIndexedEntry_fieldOffsets, first);
}

