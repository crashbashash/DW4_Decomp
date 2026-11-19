igMetaObject *g_igVertexArray_metaObject;
igMetaField *g_igVertexArray_vdataMetaField;
igMetaField *g_igVertexArray_numVertsMetaField;
igMetaField *g_igVertexArray_vtypeMetaField;
igMetaField *g_igVertexArray_usageFlagsMetaField;

igVertexArray *igVertexArray_Create(int allocator) {
    igVertexArray_EnsureRegistered();
    return (igVertexArray *)igMetaObject_CreateInstance(g_igVertexArray_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igVertexArray_GetOrCreateMetaObject(void) {
    if (g_igVertexArray_metaObject == 0) {
        g_igVertexArray_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexArray_metaObject;
}

igMetaObject *igVertexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexArray_EnsureRegistered();
    return g_igVertexArray_metaObject;
}

void igVertexArray_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexArray_Register);
}

CallbackArray *igVertexArray_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igVertexArray_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igVertexArray_GetMetaObjectFunction,
        "igVertexArray",
        0x18, /* instance size */
        0,
        &igVertexArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVertexArray_GetMetaObjectFunction(void) {
    igVertexArray_GetMetaObject();
}

static FieldFactory g_igVertexArray_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igVertexArray_fieldTable[] = {
    "_vdata",
    "_numVerts",
    "_vtype",
    "_usageFlags",
};
static igMetaField **g_igVertexArray_fieldHandles[] = {
    &g_igVertexArray_vdataMetaField,
    &g_igVertexArray_numVertsMetaField,
    &g_igVertexArray_vtypeMetaField,
    &g_igVertexArray_usageFlagsMetaField,
};
static int g_igVertexArray_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igVertexArray_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igVertexArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexArray_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    *(int *)((char *)(temp_s1) + 60) = igMemoryRefMetaField_GetDefaultDescriptor();
    *(char *)((char *)(temp_s1) + 40) = 0;
    igMetaObject_NameFields(meta, g_igVertexArray_fieldTable, g_igVertexArray_fieldHandles, g_igVertexArray_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igVertexArray_metaObject) + 60) = (int)(&igPsx2VertexArray1_1_GetMetaObjectFunction);
}

