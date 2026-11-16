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

igMetaEnum *FUN_00139e10(void) {
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

igMetaEnum *FUN_00139e70(void) {
    if (g_igBlendFunctionAttr_colorPsx2MetaEnum == 0) {
        g_igBlendFunctionAttr_colorPsx2MetaEnum = igMetaEnum_Create("BLENDING_FUNCTION_COLOR_PSX2", g_igBlendFunctionAttr_colorPsx2Names, g_igBlendFunctionAttr_colorPsx2Values, 3);
    }
    return g_igBlendFunctionAttr_colorPsx2MetaEnum;
}

void FUN_00139ed0(int arg0) {
    igBlendFunctionAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x55F3B8, arg0);
}

igMetaObject *igBlendFunctionAttr_GetOrCreateMetaObject(void) {
    if (g_igBlendFunctionAttr_metaObject == 0) {
        g_igBlendFunctionAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[24];
    u.vt = (int)&g_igBlendFunctionAttr_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igBlendFunctionAttr_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void igBlendFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendFunctionAttr_Register);
}

static igMetaObjectCallback g_igBlendFunctionAttr_callbackList[] = { FUN_0014ff00, 0 };

void igBlendFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendFunctionAttr_GetMetaObject,
        "igBlendFunctionAttr",
        0x34, /* instance size */
        igBlendFunctionAttr_GetVTable,
        &igBlendFunctionAttr_InitFields,
        0, /* extra callback item */
        g_igBlendFunctionAttr_callbackList /* callback list */
    );
}

void thunk_igBlendFunctionAttr_GetMetaObject(void) {
    igBlendFunctionAttr_GetMetaObject();
}

static FieldFactory g_igBlendFunctionAttr_ctorTable[] = {
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedCharMetaField_Create,
    igShortMetaField_Create,
    igFloatMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
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
    int temp_s1;
    igMetaObject *temp_s0;
    struct BlendAttrMetaField *t5;
    struct BlendAttrMetaField *temp_s2;
    struct BlendAttrMetaField *temp_v0;
    struct BlendAttrMetaField *temp_v0_2;
    struct BlendAttrMetaField *temp_v0_3;
    struct BlendAttrMetaField *temp_v0_4;
    struct BlendAttrMetaField *temp_v0_5;
    struct BlendAttrMetaField *temp_v0_6;
    struct BlendAttrMetaField *temp_v0_7;
    struct BlendAttrMetaField *temp_v0_8;

    temp_s0 = g_igBlendFunctionAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igBlendFunctionAttr_ctorTable, 0xB);
    temp_v0 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    igEnumMetaField_SetDefaultValue(temp_v0, g_igBlendFunctionAttr_srcDefault);
    temp_v0->f52 = FUN_00149740;
    temp_v0_2 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    igEnumMetaField_SetDefaultValue(temp_v0_2, g_igBlendFunctionAttr_dstDefault);
    temp_v0_2->f52 = FUN_00149740;
    temp_v0_3 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    igEnumMetaField_SetDefaultValue(temp_v0_3, 0);
    temp_v0_3->f52 = igMetaEnum_GetEmpty;
    temp_s2 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    temp_s2->f56 = FUN_0014fe60();
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 0);
    t5 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    t5->f48 = (void (*)())FUN_0013c420;
    temp_v0_4 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    igFloatMetaField_SetDefault(temp_v0_4, 0);
    temp_v0_4->f38 = 0;
    temp_v0_4->f48 = (void (*)())FUN_0013c470;
    temp_v0_5 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    igEnumMetaField_SetDefaultValue(temp_v0_5, 0);
    temp_v0_5->f52 = (void (*)())FUN_00139e70;
    temp_v0_6 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    igEnumMetaField_SetDefaultValue(temp_v0_6, g_igBlendFunctionAttr_blendBDefault);
    temp_v0_6->f52 = (void (*)())FUN_00139e70;
    temp_v0_7 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    igEnumMetaField_SetDefaultValue(temp_v0_7, g_igBlendFunctionAttr_blendCDefault);
    temp_v0_7->f52 = (void (*)())FUN_00139e10;
    temp_v0_8 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA);
    igEnumMetaField_SetDefaultValue(temp_v0_8, g_igBlendFunctionAttr_blendDDefault);
    temp_v0_8->f52 = (void (*)())FUN_00139e70;
    igMetaObject_NameFields(temp_s0, g_igBlendFunctionAttr_fieldTable, g_igBlendFunctionAttr_fieldHandles, g_igBlendFunctionAttr_fieldOffsets, temp_s1);
}

