igMetaObject *g_igEnvironmentMapShader2_metaObject;
igMetaField *g_igEnvironmentMapShader2_envMapTextureMetaField;
igMetaField *g_igEnvironmentMapShader2_diffuseTextureBindMetaField;
igMetaField *g_igEnvironmentMapShader2_diffuseTextureCoordIndexMetaField;
igMetaField *g_igEnvironmentMapShader2_reflectionAmountMetaField;
igMetaField *g_igEnvironmentMapShader2_isTransparentMetaField;
igMetaField *g_igEnvironmentMapShader2_glossMapTextureMetaField;
igMetaField *g_igEnvironmentMapShader2_glossTextureCoordIndexMetaField;
igMetaField *g_igEnvironmentMapShader2_configuredMetaField;
igMetaField *g_igEnvironmentMapShader2_attrPushListsMetaField;
igMetaField *g_igEnvironmentMapShader2_attrPopListsMetaField;
igMetaField *g_igEnvironmentMapShader2_useRenderPackageMetaField;
igMetaField *g_igEnvironmentMapShader2_discardUnusedImagesMetaField;
igMetaField *g_igEnvironmentMapShader2_envMapTextureBindMetaField;
igMetaField *g_igEnvironmentMapShader2_envMapCoordSourceMetaField;
igMetaField *g_igEnvironmentMapShader2_envMapTextureFuncMetaField;
igMetaField *g_igEnvironmentMapShader2_diffuseCoordSourceMetaField;
igMetaField *g_igEnvironmentMapShader2_diffuseTextureFuncMetaField;
igMetaField *g_igEnvironmentMapShader2_diffuseBlendStateMetaField;
igMetaField *g_igEnvironmentMapShader2_glossMapTextureBindMetaField;
igMetaField *g_igEnvironmentMapShader2_glossMapCoordSourceMetaField;
igMetaField *g_igEnvironmentMapShader2_glossMapTextureFuncMetaField;

igMetaObject *igEnvironmentMapShader2_GetMetaObject(void)
{
    igMetaObject *g = g_igEnvironmentMapShader2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a15a0();
    return g_igEnvironmentMapShader2_metaObject;
}

void FUN_001a15a0(void)
{
    igMetaObject_RunStaticInit(igEnvironmentMapShader2_Register);
}

static igMetaObjectCallback g_igEnvironmentMapShader2_callbackList[] = { FUN_00132420, igTextureBindAttr_EnsureRegistered, igTextureAttr_EnsureRegistered, igAttrListList_EnsureRegistered, igTextureBindAttr_EnsureRegistered, igTextureCoordSourceAttr_EnsureRegistered, igTextureFunctionAttr_EnsureRegistered, igBlendStateAttr_EnsureRegistered, 0 };

void igEnvironmentMapShader2_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igEnvironmentMapShader2_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igEnvironmentMapShader2_GetMetaObject,
        "igEnvironmentMapShader2",
        0x70, /* instance size */
        0,
        &igEnvironmentMapShader2_InitFields,
        0, /* extra callback item */
        g_igEnvironmentMapShader2_callbackList /* callback list */
    );
}

void thunk_igEnvironmentMapShader2_GetMetaObject(void) {
    igEnvironmentMapShader2_GetMetaObject();
}

static FieldFactory g_igEnvironmentMapShader2_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
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
};
static const char *g_igEnvironmentMapShader2_fieldTable[] = {
    "_envMapTexture",
    "_diffuseTextureBind",
    "_diffuseTextureCoordIndex",
    "_reflectionAmount",
    "_isTransparent",
    "_glossMapTexture",
    "_glossTextureCoordIndex",
    "_configured",
    "_attrPushLists",
    "_attrPopLists",
    "_useRenderPackage",
    "_discardUnusedImages",
    "_envMapTextureBind",
    "_envMapCoordSource",
    "_envMapTextureFunc",
    "_diffuseCoordSource",
    "_diffuseTextureFunc",
    "_diffuseBlendState",
    "_glossMapTextureBind",
    "_glossMapCoordSource",
    "_glossMapTextureFunc",
};
static igMetaField **g_igEnvironmentMapShader2_fieldHandles[] = {
    &g_igEnvironmentMapShader2_envMapTextureMetaField,
    &g_igEnvironmentMapShader2_diffuseTextureBindMetaField,
    &g_igEnvironmentMapShader2_diffuseTextureCoordIndexMetaField,
    &g_igEnvironmentMapShader2_reflectionAmountMetaField,
    &g_igEnvironmentMapShader2_isTransparentMetaField,
    &g_igEnvironmentMapShader2_glossMapTextureMetaField,
    &g_igEnvironmentMapShader2_glossTextureCoordIndexMetaField,
    &g_igEnvironmentMapShader2_configuredMetaField,
    &g_igEnvironmentMapShader2_attrPushListsMetaField,
    &g_igEnvironmentMapShader2_attrPopListsMetaField,
    &g_igEnvironmentMapShader2_useRenderPackageMetaField,
    &g_igEnvironmentMapShader2_discardUnusedImagesMetaField,
    &g_igEnvironmentMapShader2_envMapTextureBindMetaField,
    &g_igEnvironmentMapShader2_envMapCoordSourceMetaField,
    &g_igEnvironmentMapShader2_envMapTextureFuncMetaField,
    &g_igEnvironmentMapShader2_diffuseCoordSourceMetaField,
    &g_igEnvironmentMapShader2_diffuseTextureFuncMetaField,
    &g_igEnvironmentMapShader2_diffuseBlendStateMetaField,
    &g_igEnvironmentMapShader2_glossMapTextureBindMetaField,
    &g_igEnvironmentMapShader2_glossMapCoordSourceMetaField,
    &g_igEnvironmentMapShader2_glossMapTextureFuncMetaField,
};
static int g_igEnvironmentMapShader2_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    73,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
    104,
    108,
};

void igEnvironmentMapShader2_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;

    temp_s1 = (void *)(g_igEnvironmentMapShader2_metaObject);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igEnvironmentMapShader2_ctorTable, 0x15);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00131fe0();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00132850();
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)), 1.0f);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igTextureAttr_GetOrCreateMetaObject();
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7))))->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s2_4)->_construct = 1;
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB))))->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00132850();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_7)->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_10)->_persistent = 0;
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = igBlendStateAttr_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_11)->_persistent = 0;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_00132850();
    ((igMetaField *)temp_s2_12)->_persistent = 0;
    temp_s2_13 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001325e0();
    ((igMetaField *)temp_s2_13)->_persistent = 0;
    temp_s2_14 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_00131ca0();
    ((igMetaField *)temp_s2_14)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igEnvironmentMapShader2_fieldTable, g_igEnvironmentMapShader2_fieldHandles, g_igEnvironmentMapShader2_fieldOffsets, temp_s0);
    ((igMetaObject *)(g_igEnvironmentMapShader2_metaObject))->_abstractProxy = (int)(&thunk_igPsx2EnvironmentMapShader_GetMetaObject);
}

