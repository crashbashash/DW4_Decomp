igMetaObject *g_igVisualContext_metaObject;
igMetaField *g_igVisualContext_contextIndexMetaField;
igMetaField *g_igVisualContext_timerMetaField;
igMetaField *g_igVisualContext_showFrameRateMetaField;
igMetaField *g_igVisualContext_commandLineFrameRateMetaField;
igMetaField *g_igVisualContext_primitiveCountMetaField;
igMetaField *g_igVisualContext_frameStartTimeMetaField;
igMetaField *g_igVisualContext_blendMatricesCountMetaField;
igMetaField *g_igVisualContext_blendIndexMetaField;
igMetaField *g_igVisualContext_inverseTransposeMetaField;
igMetaField *g_igVisualContext_blendMatricesMetaField;
igMetaField *g_igVisualContext_inverseTransposeCountMetaField;
igMetaField *g_igVisualContext_renderingTimeMetaField;
igMetaField *g_igVisualContext_scissorTypeMetaField;
igMetaField *g_igVisualContext_viewMatrixHintMetaField;
igMetaField *g_igVisualContext_viewMatrixInverseMetaField;
igMetaField *g_igVisualContext_viewMatrixDirtyMetaField;
igMetaField *g_igVisualContext_vertexArray2MetaField;
igMetaField *g_igVisualContext_customStatesMetaField;
igMetaField *g_igVisualContext_customFieldsMetaField;
igMetaField *g_igVisualContext_ditherStateMetaField;
igMetaField *g_igVisualContext_driverDataMemoryPoolMetaField;
igMetaField *g_igVisualContext_vertexMemoryPoolMetaField;
igMetaField *g_igVisualContext_internalMemoryPoolMetaField;
igMetaField *g_igVisualContext_temporaryMemoryPoolMetaField;
igMetaField *g_igVisualContext_imageMemoryPoolMetaField;
igMetaField *g_igVisualContext_textureMemoryPoolMetaField;
igMetaField *g_igVisualContext_statisticsMemoryPoolMetaField;
igMetaField *g_igVisualContext_listMemoryPoolMetaField;

igVisualContext *igVisualContext_CreateInstance(int allocator) {
    igVisualContext_EnsureRegistered();
    return (igVisualContext *)igMetaObject_CreateInstance(g_igVisualContext_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igVisualContext_GetOrCreateMetaObject(void) {
    if (g_igVisualContext_metaObject == 0) {
        g_igVisualContext_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVisualContext_metaObject;
}

igMetaObject *igVisualContext_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContext_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVisualContext_EnsureRegistered();
    return g_igVisualContext_metaObject;
}

void igVisualContext_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVisualContext_Register);
}

static igMetaObjectCallback g_igVisualContext_callbackList[] = { igTimer_EnsureRegistered, FUN_0014ab70, FUN_0014ef20, FUN_0014ea50, igMemoryPool_EnsureRegistered, 0 };

CallbackArray *igVisualContext_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igVisualContext_metaObject,
        igContext_Register,
        igContext_GetPublishedMetaObject,
        thunk_igVisualContext_GetMetaObject,
        "igVisualContext",
        0x140, /* instance size */
        0,
        &igVisualContext_InitFields,
        0, /* extra callback item */
        g_igVisualContext_callbackList /* callback list */
    );
}

void thunk_igVisualContext_GetMetaObject(void) {
    igVisualContext_GetMetaObject();
}

int FUN_0014a170(void) {
    return g_igContext_metaObject[0];
}

static FieldFactory g_igVisualContext_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefArrayMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igVisualContext_fieldTable[] = {
    "_contextIndex",
    "_timer",
    "_showFrameRate",
    "_commandLineFrameRate",
    "_primitiveCount",
    "_frameStartTime",
    "_blendMatricesCount",
    "_blendIndex",
    "_inverseTranspose",
    "_blendMatrices",
    "_inverseTransposeCount",
    "_renderingTime",
    "_scissorType",
    "_viewMatrixHint",
    "_viewMatrixInverse",
    "_viewMatrixDirty",
    "_vertexArray2",
    "_customStates",
    "_customFields",
    "_ditherState",
    "_driverDataMemoryPool",
    "_vertexMemoryPool",
    "_internalMemoryPool",
    "_temporaryMemoryPool",
    "_imageMemoryPool",
    "_textureMemoryPool",
    "_statisticsMemoryPool",
    "_listMemoryPool",
};
static igMetaField **g_igVisualContext_fieldHandles[] = {
    &g_igVisualContext_contextIndexMetaField,
    &g_igVisualContext_timerMetaField,
    &g_igVisualContext_showFrameRateMetaField,
    &g_igVisualContext_commandLineFrameRateMetaField,
    &g_igVisualContext_primitiveCountMetaField,
    &g_igVisualContext_frameStartTimeMetaField,
    &g_igVisualContext_blendMatricesCountMetaField,
    &g_igVisualContext_blendIndexMetaField,
    &g_igVisualContext_inverseTransposeMetaField,
    &g_igVisualContext_blendMatricesMetaField,
    &g_igVisualContext_inverseTransposeCountMetaField,
    &g_igVisualContext_renderingTimeMetaField,
    &g_igVisualContext_scissorTypeMetaField,
    &g_igVisualContext_viewMatrixHintMetaField,
    &g_igVisualContext_viewMatrixInverseMetaField,
    &g_igVisualContext_viewMatrixDirtyMetaField,
    &g_igVisualContext_vertexArray2MetaField,
    &g_igVisualContext_customStatesMetaField,
    &g_igVisualContext_customFieldsMetaField,
    &g_igVisualContext_ditherStateMetaField,
    &g_igVisualContext_driverDataMemoryPoolMetaField,
    &g_igVisualContext_vertexMemoryPoolMetaField,
    &g_igVisualContext_internalMemoryPoolMetaField,
    &g_igVisualContext_temporaryMemoryPoolMetaField,
    &g_igVisualContext_imageMemoryPoolMetaField,
    &g_igVisualContext_textureMemoryPoolMetaField,
    &g_igVisualContext_statisticsMemoryPoolMetaField,
    &g_igVisualContext_listMemoryPoolMetaField,
};
static int g_igVisualContext_fieldOffsets[] = {
    20,
    56,
    60,
    61,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    96,
    104,
    108,
    172,
    236,
    240,
    304,
    308,
    312,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void igVisualContext_InitFields(void) {
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    int fieldStart;
    igMetaObject *meta;

    meta = g_igVisualContext_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVisualContext_ctorTable, 0x1C);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart), -1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igTimer_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_resetMethod = 3;
    ((igIntMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 6))->_persistent = 0;
    ((igUnsignedIntMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 7))->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 8));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = FUN_001888e0();
    ((igMemoryRefMetaField *)temp_s2_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnReset = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_persistent = 0;
    ((igRawRefMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 9))->_persistent = 0;
    ((igUnsignedIntMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xA))->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xB));
    igLongMetaField_SetDefault(temp_v0, 0);
    ((igLongMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xC));
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_00149440);
    ((igMatrix44fMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xD))->_persistent = 0;
    ((igMatrix44fMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0xE))->_persistent = 0;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0xF));
    igBoolMetaField_SetDefaultValue(temp_v0_3, 1);
    ((igBoolMetaField *)temp_v0_3)->_persistent = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x10));
    ((igObjectRefArrayMetaField *)temp_s2_3)->_metaObject = (int)FUN_0014a7c0();
    ((igObjectRefArrayMetaField *)temp_s2_3)->_num = 0x10;
    ((igObjectRefArrayMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x11));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0014ee40();
    ((igObjectRefMetaField *)temp_s2_4)->_resetMethod = 3;
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x12));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0014e970();
    ((igObjectRefMetaField *)temp_s2_5)->_resetMethod = 3;
    ((igObjectRefMetaField *)temp_s2_5)->_persistent = 0;
    ((igBoolMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x13))->_persistent = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x14));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_6)->_resetMethod = 3;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x15));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_7)->_resetMethod = 3;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x16));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_8)->_resetMethod = 3;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x17));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_9)->_resetMethod = 3;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x18));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_10)->_resetMethod = 3;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x19));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_11)->_resetMethod = 3;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x1A));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_12)->_resetMethod = 3;
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 0x1B));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_13)->_resetMethod = 3;
    igMetaObject_NameFields(meta, g_igVisualContext_fieldTable, g_igVisualContext_fieldHandles, g_igVisualContext_fieldOffsets, fieldStart);
    ((igMetaObject *)g_igVisualContext_metaObject)->_abstractProxy = (int)(&thunk_igPsx2VisualContext_GetMetaObject);
}

