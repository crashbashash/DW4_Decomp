void beFileListInfoManager_CreateInstance(int arg0) {
    FUN_003629b0();
    igMetaObject_CreateInstance(*(int *)0x5896F8, arg0);
}

igMetaObject *FUN_00362830(void) {
    if (g_beFileListInfoManager_metaObject[0] == 0) {
        g_beFileListInfoManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beFileListInfoManager_metaObject[0];
}

void *FUN_00362880(void) {
    igMetaObject *g = g_beFileListInfoManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003629b0();
    }
    return g_beFileListInfoManager_metaObject[0];
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
    FUN_001d35d0(&obj.w13, -1);
    FUN_001d35d0(&obj.w12, -1);
    igSmartPointer_igDirectoryList_Destruct(&obj.w11, -1);
    FUN_001d35d0(&obj.w10, -1);
    ObjectRef_Destruct_001c6460(&obj.w9, -1);
    FUN_00231030(&obj, 0);
    return t;
}

void FUN_003629b0(void)
{
    igMetaObject_RunStaticInit(beFileListInfoManager_Register);
}

void *beFileListInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFileListInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beFileListInfoManager_GetMetaObject,
        beFileListInfoManager_className,
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

    temp_s1 = (void *)g_beFileListInfoManager_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beFileListInfoManager_ctorTable[0], 0xC);
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
    igMetaObject_NameFields(temp_s1, &g_beFileListInfoManager_fieldTable[0], &DAT_004c6ef0[0], &DAT_004c6f20[0], temp_s0);
}

