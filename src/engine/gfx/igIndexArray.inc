igMetaObject *g_igIndexArray_metaObject;
igMetaField *g_igIndexArray_indexDataMetaField;
igMetaField *g_igIndexArray_numIndicesMetaField;
igMetaField *g_igIndexArray_dataSizeMetaField;
igMetaField *g_igIndexArray_usageFlagsMetaField;
igMetaField *g_igIndexArray_memPoolMetaField;

igMetaObject *igIndexArray_GetOrCreateMetaObject(void) {
    if (g_igIndexArray_metaObject == 0) {
        g_igIndexArray_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIndexArray_metaObject;
}

igMetaObject *igIndexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igIndexArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIndexArray_EnsureRegistered();
    return g_igIndexArray_metaObject;
}

void igIndexArray_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIndexArray_Register);
}

static igMetaObjectCallback g_igIndexArray_callbackList[] = { igMemoryPool_EnsureRegistered, 0 };

CallbackArray *igIndexArray_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igIndexArray_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igIndexArray_GetMetaObjectFunction,
        "igIndexArray",
        0x1C, /* instance size */
        0,
        &igIndexArray_InitFields,
        0, /* extra callback item */
        g_igIndexArray_callbackList /* callback list */
    );
}

void igIndexArray_GetMetaObjectFunction(void) {
    igIndexArray_GetMetaObject();
}

static FieldFactory g_igIndexArray_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igIndexArray_fieldTable[] = {
    "_indexData",
    "_numIndices",
    "_dataSize",
    "_usageFlags",
    "_memPool",
};
static igMetaField **g_igIndexArray_fieldHandles[] = {
    &g_igIndexArray_indexDataMetaField,
    &g_igIndexArray_numIndicesMetaField,
    &g_igIndexArray_dataSizeMetaField,
    &g_igIndexArray_usageFlagsMetaField,
    &g_igIndexArray_memPoolMetaField,
};
static int g_igIndexArray_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    8,
};

void igIndexArray_InitFields(void) {
    void *dataField;
    void *memoryPoolField;
    int fieldStart;
    void *dataSizeField;
    igMetaObject *meta;

    meta = g_igIndexArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igIndexArray_ctorTable, 5);
    dataField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igMemoryRefMetaField *)dataField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    ((igMemoryRefMetaField *)dataField)->_destruct = 1;
    ((igMemoryRefMetaField *)dataField)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)dataField)->_releaseOnReset = 1;
    dataSizeField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    ((Gap::Core::igEnumMetaField *)dataSizeField)->setDefault(0);
    ((igEnumMetaField *)dataSizeField)->_getMetaEnumFunction = (int)(&IG_GFX_INDEX_DATA_SIZE_GetMetaEnum);
    memoryPoolField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    ((igObjectRefMetaField *)memoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    ((igMetaField *)memoryPoolField)->_resetMethod = 3;
    ((igMetaField *)memoryPoolField)->_persistent = 0;
    ((igMetaField *)memoryPoolField)->_deepCopyMethod = 1;
    ((igMetaField *)memoryPoolField)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(meta, g_igIndexArray_fieldTable, g_igIndexArray_fieldHandles, g_igIndexArray_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igIndexArray_metaObject)->_abstractProxy = (int)(&igPsx2IndexArray_GetMetaObjectFunction);
}

