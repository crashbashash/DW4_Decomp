igMetaObject *g_beMovieInfoData_metaObject;
igMetaField *g_beMovieInfoData_parentLayerMetaField;
igMetaField *g_beMovieInfoData_callLuaNameMetaField;
igMetaField *g_beMovieInfoData_sceneInfoMetaField;

void *beMovieInfoData_GetMetaObject(void) {
    igMetaObject *g = g_beMovieInfoData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMovieInfoData_EnsureRegistered();
    }
    return g_beMovieInfoData_metaObject;
}

int beMovieInfoData_GetVTable(void) {
    beMovieInfoData obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beMovieInfoData_vtable[0];
    obj._parentLayer = 0;
    obj._callLuaName = 0;
    obj._sceneInfo = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beMovieInfoData_vtable[0];
    igSmartPointer_igSceneInfo_Destruct(&obj._sceneInfo, -1);
    igStringRef_Destruct(&obj._callLuaName, -1);
    igStringRef_Destruct(&obj._parentLayer, -1);
    beBaseInfoData_Destroy((beBaseInfoData *)&obj, (short)0);
    return vtable;
}

void beMovieInfoData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMovieInfoData_Register);
}

static igMetaObjectCallback g_beMovieInfoData_callbackList[] = { igSceneInfo_EnsureRegistered, 0 };

void *beMovieInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMovieInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beMovieInfoData_GetMetaObjectFunction,
        "beMovieInfoData",
        0x1c, /* instance size */
        beMovieInfoData_GetVTable,
        beMovieInfoData_InitFields,
        0, /* extra callback item */
        g_beMovieInfoData_callbackList /* callback list */
    );
}

void beMovieInfoData_GetMetaObjectFunction(void)
{
    beMovieInfoData_GetMetaObject();
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
    int base;
    void *sceneInfo;
    void *meta;

    meta = (void *)g_beMovieInfoData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMovieInfoData_ctorTable, 3);
    sceneInfo = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)sceneInfo)->_metaObject = igSceneInfo_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beMovieInfoData_fieldTable, g_beMovieInfoData_fieldHandles, g_beMovieInfoData_fieldOffsets, base);
}

igMetaEnum *g_beMovieInfoData_messageMetaEnum;
static const char *g_beMovieInfoData_messageNames[] = {
    "STOP", "PLAY", "PAUSE", "ISPLAY",
};
static int g_beMovieInfoData_messageValues[] = {
    0, 1, 2, 3,
};

igMetaEnum *beMovie_GetMessageEnum(void) {
    if (g_beMovieInfoData_messageMetaEnum == 0) {
        g_beMovieInfoData_messageMetaEnum = igMetaEnum_Create("Message", g_beMovieInfoData_messageNames, g_beMovieInfoData_messageValues, 4);
    }
    return g_beMovieInfoData_messageMetaEnum;
}

