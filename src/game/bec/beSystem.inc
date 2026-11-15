igMetaObject *g_beSystem_metaObject;
igMetaField *g_beSystem_isShutDownMetaField;
igMetaField *g_beSystem_svWorldTimeLMetaField;
igMetaField *g_beSystem_frameTimeLMetaField;
igMetaField *g_beSystem_frameTimeFMetaField;
igMetaField *g_beSystem_isActiveMetaField;
igMetaField *g_beSystem_isFirstTimeMetaField;
igMetaField *g_beSystem_isFrameSkipMetaField;
igMetaField *g_beSystem_randomMetaField;
igMetaField *g_beSystem_readFileListMetaField;
igMetaField *g_beSystem_stageNameMetaField;
igMetaField *g_beSystem_nextStageMetaField;
igMetaField *g_beSystem_isStageLoopMetaField;
igMetaField *g_beSystem_bootDirectoryMetaField;
igMetaField *g_beSystem_globalStrObjMetaField;
igMetaField *g_beSystem_discErrInfosMetaField;
igMetaField *g_beSystem_viewerSceneMetaField;
igMetaField *g_beSystem_dvdStatMetaField;
igMetaField *g_beSystem_execDvdErrMetaField;
igMetaField *g_beSystem_isDvdErrMetaField;
igMetaField *g_beSystem_isNowFreezeMetaField;
igMetaField *g_beSystem_isNowPadEnableMetaField;
igMetaField *g_beSystem_isResetEnableMetaField;
igMetaField *g_beSystem_isResetNowMetaField;
igMetaField *g_beSystem_isResetLastMetaField;
igMetaField *g_beSystem_isResetReleaseMetaField;
igMetaField *g_beSystem_isSResetEnableMetaField;

void beSystem_CreateInstance(int arg0) {
    FUN_00342f30();
    igMetaObject_CreateInstance(*(int *)0x587D08, arg0);
}

igMetaObject *FUN_00342ce0(void) {
    if (g_beSystem_metaObject == 0) {
        g_beSystem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSystem_metaObject;
}

void *FUN_00342d30(void) {
    unsigned char b;
    if (((void * *)&g_beSystem_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beSystem_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00342f30();
done:
    return ((void * *)&g_beSystem_metaObject)[0];
}

int beSystem_GetVTable(void) {
    struct Obj_342d80 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053b510[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b510[0];
    FUN_00229350(&obj.w20, -1);
    igSmartPointer_igInfoList_Destruct(&obj.w19, -1);
    igSmartPointer_igStringObj_Destruct(&obj.w18, -1);
    igSmartPointer_igDirectory_Destruct(&obj.w17, -1);
    igStringRef_Destruct(&obj.w15, -1);
    igStringRef_Destruct(&obj.w14, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.w13, -1);
    FUN_00342eb0((void **)&obj.w12, (short)(-1));
    FUN_00231030(&obj, 0);
    return t;
}

void **FUN_00342eb0(void **arg0, short arg1) {
    S_temp_a0_342eb0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_342eb0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00342f30(void)
{
    igMetaObject_RunStaticInit(beSystem_Register);
}

static igMetaObjectCallback g_beSystem_callbackList[] = { FUN_001e42e0, igStringRefList_EnsureRegistered, igDirectory_EnsureRegistered, igStringObj_EnsureRegistered, igInfoList_EnsureRegistered, FUN_0019f330, 0 };

void *beSystem_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSystem_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beSystem_GetMetaObject,
        "beSystem",
        0x68, /* instance size */
        beSystem_GetVTable,
        beSystem_InitFields,
        0, /* extra callback item */
        g_beSystem_callbackList /* callback list */
    );
}

void beSystem_GetMetaObject(void)
{
    FUN_00342d30();
}

static FieldFactory g_beSystem_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beSystem_fieldTable[] = {
    "_isShutDown",
    "_svWorldTimeL",
    "_frameTimeL",
    "_frameTimeF",
    "_isActive",
    "_isFirstTime",
    "_isFrameSkip",
    "_random",
    "_readFileList",
    "_stageName",
    "_nextStage",
    "_isStageLoop",
    "_bootDirectory",
    "_globalStrObj",
    "_discErrInfos",
    "_viewerScene",
    "_dvdStat",
    "_execDvdErr",
    "_isDvdErr",
    "_isNowFreeze",
    "_isNowPadEnable",
    "_isResetEnable",
    "_isResetNow",
    "_isResetLast",
    "_isResetRelease",
    "_isSResetEnable",
};
static igMetaField **g_beSystem_fieldHandles[] = {
    &g_beSystem_isShutDownMetaField,
    &g_beSystem_svWorldTimeLMetaField,
    &g_beSystem_frameTimeLMetaField,
    &g_beSystem_frameTimeFMetaField,
    &g_beSystem_isActiveMetaField,
    &g_beSystem_isFirstTimeMetaField,
    &g_beSystem_isFrameSkipMetaField,
    &g_beSystem_randomMetaField,
    &g_beSystem_readFileListMetaField,
    &g_beSystem_stageNameMetaField,
    &g_beSystem_nextStageMetaField,
    &g_beSystem_isStageLoopMetaField,
    &g_beSystem_bootDirectoryMetaField,
    &g_beSystem_globalStrObjMetaField,
    &g_beSystem_discErrInfosMetaField,
    &g_beSystem_viewerSceneMetaField,
    &g_beSystem_dvdStatMetaField,
    &g_beSystem_execDvdErrMetaField,
    &g_beSystem_isDvdErrMetaField,
    &g_beSystem_isNowFreezeMetaField,
    &g_beSystem_isNowPadEnableMetaField,
    &g_beSystem_isResetEnableMetaField,
    &g_beSystem_isResetNowMetaField,
    &g_beSystem_isResetLastMetaField,
    &g_beSystem_isResetReleaseMetaField,
    &g_beSystem_isSResetEnableMetaField,
};
static int g_beSystem_fieldOffsets[] = {
    16,
    24,
    32,
    40,
    44,
    45,
    46,
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
    93,
    94,
    95,
    96,
    97,
    98,
    99,
};

void beSystem_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSystem_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSystem_ctorTable, 0x1A);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1.0f);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4240();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA), 0);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igDirectory_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0019f210();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, g_beSystem_fieldTable, g_beSystem_fieldHandles, g_beSystem_fieldOffsets, temp_s1);
}

