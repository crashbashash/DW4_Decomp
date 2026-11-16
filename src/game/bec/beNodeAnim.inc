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

igMetaObject *beNodeAnim_ResolveMetaObject(void) {
    igMetaObject *g = g_beNodeAnim_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNodeAnim_EnsureRegistered();
    }
    return g_beNodeAnim_metaObject;
}

int beNodeAnim_GetVTable(void) {
    beNodeAnim obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beNodeAnim_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beNodeAnim_vtable[0];
    igGroup_Destroy(&obj, 0);
    return vtable;
}

void beNodeAnim_EnsureRegistered(void)
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
        beNodeAnim_StaticInitCallback, /* extra callback item */
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
    int base;
    void *meta;

    meta = (void *)g_beNodeAnim_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNodeAnim_ctorTable, 0xA);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base), 0x13DE4355);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), 0x77359400);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), ((long long)0xEE6B << 0x10) | 0x2800);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 4), 1);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 6), 1.0f);
    igMetaObject_NameFields(meta, g_beNodeAnim_fieldTable, g_beNodeAnim_fieldHandles, g_beNodeAnim_fieldOffsets, base);
}

void beNodeAnim_StaticInitCallback(void)
{
    beNodeAnim_RegisterTraversalFunction();
}

