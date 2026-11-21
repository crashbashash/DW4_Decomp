igMetaObject *g_igPsx2Media_metaObject;
igMetaField *g_igPsx2Media_headAndTailBufferMetaField;
igMetaField *g_igPsx2Media_connectionMetaField;
igMetaField *g_igPsx2Media_semaMetaField;
igMetaField *g_igPsx2Media_commandBufferMetaField;
igMetaField *g_igPsx2Media_writeBufferMetaField;
igMetaField *g_igPsx2Media_handlePoolMetaField;
igMetaField *g_igPsx2Media_conversionStringMetaField;
igMetaField *g_igPsx2Media_initializedMetaField;

void *igPsx2Media_Create(int pool) {
    igPsx2Media_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igPsx2Media_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2Media_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Media_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Media_EnsureRegistered();
    return g_igPsx2Media_metaObject;
}

int igPsx2Media_GetVTable(void) {
    igPsx2Media media;
    int result;
    igObject * sema;
    igObject * connection;
    igObject * conversionString;
    igObject_InitHeader((igObject *)&media);
    media._vtable = (int)(&g_igPsx2Media_vtable[0]);
    connection = (igObject *)&media._connection;
    *(int *)connection = 0;
    sema = (igObject *)&media._sema;
    *(int *)sema = 0;
    conversionString = (igObject *)&media._conversionString;
    *(int *)conversionString = 0;
    result = *(int *)((char *)&media + g_objectSystem->vtableProbeOffset);
    media._vtable = (int)(&g_igPsx2Media_vtable[0]);
    if (conversionString != 0) {
        conversionString = *(igObject **)conversionString;
        igObject::release(conversionString);
    }
    if (sema != 0) {
        sema = *(igObject **)sema;
        igObject::release(sema);
    }
    if (connection != 0) {
        connection = *(igObject **)connection;
        igObject::release(connection);
    }
    return result;
}

void igPsx2Media_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2Media_Register);
}

static igMetaObjectCallback g_igPsx2Media_callbackList[] = { igPsx2IopRpcConnection_EnsureRegistered, igSemaphore_EnsureRegistered, igStringObj_EnsureRegistered, 0 };

CallbackArray *igPsx2Media_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2Media_metaObject,
        Gap::Core::igMedia::arkRegisterInternal,
        Gap::Core::igMedia::getClassMeta,
        igPsx2Media_GetMetaObjectFunction,
        "igPsx2Media",
        0x28,
        igPsx2Media_GetVTable,
        igPsx2Media_InitFields,
        0,
        g_igPsx2Media_callbackList
    );
}

static FieldFactory g_igPsx2Media_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igPsx2Media_fieldTable[] = {
    "_headAndTailBuffer",
    "_connection",
    "_sema",
    "_commandBuffer",
    "_writeBuffer",
    "_handlePool",
    "_conversionString",
    "_initialized",
};
static igMetaField **g_igPsx2Media_fieldDescriptors[] = {
    &g_igPsx2Media_headAndTailBufferMetaField,
    &g_igPsx2Media_connectionMetaField,
    &g_igPsx2Media_semaMetaField,
    &g_igPsx2Media_commandBufferMetaField,
    &g_igPsx2Media_writeBufferMetaField,
    &g_igPsx2Media_handlePoolMetaField,
    &g_igPsx2Media_conversionStringMetaField,
    &g_igPsx2Media_initializedMetaField,
};
static int g_igPsx2Media_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

void igPsx2Media_InitFields(void) {
    int base;
    void *field;
    igRawRefMetaField *handlePoolField;
    void *meta;

    meta = (void *)g_igPsx2Media_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2Media_ctorTable, 8);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igPsx2IopRpcConnection_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    handlePoolField = (igRawRefMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    handlePoolField->_resetMethod = 3;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2Media_fieldTable, g_igPsx2Media_fieldDescriptors, g_igPsx2Media_fieldOffsets, base);
}

