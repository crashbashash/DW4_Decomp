igMetaObject *g_igViewModel_metaObject;
igMetaField *g_igViewModel_viewMatrixMetaField;
igMetaField *g_igViewModel_ratioMetaField;
igMetaField *g_igViewModel_hfovMetaField;
igMetaField *g_igViewModel_nearPlaneMetaField;
igMetaField *g_igViewModel_farPlaneMetaField;
igMetaField *g_igViewModel_positionMetaField;
igMetaField *g_igViewModel_directionMetaField;
igMetaField *g_igViewModel_viewUpVectorMetaField;
igMetaField *g_igViewModel_viewLeftVectorMetaField;
igMetaField *g_igViewModel_sceneUpVectorMetaField;
igMetaField *g_igViewModel_drawTimeMetaField;
igMetaField *g_igViewModel_selectedCenterMetaField;
igMetaField *g_igViewModel_selectedLengthMetaField;

igMetaObject *FUN_0045d470(void) {
    if (g_igViewModel_metaObject == 0) {
        g_igViewModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewModel_metaObject;
}

void *igViewModel_GetMetaObject(void) {
    igMetaObject *g = g_igViewModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d5c0();
    }
    return g_igViewModel_metaObject;
}

int igViewModel_GetVTable(void) {
    union U_45d510 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    igObject_InitHeader((igObject *)u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&g_igViewModel_vtable[0];
    igMatrix44f_SetIdentity((float *)&u.b[12]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem)) + 916)];
    u.vt = (int)&g_igModel_vtable[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    return r;
}

void FUN_0045d5c0(void)
{
    igMetaObject_RunStaticInit(igViewModel_Register);
}

CallbackArray *igViewModel_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewModel_GetMetaObject,
        "igViewModel",
        0xB0, /* instance size */
        igViewModel_GetVTable,
        &igViewModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewModel_GetMetaObject(void) {
    igViewModel_GetMetaObject();
}

static FieldFactory g_igViewModel_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    igLongMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    igFloatMetaField_Create,
};
static const char *g_igViewModel_fieldTable[] = {
    "_viewMatrix",
    "_ratio",
    "_hfov",
    "_nearPlane",
    "_farPlane",
    "_position",
    "_direction",
    "_viewUpVector",
    "_viewLeftVector",
    "_sceneUpVector",
    "_drawTime",
    "_selectedCenter",
    "_selectedLength",
};
static igMetaField **g_igViewModel_fieldHandles[] = {
    &g_igViewModel_viewMatrixMetaField,
    &g_igViewModel_ratioMetaField,
    &g_igViewModel_hfovMetaField,
    &g_igViewModel_nearPlaneMetaField,
    &g_igViewModel_farPlaneMetaField,
    &g_igViewModel_positionMetaField,
    &g_igViewModel_directionMetaField,
    &g_igViewModel_viewUpVectorMetaField,
    &g_igViewModel_viewLeftVectorMetaField,
    &g_igViewModel_sceneUpVectorMetaField,
    &g_igViewModel_drawTimeMetaField,
    &g_igViewModel_selectedCenterMetaField,
    &g_igViewModel_selectedLengthMetaField,
};
static int g_igViewModel_fieldOffsets[] = {
    12,
    76,
    80,
    84,
    88,
    92,
    104,
    116,
    128,
    140,
    152,
    160,
    172,
};

void igViewModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    void *temp_a1, *temp_a2, *temp_a3, *temp_a4, *temp_a5, *temp_a6;
    float v1[4];
    float v2[4];
    float v3[4];
    float v4[4];
    float v5[4];
    float v6[4];

    temp_s0 = g_igViewModel_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewModel_ctorTable, 0xD);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2), 45.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4), 1000.0f);
    temp_a1 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5);
    v1[0] = 0.0f; v1[1] = 0.0f; v1[2] = 0.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a1, v1);
    temp_a2 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6);
    v2[0] = 0.0f; v2[1] = 0.0f; v2[2] = 1.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a2, v2);
    temp_a3 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7);
    v3[0] = 0.0f; v3[1] = 1.0f; v3[2] = 0.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a3, v3);
    temp_a4 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8);
    v4[0] = 1.0f; v4[1] = 0.0f; v4[2] = 0.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a4, v4);
    temp_a5 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9);
    v5[0] = 0.0f; v5[1] = 1.0f; v5[2] = 0.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a5, v5);
    temp_a6 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB);
    v6[0] = 0.0f; v6[1] = 0.0f; v6[2] = 0.0f;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a6, v6);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewModel_fieldTable, g_igViewModel_fieldHandles, g_igViewModel_fieldOffsets, temp_s1);
}

