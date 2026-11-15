igMetaObject *g_beCameraBoxData_metaObject;
igMetaField *g_beCameraBoxData_switchMetaField;
igMetaField *g_beCameraBoxData_geometryListMetaField;
igMetaField *g_beCameraBoxData_transformListMetaField;
igMetaField *g_beCameraBoxData_eyePosListMetaField;
igMetaField *g_beCameraBoxData_intPosListMetaField;

void *FUN_003691b0(void) {
    igMetaObject *g = g_beCameraBoxData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003692d0();
    }
    return g_beCameraBoxData_metaObject;
}

int beCameraBoxData_GetVTable(void) {
    struct Obj_369200 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005349d0[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005349d0[0];
    FUN_00341160((O *)(&obj.w[5]), (short)(-1));
    FUN_00341160((O *)(&obj.w[4]), (short)(-1));
    FUN_00341160((O *)(&obj.w[3]), (short)(-1));
    FUN_0019c220(&obj.w[2], -1);
    FUN_00343260((ObjectRefWord *)(&obj.w[1]), -1);
    return r;
}

void FUN_003692d0(void)
{
    igMetaObject_RunStaticInit(beCameraBoxData_Register);
}

static igMetaObjectCallback g_beCameraBoxData_callbackList[] = { FUN_00196ad0, FUN_0019fa10, FUN_00195f50, 0 };

void *beCameraBoxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraBoxData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraBoxData_GetMetaObject,
        "beCameraBoxData",
        0x1c, /* instance size */
        beCameraBoxData_GetVTable,
        beCameraBoxData_InitFields,
        0, /* extra callback item */
        g_beCameraBoxData_callbackList /* callback list */
    );
}

void beCameraBoxData_GetMetaObject(void)
{
    FUN_003691b0();
}

static FieldFactory g_beCameraBoxData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beCameraBoxData_fieldTable[] = {
    "_switch",
    "_geometryList",
    "_transformList",
    "_eyePosList",
    "_intPosList",
};
static igMetaField **g_beCameraBoxData_fieldHandles[] = {
    &g_beCameraBoxData_switchMetaField,
    &g_beCameraBoxData_geometryListMetaField,
    &g_beCameraBoxData_transformListMetaField,
    &g_beCameraBoxData_eyePosListMetaField,
    &g_beCameraBoxData_intPosListMetaField,
};
static int g_beCameraBoxData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void beCameraBoxData_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)g_beCameraBoxData_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beCameraBoxData_ctorTable, 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00196930();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019f930();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00195e70();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beCameraBoxData_fieldTable, g_beCameraBoxData_fieldHandles, g_beCameraBoxData_fieldOffsets, temp_s0);
}

