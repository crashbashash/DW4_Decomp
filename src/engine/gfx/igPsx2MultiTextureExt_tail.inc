static const char *g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2Names[] = {
    "IG_MULTITEXTURE_BLENDING_ALPHA_SOURCE", "IG_MULTITEXTURE_BLENDING_ALPHA_DESTINATION", "IG_MULTITEXTURE_BLENDING_ALPHA_FIX",
};
static int g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2Values[] = {
    0, 1, 2,
};
igMetaEnum *g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2MetaEnum;

int FUN_001535d0(void) {
    if (g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2MetaEnum == 0) {
        g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2MetaEnum = igMetaEnum_Create("BLENDING_FUNCTION_ALPHA_PSX2", g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2Names, g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2Values, 3);
    }
    return (int)g_igPsx2MultiTextureExt_blendingFunctionAlphaPsx2MetaEnum;
}

static const char *g_igPsx2MultiTextureExt_blendingFunctionColorPsx2Names[] = {
    "IG_MULTITEXTURE_BLENDING_COLOR_SOURCE", "IG_MULTITEXTURE_BLENDING_COLOR_DESTINATION", "IG_MULTITEXTURE_BLENDING_COLOR_ZERO",
};
static int g_igPsx2MultiTextureExt_blendingFunctionColorPsx2Values[] = {
    0, 1, 2,
};
igMetaEnum *g_igPsx2MultiTextureExt_blendingFunctionColorPsx2MetaEnum;

int FUN_00153630(void) {
    if (g_igPsx2MultiTextureExt_blendingFunctionColorPsx2MetaEnum == 0) {
        g_igPsx2MultiTextureExt_blendingFunctionColorPsx2MetaEnum = igMetaEnum_Create("BLENDING_FUNCTION_COLOR_PSX2", g_igPsx2MultiTextureExt_blendingFunctionColorPsx2Names, g_igPsx2MultiTextureExt_blendingFunctionColorPsx2Values, 3);
    }
    return (int)g_igPsx2MultiTextureExt_blendingFunctionColorPsx2MetaEnum;
}

static const char *g_igPsx2MultiTextureExt_textureFunctionPsx2Names[] = {
    "IG_MULTITEXTURE_FUNCTION_REPLACE", "IG_MULTITEXTURE_FUNCTION_MODULATE_ALPHA", "IG_MULTITEXTURE_FUNCTION_ADD", "IG_MULTITEXTURE_FUNCTION_SUBTRACT",
    "IG_MULTITEXTURE_FUNCTION_DESTINATION_MINUS_SOURCE", "IG_MULTITEXTURE_FUNCTION_MODULATE_ALPHA_ADD_COLOR", "IG_MULTITEXTURE_FUNCTION_MODULATE_ALPHA_SUBTRACT", "IG_MULTITEXTURE_FUNCTION_MODULATE_ALPHA_DESTINATION_MINUS_SOURCE",
    "IG_MULTITEXTURE_FUNCTION_MODULATE_DESTINATION_ALPHA", "IG_MULTITEXTURE_FUNCTION_MODULATE_DESTINATION_ALPHA_ADD_COLOR", "IG_MULTITEXTURE_FUNCTION_MODULATE_DESTINATION_ALPHA_SUBTRACT", "IG_MULTITEXTURE_FUNCTION_MODULATE_DESTINATION_ALPHA_DESTINATION_MINUS_SOURCE",
};
static int g_igPsx2MultiTextureExt_textureFunctionPsx2Values[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb,
};
igMetaEnum *g_igPsx2MultiTextureExt_textureFunctionPsx2MetaEnum;

int FUN_00153690(void) {
    if (g_igPsx2MultiTextureExt_textureFunctionPsx2MetaEnum == 0) {
        g_igPsx2MultiTextureExt_textureFunctionPsx2MetaEnum = igMetaEnum_Create("TEXTURE_FUNCTION_PSX2", g_igPsx2MultiTextureExt_textureFunctionPsx2Names, g_igPsx2MultiTextureExt_textureFunctionPsx2Values, 12);
    }
    return (int)g_igPsx2MultiTextureExt_textureFunctionPsx2MetaEnum;
}

igMetaObject *igPsx2MultiTextureExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2MultiTextureExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153820();
    return g_igPsx2MultiTextureExt_metaObject;
}

int igPsx2MultiTextureExt_GetVTable(void) {
    Obj_153740 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00530a10[0];
    obj.r2 = 0;
    obj.vt = &g_igPsx2MultiTextureExt_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &DAT_00530a10[0];
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}

void FUN_00153820(void)
{
    igMetaObject_RunStaticInit(igPsx2MultiTextureExt_Register);
}

static igMetaObjectCallback g_igPsx2MultiTextureExt_callbackList[] = { FUN_001511a0, 0 };

CallbackArray *igPsx2MultiTextureExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2MultiTextureExt_metaObject,
        igMultiTextureExt_Register,
        igMultiTextureExt_GetPublishedMetaObject,
        thunk_igPsx2MultiTextureExt_GetMetaObject,
        "igPsx2MultiTextureExt",
        0x34, /* instance size */
        igPsx2MultiTextureExt_GetVTable,
        &igPsx2MultiTextureExt_InitFields,
        0, /* extra callback item */
        g_igPsx2MultiTextureExt_callbackList /* callback list */
    );
}

int FUN_001538b0(void) {
    return (int)g_igMultiTextureExt_metaObject;
}

static FieldFactory g_igPsx2MultiTextureExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedCharMetaField_Create,
};
static const char *g_igPsx2MultiTextureExt_fieldTable[] = {
    "_context",
    "_blendFunction",
    "_blendingState",
    "_blendA",
    "_blendB",
    "_blendC",
    "_blendD",
    "_blendFIX",
};
static igMetaField **g_igPsx2MultiTextureExt_fieldHandles[] = {
    &g_igPsx2MultiTextureExt_contextMetaField,
    &g_igPsx2MultiTextureExt_blendFunctionMetaField,
    &g_igPsx2MultiTextureExt_blendingStateMetaField,
    &g_igPsx2MultiTextureExt_blendAMetaField,
    &g_igPsx2MultiTextureExt_blendBMetaField,
    &g_igPsx2MultiTextureExt_blendCMetaField,
    &g_igPsx2MultiTextureExt_blendDMetaField,
    &g_igPsx2MultiTextureExt_blendFIXMetaField,
};
static int g_igPsx2MultiTextureExt_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
};

static int g_igPsx2MultiTextureExt_blendBDefault = 2;
static int g_igPsx2MultiTextureExt_blendCDefault = 2;
static int g_igPsx2MultiTextureExt_blendDDefault = 1;

void igPsx2MultiTextureExt_InitFields(void) {
    void *f;
    void *meta; /* matching construct: untyped handle keeps the retail register order */
    int fieldStart;

    meta = g_igPsx2MultiTextureExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2MultiTextureExt_ctorTable, 8);
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart);
    ((igObjectRefMetaField *)f)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)f)->_refCounted = 0;
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 1);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153690);
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 3);
    igEnumMetaField_SetDefaultValue(f, 0);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_00153630);
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 4);
    igEnumMetaField_SetDefaultValue(f, g_igPsx2MultiTextureExt_blendBDefault);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 5);
    igEnumMetaField_SetDefaultValue(f, g_igPsx2MultiTextureExt_blendCDefault);
    ((igEnumMetaField *)f)->_getMetaEnumFunction = (int)(&FUN_001535d0);
    f = igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 6);
    igEnumMetaField_SetDefaultValue(f, g_igPsx2MultiTextureExt_blendDDefault);
    *(void **)&((igEnumMetaField *)f)->_getMetaEnumFunction = (void *)FUN_00153630;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, fieldStart + 7), 0x80);
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2MultiTextureExt_fieldTable, g_igPsx2MultiTextureExt_fieldHandles, g_igPsx2MultiTextureExt_fieldOffsets, fieldStart);
}

