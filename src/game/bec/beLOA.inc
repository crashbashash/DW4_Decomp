igMetaObject *g_beLOA_metaObject;
igMetaField *g_beLOA_rangeMetaField;
igMetaField *g_beLOA_maxAlphaMetaField;
igMetaField *g_beLOA_addAlphaMetaField;
igMetaField *g_beLOA_oldTimeMetaField;
igMetaField *g_beLOA_statusMetaField;
igMetaField *g_beLOA_colorMetaField;
igMetaField *g_beLOA_overrideAttrListMetaField;
igMetaField *g_beLOA_blendStateAttrMetaField;
igMetaField *g_beLOA_blendFunctionAttrMetaField;
igMetaField *g_beLOA_colorAttrMetaField;

igMetaObject *FUN_0035cd40(void)
{
    igMetaObject *g = g_beLOA_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035ce60();
    return g_beLOA_metaObject;
}

int beLOA_GetVTable(void) {
    struct W_35cd90 o;
    int *p18;
    int *p17;
    int *p16;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    o.vt = &DAT_005364a0[0];
    p16 = &o.f[18];
    *p16 = 0;
    p17 = &o.f[19];
    *p17 = 0;
    p18 = &o.f[20];
    *p18 = 0;
    o.f[21] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005364a0[0];
    FUN_0019ab10(&o.f[21], -1);
    FUN_001ab380(p18, -1);
    FUN_001aaf00(p17, -1);
    FUN_0013bfe0(p16, -1);
    FUN_00195a90(&o, 0);
    return r;
}

void FUN_0035ce60(void)
{
    igMetaObject_RunStaticInit(beLOA_Register);
}

static igMetaObjectCallback g_beLOA_callbackList[] = { FUN_0013afe0, FUN_00139720, FUN_0013a040, FUN_00139000, 0 };

void *beLOA_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLOA_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beLOA_GetMetaObject,
        "beLOA",
        0x60, /* instance size */
        beLOA_GetVTable,
        beLOA_InitFields,
        FUN_0035d050, /* extra callback item */
        g_beLOA_callbackList /* callback list */
    );
}

void beLOA_GetMetaObject(void)
{
    FUN_0035cd40();
}

static FieldFactory g_beLOA_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    FUN_001872a0,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLOA_fieldTable[] = {
    "_range",
    "_maxAlpha",
    "_addAlpha",
    "_oldTime",
    "_status",
    "_color",
    "_overrideAttrList",
    "_blendStateAttr",
    "_blendFunctionAttr",
    "_colorAttr",
};
static igMetaField **g_beLOA_fieldHandles[] = {
    &g_beLOA_rangeMetaField,
    &g_beLOA_maxAlphaMetaField,
    &g_beLOA_addAlphaMetaField,
    &g_beLOA_oldTimeMetaField,
    &g_beLOA_statusMetaField,
    &g_beLOA_colorMetaField,
    &g_beLOA_overrideAttrListMetaField,
    &g_beLOA_blendStateAttrMetaField,
    &g_beLOA_blendFunctionAttrMetaField,
    &g_beLOA_colorAttrMetaField,
};
static int g_beLOA_fieldOffsets[] = {
    32,
    36,
    40,
    48,
    56,
    60,
    76,
    80,
    84,
    88,
};

void beLOA_InitFields(void) {
    int sp40[4];
    int temp_s0;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_beLOA_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beLOA_ctorTable, 0xA);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    sp40[0] = 0x3F800000;
    sp40[1] = 0x3F800000;
    sp40[2] = 0x3F800000;
    sp40[3] = 0x3F800000;
    FUN_0018e670(temp_a0, sp40);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00139640();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00139f10();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beLOA_fieldTable, g_beLOA_fieldHandles, g_beLOA_fieldOffsets, temp_s0);
}

void FUN_0035d050(void)
{
    FUN_00389fb0();
}

