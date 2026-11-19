igMetaObject *g_igParticleFormat_metaObject;
igMetaField *g_igParticleFormat_positionMetaField;
igMetaField *g_igParticleFormat_colorMetaField;
igMetaField *g_igParticleFormat_widthMetaField;
igMetaField *g_igParticleFormat_heightMetaField;
igMetaField *g_igParticleFormat_textureCoordMetaField;
igMetaField *g_igParticleFormat_primTypeMetaField;
igMetaField *g_igParticleFormat_spriteTypeMetaField;
igMetaField *g_igParticleFormat_spriteSpaceMetaField;
igMetaField *g_igParticleFormat_rotationMetaField;
igMetaField *g_igParticleFormat_lifetimeMetaField;

int igParticleFormat_Create(int arg0) {
    igParticleFormat_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igParticleFormat_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igParticleFormat_GetOrCreateMetaObject(void) {
    if (g_igParticleFormat_metaObject == 0) {
        g_igParticleFormat_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igParticleFormat_metaObject;
}

igMetaObject *igParticleFormat_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleFormat_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igParticleFormat_EnsureRegistered();
    return g_igParticleFormat_metaObject;
}

int igParticleFormat_GetVTable(void) {
    struct Obj_14d150 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igParticleFormat_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igParticleFormat_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igParticleFormat_Register);
}

CallbackArray *igParticleFormat_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igParticleFormat_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igParticleFormat_GetMetaObjectFunction,
        "igParticleFormat",
        0x30, /* instance size */
        igParticleFormat_GetVTable,
        &igParticleFormat_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igParticleFormat_GetMetaObjectFunction(void) {
    igParticleFormat_GetMetaObject();
}

static FieldFactory g_igParticleFormat_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igParticleFormat_fieldTable[] = {
    "_position",
    "_color",
    "_width",
    "_height",
    "_textureCoord",
    "_primType",
    "_spriteType",
    "_spriteSpace",
    "_rotation",
    "_lifetime",
};
static igMetaField **g_igParticleFormat_fieldHandles[] = {
    &g_igParticleFormat_positionMetaField,
    &g_igParticleFormat_colorMetaField,
    &g_igParticleFormat_widthMetaField,
    &g_igParticleFormat_heightMetaField,
    &g_igParticleFormat_textureCoordMetaField,
    &g_igParticleFormat_primTypeMetaField,
    &g_igParticleFormat_spriteTypeMetaField,
    &g_igParticleFormat_spriteSpaceMetaField,
    &g_igParticleFormat_rotationMetaField,
    &g_igParticleFormat_lifetimeMetaField,
};
static int g_igParticleFormat_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

static int g_igParticleFormat_spriteTypeDefault = 1;

void igParticleFormat_InitFields(void) {
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    int fieldStart;
    igMetaObject *meta;

    meta = g_igParticleFormat_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igParticleFormat_ctorTable, 0xA);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&X0_0014d010[0]);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_2, 0);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&X1_0014d010[0]);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 2));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_3, 0);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(&X2_0014d010[0]);
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_4, 0);
    ((igEnumMetaField *)temp_v0_4)->_getMetaEnumFunction = (int)(&X3_0014d010[0]);
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 4));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_5, 0);
    ((igEnumMetaField *)temp_v0_5)->_getMetaEnumFunction = (int)(&X4_0014d010[0]);
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_6, 0);
    ((igEnumMetaField *)temp_v0_6)->_getMetaEnumFunction = (int)(&IG_GFX_DRAW_GetMetaEnum);
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 6));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_7, g_igParticleFormat_spriteTypeDefault);
    ((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (int)(&IG_GFX_SPRITE_TYPE_GetMetaEnum);
    temp_v0_8 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 7));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_8, 0);
    ((igEnumMetaField *)temp_v0_8)->_getMetaEnumFunction = (int)(&IG_GFX_SPRITE_SIZE_SPACE_GetMetaEnum);
    temp_v0_9 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 8));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_9, 0);
    ((igEnumMetaField *)temp_v0_9)->_getMetaEnumFunction = (int)(&X5_0014d010[0]);
    temp_v0_10 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 9));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_10, 0);
    ((igEnumMetaField *)temp_v0_10)->_getMetaEnumFunction = (int)(&X6_0014d010[0]);
    igMetaObject_NameFields(meta, g_igParticleFormat_fieldTable, g_igParticleFormat_fieldHandles, g_igParticleFormat_fieldOffsets, fieldStart);
}

static const char *g_igParticleFormat_textureArgumentNames[] = {
    "IG_MULTITEXTURE_ARGUMENT_PREV_STAGE_OUTPUT", "IG_MULTITEXTURE_ARGUMENT_DIFFUSE", "IG_MULTITEXTURE_ARGUMENT_SPECULAR", "IG_MULTITEXTURE_ARGUMENT_TEXTURE",
};
static int g_igParticleFormat_textureArgumentValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igParticleFormat_textureArgumentMetaEnum;

int TEXTURE_ARGUMENT_GetMetaEnum(void) {
    if (g_igParticleFormat_textureArgumentMetaEnum == 0) {
        g_igParticleFormat_textureArgumentMetaEnum = igMetaEnum_Create("TEXTURE_ARGUMENT", g_igParticleFormat_textureArgumentNames, g_igParticleFormat_textureArgumentValues, 4);
    }
    return (int)g_igParticleFormat_textureArgumentMetaEnum;
}

static const char *g_igParticleFormat_textureStageTypeNames[] = {
    "IG_MULTITEXTURE_STAGE_DISABLE", "IG_MULTITEXTURE_STAGE_COMBINE1", "IG_MULTITEXTURE_STAGE_COMBINE2",
};
static int g_igParticleFormat_textureStageTypeValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igParticleFormat_textureStageTypeMetaEnum;

int TEXTURE_STAGE_TYPE_GetMetaEnum(void) {
    if (g_igParticleFormat_textureStageTypeMetaEnum == 0) {
        g_igParticleFormat_textureStageTypeMetaEnum = igMetaEnum_Create("TEXTURE_STAGE_TYPE", g_igParticleFormat_textureStageTypeNames, g_igParticleFormat_textureStageTypeValues, 3);
    }
    return (int)g_igParticleFormat_textureStageTypeMetaEnum;
}

static const char *g_igParticleFormat_textureFunctionTypeNames[] = {
    "IG_MULTITEXTURE_FUNCTION_TYPE_COLOR", "IG_MULTITEXTURE_FUNCTION_TYPE_ALPHA", "IG_MULTITEXTURE_FUNCTION_TYPE_COLOR_AND_ALPHA",
};
static int g_igParticleFormat_textureFunctionTypeValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igParticleFormat_textureFunctionTypeMetaEnum;

int TEXTURE_FUNCTION_TYPE_GetMetaEnum(void) {
    if (g_igParticleFormat_textureFunctionTypeMetaEnum == 0) {
        g_igParticleFormat_textureFunctionTypeMetaEnum = igMetaEnum_Create("TEXTURE_FUNCTION_TYPE", g_igParticleFormat_textureFunctionTypeNames, g_igParticleFormat_textureFunctionTypeValues, 3);
    }
    return (int)g_igParticleFormat_textureFunctionTypeMetaEnum;
}

