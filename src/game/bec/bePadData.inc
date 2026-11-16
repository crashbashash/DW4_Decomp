igMetaObject *g_bePadData_metaObject;
igMetaField *g_bePadData_isConnectMetaField;
igMetaField *g_bePadData_LStickMetaField;
igMetaField *g_bePadData_RStickMetaField;
igMetaField *g_bePadData_lTrgMetaField;
igMetaField *g_bePadData_lRptMetaField;
igMetaField *g_bePadData_lStkMetaField;
igMetaField *g_bePadData_lLastMetaField;
igMetaField *g_bePadData_lTimeMetaField;
igMetaField *g_bePadData_rTrgMetaField;
igMetaField *g_bePadData_rRptMetaField;
igMetaField *g_bePadData_rStkMetaField;
igMetaField *g_bePadData_rLastMetaField;
igMetaField *g_bePadData_rTimeMetaField;
igMetaField *g_bePadData_buttonMetaField;
igMetaField *g_bePadData_triggerMetaField;
igMetaField *g_bePadData_repeatMetaField;
igMetaField *g_bePadData_lastMetaField;
igMetaField *g_bePadData_rptimeMetaField;
igMetaField *g_bePadData_enaLenMetaField;
igMetaField *g_bePadData_adAngleMetaField;
igMetaField *g_bePadData_1sttimeMetaField;
igMetaField *g_bePadData_2ndtimeMetaField;

void bePadData_Create(int arg0) {
    bePadData_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588550, arg0);
}

void *bePadData_GetMetaObject(void) {
    igMetaObject *g = g_bePadData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadData_EnsureRegistered();
    }
    return g_bePadData_metaObject;
}

int bePadData_GetVTable(void) {
    struct Obj_34cee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_bePadData_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void bePadData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadData_Register);
}

void *bePadData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePadData_GetMetaObjectFunction,
        "bePadData",
        0x68, /* instance size */
        bePadData_GetVTable,
        bePadData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePadData_GetMetaObjectFunction(void)
{
    bePadData_GetMetaObject();
}

static FieldFactory g_bePadData_ctorTable[] = {
    igBoolMetaField_Create,
    FUN_00187b50,
    FUN_00187b50,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_bePadData_fieldTable[] = {
    "_isConnect",
    "_LStick",
    "_RStick",
    "_lTrg",
    "_lRpt",
    "_lStk",
    "_lLast",
    "_lTime",
    "_rTrg",
    "_rRpt",
    "_rStk",
    "_rLast",
    "_rTime",
    "_button",
    "_trigger",
    "_repeat",
    "_last",
    "_rptime",
    "_enaLen",
    "_adAngle",
    "_1sttime",
    "_2ndtime",
};
static igMetaField **g_bePadData_fieldHandles[] = {
    &g_bePadData_isConnectMetaField,
    &g_bePadData_LStickMetaField,
    &g_bePadData_RStickMetaField,
    &g_bePadData_lTrgMetaField,
    &g_bePadData_lRptMetaField,
    &g_bePadData_lStkMetaField,
    &g_bePadData_lLastMetaField,
    &g_bePadData_lTimeMetaField,
    &g_bePadData_rTrgMetaField,
    &g_bePadData_rRptMetaField,
    &g_bePadData_rStkMetaField,
    &g_bePadData_rLastMetaField,
    &g_bePadData_rTimeMetaField,
    &g_bePadData_buttonMetaField,
    &g_bePadData_triggerMetaField,
    &g_bePadData_repeatMetaField,
    &g_bePadData_lastMetaField,
    &g_bePadData_rptimeMetaField,
    &g_bePadData_enaLenMetaField,
    &g_bePadData_adAngleMetaField,
    &g_bePadData_1sttimeMetaField,
    &g_bePadData_2ndtimeMetaField,
};
static int g_bePadData_fieldOffsets[] = {
    8,
    12,
    20,
    28,
    32,
    36,
    40,
    44,
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
    96,
    100,
};

void bePadData_InitFields(void) {
    int sp38[2];
    int sp30[2];
    int temp_a0;
    int temp_a0_2;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_bePadData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_bePadData_ctorTable, 0x16);
    temp_a0 = ((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    sp38[0] = 0;
    sp38[1] = 0;
    FUN_0018e2f0(temp_a0, sp38);
    temp_a0_2 = ((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    sp30[0] = 0;
    sp30[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp30);
    igMetaObject_NameFields(temp_s0, g_bePadData_fieldTable, g_bePadData_fieldHandles, g_bePadData_fieldOffsets, temp_s1);
}

