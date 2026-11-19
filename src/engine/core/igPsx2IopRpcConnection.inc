igMetaObject *g_igPsx2IopRpcConnection_metaObject;
igMetaField *g_igPsx2IopRpcConnection_sifDataMetaField;
igMetaField *g_igPsx2IopRpcConnection_dataMemoryMetaField;
igMetaField *g_igPsx2IopRpcConnection_semaMetaField;

igPsx2IopRpcConnectionView *igPsx2IopRpcConnection_Create(int pool) {
    igPsx2IopRpcConnection_EnsureRegistered();
    return (igPsx2IopRpcConnectionView *)igMetaObject_CreateInstance(g_igPsx2IopRpcConnection_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2IopRpcConnection_GetOrCreateMetaObject(void) {
    if (g_igPsx2IopRpcConnection_metaObject == 0) {
        g_igPsx2IopRpcConnection_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPsx2IopRpcConnection_metaObject;
}

igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IopRpcConnection_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2IopRpcConnection_EnsureRegistered();
    return g_igPsx2IopRpcConnection_metaObject;
}

int igPsx2IopRpcConnection_GetVTable(void) {
    igPsx2IopRpcConnection connection;
    igObject_InitHeader((igObject *)&connection);
    connection._vtable = (int)&g_igPsx2IopRpcConnection_vtable[0];
    return *(int *)((char *)&connection + g_objectSystem->vtableProbeOffset);
}

void igPsx2IopRpcConnection_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2IopRpcConnection_Register);
}

CallbackArray *igPsx2IopRpcConnection_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2IopRpcConnection_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igPsx2IopRpcConnection_GetMetaObjectFunction,
        "igPsx2IopRpcConnection",
        0x14,
        igPsx2IopRpcConnection_GetVTable,
        igPsx2IopRpcConnection_InitFields,
        0,
        0
    );
}

void igPsx2IopRpcConnection_GetMetaObjectFunction(void) {
    igPsx2IopRpcConnection_GetMetaObject();
}

static FieldFactory g_igPsx2IopRpcConnection_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igPsx2IopRpcConnection_fieldTable[] = {
    "_sifData",
    "_dataMemory",
    "_sema",
};
static igMetaField **g_igPsx2IopRpcConnection_fieldDescriptors[] = {
    &g_igPsx2IopRpcConnection_sifDataMetaField,
    &g_igPsx2IopRpcConnection_dataMemoryMetaField,
    &g_igPsx2IopRpcConnection_semaMetaField,
};
static int g_igPsx2IopRpcConnection_fieldOffsets[] = {
    8,
    12,
    16,
};

void igPsx2IopRpcConnection_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igPsx2IopRpcConnection_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2IopRpcConnection_ctorTable, 3);
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2IopRpcConnection_fieldTable, g_igPsx2IopRpcConnection_fieldDescriptors, g_igPsx2IopRpcConnection_fieldOffsets, first);
}

