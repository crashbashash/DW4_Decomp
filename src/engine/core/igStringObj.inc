igMetaObject *g_igStringObj_metaObject;
igMetaField *g_igStringObj_bufferMetaField;
igMetaField *g_igStringObj_lengthMetaField;

void * igStringObj_Create(int pool) {
    igStringObj_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igStringObj_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igStringObj_GetOrCreateMetaObject(void) {
    if (g_igStringObj_metaObject == 0) {
        g_igStringObj_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStringObj_metaObject;
}

igMetaObject *igStringObj_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObj_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringObj_EnsureRegistered();
    return g_igStringObj_metaObject;
}

int igStringObj_GetVTable(void) {
    igStringObj string;

    igObject_InitHeader((igObject *)&string);
    string._vtable = (int)(&g_igStringObj_vtable[0]);
    return *(int *)((char *)&string + g_objectSystem->vtableProbeOffset);
}

void igStringObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringObj_Register);
}

CallbackArray *igStringObj_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStringObj_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igStringObj_GetMetaObjectFunction,
        "igStringObj",
        0x10,
        igStringObj_GetVTable,
        igStringObj_InitFields,
        0,
        0
    );
}

void igStringObj_GetMetaObjectFunction(void) {
    igStringObj_GetMetaObject();
}

static FieldFactory g_igStringObj_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igStringObj_fieldTable[] = {
    "_buffer",
    "_length",
};
static igMetaField **g_igStringObj_fieldDescriptors[] = {
    &g_igStringObj_bufferMetaField,
    &g_igStringObj_lengthMetaField,
};
static int g_igStringObj_fieldOffsets[] = {
    8,
    12,
};

void igStringObj_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g_igStringObj_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStringObj_ctorTable, 2);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igStringObj_fieldTable, g_igStringObj_fieldDescriptors, g_igStringObj_fieldOffsets, first);
}

