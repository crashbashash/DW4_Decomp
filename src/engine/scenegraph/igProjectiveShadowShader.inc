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

igMetaObject *FUN_0019b440(void) {
    if (g_igProjectiveShadowShader_metaObject == 0) {
        g_igProjectiveShadowShader_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    FUN_0019b800();
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
    s.vt = &DAT_00528950[0];
    FUN_0019ace0((int)((char *)&s + 32));
    FUN_0019ace0((int)((char *)&s + 44));
    FUN_0019acd0((int *)((char *)&s + 60));
    FUN_0019acd0((int *)((char *)&s + 64));
    FUN_00197330((int *)((char *)&s + 84));
    FUN_0019acc0((int *)((char *)&s + 88));
    FUN_0019acb0((int *)((char *)&s + 92));
    FUN_0019acc0((int *)((char *)&s + 96));
    FUN_0019acb0((int *)((char *)&s + 100));
    FUN_001972e0((int *)((char *)&s + 108));
    FUN_0019b7f0((int *)((char *)&s + 112));
    FUN_0019ac10((int *)((char *)&s + 116));
    FUN_0019ace0((int)((char *)&s + 132));
    FUN_0019aca0((int *)((char *)&s + 144));
    FUN_0019ac90((int *)((char *)&s + 152));
    FUN_0019ac80((int *)((char *)&s + 156));
    FUN_0019ac70((int *)((char *)&s + 160));
    FUN_0019ac60((int *)((char *)&s + 164));
    FUN_0019ac90((int *)((char *)&s + 168));
    FUN_0019ac80((int *)((char *)&s + 172));
    FUN_0019ac70((int *)((char *)&s + 176));
    p340 = (char *)&s + 180;
    FUN_0019ac60((int *)p340);
    p344 = (char *)&s + 184;
    FUN_0019ac50((int *)p344);
    p348 = (char *)&s + 188;
    FUN_00132410(p348);
    p352 = (char *)&s + 192;
    FUN_0019ac40((int *)p352);
    p356 = (char *)&s + 196;
    FUN_0019ac40((int *)p356);
    p360 = (char *)&s + 200;
    FUN_0019ac30((int *)p360);
    p364 = (char *)&s + 204;
    FUN_0019ac60((int *)p364);
    p388 = (char *)&s + 228;
    FUN_0019b7e0((int *)p388);
    p392 = (char *)&s + 232;
    FUN_0019b7e0((int *)p392);
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    s.vt = &DAT_00528950[0];
    FUN_001321b0(p392, -1);
    FUN_001321b0(p388, -1);
    FUN_0019aa10((struct Ref * *)p364, -1);
    FUN_00136370(p360, -1);
    FUN_0019ab90((ObjectRefWord *)p356, -1);
    FUN_0019ab90((ObjectRefWord *)p352, -1);
    FUN_00132390(p348, -1);
    FUN_0019a990((void * *)p344, -1);
    FUN_0019aa10((struct Ref * *)p340, -1);
    FUN_00132980((char *)&s + 176, -1);
    FUN_0019a910((void * *)((char *)&s + 172), -1);
    FUN_00133ca0((char *)&s + 168, -1);
    FUN_0019aa10((struct Ref * *)((char *)&s + 164), -1);
    FUN_00132980((char *)&s + 160, -1);
    FUN_0019a910((void * *)((char *)&s + 156), -1);
    FUN_00133ca0((char *)&s + 152, -1);
    FUN_001966b0((ObjectRefWord *)((char *)&s + 144), -1);
    FUN_0019ab10((O *)((char *)&s + 116), -1);
    FUN_001353b0((char *)&s + 112, -1);
    FUN_001971e0((O *)((char *)&s + 108), -1);
    FUN_0019a890((ObjectRefWord *)((char *)&s + 100), -1);
    FUN_00142d10((char *)&s + 96, -1);
    FUN_0019a890((ObjectRefWord *)((char *)&s + 92), -1);
    FUN_00142d10((char *)&s + 88, -1);
    FUN_001380e0((char *)&s + 84, -1);
    FUN_001958f0((void * *)((char *)&s + 64), -1);
    FUN_001958f0((void * *)((char *)&s + 60), -1);
    FUN_00195a90((struct T_195a90 *)&s, 0);
    return r;
}

int *FUN_0019b7e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019b7f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_0019b800(void)
{
    igMetaObject_RunStaticInit(igProjectiveShadowShader_Register);
}

static igMetaObjectCallback g_igProjectiveShadowShader_callbackList[] = { FUN_0019ccc0, FUN_0013ae20, FUN_001357e0, FUN_001347c0, FUN_0019fc00, FUN_001378f0, FUN_00139000, FUN_001318f0, FUN_00134370, FUN_00133d20, FUN_00132cf0, FUN_00132a00, FUN_00138b20, FUN_0014e050, FUN_00130570, FUN_00136880, FUN_00131240, 0 };

void igProjectiveShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igProjectiveShadowShader_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igProjectiveShadowShader_GetMetaObject,
        "igProjectiveShadowShader",
        0xF0, /* instance size */
        igProjectiveShadowShader_GetVTable,
        &igProjectiveShadowShader_InitFields,
        0, /* extra callback item */
        g_igProjectiveShadowShader_callbackList /* callback list */
    );
}

void thunk_igProjectiveShadowShader_GetMetaObject(void) {
    igProjectiveShadowShader_GetMetaObject();
}

static FieldFactory g_igProjectiveShadowShader_ctorTable[] = {
    FUN_00187890,
    FUN_00187890,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    FUN_00187890,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
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
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igProjectiveShadowShader_ctorTable, 0x30);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1));
    v1[0] = 0; v1[1] = 4.0f; v1[2] = 0;
    FUN_0018e470(temp_a0, v1);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    v2[0] = 0; v2[1] = -1.0f; v2[2] = 0;
    FUN_0018e470(temp_a0, v2);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 30.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    temp_s2->f56 = (int)FUN_0019cbe0();
    temp_s2->f52 = 1;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    temp_s2->f56 = (int)FUN_0019cbe0();
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 0.300000012f);
    igIntMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)), 0x80);
    igIntMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)), 0x80);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)), 0.5f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    temp_s2->f56 = FUN_0013ad40();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    temp_s2->f56 = FUN_001356f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    temp_s2->f56 = FUN_001346d0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    temp_s2->f56 = FUN_001356f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    temp_s2->f56 = FUN_001346d0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    igIntMetaField_SetDefault(temp_v0, 0);
    temp_v0->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    temp_s2->f56 = (int)FUN_0019fae0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10));
    temp_s2->f56 = FUN_00137850();
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    temp_s2->f56 = FUN_00138f20();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)), 1);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13)), 0.100000001f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14)), 1000.0f);
    temp_a0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15));
    v3[0] = 1.0f; v3[1] = 0; v3[2] = 0;
    FUN_0018e470(temp_a0, v3);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x16));
    temp_s2->f56 = FUN_00131800();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x17)), 1);
    igBoolMetaField_SetDefaultValue(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18)), 1);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19));
    temp_s2->f56 = FUN_001341f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1A));
    temp_s2->f56 = FUN_00133b70();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1B));
    temp_s2->f56 = FUN_00132ba0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1C));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D));
    temp_s2->f56 = FUN_001341f0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1E));
    temp_s2->f56 = FUN_00133b70();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F));
    temp_s2->f56 = FUN_00132ba0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x20));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x21));
    temp_s2->f56 = FUN_00138950();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22));
    temp_s2->f56 = FUN_0014dfb0();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23));
    temp_s2->f56 = FUN_00130440();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x24));
    temp_s2->f56 = FUN_00130440();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x25));
    temp_s2->f56 = FUN_00136750();
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x26));
    temp_s2->f56 = FUN_00132850();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x28)), 5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x29)), -5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2A)), 5.0f);
    igFloatMetaField_SetDefault(((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2B)), -5.0f);
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2C));
    temp_s2->f56 = FUN_00131160();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_s2 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2D));
    temp_s2->f56 = FUN_00131160();
    temp_s2->f52 = 1;
    temp_s2->f38 = 0;
    temp_v0 = ((struct Fld_19b8a0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2F));
    igBoolMetaField_SetDefaultValue(temp_v0, 1);
    temp_v0->f38 = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igProjectiveShadowShader_fieldTable, g_igProjectiveShadowShader_fieldHandles, g_igProjectiveShadowShader_fieldOffsets, temp_s1);
}

