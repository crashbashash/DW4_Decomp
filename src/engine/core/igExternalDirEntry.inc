igMetaObject *g_igExternalDirEntry_metaObject;
igMetaField *g_igExternalDirEntry_refDescriptorCell;
igMetaField *g_igExternalDirEntry_directoryNameMetaField;
igMetaField *g_igExternalDirEntry_entryNameMetaField;
igMetaField *g_igExternalDirEntry_entryIndexMetaField;
igMetaField *g_igExternalDirEntry_externalFilePathMetaField;

igMetaObject *igExternalDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalDirEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalDirEntry_EnsureRegistered();
    return g_igExternalDirEntry_metaObject;
}

int igExternalDirEntry_GetVTable(void) {
    igExternalDirEntry entry;
    int vtable;
    char *o;
    int *text;
    int *header;
    int references;
    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)&g_igExternalDirEntry_vtable[0];
    entry._directoryName = 0;
    entry._entryName = 0;
    entry._externalFilePath = 0;
    vtable = *(int *)((char *)&entry + g_objectSystem->vtableProbeOffset);
    entry._vtable = (int)&g_igExternalDirEntry_vtable[0];
    igStringRef_Destruct((igStringRef *)&entry._externalFilePath, -1);
    igStringRef_Destruct((igStringRef *)&entry._entryName, -1);
    igStringRef_Destruct((igStringRef *)&entry._directoryName, -1);
    igDirEntry_Destroy((igDirEntry *)&entry, 0);
    return vtable;
}

void igExternalDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExternalDirEntry_Register);
}

static igMetaObjectCallback g_igExternalDirEntry_callbackList[] = { igObject_EnsureRegistered, 0 };

CallbackArray *igExternalDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    return igMetaObject_RegisterClass(
        0,
        &g_igExternalDirEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalDirEntry_GetMetaObjectFunction,
        "igExternalDirEntry",
        0x2C,
        igExternalDirEntry_GetVTable,
        igExternalDirEntry_InitFields,
        0,
        g_igExternalDirEntry_callbackList
    );
}

void igExternalDirEntry_GetMetaObjectFunction(void) {
    igExternalDirEntry_GetMetaObject();
}

static FieldFactory g_igExternalDirEntry_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igExternalDirEntry_fieldTable[] = {
    "_directoryName",
    "_entryName",
    "_entryIndex",
    "_externalFilePath",
};
static igMetaField **g_igExternalDirEntry_fieldDescriptors[] = {
    &g_igExternalDirEntry_directoryNameMetaField,
    &g_igExternalDirEntry_entryNameMetaField,
    &g_igExternalDirEntry_entryIndexMetaField,
    &g_igExternalDirEntry_externalFilePathMetaField,
};
static int g_igExternalDirEntry_fieldOffsets[] = {
    28,
    32,
    36,
    40,
};


void igExternalDirEntry_InitFields(void) {
    igMetaObject *meta = g_igExternalDirEntry_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    int fields;
    igMetaObject_CreateFields(meta, g_igExternalDirEntry_ctorTable, 4);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_ref));
    field = (igMetaField *)igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_ref, &g_igExternalDirEntry_refDescriptorCell, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = (int)g_igObject_metaObject;
    field->_persistent = 0;
    field->_externalEnumStorage = (int)&g_igExternalDirEntry_refDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), "Intrinsic");
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 1), "default");
    field = (igMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    igStringMetaField_SetDefaultText((igMetaField *)field, "");
    field->_persistent = 0;
    igMetaObject_NameFields(meta, g_igExternalDirEntry_fieldTable, g_igExternalDirEntry_fieldDescriptors, g_igExternalDirEntry_fieldOffsets, base);
}

