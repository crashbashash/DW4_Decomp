igMetaObject *g_beNodeAnim_metaObject;
igMetaField *g_beNodeAnim_startTimeMetaField;
igMetaField *g_beNodeAnim_loop1TimeMetaField;
igMetaField *g_beNodeAnim_loop2TimeMetaField;
igMetaField *g_beNodeAnim_stopTimeMetaField;
igMetaField *g_beNodeAnim_isFirstTimeMetaField;
igMetaField *g_beNodeAnim_timeMetaField;
igMetaField *g_beNodeAnim_timeScaleMetaField;
igMetaField *g_beNodeAnim_timeBiasMetaField;
igMetaField *g_beNodeAnim_beforeTimeMetaField;
igMetaField *g_beNodeAnim_playTimeMetaField;

void *beNodeAnim_ResolveMetaObject(void) {
    igMetaObject *g = g_beNodeAnim_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034e930();
    }
    return g_beNodeAnim_metaObject;
}

int beNodeAnim_GetVTable(void) {
    struct Obj_34e8c0 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.f28 = 0;
    o.vt = &DAT_005381b0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005381b0[0];
    
    FUN_00195a90(&o, 0);
    return r;
}

void FUN_0034e930(void)
{
    igMetaObject_RunStaticInit(beNodeAnim_Register);
}

void *beNodeAnim_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNodeAnim_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beNodeAnim_GetMetaObject,
        "beNodeAnim",
        0x70, /* instance size */
        beNodeAnim_GetVTable,
        beNodeAnim_InitFields,
        FUN_0034eaf0, /* extra callback item */
        0 /* callback list */
    );
}

void beNodeAnim_GetMetaObject(void)
{
    beNodeAnim_ResolveMetaObject();
}

static FieldFactory g_beNodeAnim_ctorTable[] = {
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beNodeAnim_fieldTable[] = {
    "_startTime",
    "_loop1Time",
    "_loop2Time",
    "_stopTime",
    "_isFirstTime",
    "_time",
    "_timeScale",
    "_timeBias",
    "_beforeTime",
    "_playTime",
};
static igMetaField **g_beNodeAnim_fieldHandles[] = {
    &g_beNodeAnim_startTimeMetaField,
    &g_beNodeAnim_loop1TimeMetaField,
    &g_beNodeAnim_loop2TimeMetaField,
    &g_beNodeAnim_stopTimeMetaField,
    &g_beNodeAnim_isFirstTimeMetaField,
    &g_beNodeAnim_timeMetaField,
    &g_beNodeAnim_timeScaleMetaField,
    &g_beNodeAnim_timeBiasMetaField,
    &g_beNodeAnim_beforeTimeMetaField,
    &g_beNodeAnim_playTimeMetaField,
};
static int g_beNodeAnim_fieldOffsets[] = {
    32,
    40,
    48,
    56,
    64,
    72,
    80,
    88,
    96,
    104,
};

void beNodeAnim_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNodeAnim_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNodeAnim_ctorTable, 0xA);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0x13DE4355);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0x77359400);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), ((long long)0xEE6B << 0x10) | 0x2800);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6), 1.0f);
    igMetaObject_NameFields(temp_s0, g_beNodeAnim_fieldTable, g_beNodeAnim_fieldHandles, g_beNodeAnim_fieldOffsets, temp_s1);
}

void FUN_0034eaf0(void)
{
    beNodeAnim_RegisterTraversalFunction();
}

