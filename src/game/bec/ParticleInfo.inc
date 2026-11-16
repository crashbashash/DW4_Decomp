igMetaEnum *g_ParticleInfo_particleTimeTypeMetaEnum;
static const char *g_ParticleInfo_particleTimeTypeNames[] = {
    "IG_PARTICLE_TIME_NORMAL", "IG_PARTICLE_TIME_LOOP", "IG_PARTICLE_TIME_CONTINUOUS",
};
static int g_ParticleInfo_particleTimeTypeValues[] = {
    0, 1, 2,
};

igMetaEnum *ParticleInfo_GetParticleTimeTypeMetaEnum(void) {
    if (g_ParticleInfo_particleTimeTypeMetaEnum == 0) {
        g_ParticleInfo_particleTimeTypeMetaEnum = igMetaEnum_Create("IG_PARTICLE_TIME_TYPE", g_ParticleInfo_particleTimeTypeNames, g_ParticleInfo_particleTimeTypeValues, 3);
    }
    return g_ParticleInfo_particleTimeTypeMetaEnum;
}

igMetaEnum *g_ParticleInfo_particleAlphaFunctionMetaEnum;
static const char *g_ParticleInfo_particleAlphaFunctionNames[] = {
    "IG_PARTICLE_ALPHA_BLEND", "IG_PARTICLE_ALPHA_ADDITIVE",
};
static int g_ParticleInfo_particleAlphaFunctionValues[] = {
    0, 1,
};

igMetaEnum *ParticleInfo_GetParticleAlphaFunctionMetaEnum(void) {
    if (g_ParticleInfo_particleAlphaFunctionMetaEnum == 0) {
        g_ParticleInfo_particleAlphaFunctionMetaEnum = igMetaEnum_Create("IG_PARTICLE_ALPHA_FUNCTION", g_ParticleInfo_particleAlphaFunctionNames, g_ParticleInfo_particleAlphaFunctionValues, 2);
    }
    return g_ParticleInfo_particleAlphaFunctionMetaEnum;
}

igMetaEnum *g_ParticleInfo_particleAlphaTypeMetaEnum;
static const char *g_ParticleInfo_particleAlphaTypeNames[] = {
    "IG_PARTICLE_ALPHA_NONE", "IG_PARTICLE_ALPHA_1BIT", "IG_PARTICLE_ALPHA_FULL",
};
static int g_ParticleInfo_particleAlphaTypeValues[] = {
    0, 1, 2,
};

igMetaEnum *ParticleInfo_GetParticleAlphaTypeMetaEnum(void) {
    if (g_ParticleInfo_particleAlphaTypeMetaEnum == 0) {
        g_ParticleInfo_particleAlphaTypeMetaEnum = igMetaEnum_Create("IG_PARTICLE_ALPHA_TYPE", g_ParticleInfo_particleAlphaTypeNames, g_ParticleInfo_particleAlphaTypeValues, 3);
    }
    return g_ParticleInfo_particleAlphaTypeMetaEnum;
}

igMetaEnum *g_ParticleInfo_particleEmitterTypeMetaEnum;
static const char *g_ParticleInfo_particleEmitterTypeNames[] = {
    "IG_PARTICLE_EMITTER_RECTANGLE", "IG_PARTICLE_EMITTER_SPHERE", "IG_PARTICLE_EMITTER_XY_CYLINDER", "IG_PARTICLE_EMITTER_XZ_CYLINDER",
    "IG_PARTICLE_EMITTER_YZ_CYLINDER",
};
static int g_ParticleInfo_particleEmitterTypeValues[] = {
    0, 1, 2, 3, 4,
};

igMetaEnum *ParticleInfo_GetParticleEmitterTypeMetaEnum(void) {
    if (g_ParticleInfo_particleEmitterTypeMetaEnum == 0) {
        g_ParticleInfo_particleEmitterTypeMetaEnum = igMetaEnum_Create("IG_PARTICLE_EMITTER_TYPE", g_ParticleInfo_particleEmitterTypeNames, g_ParticleInfo_particleEmitterTypeValues, 5);
    }
    return g_ParticleInfo_particleEmitterTypeMetaEnum;
}

igMetaObject *g_ParticleInfo_metaObject;
igMetaField *g_ParticleInfo_pointsMetaField;
igMetaField *g_ParticleInfo_numControlsMetaField;
igMetaField *g_ParticleInfo_lifetimeMetaField;
igMetaField *g_ParticleInfo_countMetaField;
igMetaField *g_ParticleInfo_textureMetaField;
igMetaField *g_ParticleInfo_alphaTypeMetaField;
igMetaField *g_ParticleInfo_alphaFunctionMetaField;
igMetaField *g_ParticleInfo_sizeLockMetaField;
igMetaField *g_ParticleInfo_sizeWorldMetaField;
igMetaField *g_ParticleInfo_timeTypeMetaField;
igMetaField *g_ParticleInfo_particleSceneMetaField;
igMetaField *g_ParticleInfo_shapeMetaField;
igMetaField *g_ParticleInfo_maximizeMetaField;
igMetaField *g_ParticleInfo_xImageCountMetaField;
igMetaField *g_ParticleInfo_yImageCountMetaField;
igMetaField *g_ParticleInfo_resizeCurvesMetaField;
igMetaField *g_ParticleInfo_startOffsetMetaField;
igMetaField *g_ParticleInfo_geometryMetaField;

igMetaObject *ParticleInfo_GetMetaObject(void) {
    igMetaObject *g = g_ParticleInfo_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        ParticleInfo_EnsureRegistered();
    return g_ParticleInfo_metaObject;
}

int ParticleInfo_GetVTable(void) {
    ParticleInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._sceneGraph = 0;
    obj._textures = 0;
    obj._cameras = 0;
    obj._sceneGraphList = 0;
    obj._vtable = (int)&g_ParticleInfo_vtable[0];
    obj._texture = 0;
    obj._geometry = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_ParticleInfo_vtable[0];
    igSmartPointer_igGeometry_Destruct(&obj._geometry, -1);
    igSmartPointer_igImage_Destruct(&obj._texture, -1);
    igSceneInfo_Destroy((igSceneInfo *)&obj, 0);
    return vtable;
}

void ParticleInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(ParticleInfo_Register);
}

static igMetaObjectCallback g_ParticleInfo_callbackList[] = { igImage_EnsureRegistered, igGeometry_EnsureRegistered, 0 };

void *ParticleInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_ParticleInfo_metaObject,
        igSceneInfo_Register,
        igSceneInfo_GetPublishedMetaObject,
        ParticleInfo_GetMetaObjectFunction,
        "ParticleInfo",
        0x400, /* instance size */
        ParticleInfo_GetVTable,
        ParticleInfo_InitFields,
        0, /* extra callback item */
        g_ParticleInfo_callbackList /* callback list */
    );
}

void ParticleInfo_GetMetaObjectFunction(void)
{
    ParticleInfo_GetMetaObject();
}

int igSceneInfo_GetPublishedMetaObject(void) {
    return g_igSceneInfo_metaObject[0];
}

static FieldFactory g_ParticleInfo_ctorTable[] = {
    igFloatArrayMetaField_Create,
    igIntArrayMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_ParticleInfo_fieldTable[] = {
    "_points",
    "_numControls",
    "_lifetime",
    "_count",
    "_texture",
    "_alphaType",
    "_alphaFunction",
    "_sizeLock",
    "_sizeWorld",
    "_timeType",
    "_particleScene",
    "_shape",
    "_maximize",
    "_xImageCount",
    "_yImageCount",
    "_resizeCurves",
    "_startOffset",
    "_geometry",
};
static igMetaField **g_ParticleInfo_fieldHandles[] = {
    &g_ParticleInfo_pointsMetaField,
    &g_ParticleInfo_numControlsMetaField,
    &g_ParticleInfo_lifetimeMetaField,
    &g_ParticleInfo_countMetaField,
    &g_ParticleInfo_textureMetaField,
    &g_ParticleInfo_alphaTypeMetaField,
    &g_ParticleInfo_alphaFunctionMetaField,
    &g_ParticleInfo_sizeLockMetaField,
    &g_ParticleInfo_sizeWorldMetaField,
    &g_ParticleInfo_timeTypeMetaField,
    &g_ParticleInfo_particleSceneMetaField,
    &g_ParticleInfo_shapeMetaField,
    &g_ParticleInfo_maximizeMetaField,
    &g_ParticleInfo_xImageCountMetaField,
    &g_ParticleInfo_yImageCountMetaField,
    &g_ParticleInfo_resizeCurvesMetaField,
    &g_ParticleInfo_startOffsetMetaField,
    &g_ParticleInfo_geometryMetaField,
};
static int g_ParticleInfo_fieldOffsets[] = {
    64,
    832,
    960,
    964,
    968,
    972,
    976,
    980,
    981,
    984,
    988,
    992,
    996,
    1000,
    1004,
    1008,
    1012,
    1016,
};


void ParticleInfo_InitFields(void) {
    int base;
    void *f;
    void *meta;

    meta = (void *)g_ParticleInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_ParticleInfo_ctorTable, 0x12);
    f = igMetaObject_GetFieldAt(meta, base);
    ((igFloatArrayMetaField *)f)->_num = 0xC0;
    ((igFloatArrayMetaField *)f)->_resetMethod = 3;
    f = igMetaObject_GetFieldAt(meta, base + 1);
    ((igIntArrayMetaField *)f)->_num = 0x20;
    ((igIntArrayMetaField *)f)->_resetMethod = 3;
    igFloatMetaField_SetDefault((void *)((int)igMetaObject_GetFieldAt(meta, base + 2)), 10.0f);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 3), 0xA);
    f = igMetaObject_GetFieldAt(meta, base + 4);
    ((igObjectRefMetaField *)f)->_metaObject = igImage_GetOrCreateMetaObject();
    f = igMetaObject_GetFieldAt(meta, base + 5);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&ParticleInfo_GetParticleAlphaTypeMetaEnum;
    f = igMetaObject_GetFieldAt(meta, base + 6);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&ParticleInfo_GetParticleAlphaFunctionMetaEnum;
    f = igMetaObject_GetFieldAt(meta, base + 9);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&ParticleInfo_GetParticleTimeTypeMetaEnum;
    f = igMetaObject_GetFieldAt(meta, base + 0xB);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)&ParticleInfo_GetParticleEmitterTypeMetaEnum;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0xD), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0xE), 1);
    igFloatMetaField_SetDefault((void *)((int)igMetaObject_GetFieldAt(meta, base + 0x10)), 0.0f);
    f = igMetaObject_GetFieldAt(meta, base + 0x11);
    ((igObjectRefMetaField *)f)->_metaObject = igGeometry_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_ParticleInfo_fieldTable, g_ParticleInfo_fieldHandles, g_ParticleInfo_fieldOffsets, base);
}

