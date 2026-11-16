igMetaObject *g_igObjectDirEntry_metaObject;
igMetaField *g_igObjectDirEntry_typeMetaMetaField;
igMetaField *g_igObjectDirEntry_typeMetaNameMetaField;
igMetaField *g_igObjectDirEntry_majorVersionMetaField;
igMetaField *g_igObjectDirEntry_minorVersionMetaField;
igMetaField *g_igObjectDirEntry_refField;
igMetaField *g_igObjectDirEntry_typeMetaIndexMetaField;
igMetaField *g_igObjectDirEntry_memoryPoolHandleMetaField;

int igObjectDirEntry_Create(int allocator) {
    igObjectDirEntry_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igObjectDirEntry_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igObjectDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectDirEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectDirEntry_EnsureRegistered();
    return g_igObjectDirEntry_metaObject;
}

int igObjectDirEntry_GetVTable(void) {
    igObjectDirEntry o;
    int r;

    igObject_InitHeader((igObject *)&o);
    o._name = 0;
    o._vtable = (int)&g_igObjectDirEntry_vtable[0];
    o._typeMeta = 0;
    o._typeMetaName = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igObjectDirEntry_vtable[0];
    igStringRef_Destruct(&o._typeMetaName, -1);
    igSmartPointer_igMetaObject_Destruct(&o._typeMeta, -1);
    igDirEntry_Destroy(&o, 0);
    return r;
}

void igObjectDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectDirEntry_Register);
}

static igMetaObjectCallback g_igObjectDirEntry_callbackList[] = { igMetaObject_EnsureRegistered, igObject_EnsureRegistered, 0 };

CallbackArray *igObjectDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igObjectDirEntry_metaObject,
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igObjectDirEntry_GetMetaObjectFunction,
        "igObjectDirEntry",
        0x34,
        igObjectDirEntry_GetVTable,
        igObjectDirEntry_InitFields,
        0,
        g_igObjectDirEntry_callbackList
    );
}

void igObjectDirEntry_GetMetaObjectFunction(void) {
    igObjectDirEntry_GetMetaObject();
}

igMetaObject *g_igDirEntry_metaObject;
igMetaField *g_igDirEntry_indexMetaField;
igMetaField *g_igDirEntry_resolveMethodMetaField;
igMetaField *g_igDirEntry_refTypeMetaField;
igMetaField *g_igDirEntry_refField;

igMetaObject *igDirEntry_GetPublishedMetaObject(void) {
    return g_igDirEntry_metaObject;
}

static FieldFactory g_igObjectDirEntry_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igObjectDirEntry_fieldTable[] = {
    "_typeMeta",
    "_typeMetaName",
    "_majorVersion",
    "_minorVersion",
    "_typeMetaIndex",
    "_memoryPoolHandle",
};
static igMetaField **g_igObjectDirEntry_fieldDescriptors[] = {
    &g_igObjectDirEntry_typeMetaMetaField,
    &g_igObjectDirEntry_typeMetaNameMetaField,
    &g_igObjectDirEntry_majorVersionMetaField,
    &g_igObjectDirEntry_minorVersionMetaField,
    &g_igObjectDirEntry_typeMetaIndexMetaField,
    &g_igObjectDirEntry_memoryPoolHandleMetaField,
};
static int g_igObjectDirEntry_fieldOffsets[] = {
    28,
    32,
    36,
    40,
    48,
    44,
};

igMetaObject *g_igObject_metaObject;


void igObjectDirEntry_InitFields(void) {
    igMetaObject *meta = g_igObjectDirEntry_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igStringMetaField *text;
    igObjectRefMetaField *ref;
    int fields;
    int index;
    igMetaObject_CreateFields(meta, g_igObjectDirEntry_ctorTable, 6);
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    ref->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igMetaField *)ref)->_persistent = 0;
    text = (igStringMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    igStringMetaField_SetDefaultText((int *)text, (int)"NoMeta");
    text->_destruct = 1;
    ((igMetaField *)text)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 2))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 3))->_persistent = 0;
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((char *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_ref));
    field = (igMetaField *)igObjectRefMetaField_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_ref, &g_igObjectDirEntry_refField, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = (int)g_igObject_metaObject;
    igObjectRefMetaField_SetDefault((igObjectRefMetaField *)field, 0);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)&g_igObjectDirEntry_refField;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 4), -1);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 5), -1);
    igMetaObject_NameFields(meta, g_igObjectDirEntry_fieldTable, g_igObjectDirEntry_fieldDescriptors, g_igObjectDirEntry_fieldOffsets, base);
}

