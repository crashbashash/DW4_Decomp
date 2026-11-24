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
        Gap::Sg::igAnimationState::arkRegisterInternal,
        Gap::Sg::igAnimationState::getClassMeta,
        igEnbayaAnimationState_GetMetaObjectFunction,
        "igEnbayaAnimationState",
        sizeof(igEnbayaAnimationState),                   /* Instance size. */
        igEnbayaAnimationState_GetVTable,
        &igEnbayaAnimationState_InitFields,
        FUN_001a2190, /* extra callback item */
        0 /* callback list */
    );
}

void igEnbayaAnimationState_GetMetaObjectFunction(void) {
    igEnbayaAnimationState_GetMetaObject();
}

namespace Gap {
namespace Sg {

igMetaObject *igAnimationState::_Meta;
igMetaField *igAnimationState::k_animation;
igMetaField *igAnimationState::k_combineMode;
igMetaField *igAnimationState::k_transitionMode;
igMetaField *igAnimationState::k_status;
igMetaField *igAnimationState::k_baseState;
igMetaField *igAnimationState::k_new;
igMetaField *igAnimationState::k_currentBlendRatio;
igMetaField *igAnimationState::k_localTime;
igMetaField *igAnimationState::k_baseTransitionTime;
igMetaField *igAnimationState::k_timeScale;
igMetaField *igAnimationState::k_timeBias;
igMetaField *igAnimationState::k_blendStartTime;
igMetaField *igAnimationState::k_blendStartRatio;
igMetaField *igAnimationState::k_blendRatioRange;
igMetaField *igAnimationState::k_blendDuration;
igMetaField *igAnimationState::k_animationStartTime;
igMetaField *igAnimationState::k_cachedCycleTime;
igMetaField *igAnimationState::k_cachedCycleNumber;
igMetaField *igAnimationState::k_cycleMatchTargetState;
igMetaField *igAnimationState::k_isCycleMatchTarget;
igMetaField *igAnimationState::k_cycleMatchDisable;
igMetaField *igAnimationState::k_manualCycleMatch;
igMetaField *igAnimationState::k_cycleMatchBaseDuration;
igMetaField *igAnimationState::k_cycleMatchDurationRange;
igMetaField *igAnimationState::k_cycleMatchTargetDuration;
igMetaField *igAnimationState::k_timeRequested;
}
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
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igEnbayaAnimationState_fieldTable, g_igEnbayaAnimationState_fieldHandles, g_igEnbayaAnimationState_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)FUN_001a21a0);
}

void FUN_001a2190(void) {
    FUN_001c10f0();
}

void FUN_001a21a0(void) {
    FUN_001c1100();
}

