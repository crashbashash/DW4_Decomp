igMetaObject *g_igCompressedTransformSequence1_5Data_metaObject;
igMetaField *g_igCompressedTransformSequence1_5Data_compressedTranslationListMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_compressedQuatListMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_compressedScaleListMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_compressedTimeListMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_translationBaseMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_translationRangeMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_quatBaseMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_quatRangeMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_scaleBaseMetaField;
igMetaField *g_igCompressedTransformSequence1_5Data_scaleRangeMetaField;

igMetaObject *igCompressedTransformSequence1_5Data_GetOrCreateMetaObject(void) {
    if (g_igCompressedTransformSequence1_5Data_metaObject == 0) {
        g_igCompressedTransformSequence1_5Data_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCompressedTransformSequence1_5Data_metaObject;
}

igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void)
{
    igMetaObject *g = g_igCompressedTransformSequence1_5Data_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCompressedTransformSequence1_5Data_EnsureRegistered();
    return g_igCompressedTransformSequence1_5Data_metaObject;
}

int igCompressedTransformSequence1_5Data_GetVTable(void) {
    struct Obj_1a2590 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCompressedTransformSequence1_5Data_vtable[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igCompressedTransformSequence1_5Data_vtable[0];
    FUN_00164870(&obj.w5, -1);
    FUN_00164870(&obj.w4, -1);
    FUN_00164870(&obj.w3, -1);
    FUN_00164870(&obj.w2, -1);
    return t;
}

void igCompressedTransformSequence1_5Data_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCompressedTransformSequence1_5Data_Register);
}

static igMetaObjectCallback g_igCompressedTransformSequence1_5Data_callbackList[] = { igUnsignedShortList_EnsureRegistered, 0 };

CallbackArray *igCompressedTransformSequence1_5Data_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompressedTransformSequence1_5Data_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCompressedTransformSequence1_5Data_GetMetaObjectFunction,
        "igCompressedTransformSequence1_5Data",
        0x30, /* instance size */
        igCompressedTransformSequence1_5Data_GetVTable,
        &igCompressedTransformSequence1_5Data_InitFields,
        0, /* extra callback item */
        g_igCompressedTransformSequence1_5Data_callbackList /* callback list */
    );
}

void igCompressedTransformSequence1_5Data_GetMetaObjectFunction(void) {
    igCompressedTransformSequence1_5Data_GetMetaObject();
}

static FieldFactory g_igCompressedTransformSequence1_5Data_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igCompressedTransformSequence1_5Data_fieldTable[] = {
    "_compressedTranslationList",
    "_compressedQuatList",
    "_compressedScaleList",
    "_compressedTimeList",
    "_translationBase",
    "_translationRange",
    "_quatBase",
    "_quatRange",
    "_scaleBase",
    "_scaleRange",
};
static igMetaField **g_igCompressedTransformSequence1_5Data_fieldHandles[] = {
    &g_igCompressedTransformSequence1_5Data_compressedTranslationListMetaField,
    &g_igCompressedTransformSequence1_5Data_compressedQuatListMetaField,
    &g_igCompressedTransformSequence1_5Data_compressedScaleListMetaField,
    &g_igCompressedTransformSequence1_5Data_compressedTimeListMetaField,
    &g_igCompressedTransformSequence1_5Data_translationBaseMetaField,
    &g_igCompressedTransformSequence1_5Data_translationRangeMetaField,
    &g_igCompressedTransformSequence1_5Data_quatBaseMetaField,
    &g_igCompressedTransformSequence1_5Data_quatRangeMetaField,
    &g_igCompressedTransformSequence1_5Data_scaleBaseMetaField,
    &g_igCompressedTransformSequence1_5Data_scaleRangeMetaField,
};
static int g_igCompressedTransformSequence1_5Data_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void igCompressedTransformSequence1_5Data_InitFields(void) {
    int base;
    void *compressedTimeListField;
    void *compressedScaleListField;
    void *compressedQuatListField;
    void *compressedTranslationListField;
    void *meta;

    meta = (void *)g_igCompressedTransformSequence1_5Data_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCompressedTransformSequence1_5Data_ctorTable, 0xA);
    compressedTranslationListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)compressedTranslationListField)->_metaObject = (int)igUnsignedShortList_GetOrCreateMetaObject();
    compressedQuatListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)compressedQuatListField)->_metaObject = (int)igUnsignedShortList_GetOrCreateMetaObject();
    compressedScaleListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)compressedScaleListField)->_metaObject = (int)igUnsignedShortList_GetOrCreateMetaObject();
    compressedTimeListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)compressedTimeListField)->_metaObject = (int)igUnsignedShortList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igCompressedTransformSequence1_5Data_fieldTable, g_igCompressedTransformSequence1_5Data_fieldHandles, g_igCompressedTransformSequence1_5Data_fieldOffsets, base);
}

