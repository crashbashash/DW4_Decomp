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

void *beWaterPlainInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beWaterPlainInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterPlainInfoRam_EnsureRegistered();
    }
    return g_beWaterPlainInfoRam_metaObject;
}

int beWaterPlainInfoRam_GetVTable(void) {
    struct Obj_3400e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &g_beWaterPlainInfoRam_vtable[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    obj.w38 = 0;
    obj.w44 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beWaterPlainInfoRam_vtable[0];
    FUN_00340240((igSmartPointer<igObject> *)&obj.w44, (long long)(-1));
    FUN_003401c0((igSmartPointer<igObject> *)&obj.w38, (short)(-1));
    igSmartPointer_igIntList_Destruct(&obj.w23, -1);
    FUN_001354b0(&obj.w22, -1);
    FUN_001338d0(&obj.w21, -1);
    FUN_0033e920((S *)&obj, (long long)0);
    return t;
}

igSmartPointer<igObject> *FUN_003401c0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_00340240(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beWaterPlainInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfoRam_Register);
}

static igMetaObjectCallback g_beWaterPlainInfoRam_callbackList[] = { igVertexArray_EnsureRegistered, igFloatList_EnsureRegistered, igIntList_EnsureRegistered, igFloatListList_EnsureRegistered, beWaterMove_EnsureRegistered, 0 };

void *beWaterPlainInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterPlainInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWaterPlainInfoRam_GetMetaObjectFunction,
        "beWaterPlainInfoRam",
        0xb8, /* instance size */
        beWaterPlainInfoRam_GetVTable,
        beWaterPlainInfoRam_InitFields,
        0, /* extra callback item */
        g_beWaterPlainInfoRam_callbackList /* callback list */
    );
}

void beWaterPlainInfoRam_GetMetaObjectFunction(void)
{
    beWaterPlainInfoRam_GetMetaObject();
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
    void *vertexArray;
    void *dampeningGrid;
    void *dplist2VertexNO;
    void *gridLists;
    void *waterMove;
    void *meta;
    int base;

    meta = (void *)g_beWaterPlainInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWaterPlainInfoRam_ctorTable, 0x1B);
    vertexArray = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)vertexArray)->_metaObject = igVertexArray_GetOrCreateMetaObject();
    dampeningGrid = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)dampeningGrid)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)dampeningGrid)->_construct = 1;
    dplist2VertexNO = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)dplist2VertexNO)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)dplist2VertexNO)->_construct = 1;
    gridLists = (void *)(igMetaObject_GetFieldAt(meta, base + 0x15));
    ((igObjectRefMetaField *)gridLists)->_metaObject = igFloatListList_GetOrCreateMetaObject();
    ((igRefMetaField *)gridLists)->_construct = 1;
    waterMove = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1A));
    ((igObjectRefMetaField *)waterMove)->_metaObject = (int)beWaterMove_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beWaterPlainInfoRam_fieldTable, g_beWaterPlainInfoRam_fieldHandles, g_beWaterPlainInfoRam_fieldOffsets, base);
}

