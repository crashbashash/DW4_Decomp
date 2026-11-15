igMetaObject *g_beModelCtrlMoveObject_metaObject;
igMetaField *g_beModelCtrlMoveObject_isRunMetaField;
igMetaField *g_beModelCtrlMoveObject_endTimeMetaField;
igMetaField *g_beModelCtrlMoveObject_modeMetaField;
igMetaField *g_beModelCtrlMoveObject_valueMetaField;
igMetaField *g_beModelCtrlMoveObject_accMetaField;
igMetaField *g_beModelCtrlMoveObject_speedMetaField;
igMetaField *g_beModelCtrlMoveObject_isSeqStopMetaField;
igMetaField *g_beModelCtrlMoveObject_stopValueMetaField;
igMetaField *g_beModelCtrlMoveObject_stopFrameMetaField;

void beModelCtrlMoveObject_Create(int arg0) {
    FUN_00352a10();
    igMetaObject_CreateInstance(*(int *)0x588B48, arg0);
}

igMetaObject *FUN_00352980(void) {
    igMetaObject *g = g_beModelCtrlMoveObject_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00352a10();
    return g_beModelCtrlMoveObject_metaObject;
}

int beModelCtrlMoveObject_GetVTable(void) {
    struct Obj_3529d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00537cf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00352a10(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObject_Register);
}

void *beModelCtrlMoveObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMoveObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlMoveObject_GetMetaObject,
        "beModelCtrlMoveObject",
        0x2c, /* instance size */
        beModelCtrlMoveObject_GetVTable,
        beModelCtrlMoveObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMoveObject_GetMetaObject(void)
{
    FUN_00352980();
}

static FieldFactory g_beModelCtrlMoveObject_ctorTable[] = {
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlMoveObject_fieldTable[] = {
    "_isRun",
    "_endTime",
    "_mode",
    "_value",
    "_acc",
    "_speed",
    "_isSeqStop",
    "_stopValue",
    "_stopFrame",
};
static igMetaField **g_beModelCtrlMoveObject_fieldHandles[] = {
    &g_beModelCtrlMoveObject_isRunMetaField,
    &g_beModelCtrlMoveObject_endTimeMetaField,
    &g_beModelCtrlMoveObject_modeMetaField,
    &g_beModelCtrlMoveObject_valueMetaField,
    &g_beModelCtrlMoveObject_accMetaField,
    &g_beModelCtrlMoveObject_speedMetaField,
    &g_beModelCtrlMoveObject_isSeqStopMetaField,
    &g_beModelCtrlMoveObject_stopValueMetaField,
    &g_beModelCtrlMoveObject_stopFrameMetaField,
};
static int g_beModelCtrlMoveObject_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlMoveObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlMoveObject_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlMoveObject_ctorTable, 9);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))), 0.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3))), 0.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4))), 0.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5))), 0.0f);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlMoveObject_fieldTable, g_beModelCtrlMoveObject_fieldHandles, g_beModelCtrlMoveObject_fieldOffsets, temp_s1);
}

