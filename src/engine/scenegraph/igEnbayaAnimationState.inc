namespace Gap {
namespace Sg {

igMetaObject *igEnbayaAnimationState::_Meta;
igMetaField *igEnbayaAnimationState::k_context;
igMetaField *igEnbayaAnimationState::k_fastCacheDecodingState;

igMetaObject *igEnbayaAnimationState::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnbayaAnimationState::retrieveVTablePointer()
{
    igEnbayaAnimationState temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnbayaAnimationState::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnbayaAnimationState::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAnimationState::arkRegisterInternal,
        Gap::Sg::igAnimationState::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnbayaAnimationState",
        sizeof(igEnbayaAnimationState),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        FUN_001a2190,
        0
    );
}

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

void igEnbayaAnimationState::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igRawRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_context", "_fastCacheDecodingState" };
    static igMetaField **enumStorage[] = { &k_context, &k_fastCacheDecodingState };
    static int offsets[] = { 160, 164 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)FUN_001a21a0);
}
}
}

void FUN_001a2190(void) {
    FUN_001c10f0();
}

void FUN_001a21a0(void) {
    FUN_001c1100();
}

