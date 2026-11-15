igMetaObject *g_beMeterCtrlOneData_metaObject;
igMetaField *g_beMeterCtrlOneData_nodeMetaField;
igMetaField *g_beMeterCtrlOneData_maxValueFMetaField;
igMetaField *g_beMeterCtrlOneData_ratioTimeValueFMetaField;
igMetaField *g_beMeterCtrlOneData_addMaxValueFMetaField;
igMetaField *g_beMeterCtrlOneData_nowValueFMetaField;
igMetaField *g_beMeterCtrlOneData_dspValueFMetaField;
igMetaField *g_beMeterCtrlOneData_nonZeroTimeLMetaField;
igMetaField *g_beMeterCtrlOneData_nonMaxTimeLMetaField;
igMetaField *g_beMeterCtrlOneData_ketaKazuMetaField;
igMetaField *g_beMeterCtrlOneData_isChangeMetaField;
igMetaField *g_beMeterCtrlOneData_isZeroSuppMetaField;
igMetaField *g_beMeterCtrlOneData_isNotchModeMetaField;
igMetaField *g_beMeterCtrlOneData_hpMetaField;
igMetaField *g_beMeterCtrlOneData_mHpMetaField;

void *FUN_003572d0(void) {
    igMetaObject *g = g_beMeterCtrlOneData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00357450();
    }
    return g_beMeterCtrlOneData_metaObject;
}

int beMeterCtrlOneData_GetVTable(void) {
    struct Obj_357320 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536fe0[0];
    obj.w3 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536fe0[0];
    FUN_00350b10((void **)&obj.w17, (short)(-1));
    FUN_00350b10((void **)&obj.w16, (short)(-1));
    FUN_003573d0((void **)&obj.w3, (long long)(-1));
    FUN_00131bc0(&obj, 0);
    return t;
}

void **FUN_003573d0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00357450(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlOneData_Register);
}

static igMetaObjectCallback g_beMeterCtrlOneData_callbackList[] = { FUN_00356de0, FUN_00365680, 0 };

void *beMeterCtrlOneData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlOneData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMeterCtrlOneData_GetMetaObject,
        "beMeterCtrlOneData",
        0x48, /* instance size */
        beMeterCtrlOneData_GetVTable,
        beMeterCtrlOneData_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlOneData_callbackList /* callback list */
    );
}

void beMeterCtrlOneData_GetMetaObject(void)
{
    FUN_003572d0();
}

static FieldFactory g_beMeterCtrlOneData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMeterCtrlOneData_fieldTable[] = {
    "_node",
    "_maxValueF",
    "_ratioTimeValueF",
    "_addMaxValueF",
    "_nowValueF",
    "_dspValueF",
    "_nonZeroTimeL",
    "_nonMaxTimeL",
    "_ketaKazu",
    "_isChange",
    "_isZeroSupp",
    "_isNotchMode",
    "_hp",
    "_mHp",
};
static igMetaField **g_beMeterCtrlOneData_fieldHandles[] = {
    &g_beMeterCtrlOneData_nodeMetaField,
    &g_beMeterCtrlOneData_maxValueFMetaField,
    &g_beMeterCtrlOneData_ratioTimeValueFMetaField,
    &g_beMeterCtrlOneData_addMaxValueFMetaField,
    &g_beMeterCtrlOneData_nowValueFMetaField,
    &g_beMeterCtrlOneData_dspValueFMetaField,
    &g_beMeterCtrlOneData_nonZeroTimeLMetaField,
    &g_beMeterCtrlOneData_nonMaxTimeLMetaField,
    &g_beMeterCtrlOneData_ketaKazuMetaField,
    &g_beMeterCtrlOneData_isChangeMetaField,
    &g_beMeterCtrlOneData_isZeroSuppMetaField,
    &g_beMeterCtrlOneData_isNotchModeMetaField,
    &g_beMeterCtrlOneData_hpMetaField,
    &g_beMeterCtrlOneData_mHpMetaField,
};
static int g_beMeterCtrlOneData_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    40,
    48,
    56,
    60,
    61,
    62,
    64,
    68,
};

void beMeterCtrlOneData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beMeterCtrlOneData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMeterCtrlOneData_ctorTable, 0xE);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00356cc0();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0.0f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_00365550();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_00365550();
    igMetaObject_NameFields(temp_s0, g_beMeterCtrlOneData_fieldTable, g_beMeterCtrlOneData_fieldHandles, g_beMeterCtrlOneData_fieldOffsets, temp_s2);
}

igMetaEnum *g_beMeterCtrlOneData_msgActionMetaEnum;
static const char *g_beMeterCtrlOneData_msgActionNames[] = {
    "GETVALUE", "SETVALUE", "ADDVALUE", "GETPERCENT",
    "SETPERCENT", "ADDPERCENT", "SETMAXVALUE", "SETMODELHP",
};
static int g_beMeterCtrlOneData_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *FUN_00357600(void) {
    if (g_beMeterCtrlOneData_msgActionMetaEnum == 0) {
        g_beMeterCtrlOneData_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beMeterCtrlOneData_msgActionNames, g_beMeterCtrlOneData_msgActionValues, 8);
    }
    return g_beMeterCtrlOneData_msgActionMetaEnum;
}

