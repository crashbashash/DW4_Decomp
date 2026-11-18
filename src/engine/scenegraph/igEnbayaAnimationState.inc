igMetaObject *g_igEnbayaAnimationState_metaObject;
igMetaField *g_igEnbayaAnimationState_contextMetaField;
igMetaField *g_igEnbayaAnimationState_fastCacheDecodingStateMetaField;

igMetaObject *igEnbayaAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaAnimationState_EnsureRegistered();
    return g_igEnbayaAnimationState_metaObject;
}

int igEnbayaAnimationState_GetVTable(void) {
    union U_1a1e80 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p48;
    char *pB8;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igAnimationState_vtable[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p58 = &u.b[24];
    *(int *)p58 = 0;
    pB8 = &u.b[120];
    *(int *)pB8 = 0;
    u.vt = (int)&g_igEnbayaAnimationState_vtable[0];
    r = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igAnimationState_vtable[0];
    if (pB8 != 0) {
        v1 = *(int **)pB8;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    return r;
}

void igEnbayaAnimationState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnbayaAnimationState_Register);
}

CallbackArray *igEnbayaAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEnbayaAnimationState_metaObject,
        igAnimationState_Register,
        igAnimationState_GetPublishedMetaObject,
        thunk_igEnbayaAnimationState_GetMetaObject,
        "igEnbayaAnimationState",
        sizeof(igEnbayaAnimationState),                   /* Instance size. */
        igEnbayaAnimationState_GetVTable,
        &igEnbayaAnimationState_InitFields,
        FUN_001a2190, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEnbayaAnimationState_GetMetaObject(void) {
    igEnbayaAnimationState_GetMetaObject();
}

igMetaObject *g_igAnimationState_metaObject;
igMetaField *g_igAnimationState_animationMetaField;
igMetaField *g_igAnimationState_combineModeMetaField;
igMetaField *g_igAnimationState_transitionModeMetaField;
igMetaField *g_igAnimationState_statusMetaField;
igMetaField *g_igAnimationState_baseStateMetaField;
igMetaField *g_igAnimationState_newMetaField;
igMetaField *g_igAnimationState_currentBlendRatioMetaField;
igMetaField *g_igAnimationState_localTimeMetaField;
igMetaField *g_igAnimationState_baseTransitionTimeMetaField;
igMetaField *g_igAnimationState_timeScaleMetaField;
igMetaField *g_igAnimationState_timeBiasMetaField;
igMetaField *g_igAnimationState_blendStartTimeMetaField;
igMetaField *g_igAnimationState_blendStartRatioMetaField;
igMetaField *g_igAnimationState_blendRatioRangeMetaField;
igMetaField *g_igAnimationState_blendDurationMetaField;
igMetaField *g_igAnimationState_animationStartTimeMetaField;
igMetaField *g_igAnimationState_cachedCycleTimeMetaField;
igMetaField *g_igAnimationState_cachedCycleNumberMetaField;
igMetaField *g_igAnimationState_cycleMatchTargetStateMetaField;
igMetaField *g_igAnimationState_isCycleMatchTargetMetaField;
igMetaField *g_igAnimationState_cycleMatchDisableMetaField;
igMetaField *g_igAnimationState_manualCycleMatchMetaField;
igMetaField *g_igAnimationState_cycleMatchBaseDurationMetaField;
igMetaField *g_igAnimationState_cycleMatchDurationRangeMetaField;
igMetaField *g_igAnimationState_cycleMatchTargetDurationMetaField;
igMetaField *g_igAnimationState_timeRequestedMetaField;

igMetaObject *FUN_001a20d0(void) {
    return g_igAnimationState_metaObject;
}

static FieldFactory g_igEnbayaAnimationState_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igEnbayaAnimationState_fieldTable[] = {
    "_context",
    "_fastCacheDecodingState",
};
static igMetaField **g_igEnbayaAnimationState_fieldHandles[] = {
    &g_igEnbayaAnimationState_contextMetaField,
    &g_igEnbayaAnimationState_fastCacheDecodingStateMetaField,
};
static int g_igEnbayaAnimationState_fieldOffsets[] = {
    160,
    164,
};

void igEnbayaAnimationState_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnbayaAnimationState_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igEnbayaAnimationState_ctorTable, 2);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1))) + 38) = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igEnbayaAnimationState_fieldTable, g_igEnbayaAnimationState_fieldHandles, g_igEnbayaAnimationState_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)FUN_001a21a0);
}

void FUN_001a2190(void) {
    FUN_001c10f0();
}

void FUN_001a21a0(void) {
    FUN_001c1100();
}

