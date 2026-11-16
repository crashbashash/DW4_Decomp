igMetaObject *g_igVertexArray1_1_metaObject;
igMetaField *g_igVertexArray1_1_vertexFormatMetaField;
igMetaField *g_igVertexArray1_1_blendWeightsMetaField;
igMetaField *g_igVertexArray1_1_blendIndicesMetaField;
igMetaField *g_igVertexArray1_1_blendIndexMetaField;
igMetaField *g_igVertexArray1_1_pointSpriteSizeMetaField;
igMetaField *g_igVertexArray1_1_memPoolMetaField;

int FUN_0014b680(int arg0) {
    igVertexArray1_1_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igVertexArray1_1_metaObject, arg0);
}

igMetaObject *igVertexArray1_1_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray1_1_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexArray1_1_EnsureRegistered();
    return g_igVertexArray1_1_metaObject;
}

void igVertexArray1_1_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexArray1_1_Register);
}

static igMetaObjectCallback g_igVertexArray1_1_callbackList[] = { igMemoryPool_EnsureRegistered, 0 };

void igVertexArray1_1_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igVertexArray1_1_metaObject,
        igVertexArray_Register,
        igVertexArray_GetPublishedMetaObject,
        thunk_igVertexArray1_1_GetMetaObject,
        "igVertexArray1_1",
        0x30, /* instance size */
        0,
        &igVertexArray1_1_InitFields,
        thunk_FUN_0015e010, /* extra callback item */
        g_igVertexArray1_1_callbackList /* callback list */
    );
}

void thunk_igVertexArray1_1_GetMetaObject(void) {
    igVertexArray1_1_GetMetaObject();
}

igMetaObject *FUN_0014b7b0(void) {
    return g_igVertexArray_metaObject;
}

static FieldFactory g_igVertexArray1_1_ctorTable[] = {
    igStructMetaField_Create,
    igMemoryRefMetaField_Create,
    igMemoryRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igVertexArray1_1_fieldTable[] = {
    "_vertexFormat",
    "_blendWeights",
    "_blendIndices",
    "_blendIndex",
    "_pointSpriteSize",
    "_memPool",
};
static igMetaField **g_igVertexArray1_1_fieldHandles[] = {
    &g_igVertexArray1_1_vertexFormatMetaField,
    &g_igVertexArray1_1_blendWeightsMetaField,
    &g_igVertexArray1_1_blendIndicesMetaField,
    &g_igVertexArray1_1_blendIndexMetaField,
    &g_igVertexArray1_1_pointSpriteSizeMetaField,
    &g_igVertexArray1_1_memPoolMetaField,
};
static int g_igVertexArray1_1_fieldOffsets[] = {
    28,
    32,
    36,
    40,
    44,
    24,
};

void igVertexArray1_1_InitFields(void) {
    void *meta; /* matching construct: untyped handle keeps the retail register order */
    struct F *temp_s2;
    struct F *temp_s2_3;
    struct F *temp_s2_4;
    int fieldStart;
    struct F *temp_s2_2;

    meta = g_igVertexArray1_1_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igVertexArray1_1_ctorTable, 6);
    temp_s2 = (struct F *)(igMetaObject_GetFieldAt(meta, fieldStart));
    temp_s2->f20 = 4;
    temp_s2 = (struct F *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    temp_s2->f60 = igFloatMetaField_GetDefaultDescriptor();
    temp_s2->f53 = 1;
    temp_s2->f64 = 1;
    temp_s2->f65 = 1;
    temp_s2_2 = (struct F *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    temp_s2_2->f60 = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s2_2->f53 = 1;
    temp_s2_2->f64 = 1;
    temp_s2_2->f65 = 1;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 3)) + 38) = 0;
    temp_s2_3 = (struct F *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    temp_s2_3->f60 = igFloatMetaField_GetDefaultDescriptor();
    temp_s2_3->f53 = 1;
    temp_s2_3->f64 = 1;
    temp_s2_3->f65 = 1;
    temp_s2_4 = (struct F *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    temp_s2_4->f56 = igMemoryPool_GetOrCreateMetaObject();
    temp_s2_4->f36 = 3;
    temp_s2_4->f38 = 0;
    temp_s2_4->f40 = 1;
    temp_s2_4->f39 = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igVertexArray1_1_fieldTable, g_igVertexArray1_1_fieldHandles, g_igVertexArray1_1_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igVertexArray1_1_metaObject) + 60) = (int)(&thunk_igPsx2VertexArray1_1_GetMetaObject);
}

