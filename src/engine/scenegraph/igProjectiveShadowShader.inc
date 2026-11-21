igMetaObject *g_igProjectiveShadowShader_metaObject;
igMetaField *g_igProjectiveShadowShader_lightPosMetaField;
igMetaField *g_igProjectiveShadowShader_lightDirMetaField;
igMetaField *g_igProjectiveShadowShader_cutoffMetaField;
igMetaField *g_igProjectiveShadowShader_shadowCastersMetaField;
igMetaField *g_igProjectiveShadowShader_shadowReceiversMetaField;
igMetaField *g_igProjectiveShadowShader_shadowFactorMetaField;
igMetaField *g_igProjectiveShadowShader_shadowTexWMetaField;
igMetaField *g_igProjectiveShadowShader_shadowTexHMetaField;
igMetaField *g_igProjectiveShadowShader_shadowLightnessMetaField;
igMetaField *g_igProjectiveShadowShader_viewToProjectedLightTextureMatrixpAttrListMetaField;
igMetaField *g_igProjectiveShadowShader_lightMVMAttrMetaField;
igMetaField *g_igProjectiveShadowShader_lightProjAttrMetaField;
igMetaField *g_igProjectiveShadowShader_blurMVMAttrMetaField;
igMetaField *g_igProjectiveShadowShader_blurProjAttrMetaField;
igMetaField *g_igProjectiveShadowShader_initedMetaField;
igMetaField *g_igProjectiveShadowShader_quadsGeomMetaField;
igMetaField *g_igProjectiveShadowShader_unusedMetaField;
igMetaField *g_igProjectiveShadowShader_shadowColorMetaField;
igMetaField *g_igProjectiveShadowShader_blurStateMetaField;
igMetaField *g_igProjectiveShadowShader_zNearMetaField;
igMetaField *g_igProjectiveShadowShader_zFarMetaField;
igMetaField *g_igProjectiveShadowShader_upVectorMetaField;
igMetaField *g_igProjectiveShadowShader_viewToProjectedLightTextureMatrixMetaField;
igMetaField *g_igProjectiveShadowShader_drawReceiverMetaField;
igMetaField *g_igProjectiveShadowShader_updateShadowMapMetaField;
igMetaField *g_igProjectiveShadowShader_pShadowTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_pSetShadowTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_pShadowTexMetaField;
igMetaField *g_igProjectiveShadowShader_pShadowTexBindMetaField;
igMetaField *g_igProjectiveShadowShader_pBlurTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_pSetBlurTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_pBlurTexMetaField;
igMetaField *g_igProjectiveShadowShader_pBlurTexBindMetaField;
igMetaField *g_igProjectiveShadowShader_shadowCopyBackMetaField;
igMetaField *g_igProjectiveShadowShader_shadowCopyBackImageMetaField;
igMetaField *g_igProjectiveShadowShader_shadowViewportMetaField;
igMetaField *g_igProjectiveShadowShader_shadowInnerViewportMetaField;
igMetaField *g_igProjectiveShadowShader_lightMetaField;
igMetaField *g_igProjectiveShadowShader_pShadowTexBind1MetaField;
igMetaField *g_igProjectiveShadowShader_useOrthographicMetaField;
igMetaField *g_igProjectiveShadowShader_topMetaField;
igMetaField *g_igProjectiveShadowShader_bottomMetaField;
igMetaField *g_igProjectiveShadowShader_rightMetaField;
igMetaField *g_igProjectiveShadowShader_leftMetaField;
igMetaField *g_igProjectiveShadowShader_unloadShadowTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_unloadBlurTexRDMetaField;
igMetaField *g_igProjectiveShadowShader_releaseRenderDestinationAfterDrawMetaField;
igMetaField *g_igProjectiveShadowShader_useShadowFactorMetaField;

igMetaObject *igProjectiveShadowShader_GetOrCreateMetaObject(void) {
    if (g_igProjectiveShadowShader_metaObject == 0) {
        g_igProjectiveShadowShader_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igProjectiveShadowShader_metaObject;
}

igMetaObject *igProjectiveShadowShader_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igProjectiveShadowShader_metaObject != 0) {
        ready = (g_igProjectiveShadowShader_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igProjectiveShadowShader_EnsureRegistered();
done:
    return g_igProjectiveShadowShader_metaObject;
}

int igProjectiveShadowShader_GetVTable(void) {
    struct S_19b4e0 s;
    char *p392;
    int r;
    char *p388;
    char *p384;
    char *p380;
    char *p376;
    char *p372;
    char *p368;
    char *p364;
    char *p360;
    char *p356;
    char *p352;
    char *p348;
    char *p344;
    char *p340;
    FUN_0019acf0((igGroup *)&s);
    s.vt = &g_igProjectiveShadowShader_vtable[0];
    FUN_0019ace0((int)((char *)&s + 32));
    FUN_0019ace0((int)((char *)&s + 44));
    igSmartPointer_igNodeList_Construct((int *)((char *)&s + 60));
    igSmartPointer_igNodeList_Construct((int *)((char *)&s + 64));
    igSmartPointer_igNonRefCountedAttrList_Construct((int *)((char *)&s + 84));
    igSmartPointer_igModelViewMatrixAttr_Construct((int *)((char *)&s + 88));
    igSmartPointer_igProjectionMatrixAttr_Construct((int *)((char *)&s + 92));
    igSmartPointer_igModelViewMatrixAttr_Construct((int *)((char *)&s + 96));
    igSmartPointer_igProjectionMatrixAttr_Construct((int *)((char *)&s + 100));
    igSmartPointer_igGeometry_Construct((int *)((char *)&s + 108));
    igSmartPointer_igGeometryAttr_Construct((int *)((char *)&s + 112));
    igSmartPointer_igColorAttr_Construct((int *)((char *)&s + 116));
    FUN_0019ace0((int)((char *)&s + 132));
    igSmartPointer_igTextureMatrixAttr_Construct((int *)((char *)&s + 144));
    igSmartPointer_igRenderDestinationAttr_Construct((int *)((char *)&s + 152));
    igSmartPointer_igSetRenderDestinationAttr_Construct((int *)((char *)&s + 156));
    igSmartPointer_igTextureAttr_Construct((int *)((char *)&s + 160));
    igSmartPointer_igTextureBindAttr_Construct((int *)((char *)&s + 164));
    igSmartPointer_igRenderDestinationAttr_Construct((int *)((char *)&s + 168));
    igSmartPointer_igSetRenderDestinationAttr_Construct((int *)((char *)&s + 172));
    igSmartPointer_igTextureAttr_Construct((int *)((char *)&s + 176));
    p340 = (char *)&s + 180;
    igSmartPointer_igTextureBindAttr_Construct((int *)p340);
    p344 = (char *)&s + 184;
    igSmartPointer_igCopyRenderDestinationAttr_Construct((int *)p344);
    p348 = (char *)&s + 188;
    FUN_00132410((int *)p348);
    p352 = (char *)&s + 192;
    igSmartPointer_igViewportAttr_Construct((int *)p352);
    p356 = (char *)&s + 196;
    igSmartPointer_igViewportAttr_Construct((int *)p356);
    p360 = (char *)&s + 200;
    igSmartPointer_igLightAttr_Construct((int *)p360);
    p364 = (char *)&s + 204;
    igSmartPointer_igTextureBindAttr_Construct((int *)p364);
    p388 = (char *)&s + 228;
    igSmartPointer_igTextureUnloadAttr_Construct((int *)p388);
    p392 = (char *)&s + 232;
    igSmartPointer_igTextureUnloadAttr_Construct((int *)p392);
    r = *(int *)((char *)&s + g_objectSystem->vtableProbeOffset);
    s.vt = &g_igProjectiveShadowShader_vtable[0];
    FUN_001321b0((void **)p392, (long long)-1);
    FUN_001321b0((void **)p388, (long long)-1);
    igSmartPointer_igTextureBindAttr_Destruct((igSmartPointer<igObject> *)p364, -1);
    FUN_00136370((ObjectRefWord *)p360, -1);
    igSmartPointer_igViewportAttr_Destruct((igSmartPointer<igObject> *)p356, -1);
    igSmartPointer_igViewportAttr_Destruct((igSmartPointer<igObject> *)p352, -1);
    igSmartPointer_igImage_Destruct((igSmartPointer<igObject> *)p348, -1);
    igSmartPointer_igCopyRenderDestinationAttr_Destruct((igSmartPointer<igObject> *)p344, -1);
    igSmartPointer_igTextureBindAttr_Destruct((igSmartPointer<igObject> *)p340, -1);
    igSmartPointer_igTextureAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 176), -1);
    igSmartPointer_igSetRenderDestinationAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 172), -1);
    FUN_00133ca0((ObjectRefWord *)((char *)&s + 168), -1);
    igSmartPointer_igTextureBindAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 164), -1);
    igSmartPointer_igTextureAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 160), -1);
    igSmartPointer_igSetRenderDestinationAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 156), -1);
    FUN_00133ca0((ObjectRefWord *)((char *)&s + 152), -1);
    igSmartPointer_igTextureMatrixAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 144), -1);
    igSmartPointer_igColorAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 116), -1);
    igSmartPointer_igGeometryAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 112), -1);
    igSmartPointer_igGeometry_Destruct((igSmartPointer<igObject> *)((char *)&s + 108), -1);
    igSmartPointer_igProjectionMatrixAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 100), -1);
    igSmartPointer_igModelViewMatrixAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 96), -1);
    igSmartPointer_igProjectionMatrixAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 92), -1);
    igSmartPointer_igModelViewMatrixAttr_Destruct((igSmartPointer<igObject> *)((char *)&s + 88), -1);
    FUN_001380e0((void **)((char *)&s + 84), (short)-1);
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)((char *)&s + 64), -1);
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)((char *)&s + 60), -1);
    igGroup_Destroy((igGroup *)&s, 0);
    return r;
}

int *igSmartPointer_igTextureUnloadAttr_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igGeometryAttr_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void igProjectiveShadowShader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igProjectiveShadowShader_Register);
}

static igMetaObjectCallback g_igProjectiveShadowShader_callbackList[] = { igNodeList_EnsureRegistered, igNonRefCountedAttrList_EnsureRegistered, Gap::Attrs::igModelViewMatrixAttr::arkRegister, Gap::Attrs::igProjectionMatrixAttr::arkRegister, igGeometry_EnsureRegistered, igGeometryAttr_EnsureRegistered, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igTextureMatrixAttr::arkRegister, igRenderDestinationAttr_EnsureRegistered, igSetRenderDestinationAttr_EnsureRegistered, igTextureAttr_EnsureRegistered, igTextureBindAttr_EnsureRegistered, igCopyRenderDestinationAttr_EnsureRegistered, igImage_EnsureRegistered, Gap::Attrs::igViewportAttr::arkRegister, igLightAttr_EnsureRegistered, Gap::Attrs::igTextureUnloadAttr::arkRegister, 0 };

CallbackArray *igProjectiveShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igProjectiveShadowShader_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igProjectiveShadowShader_GetMetaObjectFunction,
        "igProjectiveShadowShader",
        0xF0, /* instance size */
        igProjectiveShadowShader_GetVTable,
        &igProjectiveShadowShader_InitFields,
        0, /* extra callback item */
        g_igProjectiveShadowShader_callbackList /* callback list */
    );
}

void igProjectiveShadowShader_GetMetaObjectFunction(void) {
    igProjectiveShadowShader_GetMetaObject();
}

static FieldFactory g_igProjectiveShadowShader_ctorTable[] = {
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
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
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igProjectiveShadowShader_fieldTable[] = {
    "_lightPos",
    "_lightDir",
    "_cutoff",
    "_shadowCasters",
    "_shadowReceivers",
    "_shadowFactor",
    "_shadowTexW",
    "_shadowTexH",
    "_shadowLightness",
    "_viewToProjectedLightTextureMatrixpAttrList",
    "_lightMVMAttr",
    "_lightProjAttr",
    "_blurMVMAttr",
    "_blurProjAttr",
    "_inited",
    "_quadsGeom",
    "_unused",
    "_shadowColor",
    "_blurState",
    "_zNear",
    "_zFar",
    "_upVector",
    "_viewToProjectedLightTextureMatrix",
    "_drawReceiver",
    "_updateShadowMap",
    "_pShadowTexRD",
    "_pSetShadowTexRD",
    "_pShadowTex",
    "_pShadowTexBind",
    "_pBlurTexRD",
    "_pSetBlurTexRD",
    "_pBlurTex",
    "_pBlurTexBind",
    "_shadowCopyBack",
    "_shadowCopyBackImage",
    "_shadowViewport",
    "_shadowInnerViewport",
    "_light",
    "_pShadowTexBind1",
    "_useOrthographic",
    "_top",
    "_bottom",
    "_right",
    "_left",
    "_unloadShadowTexRD",
    "_unloadBlurTexRD",
    "_releaseRenderDestinationAfterDraw",
    "_useShadowFactor",
};
static igMetaField **g_igProjectiveShadowShader_fieldHandles[] = {
    &g_igProjectiveShadowShader_lightPosMetaField,
    &g_igProjectiveShadowShader_lightDirMetaField,
    &g_igProjectiveShadowShader_cutoffMetaField,
    &g_igProjectiveShadowShader_shadowCastersMetaField,
    &g_igProjectiveShadowShader_shadowReceiversMetaField,
    &g_igProjectiveShadowShader_shadowFactorMetaField,
    &g_igProjectiveShadowShader_shadowTexWMetaField,
    &g_igProjectiveShadowShader_shadowTexHMetaField,
    &g_igProjectiveShadowShader_shadowLightnessMetaField,
    &g_igProjectiveShadowShader_viewToProjectedLightTextureMatrixpAttrListMetaField,
    &g_igProjectiveShadowShader_lightMVMAttrMetaField,
    &g_igProjectiveShadowShader_lightProjAttrMetaField,
    &g_igProjectiveShadowShader_blurMVMAttrMetaField,
    &g_igProjectiveShadowShader_blurProjAttrMetaField,
    &g_igProjectiveShadowShader_initedMetaField,
    &g_igProjectiveShadowShader_quadsGeomMetaField,
    &g_igProjectiveShadowShader_unusedMetaField,
    &g_igProjectiveShadowShader_shadowColorMetaField,
    &g_igProjectiveShadowShader_blurStateMetaField,
    &g_igProjectiveShadowShader_zNearMetaField,
    &g_igProjectiveShadowShader_zFarMetaField,
    &g_igProjectiveShadowShader_upVectorMetaField,
    &g_igProjectiveShadowShader_viewToProjectedLightTextureMatrixMetaField,
    &g_igProjectiveShadowShader_drawReceiverMetaField,
    &g_igProjectiveShadowShader_updateShadowMapMetaField,
    &g_igProjectiveShadowShader_pShadowTexRDMetaField,
    &g_igProjectiveShadowShader_pSetShadowTexRDMetaField,
    &g_igProjectiveShadowShader_pShadowTexMetaField,
    &g_igProjectiveShadowShader_pShadowTexBindMetaField,
    &g_igProjectiveShadowShader_pBlurTexRDMetaField,
    &g_igProjectiveShadowShader_pSetBlurTexRDMetaField,
    &g_igProjectiveShadowShader_pBlurTexMetaField,
    &g_igProjectiveShadowShader_pBlurTexBindMetaField,
    &g_igProjectiveShadowShader_shadowCopyBackMetaField,
    &g_igProjectiveShadowShader_shadowCopyBackImageMetaField,
    &g_igProjectiveShadowShader_shadowViewportMetaField,
    &g_igProjectiveShadowShader_shadowInnerViewportMetaField,
    &g_igProjectiveShadowShader_lightMetaField,
    &g_igProjectiveShadowShader_pShadowTexBind1MetaField,
    &g_igProjectiveShadowShader_useOrthographicMetaField,
    &g_igProjectiveShadowShader_topMetaField,
    &g_igProjectiveShadowShader_bottomMetaField,
    &g_igProjectiveShadowShader_rightMetaField,
    &g_igProjectiveShadowShader_leftMetaField,
    &g_igProjectiveShadowShader_unloadShadowTexRDMetaField,
    &g_igProjectiveShadowShader_unloadBlurTexRDMetaField,
    &g_igProjectiveShadowShader_releaseRenderDestinationAfterDrawMetaField,
    &g_igProjectiveShadowShader_useShadowFactorMetaField,
};
static int g_igProjectiveShadowShader_fieldOffsets[] = {
    32,
    44,
    56,
    60,
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
    104,
    108,
    112,
    116,
    120,
    124,
    128,
    132,
    144,
    148,
    149,
    152,
    156,
    160,
    164,
    168,
    172,
    176,
    180,
    184,
    188,
    192,
    196,
    200,
    204,
    208,
    212,
    216,
    220,
    224,
    228,
    232,
    236,
    237,
};

void igProjectiveShadowShader_InitFields(void) {
    float v1[4];
    float v2[4];
    float v3[4];
    int temp_s1;
    void *temp_s0;
    struct Fld_19b8a0 *temp_a0;
    struct Fld_19b8a0 *temp_s2;
    struct Fld_19b8a0 *temp_v0;

    temp_s0 = (void *)g_igProjectiveShadowShader_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igProjectiveShadowShader_ctorTable, 0x30);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    v1[0] = 0; v1[1] = 4.0f; v1[2] = 0;
    ((Gap::Math::igVec3fMetaField *)temp_a0)->setDefault(*(const igVec3f *)v1);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    v2[0] = 0; v2[1] = -1.0f; v2[2] = 0;
    ((Gap::Math::igVec3fMetaField *)temp_a0)->setDefault(*(const igVec3f *)v2);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)))->setDefault(30.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    temp_s2->f56 = (int)igNodeList_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    temp_s2->f56 = (int)igNodeList_GetOrCreateMetaObject();
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)))->setDefault(0.300000012f);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)))->setDefault(0x80);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)))->setDefault(0x80);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->setDefault(0.5f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    temp_s2->f56 = (int)igNonRefCountedAttrList_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA));
    temp_s2->f56 = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB));
    temp_s2->f56 = (int)Gap::Attrs::igProjectionMatrixAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC));
    temp_s2->f56 = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD));
    temp_s2->f56 = (int)Gap::Attrs::igProjectionMatrixAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE));
    ((Gap::Core::igIntMetaField *)temp_v0)->setDefault(0);
    temp_v0->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF));
    temp_s2->f56 = (int)igGeometry_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10));
    temp_s2->f56 = (int)igGeometryAttr_GetOrCreateMetaObject();
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11));
    temp_s2->f56 = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12)))->setDefault(1);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x13)))->setDefault(0.100000001f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14)))->setDefault(1000.0f);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15));
    v3[0] = 1.0f; v3[1] = 0; v3[2] = 0;
    ((Gap::Math::igVec3fMetaField *)temp_a0)->setDefault(*(const igVec3f *)v3);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x16));
    temp_s2->f56 = (int)Gap::Attrs::igTextureMatrixAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x17)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x18)))->setDefault(1);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x19));
    temp_s2->f56 = (int)igRenderDestinationAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1A));
    temp_s2->f56 = (int)igSetRenderDestinationAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1B));
    temp_s2->f56 = (int)igTextureAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1C));
    temp_s2->f56 = (int)igTextureBindAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1D));
    temp_s2->f56 = (int)igRenderDestinationAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E));
    temp_s2->f56 = (int)igSetRenderDestinationAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F));
    temp_s2->f56 = (int)igTextureAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x20));
    temp_s2->f56 = (int)igTextureBindAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x21));
    temp_s2->f56 = (int)igCopyRenderDestinationAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x22));
    temp_s2->f56 = (int)igImage_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x23));
    temp_s2->f56 = (int)Gap::Attrs::igViewportAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x24));
    temp_s2->f56 = (int)Gap::Attrs::igViewportAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x25));
    temp_s2->f56 = (int)igLightAttr_GetOrCreateMetaObject();
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x26));
    temp_s2->f56 = (int)igTextureBindAttr_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x28)))->setDefault(5.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x29)))->setDefault(-5.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x2A)))->setDefault(5.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x2B)))->setDefault(-5.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x2C));
    temp_s2->f56 = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x2D));
    temp_s2->f56 = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x2F));
    ((Gap::Core::igBoolMetaField *)temp_v0)->setDefault(1);
    temp_v0->f38 = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igProjectiveShadowShader_fieldTable, g_igProjectiveShadowShader_fieldHandles, g_igProjectiveShadowShader_fieldOffsets, temp_s1);
}

