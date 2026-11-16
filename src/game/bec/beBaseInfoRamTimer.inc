igMetaObject *g_beBaseInfoRamTimer_metaObject;
igMetaField *g_beBaseInfoRamTimer_timeScaleMetaField;
igMetaField *g_beBaseInfoRamTimer_timeBiasMetaField;
igMetaField *g_beBaseInfoRamTimer_endTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_svWorldTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_svBeforTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_keikaFrameMetaField;

beBaseInfoRamTimer *beBaseInfoRamTimer_Create(int allocator) {
    beBaseInfoRamTimer_EnsureRegistered();
    return (beBaseInfoRamTimer *)igMetaObject_CreateInstance(*(int *)0x589D78, allocator);
}

void *beBaseInfoRamTimer_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoRamTimer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBaseInfoRamTimer_EnsureRegistered();
    }
    return g_beBaseInfoRamTimer_metaObject;
}

int beBaseInfoRamTimer_GetVTable(void) {
    beBaseInfoRamTimer obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beBaseInfoRamTimer_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beBaseInfoRamTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamTimer_Register);
}

void *beBaseInfoRamTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoRamTimer_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBaseInfoRamTimer_GetMetaObjectFunction,
        "beBaseInfoRamTimer",
        0x40, /* instance size */
        beBaseInfoRamTimer_GetVTable,
        beBaseInfoRamTimer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBaseInfoRamTimer_GetMetaObjectFunction(void)
{
    beBaseInfoRamTimer_GetMetaObject();
}

static FieldFactory g_beBaseInfoRamTimer_ctorTable[] = {
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beBaseInfoRamTimer_fieldTable[] = {
    "_timeScale",
    "_timeBias",
    "_endTime",
    "_svWorldTime",
    "_svBeforTime",
    "_keikaFrame",
};
static igMetaField **g_beBaseInfoRamTimer_fieldHandles[] = {
    &g_beBaseInfoRamTimer_timeScaleMetaField,
    &g_beBaseInfoRamTimer_timeBiasMetaField,
    &g_beBaseInfoRamTimer_endTimeMetaField,
    &g_beBaseInfoRamTimer_svWorldTimeMetaField,
    &g_beBaseInfoRamTimer_svBeforTimeMetaField,
    &g_beBaseInfoRamTimer_keikaFrameMetaField,
};
static int g_beBaseInfoRamTimer_fieldOffsets[] = {
    16,
    24,
    32,
    40,
    48,
    56,
};

void beBaseInfoRamTimer_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beBaseInfoRamTimer_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBaseInfoRamTimer_ctorTable, 6);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(meta, base))), 1.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(meta, base + 5))), 0.0f);
    igMetaObject_NameFields(meta, g_beBaseInfoRamTimer_fieldTable, g_beBaseInfoRamTimer_fieldHandles, g_beBaseInfoRamTimer_fieldOffsets, base);
}

