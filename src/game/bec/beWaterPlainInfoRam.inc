igMetaObject *g_beWaterPlainInfoRam_metaObject;
igMetaField *g_beWaterPlainInfoRam_dampeningCoefficientMetaField;
igMetaField *g_beWaterPlainInfoRam_AMetaField;
igMetaField *g_beWaterPlainInfoRam_BMetaField;
igMetaField *g_beWaterPlainInfoRam_waveSpeedMetaField;
igMetaField *g_beWaterPlainInfoRam_shallminMetaField;
igMetaField *g_beWaterPlainInfoRam_shallmaxMetaField;
igMetaField *g_beWaterPlainInfoRam_shalldampMetaField;
igMetaField *g_beWaterPlainInfoRam_deepminMetaField;
igMetaField *g_beWaterPlainInfoRam_deepmaxMetaField;
igMetaField *g_beWaterPlainInfoRam_deepdampMetaField;
igMetaField *g_beWaterPlainInfoRam_vertexArrayMetaField;
igMetaField *g_beWaterPlainInfoRam_dampeningGridMetaField;
igMetaField *g_beWaterPlainInfoRam_dplist2VertexNOMetaField;
igMetaField *g_beWaterPlainInfoRam_mapWidthMetaField;
igMetaField *g_beWaterPlainInfoRam_mapHeightMetaField;
igMetaField *g_beWaterPlainInfoRam_posMetaField;
igMetaField *g_beWaterPlainInfoRam_areaMaxMetaField;
igMetaField *g_beWaterPlainInfoRam_areaMinMetaField;
igMetaField *g_beWaterPlainInfoRam_xsizeMetaField;
igMetaField *g_beWaterPlainInfoRam_zsizeMetaField;
igMetaField *g_beWaterPlainInfoRam_cellSizeMetaField;
igMetaField *g_beWaterPlainInfoRam_gridListsMetaField;
igMetaField *g_beWaterPlainInfoRam_maxYMetaField;
igMetaField *g_beWaterPlainInfoRam_minYMetaField;
igMetaField *g_beWaterPlainInfoRam_defaultYMetaField;
igMetaField *g_beWaterPlainInfoRam_updateTimeMetaField;
igMetaField *g_beWaterPlainInfoRam_waterMoveMetaField;

void *FUN_00340090(void) {
    igMetaObject *g = g_beWaterPlainInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003402c0();
    }
    return g_beWaterPlainInfoRam_metaObject;
}

int beWaterPlainInfoRam_GetVTable(void) {
    struct Obj_3400e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &DAT_00539a70[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    obj.w38 = 0;
    obj.w44 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539a70[0];
    FUN_00340240((void **)&obj.w44, (long long)(-1));
    FUN_003401c0((struct Ref **)&obj.w38, (short)(-1));
    igSmartPointer_igIntList_Destruct(&obj.w23, -1);
    FUN_001354b0(&obj.w22, -1);
    FUN_001338d0(&obj.w21, -1);
    FUN_0033e920((S *)&obj, (long long)0);
    return t;
}

void **FUN_003401c0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_00340240(void **arg0, long long arg1) {
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

void FUN_003402c0(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfoRam_Register);
}

static igMetaObjectCallback g_beWaterPlainInfoRam_callbackList[] = { FUN_0014ba20, igFloatList_EnsureRegistered, igIntList_EnsureRegistered, igFloatListList_EnsureRegistered, FUN_003405c0, 0 };

void *beWaterPlainInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterPlainInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWaterPlainInfoRam_GetMetaObject,
        "beWaterPlainInfoRam",
        0xb8, /* instance size */
        beWaterPlainInfoRam_GetVTable,
        beWaterPlainInfoRam_InitFields,
        0, /* extra callback item */
        g_beWaterPlainInfoRam_callbackList /* callback list */
    );
}

void beWaterPlainInfoRam_GetMetaObject(void)
{
    FUN_00340090();
}

static FieldFactory g_beWaterPlainInfoRam_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    FUN_00187890,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWaterPlainInfoRam_fieldTable[] = {
    "_dampeningCoefficient",
    "_A",
    "_B",
    "_waveSpeed",
    "_shallmin",
    "_shallmax",
    "_shalldamp",
    "_deepmin",
    "_deepmax",
    "_deepdamp",
    "_vertexArray",
    "_dampeningGrid",
    "_dplist2VertexNO",
    "_mapWidth",
    "_mapHeight",
    "_pos",
    "_areaMax",
    "_areaMin",
    "_xsize",
    "_zsize",
    "_cellSize",
    "_gridLists",
    "_maxY",
    "_minY",
    "_defaultY",
    "_updateTime",
    "_waterMove",
};
static igMetaField **g_beWaterPlainInfoRam_fieldHandles[] = {
    &g_beWaterPlainInfoRam_dampeningCoefficientMetaField,
    &g_beWaterPlainInfoRam_AMetaField,
    &g_beWaterPlainInfoRam_BMetaField,
    &g_beWaterPlainInfoRam_waveSpeedMetaField,
    &g_beWaterPlainInfoRam_shallminMetaField,
    &g_beWaterPlainInfoRam_shallmaxMetaField,
    &g_beWaterPlainInfoRam_shalldampMetaField,
    &g_beWaterPlainInfoRam_deepminMetaField,
    &g_beWaterPlainInfoRam_deepmaxMetaField,
    &g_beWaterPlainInfoRam_deepdampMetaField,
    &g_beWaterPlainInfoRam_vertexArrayMetaField,
    &g_beWaterPlainInfoRam_dampeningGridMetaField,
    &g_beWaterPlainInfoRam_dplist2VertexNOMetaField,
    &g_beWaterPlainInfoRam_mapWidthMetaField,
    &g_beWaterPlainInfoRam_mapHeightMetaField,
    &g_beWaterPlainInfoRam_posMetaField,
    &g_beWaterPlainInfoRam_areaMaxMetaField,
    &g_beWaterPlainInfoRam_areaMinMetaField,
    &g_beWaterPlainInfoRam_xsizeMetaField,
    &g_beWaterPlainInfoRam_zsizeMetaField,
    &g_beWaterPlainInfoRam_cellSizeMetaField,
    &g_beWaterPlainInfoRam_gridListsMetaField,
    &g_beWaterPlainInfoRam_maxYMetaField,
    &g_beWaterPlainInfoRam_minYMetaField,
    &g_beWaterPlainInfoRam_defaultYMetaField,
    &g_beWaterPlainInfoRam_updateTimeMetaField,
    &g_beWaterPlainInfoRam_waterMoveMetaField,
};
static int g_beWaterPlainInfoRam_fieldOffsets[] = {
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
    104,
    116,
    128,
    140,
    144,
    148,
    152,
    156,
    160,
    164,
    168,
    176,
};

void beWaterPlainInfoRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beWaterPlainInfoRam_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beWaterPlainInfoRam_ctorTable, 0x1B);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b980();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igFloatListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_00340490();
    igMetaObject_NameFields(temp_s1, g_beWaterPlainInfoRam_fieldTable, g_beWaterPlainInfoRam_fieldHandles, g_beWaterPlainInfoRam_fieldOffsets, temp_s0);
}

