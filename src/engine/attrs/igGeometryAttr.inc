igMetaObject *g_igGeometryAttr_metaObject;
igMetaField *g_igGeometryAttr_vertexArrayMetaField;
igMetaField *g_igGeometryAttr_indexArrayMetaField;
igMetaField *g_igGeometryAttr_primTypeMetaField;
igMetaField *g_igGeometryAttr_numPrimsMetaField;
igMetaField *g_igGeometryAttr_offsetMetaField;
igMetaField *g_igGeometryAttr_primLengthsMetaField;
igMetaField *g_igGeometryAttr_handleMetaField;
igMetaField *g_igGeometryAttr_dPdsMetaField;
igMetaField *g_igGeometryAttr_dPdtMetaField;

igGeometryAttr *igGeometryAttr_Create(int allocator) {
    FUN_001378f0();
    return (igGeometryAttr *)igMetaObject_CreateInstance(*(igMetaObject * *)0x55F170, (igMemoryPoolView *)allocator);
}

igMetaObject *FUN_00137850(void) {
    if (g_igGeometryAttr_metaObject == 0) {
        g_igGeometryAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGeometryAttr_metaObject;
}

igMetaObject *igGeometryAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001378f0();
    return g_igGeometryAttr_metaObject;
}

void FUN_001378f0(void)
{
    igMetaObject_RunStaticInit(igGeometryAttr_Register);
}

static igMetaObjectCallback g_igGeometryAttr_callbackList[] = { igVertexArray_EnsureRegistered, igIndexArray_EnsureRegistered, igUnsignedIntList_EnsureRegistered, igVec3fList_EnsureRegistered, 0 };

CallbackArray *igGeometryAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igGeometryAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryAttr_GetMetaObject,
        "igGeometryAttr",
        0x30, /* instance size */
        0,
        &igGeometryAttr_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr_callbackList /* callback list */
    );
}

void thunk_igGeometryAttr_GetMetaObject(void) {
    igGeometryAttr_GetMetaObject();
}

static FieldFactory g_igGeometryAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igGeometryAttr_fieldTable[] = {
    "_vertexArray",
    "_indexArray",
    "_primType",
    "_numPrims",
    "_offset",
    "_primLengths",
    "_handle",
    "_dPds",
    "_dPdt",
};
static igMetaField **g_igGeometryAttr_fieldHandles[] = {
    &g_igGeometryAttr_vertexArrayMetaField,
    &g_igGeometryAttr_indexArrayMetaField,
    &g_igGeometryAttr_primTypeMetaField,
    &g_igGeometryAttr_numPrimsMetaField,
    &g_igGeometryAttr_offsetMetaField,
    &g_igGeometryAttr_primLengthsMetaField,
    &g_igGeometryAttr_handleMetaField,
    &g_igGeometryAttr_dPdsMetaField,
    &g_igGeometryAttr_dPdtMetaField,
};
static int g_igGeometryAttr_fieldOffsets[] = {
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

void igGeometryAttr_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_v0;
    igMetaObject *temp_s1;

    temp_s1 = g_igGeometryAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igGeometryAttr_ctorTable, 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014d7f0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igUnsignedIntList_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s1, g_igGeometryAttr_fieldTable, g_igGeometryAttr_fieldHandles, g_igGeometryAttr_fieldOffsets, temp_s0);
    *(int *)((char *)(g_igGeometryAttr_metaObject) + 60) = (int)thunk_igGeometryAttr1_5_GetMetaObject;
}

