igMetaObject *g_igIndexArray_metaObject;
igMetaField *g_igIndexArray_indexDataMetaField;
igMetaField *g_igIndexArray_numIndicesMetaField;
igMetaField *g_igIndexArray_dataSizeMetaField;
igMetaField *g_igIndexArray_usageFlagsMetaField;
igMetaField *g_igIndexArray_memPoolMetaField;

igMetaObject *FUN_0014d7f0(void) {
    if (g_igIndexArray_metaObject == 0) {
        g_igIndexArray_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

void igIndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igIndexArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIndexArray_GetMetaObject,
        "igIndexArray",
        0x1C, /* instance size */
        0,
        &igIndexArray_InitFields,
        0, /* extra callback item */
        g_igIndexArray_callbackList /* callback list */
    );
}

void thunk_igIndexArray_GetMetaObject(void) {
    igIndexArray_GetMetaObject();
}

static FieldFactory g_igIndexArray_ctorTable[] = {
    igMemoryRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igEnumMetaField_Create,
    igUnsignedIntMetaField_Create,
    igObjectRefMetaField_Create,
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
    void *temp_s1;
    void *temp_s1_2;
    int fieldStart;
    void *temp_v0;
    igMetaObject *meta;

    meta = g_igIndexArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igIndexArray_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001493e0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1_2)->_resetMethod = 3;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)temp_s1_2)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1_2)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(meta, g_igIndexArray_fieldTable, g_igIndexArray_fieldHandles, g_igIndexArray_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igIndexArray_metaObject)->_abstractProxy = (int)(&thunk_igPsx2IndexArray_GetMetaObject);
}

