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
    ParticleArray obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._particleFormat = 0;
    obj._internalVertexArray = 0;
    obj._context = 0;
    obj._pointSpriteInterface = 0;
    obj._primLengthArray = 0;
    obj._vtable = (int)&g_ParticleArray_vtable[0];
    obj._vertexArray1 = 0;
    obj._vertexArray2 = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_ParticleArray_vtable[0];
    igSmartPointer_igVertexArray_Destruct((igSmartPointer<igObject> *)&obj._vertexArray2, -1);
    igSmartPointer_igVertexArray_Destruct((igSmartPointer<igObject> *)&obj._vertexArray1, -1);
    igParticleArray_Destroy((igParticleArray *)&obj, 0);
    return vtable;
}

void ParticleArray_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(ParticleArray_Register);
}

static igMetaObjectCallback g_ParticleArray_callbackList[] = { igVertexArray_EnsureRegistered, 0 };

CallbackArray *ParticleArray_Register(void) {
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
    int base;
    void *vertexArray2;
    void *vertexArray1;
    igMetaObject *meta;

    meta = g_ParticleArray_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_ParticleArray_ctorTable, 0xB);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), 1.0f);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 2), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 4), 0.0f);
    vertexArray1 = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)vertexArray1)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)vertexArray1)->_persistent = 0;
    vertexArray2 = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)vertexArray2)->_metaObject = (int)igVertexArray_GetOrCreateMetaObject();
    ((igMetaField *)vertexArray2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0xA))->_persistent = 0;
    igMetaObject_NameFields(meta, g_ParticleArray_fieldTable, g_ParticleArray_fieldHandles, g_ParticleArray_fieldOffsets, base);
}

