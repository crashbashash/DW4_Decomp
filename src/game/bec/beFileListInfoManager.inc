igMetaObject *g_beFileListInfoManager_metaObject;
igMetaField *g_beFileListInfoManager_systemMetaField;
igMetaField *g_beFileListInfoManager_messengerMetaField;
igMetaField *g_beFileListInfoManager_sceneInfoManagerMetaField;
igMetaField *g_beFileListInfoManager_isReadOnetimeMetaField;
igMetaField *g_beFileListInfoManager_onetimeCountMetaField;
igMetaField *g_beFileListInfoManager_fnamesMetaField;
igMetaField *g_beFileListInfoManager_infoListMetaField;
igMetaField *g_beFileListInfoManager_dirListMetaField;
igMetaField *g_beFileListInfoManager_readInfoListMetaField;
igMetaField *g_beFileListInfoManager_importantInfoListMetaField;
igMetaField *g_beFileListInfoManager_loadedMetaField;
igMetaField *g_beFileListInfoManager_procMetaField;

void beFileListInfoManager_CreateInstance(int arg0) {
    FUN_003629b0();
    igMetaObject_CreateInstance(*(int *)0x5896F8, arg0);
}

igMetaObject *FUN_00362830(void) {
    if (g_beFileListInfoManager_metaObject == 0) {
        g_beFileListInfoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beFileListInfoManager_metaObject;
}

void *FUN_00362880(void) {
    igMetaObject *g = g_beFileListInfoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003629b0();
    }
    return g_beFileListInfoManager_metaObject;
}

int beFileListInfoManager_GetVTable(void) {
    struct Obj_3628d0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053a4e0[0];
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053a4e0[0];
    igSmartPointer_igInfoList_Destruct(&obj.w13, -1);
    igSmartPointer_igInfoList_Destruct(&obj.w12, -1);
    igSmartPointer_igDirectoryList_Destruct(&obj.w11, -1);
    igSmartPointer_igInfoList_Destruct(&obj.w10, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.w9, -1);
    FUN_00231030(&obj, 0);
    return t;
}

void FUN_003629b0(void)
{
    igMetaObject_RunStaticInit(beFileListInfoManager_Register);
}

static igMetaObjectCallback g_beFileListInfoManager_callbackList[] = { FUN_00342f30, FUN_00357d10, FUN_00459e40, igStringRefList_EnsureRegistered, igInfoList_EnsureRegistered, igDirectoryList_EnsureRegistered, 0 };

void *beFileListInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFileListInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beFileListInfoManager_GetMetaObject,
        "beFileListInfoManager",
        0x40, /* instance size */
        beFileListInfoManager_GetVTable,
        beFileListInfoManager_InitFields,
        0, /* extra callback item */
        g_beFileListInfoManager_callbackList /* callback list */
    );
}

void beFileListInfoManager_GetMetaObject(void)
{
    FUN_00362880();
}

static FieldFactory g_beFileListInfoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beFileListInfoManager_fieldTable[] = {
    "_system",
    "_messenger",
    "_sceneInfoManager",
    "_isReadOnetime",
    "_onetimeCount",
    "_fnames",
    "_infoList",
    "_dirList",
    "_readInfoList",
    "_importantInfoList",
    "_loaded",
    "_proc",
};
static igMetaField **g_beFileListInfoManager_fieldHandles[] = {
    &g_beFileListInfoManager_systemMetaField,
    &g_beFileListInfoManager_messengerMetaField,
    &g_beFileListInfoManager_sceneInfoManagerMetaField,
    &g_beFileListInfoManager_isReadOnetimeMetaField,
    &g_beFileListInfoManager_onetimeCountMetaField,
    &g_beFileListInfoManager_fnamesMetaField,
    &g_beFileListInfoManager_infoListMetaField,
    &g_beFileListInfoManager_dirListMetaField,
    &g_beFileListInfoManager_readInfoListMetaField,
    &g_beFileListInfoManager_importantInfoListMetaField,
    &g_beFileListInfoManager_loadedMetaField,
    &g_beFileListInfoManager_procMetaField,
};
static int g_beFileListInfoManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
};

void beFileListInfoManager_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s1;

    temp_s1 = (void *)g_beFileListInfoManager_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beFileListInfoManager_ctorTable, 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00357910();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igDirectoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beFileListInfoManager_fieldTable, g_beFileListInfoManager_fieldHandles, g_beFileListInfoManager_fieldOffsets, temp_s0);
}

