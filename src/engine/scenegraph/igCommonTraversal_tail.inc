static igMetaObjectCallback g_igCommonTraversal_callbackList[] = { igAttrStackManager_EnsureRegistered, igTransformStack_EnsureRegistered, igVisualContext_EnsureRegistered, igCapabilityManager_EnsureRegistered, igAttrDefaultManager_EnsureRegistered, igNonRefCountedAttrList_EnsureRegistered, igSorter_EnsureRegistered, igModelViewMatrixAttrPool_EnsureRegistered, igTimeAttrPool_EnsureRegistered, igVertexBlendMatrixAttrPool_EnsureRegistered, igTextureMatrixAttrPool_EnsureRegistered, igVertexBlendMatrixListAttrPool_EnsureRegistered, igMatrixObjectPool_EnsureRegistered, igProjectionMatrixAttrPool_EnsureRegistered, igMatrixOptStateAttr_EnsureRegistered, igNormalizeNormalsStateAttr_EnsureRegistered, igLongStack_EnsureRegistered, igNonRefCountedMatrixObjectList_EnsureRegistered, igNonRefCountedTransformList_EnsureRegistered, igIntList_EnsureRegistered, igStringObjList_EnsureRegistered, igNodeListList_EnsureRegistered, igBlendMatricesAttrPool_EnsureRegistered, igTimeAttr_EnsureRegistered, 0 };

CallbackArray *igCommonTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCommonTraversal_metaObject,
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        &igCommonTraversal_GetMetaObjectFunction,
        "igCommonTraversal",
        0x1D8, /* instance size */
        &igCommonTraversal_GetVTable,
        &igCommonTraversal_InitFields,
        &FUN_001a44d0, /* extra callback item */
        g_igCommonTraversal_callbackList /* callback list */
    );
}

void igCommonTraversal_GetMetaObjectFunction(void) {
    igCommonTraversal_GetMetaObject();
}

static FieldFactory g_igCommonTraversal_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igCommonTraversal_fieldTable[] = {
    "_attrStack",
    "_transformStack",
    "_vc",
    "_capabilityManager",
    "_defaultManager",
    "_flushedAttrs",
    "_sorter",
    "_matrixPool",
    "_timePool",
    "_blendMatrixPool",
    "_texMatPool",
    "_vertexBlendMatListPool",
    "_matrixObjectPool",
    "_projectionMatrixPool",
    "_viewMat",
    "_viewMatInv",
    "_modeMask",
    "_matrixOptimization",
    "_normalizeNormalsEnable",
    "_timeStack",
    "_matrixObjectList",
    "_timeLongBuf",
    "_timeBuffered",
    "_boneMatrixPaletteList",
    "_blendMatrixPaletteList",
    "_blendMatrixPaletteLengths",
    "_segmentOverrideNames",
    "_segmentOverrideStacks",
    "_blendMatricesAttrPool",
    "_projMat",
    "_defaultTimeAttr",
    "_jointChainCount",
    "_jointMvmBase",
    "_jointMvmInverseBase",
    "_jointGraphRootTraversed",
};
static igMetaField **g_igCommonTraversal_fieldHandles[] = {
    &g_igCommonTraversal_attrStackMetaField,
    &g_igCommonTraversal_transformStackMetaField,
    &g_igCommonTraversal_vcMetaField,
    &g_igCommonTraversal_capabilityManagerMetaField,
    &g_igCommonTraversal_defaultManagerMetaField,
    &g_igCommonTraversal_flushedAttrsMetaField,
    &g_igCommonTraversal_sorterMetaField,
    &g_igCommonTraversal_matrixPoolMetaField,
    &g_igCommonTraversal_timePoolMetaField,
    &g_igCommonTraversal_blendMatrixPoolMetaField,
    &g_igCommonTraversal_texMatPoolMetaField,
    &g_igCommonTraversal_vertexBlendMatListPoolMetaField,
    &g_igCommonTraversal_matrixObjectPoolMetaField,
    &g_igCommonTraversal_projectionMatrixPoolMetaField,
    &g_igCommonTraversal_viewMatMetaField,
    &g_igCommonTraversal_viewMatInvMetaField,
    &g_igCommonTraversal_modeMaskMetaField,
    &g_igCommonTraversal_matrixOptimizationMetaField,
    &g_igCommonTraversal_normalizeNormalsEnableMetaField,
    &g_igCommonTraversal_timeStackMetaField,
    &g_igCommonTraversal_matrixObjectListMetaField,
    &g_igCommonTraversal_timeLongBufMetaField,
    &g_igCommonTraversal_timeBufferedMetaField,
    &g_igCommonTraversal_boneMatrixPaletteListMetaField,
    &g_igCommonTraversal_blendMatrixPaletteListMetaField,
    &g_igCommonTraversal_blendMatrixPaletteLengthsMetaField,
    &g_igCommonTraversal_segmentOverrideNamesMetaField,
    &g_igCommonTraversal_segmentOverrideStacksMetaField,
    &g_igCommonTraversal_blendMatricesAttrPoolMetaField,
    &g_igCommonTraversal_projMatMetaField,
    &g_igCommonTraversal_defaultTimeAttrMetaField,
    &g_igCommonTraversal_jointChainCountMetaField,
    &g_igCommonTraversal_jointMvmBaseMetaField,
    &g_igCommonTraversal_jointMvmInverseBaseMetaField,
    &g_igCommonTraversal_jointGraphRootTraversedMetaField,
};
static int g_igCommonTraversal_fieldOffsets[] = {
    52,
    56,
    60,
    32,
    36,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
    164,
    228,
    232,
    236,
    240,
    244,
    40,
    48,
    248,
    252,
    256,
    260,
    264,
    268,
    272,
    336,
    340,
    344,
    408,
    49,
};

void igCommonTraversal_InitFields(void) {
    void *temp_v0;
    void *temp_s2_9;
    void *temp_s2_8;
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_30;
    void *temp_s2_2;
    void *temp_s2_29;
    void *temp_s2_28;
    void *temp_s2_27;
    void *temp_s2_26;
    void *temp_s2_25;
    void *temp_s2_24;
    void *temp_s2_23;
    void *temp_s2_22;
    void *temp_s2_21;
    void *temp_s2_20;
    void *temp_s2_19;
    void *temp_s2_18;
    void *temp_s2_17;
    void *temp_s2_16;
    void *temp_s2_15;
    void *temp_s2_14;
    void *temp_s2_13;
    void *temp_s2_12;
    void *temp_s2_11;
    void *temp_s2_10;
    void *temp_s2;
    int temp_s1;
    void *temp_s0;
    struct M_1a38e0 b1o;
    struct V b1a;
    struct V b1b;
    struct V b1c;
    struct V b1d;
    struct M_1a38e0 b2o;
    struct V b2a;
    struct V b2b;
    struct V b2c;
    struct V b2d;
    struct M_1a38e0 b3o;
    struct V b3a;
    struct V b3b;
    struct V b3c;
    struct V b3d;
    struct M_1a38e0 b4o;
    struct V b4a;
    struct V b4b;
    struct V b4c;
    struct V b4d;
    struct M_1a38e0 b5o;
    struct V b5a;
    struct V b5b;
    struct V b5c;
    struct V b5d;

    temp_s0 = (void *)g_igCommonTraversal_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCommonTraversal_ctorTable, 0x23);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igAttrStackManager_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igTransformStack_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igCapabilityManager_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igAttrDefaultManager_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igNonRefCountedAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = ((int)FUN_00196c10());
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igModelViewMatrixAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)igTimeAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)igVertexBlendMatrixAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)igTextureMatrixAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)igVertexBlendMatrixListAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = (int)igMatrixObjectPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = (int)igProjectionMatrixAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE)));
    b1d.x = 0;b1d.y = 0;b1d.z = 0;b1d.w = 0x3F800000;
    b1c.x = 0;b1c.y = 0;b1c.z = 0x3F800000;b1c.w = 0;
    b1b.x = 0;b1b.y = 0x3F800000;b1b.z = 0;b1b.w = 0;
    b1a.x = 0x3F800000;b1a.y = 0;b1a.z = 0;b1a.w = 0;
    igMatrix44f_FromRows((float *)&b1o, (igVec4f *)&b1a, (igVec4f *)&b1b, (igVec4f *)&b1c, (igVec4f *)&b1d);
    FUN_0018c640(temp_s2_15, &b1o);
    temp_s2_16 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF)));
    b2d.x = 0;b2d.y = 0;b2d.z = 0;b2d.w = 0x3F800000;
    b2c.x = 0;b2c.y = 0;b2c.z = 0x3F800000;b2c.w = 0;
    b2b.x = 0;b2b.y = 0x3F800000;b2b.z = 0;b2b.w = 0;
    b2a.x = 0x3F800000;b2a.y = 0;b2a.z = 0;b2a.w = 0;
    igMatrix44f_FromRows((float *)&b2o, (igVec4f *)&b2a, (igVec4f *)&b2b, (igVec4f *)&b2c, (igVec4f *)&b2d);
    FUN_0018c640(temp_s2_16, &b2o);
    temp_s2_17 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11)));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = igMatrixOptStateAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = igNormalizeNormalsStateAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = igLongStack_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = igNonRefCountedMatrixObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_20)->_construct = 1;
    ((igMetaField *)temp_s2_20)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15)));
    igLongMetaField_SetDefault((igMetaField *)temp_v0, -1);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x16)))->_persistent = 0;
    temp_s2_21 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x17)));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_21)->_construct = 1;
    ((igMetaField *)temp_s2_21)->_persistent = 0;
    temp_s2_22 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x18)));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_22)->_construct = 1;
    ((igMetaField *)temp_s2_22)->_persistent = 0;
    temp_s2_23 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x19)));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_23)->_construct = 1;
    ((igMetaField *)temp_s2_23)->_persistent = 0;
    temp_s2_24 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1A)));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_24)->_construct = 1;
    ((igMetaField *)temp_s2_24)->_persistent = 0;
    temp_s2_25 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1B)));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = (int)igNodeListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_25)->_construct = 1;
    ((igMetaField *)temp_s2_25)->_persistent = 0;
    temp_s2_26 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1C)));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = (int)igBlendMatricesAttrPool_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_26)->_construct = 1;
    ((igMetaField *)temp_s2_26)->_persistent = 0;
    temp_s2_27 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1D)));
    b3d.x = 0;b3d.y = 0;b3d.z = 0;b3d.w = 0x3F800000;
    b3c.x = 0;b3c.y = 0;b3c.z = 0x3F800000;b3c.w = 0;
    b3b.x = 0;b3b.y = 0x3F800000;b3b.z = 0;b3b.w = 0;
    b3a.x = 0x3F800000;b3a.y = 0;b3a.z = 0;b3a.w = 0;
    igMatrix44f_FromRows((float *)&b3o, (igVec4f *)&b3a, (igVec4f *)&b3b, (igVec4f *)&b3c, (igVec4f *)&b3d);
    FUN_0018c640(temp_s2_27, &b3o);
    temp_s2_28 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E)));
    ((igObjectRefMetaField *)temp_s2_28)->_metaObject = igTimeAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_28)->_construct = 1;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F)))->_persistent = 0;
    temp_s2_29 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x20)));
    b4d.x = 0;b4d.y = 0;b4d.z = 0;b4d.w = 0x3F800000;
    b4c.x = 0;b4c.y = 0;b4c.z = 0x3F800000;b4c.w = 0;
    b4b.x = 0;b4b.y = 0x3F800000;b4b.z = 0;b4b.w = 0;
    b4a.x = 0x3F800000;b4a.y = 0;b4a.z = 0;b4a.w = 0;
    igMatrix44f_FromRows((float *)&b4o, (igVec4f *)&b4a, (igVec4f *)&b4b, (igVec4f *)&b4c, (igVec4f *)&b4d);
    FUN_0018c640(temp_s2_29, &b4o);
    ((igMetaField *)temp_s2_29)->_persistent = 0;
    temp_s2_30 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x21)));
    b5d.x = 0;b5d.y = 0;b5d.z = 0;b5d.w = 0x3F800000;
    b5c.x = 0;b5c.y = 0;b5c.z = 0x3F800000;b5c.w = 0;
    b5b.x = 0;b5b.y = 0x3F800000;b5b.z = 0;b5b.w = 0;
    b5a.x = 0x3F800000;b5a.y = 0;b5a.z = 0;b5a.w = 0;
    igMatrix44f_FromRows((float *)&b5o, (igVec4f *)&b5a, (igVec4f *)&b5b, (igVec4f *)&b5c, (igVec4f *)&b5d);
    FUN_0018c640(temp_s2_30, &b5o);
    ((igMetaField *)temp_s2_30)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x22)))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCommonTraversal_fieldTable, g_igCommonTraversal_fieldHandles, g_igCommonTraversal_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)&thunk_igCommonTraversal_UserUnregister);
}

