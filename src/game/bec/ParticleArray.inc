igMetaObject *g_ParticleArray_metaObject;
igMetaField *g_ParticleArray_xImageCountMetaField;
igMetaField *g_ParticleArray_yImageCountMetaField;
igMetaField *g_ParticleArray_loopTimeMetaField;
igMetaField *g_ParticleArray_continuousTimeMetaField;
igMetaField *g_ParticleArray_startOffsetMetaField;
igMetaField *g_ParticleArray_hasTextureCoordinatesMetaField;
igMetaField *g_ParticleArray_vertexArray1MetaField;
igMetaField *g_ParticleArray_vertexArray2MetaField;
igMetaField *g_ParticleArray_whichVertexArrayMetaField;
igMetaField *g_ParticleArray_setConstant1MetaField;
igMetaField *g_ParticleArray_setConstant2MetaField;

void *ParticleArray_GetMetaObject(void) {
    igMetaObject *g = g_ParticleArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        ParticleArray_EnsureRegistered();
    }
    return g_ParticleArray_metaObject;
}

int ParticleArray_GetVTable(void) {
    struct Obj_36e310 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    obj.vt = &g_ParticleArray_vtable[0];
    obj.w28 = 0;
    obj.w29 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_ParticleArray_vtable[0];
    FUN_001338d0(&obj.w29, -1);
    FUN_001338d0(&obj.w28, -1);
    FUN_0014caf0(&obj, 0);
    return t;
}

void ParticleArray_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(ParticleArray_Register);
}

static igMetaObjectCallback g_ParticleArray_callbackList[] = { igVertexArray_EnsureRegistered, 0 };

void *ParticleArray_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        ParticleArray_GetMetaObjectFunction,
        "ParticleArray",
        0x7c, /* instance size */
        ParticleArray_GetVTable,
        ParticleArray_InitFields,
        0, /* extra callback item */
        g_ParticleArray_callbackList /* callback list */
    );
}

void ParticleArray_GetMetaObjectFunction(void)
{
    ParticleArray_GetMetaObject();
}

static FieldFactory g_ParticleArray_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_ParticleArray_fieldTable[] = {
    "_xImageCount",
    "_yImageCount",
    "_loopTime",
    "_continuousTime",
    "_startOffset",
    "_hasTextureCoordinates",
    "_vertexArray1",
    "_vertexArray2",
    "_whichVertexArray",
    "_setConstant1",
    "_setConstant2",
};
static igMetaField **g_ParticleArray_fieldHandles[] = {
    &g_ParticleArray_xImageCountMetaField,
    &g_ParticleArray_yImageCountMetaField,
    &g_ParticleArray_loopTimeMetaField,
    &g_ParticleArray_continuousTimeMetaField,
    &g_ParticleArray_startOffsetMetaField,
    &g_ParticleArray_hasTextureCoordinatesMetaField,
    &g_ParticleArray_vertexArray1MetaField,
    &g_ParticleArray_vertexArray2MetaField,
    &g_ParticleArray_whichVertexArrayMetaField,
    &g_ParticleArray_setConstant1MetaField,
    &g_ParticleArray_setConstant2MetaField,
};
static int g_ParticleArray_fieldOffsets[] = {
    92,
    96,
    100,
    101,
    104,
    108,
    112,
    116,
    120,
    121,
    122,
};

void ParticleArray_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_ParticleArray_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_ParticleArray_ctorTable, 0xB);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, g_ParticleArray_fieldTable, g_ParticleArray_fieldHandles, g_ParticleArray_fieldOffsets, temp_s2);
}

