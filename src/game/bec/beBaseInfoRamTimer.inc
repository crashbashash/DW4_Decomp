igMetaObject *g_beBaseInfoRamTimer_metaObject;
igMetaField *g_beBaseInfoRamTimer_timeScaleMetaField;
igMetaField *g_beBaseInfoRamTimer_timeBiasMetaField;
igMetaField *g_beBaseInfoRamTimer_endTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_svWorldTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_svBeforTimeMetaField;
igMetaField *g_beBaseInfoRamTimer_keikaFrameMetaField;

void beBaseInfoRamTimer_Create(int arg0) {
    beBaseInfoRamTimer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589D78, arg0);
}

void *beBaseInfoRamTimer_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoRamTimer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBaseInfoRamTimer_EnsureRegistered();
    }
    return g_beBaseInfoRamTimer_metaObject;
}

int beBaseInfoRamTimer_GetVTable(void) {
    struct Obj_36a5a0 o;
    int temp_s0;
    void **q;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(&o);
    q = &o.s;
    *q = 0;
    o.vt = &g_igNamedObject_vtable[0];
    o.vt = &g_beBaseInfoRamTimer_vtable[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igNamedObject_vtable[0];
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoRamTimer_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBaseInfoRamTimer_ctorTable, 6);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1))), 1.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5))), 0.0f);
    igMetaObject_NameFields(temp_s0, g_beBaseInfoRamTimer_fieldTable, g_beBaseInfoRamTimer_fieldHandles, g_beBaseInfoRamTimer_fieldOffsets, temp_s1);
}

