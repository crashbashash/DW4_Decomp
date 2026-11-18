igMetaObject *g_igLightAttr_metaObject;
igMetaField *g_igLightAttr_lightTypeMetaField;
igMetaField *g_igLightAttr_lightIdMetaField;
igMetaField *g_igLightAttr_positionMetaField;
igMetaField *g_igLightAttr_ambientMetaField;
igMetaField *g_igLightAttr_diffuseMetaField;
igMetaField *g_igLightAttr_specularMetaField;
igMetaField *g_igLightAttr_directionMetaField;
igMetaField *g_igLightAttr_falloffMetaField;
igMetaField *g_igLightAttr_cutoffMetaField;
igMetaField *g_igLightAttr_attenuationMetaField;
igMetaField *g_igLightAttr_shininessMetaField;
igMetaField *g_igLightAttr_cachedPositionMetaField;
igMetaField *g_igLightAttr_cachedDirectionMetaField;
igMetaField *g_igLightAttr_vcMetaField;
igMetaField *g_igLightAttr_changedMetaField;
igMetaField *g_igLightAttr_cacheableMetaField;

igMetaObject *FUN_00136750(void) {
    if (g_igLightAttr_metaObject == 0) {
        g_igLightAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightAttr_metaObject;
}

igMetaObject *igLightAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightAttr_EnsureRegistered();
    return g_igLightAttr_metaObject;
}

int igLightAttr_GetVTable(void) {
    union U_1367f0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igLightAttr_vtable[0];
    ps = &u.b[140];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igLightAttr_vtable[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igLightAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightAttr_Register);
}

static igMetaObjectCallback g_igLightAttr_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igLightAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightAttr_GetMetaObject,
        "igLightAttr",
        0x94, /* instance size */
        igLightAttr_GetVTable,
        &igLightAttr_InitFields,
        0, /* extra callback item */
        g_igLightAttr_callbackList /* callback list */
    );
}

void thunk_igLightAttr_GetMetaObject(void) {
    igLightAttr_GetMetaObject();
}

static FieldFactory g_igLightAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igLightAttr_fieldTable[] = {
    "_lightType",
    "_lightId",
    "_position",
    "_ambient",
    "_diffuse",
    "_specular",
    "_direction",
    "_falloff",
    "_cutoff",
    "_attenuation",
    "_shininess",
    "_cachedPosition",
    "_cachedDirection",
    "_vc",
    "_changed",
    "_cacheable",
};
static igMetaField **g_igLightAttr_fieldHandles[] = {
    &g_igLightAttr_lightTypeMetaField,
    &g_igLightAttr_lightIdMetaField,
    &g_igLightAttr_positionMetaField,
    &g_igLightAttr_ambientMetaField,
    &g_igLightAttr_diffuseMetaField,
    &g_igLightAttr_specularMetaField,
    &g_igLightAttr_directionMetaField,
    &g_igLightAttr_falloffMetaField,
    &g_igLightAttr_cutoffMetaField,
    &g_igLightAttr_attenuationMetaField,
    &g_igLightAttr_shininessMetaField,
    &g_igLightAttr_cachedPositionMetaField,
    &g_igLightAttr_cachedDirectionMetaField,
    &g_igLightAttr_vcMetaField,
    &g_igLightAttr_changedMetaField,
    &g_igLightAttr_cacheableMetaField,
};
static int g_igLightAttr_fieldOffsets[] = {
    12,
    16,
    20,
    32,
    48,
    64,
    80,
    92,
    96,
    100,
    112,
    116,
    128,
    140,
    144,
    145,
};

int g_igLightAttr_lightTypeDefault = 1;

void igLightAttr_InitFields(void) {
    float vh[4];
    float vg[4];
    float vf[4];
    float ve[4];
    float vd[4];
    float vc[4];
    float vb[4];
    float va[4];
    int temp_s1;
    igMetaObject *temp_s0;
    struct LightMetaFieldView *temp_s2;
    struct LightMetaFieldView *tv;

    temp_s0 = g_igLightAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igLightAttr_ctorTable, 0x10);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_s2, g_igLightAttr_lightTypeDefault);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2->f52 = (void (*)(void))FUN_00149a40;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    igIntMetaField_SetDefault((igMetaField *)temp_s2, -1);
    temp_s2->f38 = 0;
    temp_s2->f40 = 4;
    temp_s2->f39 = 4;
    temp_s2->f44 = 3;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    vh[0] = 0; vh[1] = 0; vh[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_s2, vh);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    vc[3] = 1.0f; vc[0] = 0.6f; vc[1] = 0.6f; vc[2] = 0.6f;
    igVec4fMetaField_SetDefault((igMetaField *)temp_s2, vc);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    vb[0] = 1.0f; vb[1] = 1.0f; vb[2] = 1.0f; vb[3] = 1.0f;
    igVec4fMetaField_SetDefault((igMetaField *)temp_s2, vb);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    va[3] = 1.0f; va[0] = 0; va[1] = 0; va[2] = 0;
    igVec4fMetaField_SetDefault((igMetaField *)temp_s2, va);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    vg[2] = 1.0f; vg[0] = 0; vg[1] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_s2, vg);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    tv = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    tv->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    igFloatMetaField_SetDefault((igMetaField *)temp_s2, 180.0f);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    vf[0] = 1.0f; vf[1] = 0; vf[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_s2, vf);
    temp_s2->f48 = (void (*)())FUN_0013ef20;
    tv = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA);
    tv->f48 = (void (*)())FUN_0013ef20;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    ve[0] = 0; ve[1] = 0; ve[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_s2, ve);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC);
    vd[0] = 0; vd[2] = -1.0f; vd[1] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_s2, vd);
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD);
    temp_s2->f56 = (int)igVisualContext_GetOrCreateMetaObject();
    temp_s2->f38 = 0;
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE);
    igBoolMetaField_SetDefaultValue((igMetaField *)temp_s2, 1);
    temp_s2->f38 = 0;
    temp_s2 = (LightMetaFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF);
    igBoolMetaField_SetDefaultValue((igMetaField *)temp_s2, 1);
    temp_s2->f38 = 0;
    igMetaObject_NameFields(temp_s0, g_igLightAttr_fieldTable, g_igLightAttr_fieldHandles, g_igLightAttr_fieldOffsets, temp_s1);
}

