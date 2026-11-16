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

bePadData *bePadData_Create(int allocator) {
    bePadData_EnsureRegistered();
    return (bePadData *)igMetaObject_CreateInstance(g_bePadData_metaObject, (igMemoryPoolView *)allocator);
}

void *bePadData_GetMetaObject(void) {
    igMetaObject *g = g_bePadData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadData_EnsureRegistered();
    }
    return g_bePadData_metaObject;
}

int bePadData_GetVTable(void) {
    bePadData obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_bePadData_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void bePadData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadData_Register);
}

CallbackArray *bePadData_Register(void) {
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
    igVec2fMetaField_CreateInstance,
    igVec2fMetaField_CreateInstance,
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
    int lStickDefault[2];
    int rStickDefault[2];
    int LStick;
    int RStick;
    int base;
    igMetaObject *meta;

    meta = g_bePadData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePadData_ctorTable, 0x16);
    LStick = ((int)igMetaObject_GetFieldAt(meta, base + 1));
    lStickDefault[0] = 0;
    lStickDefault[1] = 0;
    igVec2fMetaField_SetDefault(LStick, lStickDefault);
    RStick = ((int)igMetaObject_GetFieldAt(meta, base + 2));
    rStickDefault[0] = 0;
    rStickDefault[1] = 0;
    igVec2fMetaField_SetDefault(RStick, rStickDefault);
    igMetaObject_NameFields(meta, g_bePadData_fieldTable, g_bePadData_fieldHandles, g_bePadData_fieldOffsets, base);
}

