igMetaObject *g_beAction2InfoWork_metaObject;
igMetaField *g_beAction2InfoWork_comDataMetaField;
igMetaField *g_beAction2InfoWork_comIndexMetaField;
igMetaField *g_beAction2InfoWork_isNoHokanMetaField;
igMetaField *g_beAction2InfoWork_isMotionMetaField;
igMetaField *g_beAction2InfoWork_motionSt0MetaField;
igMetaField *g_beAction2InfoWork_motionIsEndMetaField;
igMetaField *g_beAction2InfoWork_jointSt0MetaField;
igMetaField *g_beAction2InfoWork_jointStartTimeLMetaField;
igMetaField *g_beAction2InfoWork_jointEndTimeLMetaField;
igMetaField *g_beAction2InfoWork_jointIsEndMetaField;
igMetaField *g_beAction2InfoWork_fadeSt0MetaField;
igMetaField *g_beAction2InfoWork_fadeLimitValueMetaField;
igMetaField *g_beAction2InfoWork_fadeAddValueMetaField;
igMetaField *g_beAction2InfoWork_fadeValueMetaField;
igMetaField *g_beAction2InfoWork_waitSt0MetaField;
igMetaField *g_beAction2InfoWork_flashSt0MetaField;
igMetaField *g_beAction2InfoWork_isFreezeMetaField;
igMetaField *g_beAction2InfoWork_colorAttrMetaField;
igMetaField *g_beAction2InfoWork_blendStateAttrMetaField;
igMetaField *g_beAction2InfoWork_textureStateAttrMetaField;
igMetaField *g_beAction2InfoWork_lightingStateAttrMetaField;

void beAction2InfoWork_CreateInstance(int arg0) {
    FUN_0036c4d0();
    igMetaObject_CreateInstance(*(int *)0x589E98, arg0);
}

igMetaObject *FUN_0036c2e0(void) {
    if (g_beAction2InfoWork_metaObject == 0) {
        g_beAction2InfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beAction2InfoWork_metaObject;
}

igMetaObject *FUN_0036c330(void)
{
    igMetaObject *g = g_beAction2InfoWork_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036c4d0();
    return g_beAction2InfoWork_metaObject;
}

int beAction2InfoWork_GetVTable(void) {
    union U_36c380 u;
    int temp_s;
    char *p184;
    char *p180;
    char *p176;
    char *p104;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005343b0[0];
    p104 = &u.b[8];
    *(int *)p104 = 0;
    p176 = &u.b[80];
    *(int *)p176 = 0;
    p180 = &u.b[84];
    *(int *)p180 = 0;
    p184 = &u.b[88];
    *(int *)p184 = 0;
    *(int *)&u.b[92] = 0;
    temp_s = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005343b0[0];
    FUN_00239200(&u.b[92], -1);
    FUN_001d21b0(p184, -1);
    FUN_001aaf00(p180, -1);
    FUN_0019ab10(p176, -1);
    FUN_0036c450((void **)p104, (short)(-1));
    return temp_s;
}

void **FUN_0036c450(void **arg0, short arg1) {
    S_temp_a0_36c450 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_36c450 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0036c4d0(void)
{
    igMetaObject_RunStaticInit(beAction2InfoWork_Register);
}

static igMetaObjectCallback g_beAction2InfoWork_callbackList[] = { FUN_0036db70, FUN_00139000, FUN_00139720, FUN_001314b0, FUN_00135f40, 0 };

void *beAction2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beAction2InfoWork_GetMetaObject,
        "beAction2InfoWork",
        0x60, /* instance size */
        beAction2InfoWork_GetVTable,
        beAction2InfoWork_InitFields,
        0, /* extra callback item */
        g_beAction2InfoWork_callbackList /* callback list */
    );
}

void beAction2InfoWork_GetMetaObject(void)
{
    FUN_0036c330();
}

static FieldFactory g_beAction2InfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beAction2InfoWork_fieldTable[] = {
    "_comData",
    "_comIndex",
    "_isNoHokan",
    "_isMotion",
    "_motionSt0",
    "_motionIsEnd",
    "_jointSt0",
    "_jointStartTimeL",
    "_jointEndTimeL",
    "_jointIsEnd",
    "_fadeSt0",
    "_fadeLimitValue",
    "_fadeAddValue",
    "_fadeValue",
    "_waitSt0",
    "_flashSt0",
    "_isFreeze",
    "_colorAttr",
    "_blendStateAttr",
    "_textureStateAttr",
    "_lightingStateAttr",
};
static igMetaField **g_beAction2InfoWork_fieldHandles[] = {
    &g_beAction2InfoWork_comDataMetaField,
    &g_beAction2InfoWork_comIndexMetaField,
    &g_beAction2InfoWork_isNoHokanMetaField,
    &g_beAction2InfoWork_isMotionMetaField,
    &g_beAction2InfoWork_motionSt0MetaField,
    &g_beAction2InfoWork_motionIsEndMetaField,
    &g_beAction2InfoWork_jointSt0MetaField,
    &g_beAction2InfoWork_jointStartTimeLMetaField,
    &g_beAction2InfoWork_jointEndTimeLMetaField,
    &g_beAction2InfoWork_jointIsEndMetaField,
    &g_beAction2InfoWork_fadeSt0MetaField,
    &g_beAction2InfoWork_fadeLimitValueMetaField,
    &g_beAction2InfoWork_fadeAddValueMetaField,
    &g_beAction2InfoWork_fadeValueMetaField,
    &g_beAction2InfoWork_waitSt0MetaField,
    &g_beAction2InfoWork_flashSt0MetaField,
    &g_beAction2InfoWork_isFreezeMetaField,
    &g_beAction2InfoWork_colorAttrMetaField,
    &g_beAction2InfoWork_blendStateAttrMetaField,
    &g_beAction2InfoWork_textureStateAttrMetaField,
    &g_beAction2InfoWork_lightingStateAttrMetaField,
};
static int g_beAction2InfoWork_fieldOffsets[] = {
    8,
    12,
    16,
    17,
    20,
    24,
    28,
    32,
    40,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
};

void beAction2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2InfoWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beAction2InfoWork_ctorTable, 0x15);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036d9f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x11));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00138f20();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x12));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00139640();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x13));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_001313d0();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0x14));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = FUN_00135e60();
    igMetaObject_NameFields(temp_s0, g_beAction2InfoWork_fieldTable, g_beAction2InfoWork_fieldHandles, g_beAction2InfoWork_fieldOffsets, temp_s2);
}

