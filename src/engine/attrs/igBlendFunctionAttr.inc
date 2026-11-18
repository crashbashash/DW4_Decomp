igMetaEnum *g_igBlendFunctionAttr_alphaPsx2MetaEnum;
igMetaEnum *g_igBlendFunctionAttr_colorPsx2MetaEnum;
igMetaObject *g_igBlendFunctionAttr_metaObject;
igMetaField *g_igBlendFunctionAttr_srcMetaField;
igMetaField *g_igBlendFunctionAttr_dstMetaField;
igMetaField *g_igBlendFunctionAttr_eqMetaField;
igMetaField *g_igBlendFunctionAttr_blendEquationExtMetaField;
igMetaField *g_igBlendFunctionAttr_blendConstantMetaField;
igMetaField *g_igBlendFunctionAttr_blendStageMetaField;
igMetaField *g_igBlendFunctionAttr_blendConstantFloatMetaField;
igMetaField *g_igBlendFunctionAttr_blendAMetaField;
igMetaField *g_igBlendFunctionAttr_blendBMetaField;
igMetaField *g_igBlendFunctionAttr_blendCMetaField;
igMetaField *g_igBlendFunctionAttr_blendDMetaField;

static const char *g_igBlendFunctionAttr_alphaPsx2Names[] = {
    "IG_BLENDING_ALPHA_SOURCE",
    "IG_BLENDING_ALPHA_DESTINATION",
    "IG_BLENDING_ALPHA_FIX",
};
static int g_igBlendFunctionAttr_alphaPsx2Values[] = {
    0,
    1,
    2,
};

igMetaEnum *igBlendFunctionAttr_GetBlendingFunctionAlphaPsx2MetaEnum(void) {
    if (g_igBlendFunctionAttr_alphaPsx2MetaEnum == 0) {
        g_igBlendFunctionAttr_alphaPsx2MetaEnum = igMetaEnum_Create("BLENDING_FUNCTION_ALPHA_PSX2", g_igBlendFunctionAttr_alphaPsx2Names, g_igBlendFunctionAttr_alphaPsx2Values, 3);
    }
    return g_igBlendFunctionAttr_alphaPsx2MetaEnum;
}

static const char *g_igBlendFunctionAttr_colorPsx2Names[] = {
    "IG_BLENDING_COLOR_SOURCE",
    "IG_BLENDING_COLOR_DESTINATION",
    "IG_BLENDING_COLOR_ZERO",
};
static int g_igBlendFunctionAttr_colorPsx2Values[] = {
    0,
    1,
    2,
};

igMetaEnum *igBlendFunctionAttr_GetBlendingFunctionColorPsx2MetaEnum(void) {
    if (g_igBlendFunctionAttr_colorPsx2MetaEnum == 0) {
        g_igBlendFunctionAttr_colorPsx2MetaEnum = igMetaEnum_Create("BLENDING_FUNCTION_COLOR_PSX2", g_igBlendFunctionAttr_colorPsx2Names, g_igBlendFunctionAttr_colorPsx2Values, 3);
    }
    return g_igBlendFunctionAttr_colorPsx2MetaEnum;
}

igBlendFunctionAttr *igBlendFunctionAttr_Create(igMemoryPoolView *pool) {
    igBlendFunctionAttr_EnsureRegistered();
    return (igBlendFunctionAttr *)igMetaObject_CreateInstance(g_igBlendFunctionAttr_metaObject, pool);
}

igMetaObject *igBlendFunctionAttr_GetOrCreateMetaObject(void) {
    if (g_igBlendFunctionAttr_metaObject == 0) {
        g_igBlendFunctionAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendFunctionAttr_metaObject;
}

igMetaObject *igBlendFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendFunctionAttr_EnsureRegistered();
    return g_igBlendFunctionAttr_metaObject;
}

int igBlendFunctionAttr_GetVTable(void) {
    union U_139fb0 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[24];
    u.vt = (int)&g_igBlendFunctionAttr_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igBlendFunctionAttr_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

void igBlendFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendFunctionAttr_Register);
}

static igMetaObjectCallback g_igBlendFunctionAttr_callbackList[] = { igBlendEquationExt_EnsureRegistered, 0 };

CallbackArray *igBlendFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igBlendFunctionAttr_GetMetaObjectFunction,
        "igBlendFunctionAttr",
        0x34, /* instance size */
        igBlendFunctionAttr_GetVTable,
        &igBlendFunctionAttr_InitFields,
        0, /* extra callback item */
        g_igBlendFunctionAttr_callbackList /* callback list */
    );
}

void igBlendFunctionAttr_GetMetaObjectFunction(void) {
    igBlendFunctionAttr_GetMetaObject();
}

static FieldFactory g_igBlendFunctionAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedCharMetaField_Create,
    (FieldFactory)igShortMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igBlendFunctionAttr_fieldTable[] = {
    "_src",
    "_dst",
    "_eq",
    "_blendEquationExt",
    "_blendConstant",
    "_blendStage",
    "_blendConstantFloat",
    "_blendA",
    "_blendB",
    "_blendC",
    "_blendD",
};
static igMetaField **g_igBlendFunctionAttr_fieldHandles[] = {
    &g_igBlendFunctionAttr_srcMetaField,
    &g_igBlendFunctionAttr_dstMetaField,
    &g_igBlendFunctionAttr_eqMetaField,
    &g_igBlendFunctionAttr_blendEquationExtMetaField,
    &g_igBlendFunctionAttr_blendConstantMetaField,
    &g_igBlendFunctionAttr_blendStageMetaField,
    &g_igBlendFunctionAttr_blendConstantFloatMetaField,
    &g_igBlendFunctionAttr_blendAMetaField,
    &g_igBlendFunctionAttr_blendBMetaField,
    &g_igBlendFunctionAttr_blendCMetaField,
    &g_igBlendFunctionAttr_blendDMetaField,
};
static int g_igBlendFunctionAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    30,
    32,
    36,
    40,
    44,
    48,
};

int g_igBlendFunctionAttr_srcDefault = 4;
int g_igBlendFunctionAttr_dstDefault = 5;
int g_igBlendFunctionAttr_blendBDefault = 2;
int g_igBlendFunctionAttr_blendCDefault = 2;
int g_igBlendFunctionAttr_blendDDefault = 1;

void igBlendFunctionAttr_InitFields(void) {
    int base;
    igMetaObject *meta;
    struct MetaFieldSetupView *t5;
    struct MetaFieldSetupView *field;
    struct MetaFieldSetupView *field2;
    struct MetaFieldSetupView *field3;
    struct MetaFieldSetupView *field4;
    struct MetaFieldSetupView *field5;
    struct MetaFieldSetupView *field6;
    struct MetaFieldSetupView *field7;
    struct MetaFieldSetupView *field8;
    struct MetaFieldSetupView *field9;

    meta = g_igBlendFunctionAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igBlendFunctionAttr_ctorTable, 0xB);
    field2 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base);
    igEnumMetaField_SetDefaultValue((igMetaField *)field2, g_igBlendFunctionAttr_srcDefault);
    field2->_getMetaEnumFunction = IG_GFX_BLENDING_FUNCTION_GetMetaEnum;
    field3 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 1);
    igEnumMetaField_SetDefaultValue((igMetaField *)field3, g_igBlendFunctionAttr_dstDefault);
    field3->_getMetaEnumFunction = IG_GFX_BLENDING_FUNCTION_GetMetaEnum;
    field4 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 2);
    igEnumMetaField_SetDefaultValue((igMetaField *)field4, 0);
    field4->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    field = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 3);
    field->_metaObject = igBlendEquationExt_GetOrCreateMetaObject();
    field->_deepCopyMethod = 1;
    field->_shallowCopyMethod = 1;
    field->_isAlikeShallowMethod = 3;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 4), 0);
    t5 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 5);
    t5->_invarianceFunction = (void (*)())igBlendFunctionAttr_SynchronizeCachedUnitID;
    field5 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 6);
    igFloatMetaField_SetDefault((igMetaField *)field5, 0);
    field5->_persistent = 0;
    field5->_invarianceFunction = (void (*)())igBlendFunctionAttr_SynchronizeBlendConstant;
    field6 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 7);
    igEnumMetaField_SetDefaultValue((igMetaField *)field6, 0);
    field6->_getMetaEnumFunction = (void (*)())igBlendFunctionAttr_GetBlendingFunctionColorPsx2MetaEnum;
    field7 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 8);
    igEnumMetaField_SetDefaultValue((igMetaField *)field7, g_igBlendFunctionAttr_blendBDefault);
    field7->_getMetaEnumFunction = (void (*)())igBlendFunctionAttr_GetBlendingFunctionColorPsx2MetaEnum;
    field8 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 9);
    igEnumMetaField_SetDefaultValue((igMetaField *)field8, g_igBlendFunctionAttr_blendCDefault);
    field8->_getMetaEnumFunction = (void (*)())igBlendFunctionAttr_GetBlendingFunctionAlphaPsx2MetaEnum;
    field9 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 0xA);
    igEnumMetaField_SetDefaultValue((igMetaField *)field9, g_igBlendFunctionAttr_blendDDefault);
    field9->_getMetaEnumFunction = (void (*)())igBlendFunctionAttr_GetBlendingFunctionColorPsx2MetaEnum;
    igMetaObject_NameFields(meta, g_igBlendFunctionAttr_fieldTable, g_igBlendFunctionAttr_fieldHandles, g_igBlendFunctionAttr_fieldOffsets, base);
}

