static const char *g_igAnimationState_statusNames[] = {
    "kPlaying", "kPaused", "kAwaitingTransitionPoint", "kFinished",
};
static int g_igAnimationState_statusValues[] = {
    0, 1, 2, 3,
};
namespace Gap {
namespace Sg {

igMetaEnum *igAnimationState::Status_Meta;

igMetaEnum *igAnimationState::getStatusMetaEnum() {
    if (Status_Meta == 0) {
        Status_Meta = Gap::Core::igMetaEnum::createMetaEnum("Status", g_igAnimationState_statusNames, g_igAnimationState_statusValues, 4);
    }
    return Status_Meta;
}
}
}

static const char *g_igAnimationState_transitionModeNames[] = {
    "kEaseIn", "kEaseInReplace", "kEaseOut", "kManual",
    "kNone", "kEaseInReplaceAll",
};
static int g_igAnimationState_transitionModeValues[] = {
    0, 1, 2, 3, 4, 5,
};
namespace Gap {
namespace Sg {

igMetaEnum *igAnimationState::TransitionMode_Meta;

igMetaEnum *igAnimationState::getTransitionModeMetaEnum() {
    if (TransitionMode_Meta == 0) {
        TransitionMode_Meta = Gap::Core::igMetaEnum::createMetaEnum("TransitionMode", g_igAnimationState_transitionModeNames, g_igAnimationState_transitionModeValues, 6);
    }
    return TransitionMode_Meta;
}
}
}

static const char *g_igAnimationState_combineModeNames[] = {
    "kOverride", "kBlend", "kTween",
};
static int g_igAnimationState_combineModeValues[] = {
    0, 1, 2,
};
namespace Gap {
namespace Sg {

igMetaEnum *igAnimationState::CombineMode_Meta;

igMetaEnum *igAnimationState::getCombineModeMetaEnum() {
    if (CombineMode_Meta == 0) {
        CombineMode_Meta = Gap::Core::igMetaEnum::createMetaEnum("CombineMode", g_igAnimationState_combineModeNames, g_igAnimationState_combineModeValues, 3);
    }
    return CombineMode_Meta;
}
}
}

void FUN_001a6bb0(int arg0) {
    Gap::Sg::igAnimationState::arkRegister();
    igMetaObject_CreateInstance((igMetaObject *)Gap::Sg::igAnimationState::getClassMeta(), (igMemoryPoolView *)arg0);
}

namespace Gap {
namespace Sg {

igMetaObject *igAnimationState::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAnimationState::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationState::retrieveVTablePointer()
{
    igAnimationState temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationState::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationState::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimation::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationState",
        sizeof(igAnimationState),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationState::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igUnsignedLongMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_animation", "_combineMode", "_transitionMode", "_status", "_baseState", "_new", "_currentBlendRatio", "_localTime", "_baseTransitionTime", "_timeScale", "_timeBias", "_blendStartTime", "_blendStartRatio", "_blendRatioRange", "_blendDuration", "_animationStartTime", "_cachedCycleTime", "_cachedCycleNumber", "_cycleMatchTargetState", "_isCycleMatchTarget", "_cycleMatchDisable", "_manualCycleMatch", "_cycleMatchBaseDuration", "_cycleMatchDurationRange", "_cycleMatchTargetDuration", "_timeRequested" };
    static igMetaField **enumStorage[] = { &k_animation, &k_combineMode, &k_transitionMode, &k_status, &k_baseState, &k_new, &k_currentBlendRatio, &k_localTime, &k_baseTransitionTime, &k_timeScale, &k_timeBias, &k_blendStartTime, &k_blendStartRatio, &k_blendRatioRange, &k_blendDuration, &k_animationStartTime, &k_cachedCycleTime, &k_cachedCycleNumber, &k_cycleMatchTargetState, &k_isCycleMatchTarget, &k_cycleMatchDisable, &k_manualCycleMatch, &k_cycleMatchBaseDuration, &k_cycleMatchDurationRange, &k_cycleMatchTargetDuration, &k_timeRequested };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64, 72, 80, 84, 88, 96, 104, 112, 120, 124, 125, 126, 128, 136, 144, 152 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 26);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igAnimation::getClassTypeLazy();
        metaField->_resetMethod = 2;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igAnimationState::getCombineModeMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igAnimationState::getTransitionModeMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Sg::igAnimationState::getStatusMetaEnum;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)getClassTypeLazy();
        metaField->_resetMethod = 2;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(1.0f);
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_persistent = 0;
    }
    {
        igUnsignedLongMetaField *metaField = (igUnsignedLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)getClassTypeLazy();
        metaField->_resetMethod = 2;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

