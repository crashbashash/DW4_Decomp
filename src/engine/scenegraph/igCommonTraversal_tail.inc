static igMetaObjectCallback g_igCommonTraversal_callbackList[] = { igAttrStackManager_EnsureRegistered, igTransformStack_EnsureRegistered, igVisualContext_EnsureRegistered, igCapabilityManager_EnsureRegistered, igAttrDefaultManager_EnsureRegistered, igNonRefCountedAttrList_EnsureRegistered, igSorter_EnsureRegistered, igModelViewMatrixAttrPool_EnsureRegistered, igTimeAttrPool_EnsureRegistered, igVertexBlendMatrixAttrPool_EnsureRegistered, igTextureMatrixAttrPool_EnsureRegistered, igVertexBlendMatrixListAttrPool_EnsureRegistered, igMatrixObjectPool_EnsureRegistered, igProjectionMatrixAttrPool_EnsureRegistered, Gap::Attrs::igMatrixOptStateAttr::arkRegister, Gap::Attrs::igNormalizeNormalsStateAttr::arkRegister, igLongStack_EnsureRegistered, igNonRefCountedMatrixObjectList_EnsureRegistered, igNonRefCountedTransformList_EnsureRegistered, Gap::Core::igIntList::arkRegister, igStringObjList_EnsureRegistered, igNodeListList_EnsureRegistered, igBlendMatricesAttrPool_EnsureRegistered, Gap::Attrs::igTimeAttr::arkRegister, 0 };

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
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
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
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
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
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igCapabilityManager_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igAttrDefaultManager_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igNonRefCountedAttrList_GetOrCreateMetaObject();
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
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_15)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                        igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    temp_s2_16 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_16)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                        igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    temp_s2_17 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11)));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = (int)Gap::Attrs::igMatrixOptStateAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = (int)Gap::Attrs::igNormalizeNormalsStateAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = (int)igLongStack_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = (int)igNonRefCountedMatrixObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_20)->_construct = 1;
    ((igMetaField *)temp_s2_20)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15)));
    ((Gap::Core::igLongMetaField *)temp_v0)->setDefault(-1);
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
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
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
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_27)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                        igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    temp_s2_28 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E)));
    ((igObjectRefMetaField *)temp_s2_28)->_metaObject = (int)Gap::Attrs::igTimeAttr::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_28)->_construct = 1;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F)))->_persistent = 0;
    temp_s2_29 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x20)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_29)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                        igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((igMetaField *)temp_s2_29)->_persistent = 0;
    temp_s2_30 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x21)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_30)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                        igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((igMetaField *)temp_s2_30)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x22)))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCommonTraversal_fieldTable, g_igCommonTraversal_fieldHandles, g_igCommonTraversal_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)&thunk_igCommonTraversal_UserUnregister);
}

