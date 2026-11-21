igMetaObject *g_igViewerParameters_metaObject;
igMetaField *g_igViewerParameters_sceneMetaField;
igMetaField *g_igViewerParameters_upVectorMetaField;
igMetaField *g_igViewerParameters_ratioMetaField;
igMetaField *g_igViewerParameters_hfovMetaField;
igMetaField *g_igViewerParameters_nearPlaneMetaField;
igMetaField *g_igViewerParameters_farPlaneMetaField;
igMetaField *g_igViewerParameters_projectionMatrixMetaField;
igMetaField *g_igViewerParameters_viewMatrixMetaField;
igMetaField *g_igViewerParameters_drawTimeMetaField;
igMetaField *g_igViewerParameters_sortTextureMetaField;
igMetaField *g_igViewerParameters_sortTransparentMetaField;
igMetaField *g_igViewerParameters_sortTransparentDistanceMetaField;
igMetaField *g_igViewerParameters_transparencyModeMetaField;
igMetaField *g_igViewerParameters_useSceneLightsMetaField;
igMetaField *g_igViewerParameters_useHeadLightMetaField;
igMetaField *g_igViewerParameters_useHeadLightSpecularMetaField;
igMetaField *g_igViewerParameters_alphaTestMetaField;
igMetaField *g_igViewerParameters_alphaTestForceMetaField;
igMetaField *g_igViewerParameters_backFaceCullingMetaField;
igMetaField *g_igViewerParameters_backFaceCullingForceMetaField;
igMetaField *g_igViewerParameters_wireframeMetaField;
igMetaField *g_igViewerParameters_wireframeForceMetaField;
igMetaField *g_igViewerParameters_flatShadingMetaField;
igMetaField *g_igViewerParameters_flatShadingForceMetaField;
igMetaField *g_igViewerParameters_disablesMetaField;
igMetaField *g_igViewerParameters_showGuiMetaField;
igMetaField *g_igViewerParameters_showBoundingBoxMetaField;
igMetaField *g_igViewerParameters_showNormalsMetaField;
igMetaField *g_igViewerParameters_flushFramesMetaField;
igMetaField *g_igViewerParameters_operationModeMetaField;
igMetaField *g_igViewerParameters_firstCameraModeMetaField;
igMetaField *g_igViewerParameters_camerasMetaField;
igMetaField *g_igViewerParameters_beginTimeMetaField;
igMetaField *g_igViewerParameters_endTimeMetaField;
igMetaField *g_igViewerParameters_selectedObjectMetaField;
igMetaField *g_igViewerParameters_timeOperationMetaField;
igMetaField *g_igViewerParameters_loopModeMetaField;
igMetaField *g_igViewerParameters_speedMetaField;
igMetaField *g_igViewerParameters_cursorPositionMetaField;

igMetaObject *igViewerParameters_GetOrCreateMetaObject(void) {
    if (g_igViewerParameters_metaObject == 0) {
        g_igViewerParameters_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerParameters_metaObject;
}

SigViewerParameters_GetMetaObject *igViewerParameters_GetMetaObject(void) {
    if (((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject) == 0 || !((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject)->ok()) igViewerParameters_EnsureRegistered();
    return ((SigViewerParameters_GetMetaObject *)g_igViewerParameters_metaObject);
}

int igViewerParameters_GetVTable(void) {
    union U_45b4c0 u;
    int temp_s1;
    int pi = (int)u.b;
    char *p;
    igObject_InitHeader((igObject *)pi);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&g_igViewerParameters_vtable[0];
    p = &u.b[12];
    *(int *)p = 0;
    igMatrix44f_SetIdentity((float *)&u.b[44]);
    igMatrix44f_SetIdentity((float *)(pi + 108));
    *(int *)(pi + 204) = 0;
    *(int *)(pi + 220) = 0;
    *(int *)(pi + 240) = 0;
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00542090[4];
    igSmartPointer_igGraphPath_Destruct((igSmartPointer<igObject> *)&u.b[240], -1);
    igSmartPointer_igGraphPathList_Destruct((igSmartPointer<igObject> *)&u.b[220], -1);
    igSmartPointer_igBitMask_Destruct((igSmartPointer<igObject> *)&u.b[204], -1);
    igSmartPointer_igGroup_Destruct((igSmartPointer<igObject> *)p, -1);
    igModel_Destroy((igModel *)u.b, 0);
    return temp_s1;
}

void igViewerParameters_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewerParameters_Register);
}

static igMetaObjectCallback g_igViewerParameters_callbackList[] = { igGroup_EnsureRegistered, igBitMask_EnsureRegistered, igGraphPathList_EnsureRegistered, igGraphPath_EnsureRegistered, 0 };

CallbackArray *igViewerParameters_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerParameters_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewerParameters_GetMetaObject,
        "igViewerParameters",
        0x108, /* instance size */
        igViewerParameters_GetVTable,
        &igViewerParameters_InitFields,
        0, /* extra callback item */
        g_igViewerParameters_callbackList /* callback list */
    );
}

void thunk_igViewerParameters_GetMetaObject(void) {
    igViewerParameters_GetMetaObject();
}

static FieldFactory g_igViewerParameters_ctorTable[] = {
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool,
};
static const char *g_igViewerParameters_fieldTable[] = {
    "_scene",
    "_upVector",
    "_ratio",
    "_hfov",
    "_nearPlane",
    "_farPlane",
    "_projectionMatrix",
    "_viewMatrix",
    "_drawTime",
    "_sortTexture",
    "_sortTransparent",
    "_sortTransparentDistance",
    "_transparencyMode",
    "_useSceneLights",
    "_useHeadLight",
    "_useHeadLightSpecular",
    "_alphaTest",
    "_alphaTestForce",
    "_backFaceCulling",
    "_backFaceCullingForce",
    "_wireframe",
    "_wireframeForce",
    "_flatShading",
    "_flatShadingForce",
    "_disables",
    "_showGui",
    "_showBoundingBox",
    "_showNormals",
    "_flushFrames",
    "_operationMode",
    "_firstCameraMode",
    "_cameras",
    "_beginTime",
    "_endTime",
    "_selectedObject",
    "_timeOperation",
    "_loopMode",
    "_speed",
    "_cursorPosition",
};
static igMetaField **g_igViewerParameters_fieldHandles[] = {
    &g_igViewerParameters_sceneMetaField,
    &g_igViewerParameters_upVectorMetaField,
    &g_igViewerParameters_ratioMetaField,
    &g_igViewerParameters_hfovMetaField,
    &g_igViewerParameters_nearPlaneMetaField,
    &g_igViewerParameters_farPlaneMetaField,
    &g_igViewerParameters_projectionMatrixMetaField,
    &g_igViewerParameters_viewMatrixMetaField,
    &g_igViewerParameters_drawTimeMetaField,
    &g_igViewerParameters_sortTextureMetaField,
    &g_igViewerParameters_sortTransparentMetaField,
    &g_igViewerParameters_sortTransparentDistanceMetaField,
    &g_igViewerParameters_transparencyModeMetaField,
    &g_igViewerParameters_useSceneLightsMetaField,
    &g_igViewerParameters_useHeadLightMetaField,
    &g_igViewerParameters_useHeadLightSpecularMetaField,
    &g_igViewerParameters_alphaTestMetaField,
    &g_igViewerParameters_alphaTestForceMetaField,
    &g_igViewerParameters_backFaceCullingMetaField,
    &g_igViewerParameters_backFaceCullingForceMetaField,
    &g_igViewerParameters_wireframeMetaField,
    &g_igViewerParameters_wireframeForceMetaField,
    &g_igViewerParameters_flatShadingMetaField,
    &g_igViewerParameters_flatShadingForceMetaField,
    &g_igViewerParameters_disablesMetaField,
    &g_igViewerParameters_showGuiMetaField,
    &g_igViewerParameters_showBoundingBoxMetaField,
    &g_igViewerParameters_showNormalsMetaField,
    &g_igViewerParameters_flushFramesMetaField,
    &g_igViewerParameters_operationModeMetaField,
    &g_igViewerParameters_firstCameraModeMetaField,
    &g_igViewerParameters_camerasMetaField,
    &g_igViewerParameters_beginTimeMetaField,
    &g_igViewerParameters_endTimeMetaField,
    &g_igViewerParameters_selectedObjectMetaField,
    &g_igViewerParameters_timeOperationMetaField,
    &g_igViewerParameters_loopModeMetaField,
    &g_igViewerParameters_speedMetaField,
    &g_igViewerParameters_cursorPositionMetaField,
};
static int g_igViewerParameters_fieldOffsets[] = {
    12,
    16,
    28,
    32,
    36,
    40,
    44,
    108,
    176,
    184,
    185,
    186,
    188,
    192,
    193,
    194,
    195,
    196,
    197,
    198,
    199,
    200,
    201,
    202,
    204,
    208,
    209,
    210,
    211,
    212,
    216,
    220,
    224,
    232,
    240,
    244,
    248,
    252,
    256,
};

void igViewerParameters_InitFields(void) {
    struct Fld *temp_s2_4;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2;
    void *temp_a0_2;
    void *temp_a0;
    int temp_s1;
    void *temp_s0;
    int sp50[3];
    int sp48[2];

    temp_s0 = g_igViewerParameters_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerParameters_ctorTable, 0x27);
    temp_s2 = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1);
    temp_s2->f56 = (int)(igGroup_GetOrCreateMetaObject());
    temp_s2->f52 = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    sp50[0] = 0;
    sp50[1] = 0x3F800000;
    sp50[2] = 0;
    ((Gap::Math::igVec3fMetaField *)temp_a0)->setDefault(*(const igVec3f *)sp50);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)))->setDefault(1.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)))->setDefault(45.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)))->setDefault(1.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)))->setDefault(1000.0f);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)))->setDefault(0);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10)))->setDefault(1);
    temp_s2_2 = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x18);
    temp_s2_2->f56 = (int)igBitMask_GetOrCreateMetaObject();
    temp_s2_2->f52 = 1;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x19)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1A)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1D)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E)))->setDefault(4);
    temp_s2_3 = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F);
    temp_s2_3->f56 = (int)igGraphPathList_GetOrCreateMetaObject();
    temp_s2_3->f52 = 1;
    temp_s2_4 = (struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x22);
    temp_s2_4->f56 = (int)(igGraphPath_GetOrCreateMetaObject());
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x23)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x24)))->setDefault(2);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x25)))->setDefault(1.0f);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x26));
    sp48[0] = 0;
    sp48[1] = 0;
    ((Gap::Math::igVec2fMetaField *)temp_a0_2)->setDefault(*(const igVec2f *)sp48);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerParameters_fieldTable, g_igViewerParameters_fieldHandles, g_igViewerParameters_fieldOffsets, temp_s1);
}

