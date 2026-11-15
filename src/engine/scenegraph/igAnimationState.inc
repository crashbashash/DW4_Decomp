static const char *g_igAnimationState_statusNames[] = {
    "kPlaying", "kPaused", "kAwaitingTransitionPoint", "kFinished",
};
static int g_igAnimationState_statusValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igAnimationState_statusMetaEnum;

igMetaEnum *FUN_001a6a90(void) {
    if (g_igAnimationState_statusMetaEnum == 0) {
        g_igAnimationState_statusMetaEnum = igMetaEnum_Create("Status", g_igAnimationState_statusNames, g_igAnimationState_statusValues, 4);
    }
    return g_igAnimationState_statusMetaEnum;
}

static const char *g_igAnimationState_transitionModeNames[] = {
    "kEaseIn", "kEaseInReplace", "kEaseOut", "kManual",
    "kNone", "kEaseInReplaceAll",
};
static int g_igAnimationState_transitionModeValues[] = {
    0, 1, 2, 3, 4, 5,
};
igMetaEnum *g_igAnimationState_transitionModeMetaEnum;

igMetaEnum *FUN_001a6af0(void) {
    if (g_igAnimationState_transitionModeMetaEnum == 0) {
        g_igAnimationState_transitionModeMetaEnum = igMetaEnum_Create("TransitionMode", g_igAnimationState_transitionModeNames, g_igAnimationState_transitionModeValues, 6);
    }
    return g_igAnimationState_transitionModeMetaEnum;
}

static const char *g_igAnimationState_combineModeNames[] = {
    "kOverride", "kBlend", "kTween",
};
static int g_igAnimationState_combineModeValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igAnimationState_combineModeMetaEnum;

igMetaEnum *FUN_001a6b50(void) {
    if (g_igAnimationState_combineModeMetaEnum == 0) {
        g_igAnimationState_combineModeMetaEnum = igMetaEnum_Create("CombineMode", g_igAnimationState_combineModeNames, g_igAnimationState_combineModeValues, 3);
    }
    return g_igAnimationState_combineModeMetaEnum;
}

void FUN_001a6bb0(int arg0) {
    FUN_001a6dc0();
    igMetaObject_CreateInstance((int)g_igAnimationState_metaObject, arg0);
}

igMetaObject *FUN_001a6bf0(void) {
    if (g_igAnimationState_metaObject == 0) {
        g_igAnimationState_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAnimationState_metaObject;
}

igMetaObject *igAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6dc0();
    return g_igAnimationState_metaObject;
}

int igAnimationState_GetVTable(void) {
    union U_1a6c90 u;
    int temp_s2;
    S_ref *q3;
    S_ref *q2;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00529550[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[24];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[120];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00529550[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    return temp_s2;
}

void FUN_001a6dc0(void)
{
    igMetaObject_RunStaticInit(igAnimationState_Register);
}

static igMetaObjectCallback g_igAnimationState_callbackList[] = { FUN_001a9290, 0 };

void igAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationState_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationState_GetMetaObject,
        "igAnimationState",
        0xA0, /* instance size */
        igAnimationState_GetVTable,
        &igAnimationState_InitFields,
        0, /* extra callback item */
        g_igAnimationState_callbackList /* callback list */
    );
}

void thunk_igAnimationState_GetMetaObject(void) {
    igAnimationState_GetMetaObject();
}

static FieldFactory g_igAnimationState_ctorTable[] = {
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igUnsignedLongMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_igAnimationState_fieldTable[] = {
    "_animation",
    "_combineMode",
    "_transitionMode",
    "_status",
    "_baseState",
    "_new",
    "_currentBlendRatio",
    "_localTime",
    "_baseTransitionTime",
    "_timeScale",
    "_timeBias",
    "_blendStartTime",
    "_blendStartRatio",
    "_blendRatioRange",
    "_blendDuration",
    "_animationStartTime",
    "_cachedCycleTime",
    "_cachedCycleNumber",
    "_cycleMatchTargetState",
    "_isCycleMatchTarget",
    "_cycleMatchDisable",
    "_manualCycleMatch",
    "_cycleMatchBaseDuration",
    "_cycleMatchDurationRange",
    "_cycleMatchTargetDuration",
    "_timeRequested",
};
static igMetaField **g_igAnimationState_fieldHandles[] = {
    &g_igAnimationState_animationMetaField,
    &g_igAnimationState_combineModeMetaField,
    &g_igAnimationState_transitionModeMetaField,
    &g_igAnimationState_statusMetaField,
    &g_igAnimationState_baseStateMetaField,
    &g_igAnimationState_newMetaField,
    &g_igAnimationState_currentBlendRatioMetaField,
    &g_igAnimationState_localTimeMetaField,
    &g_igAnimationState_baseTransitionTimeMetaField,
    &g_igAnimationState_timeScaleMetaField,
    &g_igAnimationState_timeBiasMetaField,
    &g_igAnimationState_blendStartTimeMetaField,
    &g_igAnimationState_blendStartRatioMetaField,
    &g_igAnimationState_blendRatioRangeMetaField,
    &g_igAnimationState_blendDurationMetaField,
    &g_igAnimationState_animationStartTimeMetaField,
    &g_igAnimationState_cachedCycleTimeMetaField,
    &g_igAnimationState_cachedCycleNumberMetaField,
    &g_igAnimationState_cycleMatchTargetStateMetaField,
    &g_igAnimationState_isCycleMatchTargetMetaField,
    &g_igAnimationState_cycleMatchDisableMetaField,
    &g_igAnimationState_manualCycleMatchMetaField,
    &g_igAnimationState_cycleMatchBaseDurationMetaField,
    &g_igAnimationState_cycleMatchDurationRangeMetaField,
    &g_igAnimationState_cycleMatchTargetDurationMetaField,
    &g_igAnimationState_timeRequestedMetaField,
};
static int g_igAnimationState_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    40,
    48,
    56,
    64,
    72,
    80,
    84,
    88,
    96,
    104,
    112,
    120,
    124,
    125,
    126,
    128,
    136,
    144,
    152,
};

void igAnimationState_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationState_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationState_ctorTable, 0x1A);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001a9130();
    ((igMetaField *)temp_s2)->_resetMethod = 2;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001a6b50);
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_001a6af0);
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)));
    igEnumMetaField_SetDefaultValue(temp_v0_3, 0);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_001a6a90);
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_001a6bf0();
    ((igMetaField *)temp_s2_2)->_resetMethod = 2;
    igBoolMetaField_SetDefaultValue(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 1);
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9)), 1.0f);
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11)))->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_001a6bf0();
    ((igMetaField *)temp_s2_3)->_resetMethod = 2;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19)))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationState_fieldTable, g_igAnimationState_fieldHandles, g_igAnimationState_fieldOffsets, temp_s1);
}

