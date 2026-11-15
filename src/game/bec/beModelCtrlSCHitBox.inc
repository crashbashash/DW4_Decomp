igMetaObject *g_beModelCtrlSCHitBox_metaObject;
igMetaField *g_beModelCtrlSCHitBox_kindMetaField;
igMetaField *g_beModelCtrlSCHitBox_bulletModeMetaField;
igMetaField *g_beModelCtrlSCHitBox_endFrameMetaField;
igMetaField *g_beModelCtrlSCHitBox_offsetMetaField;
igMetaField *g_beModelCtrlSCHitBox_boxSizeMetaField;
igMetaField *g_beModelCtrlSCHitBox_isPositionLockMetaField;

void beModelCtrlSCHitBox_Create(int arg0) {
    FUN_0034f7c0();
    igMetaObject_CreateInstance(*(int *)0x5887C8, arg0);
}

igMetaObject *FUN_0034f730(void) {
    if (g_beModelCtrlSCHitBox_metaObject == 0 || !isValid(g_beModelCtrlSCHitBox_metaObject)) FUN_0034f7c0();
    return g_beModelCtrlSCHitBox_metaObject;
}

int beModelCtrlSCHitBox_GetVTable(void) {
    struct Obj_34f780 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053af60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034f7c0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCHitBox_Register);
}

void *beModelCtrlSCHitBox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCHitBox_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCHitBox_GetMetaObject,
        "beModelCtrlSCHitBox",
        0x3c, /* instance size */
        beModelCtrlSCHitBox_GetVTable,
        beModelCtrlSCHitBox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCHitBox_GetMetaObject(void)
{
    FUN_0034f730();
}

static FieldFactory g_beModelCtrlSCHitBox_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlSCHitBox_fieldTable[] = {
    "_kind",
    "_bulletMode",
    "_endFrame",
    "_offset",
    "_boxSize",
    "_isPositionLock",
};
static igMetaField **g_beModelCtrlSCHitBox_fieldHandles[] = {
    &g_beModelCtrlSCHitBox_kindMetaField,
    &g_beModelCtrlSCHitBox_bulletModeMetaField,
    &g_beModelCtrlSCHitBox_endFrameMetaField,
    &g_beModelCtrlSCHitBox_offsetMetaField,
    &g_beModelCtrlSCHitBox_boxSizeMetaField,
    &g_beModelCtrlSCHitBox_isPositionLockMetaField,
};
static int g_beModelCtrlSCHitBox_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    44,
    56,
};

void beModelCtrlSCHitBox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSCHitBox_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlSCHitBox_ctorTable, 6);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlSCHitBox_fieldTable, g_beModelCtrlSCHitBox_fieldHandles, g_beModelCtrlSCHitBox_fieldOffsets, temp_s1);
}

