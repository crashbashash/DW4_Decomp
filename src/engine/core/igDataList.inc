igMetaObject *g_igDataList_metaObject;
igMetaField *g_igDataList_countMetaField;
igMetaField *g_igDataList_capacityMetaField;
igMetaField *g_igDataList_dataField;

void * igDataList_Create(int pool) {
    igDataList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igDataList_metaObject, (igMemoryPoolView *)pool));
}

/* Created with allocation only when missing. */
igMetaObject *igDataList_GetOrCreateMetaObject(void) {
    if (g_igDataList_metaObject == 0) {
        g_igDataList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataList_metaObject;
}

igMetaObject *igDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataList_EnsureRegistered();
    return g_igDataList_metaObject;
}

int igDataList_GetVTable(void) {
    igDataList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igDataList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataList_Register);
}

CallbackArray *igDataList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDataList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igDataList_GetMetaObjectFunction,
        "igDataList",
        0x14,
        igDataList_GetVTable,
        igDataList_InitFields,
        0,
        0
    );
}

void igDataList_GetMetaObjectFunction(void) {
    igDataList_GetMetaObject();
}

static FieldFactory g_igDataList_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
};
static const char *g_igDataList_fieldTable[] = {
    "_count",
    "_capacity",
    "_data",
};
static igMetaField **g_igDataList_fieldDescriptors[] = {
    &g_igDataList_countMetaField,
    &g_igDataList_capacityMetaField,
    &g_igDataList_dataField,
};
static int g_igDataList_fieldOffsets[] = {
    8,
    12,
    16,
};

void igDataList_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igDataList_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDataList_ctorTable, 3);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDataList_fieldTable, g_igDataList_fieldDescriptors, g_igDataList_fieldOffsets, base);
}

