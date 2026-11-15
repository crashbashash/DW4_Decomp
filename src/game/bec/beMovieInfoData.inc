igMetaObject *g_beMovieInfoData_metaObject;
igMetaField *g_beMovieInfoData_parentLayerMetaField;
igMetaField *g_beMovieInfoData_callLuaNameMetaField;
igMetaField *g_beMovieInfoData_sceneInfoMetaField;

void *FUN_0034ec80(void) {
    igMetaObject *g = g_beMovieInfoData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034ed80();
    }
    return g_beMovieInfoData_metaObject;
}

int beMovieInfoData_GetVTable(void) {
    struct Obj_34ecd0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00538040[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538040[0];
    FUN_001d3650(&obj.w6, -1);
    FUN_00130720(&obj.w5, -1);
    FUN_00130720(&obj.w4, -1);
    FUN_00344030((struct W_344030 *)&obj, (short)0);
    return t;
}

void FUN_0034ed80(void)
{
    igMetaObject_RunStaticInit(beMovieInfoData_Register);
}

static igMetaObjectCallback g_beMovieInfoData_callbackList[] = { FUN_0019b270, 0 };

void *beMovieInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMovieInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beMovieInfoData_GetMetaObject,
        "beMovieInfoData",
        0x1c, /* instance size */
        beMovieInfoData_GetVTable,
        beMovieInfoData_InitFields,
        0, /* extra callback item */
        g_beMovieInfoData_callbackList /* callback list */
    );
}

void beMovieInfoData_GetMetaObject(void)
{
    FUN_0034ec80();
}

static FieldFactory g_beMovieInfoData_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMovieInfoData_fieldTable[] = {
    "_parentLayer",
    "_callLuaName",
    "_sceneInfo",
};
static igMetaField **g_beMovieInfoData_fieldHandles[] = {
    &g_beMovieInfoData_parentLayerMetaField,
    &g_beMovieInfoData_callLuaNameMetaField,
    &g_beMovieInfoData_sceneInfoMetaField,
};
static int g_beMovieInfoData_fieldOffsets[] = {
    16,
    20,
    24,
};

void beMovieInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMovieInfoData_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMovieInfoData_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019aee0();
    igMetaObject_NameFields(temp_s0, g_beMovieInfoData_fieldTable, g_beMovieInfoData_fieldHandles, g_beMovieInfoData_fieldOffsets, temp_s2);
}

igMetaEnum *g_beMovieInfoData_messageMetaEnum;
static const char *g_beMovieInfoData_messageNames[] = {
    "STOP", "PLAY", "PAUSE", "ISPLAY",
};
static int g_beMovieInfoData_messageValues[] = {
    0, 1, 2, 3,
};

igMetaEnum *FUN_0034eed0(void) {
    if (g_beMovieInfoData_messageMetaEnum == 0) {
        g_beMovieInfoData_messageMetaEnum = igMetaEnum_Create("Message", g_beMovieInfoData_messageNames, g_beMovieInfoData_messageValues, 4);
    }
    return g_beMovieInfoData_messageMetaEnum;
}

