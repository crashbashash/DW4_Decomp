namespace Gap {
namespace Sg {

igMetaObject *igAnimationCombiner::_Meta;
igMetaField *igAnimationCombiner::k_boneInfoListList;
igMetaField *igAnimationCombiner::k_boneInfoListBase;
igMetaField *igAnimationCombiner::k_animationStateList;
igMetaField *igAnimationCombiner::k_resultQuaternionArray;
igMetaField *igAnimationCombiner::k_animationCacheMatrixArray;
igMetaField *igAnimationCombiner::k_cacheTime;
igMetaField *igAnimationCombiner::k_cacheValid;
igMetaField *igAnimationCombiner::k_hierarchyUpdated;
igMetaField *igAnimationCombiner::k_boneMatrixArray;
igMetaField *igAnimationCombiner::k_blendMatrixArray;
igMetaField *igAnimationCombiner::k_animationStateTime;
igMetaField *igAnimationCombiner::k_lastCleanStatesTime;
igMetaField *igAnimationCombiner::k_cleanStatesTimeThreshold;
igMetaField *igAnimationCombiner::k_cleanStatesTransitionMargin;

igMetaObject *igAnimationCombiner::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationCombiner::retrieveVTablePointer()
{
    igAnimationCombiner temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igAnimationCombiner::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationCombiner::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationCombinerBoneInfoListList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Sg::igAnimationStateList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAnimationSystem::arkRegisterInternal,
        Gap::Sg::igAnimationSystem::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationCombiner",
        sizeof(igAnimationCombiner),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        thunk_FUN_001abca0,
        regFunctions
    );
}

void igAnimationCombiner::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_boneInfoListList", "_boneInfoListBase", "_animationStateList", "_resultQuaternionArray", "_animationCacheMatrixArray", "_cacheTime", "_cacheValid", "_hierarchyUpdated", "_boneMatrixArray", "_blendMatrixArray", "_animationStateTime", "_lastCleanStatesTime", "_cleanStatesTimeThreshold", "_cleanStatesTransitionMargin" };
    static igMetaField **enumStorage[] = { &k_boneInfoListList, &k_boneInfoListBase, &k_animationStateList, &k_resultQuaternionArray, &k_animationCacheMatrixArray, &k_cacheTime, &k_cacheValid, &k_hierarchyUpdated, &k_boneMatrixArray, &k_blendMatrixArray, &k_animationStateTime, &k_lastCleanStatesTime, &k_cleanStatesTimeThreshold, &k_cleanStatesTransitionMargin };
    static int offsets[] = { 48, 52, 56, 60, 64, 72, 80, 81, 84, 88, 16, 24, 32, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 14);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igAnimationCombinerBoneInfoListList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igAnimationStateList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_memType = (int)Gap::Math::igVec4fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_persistent = 0;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(-1);
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(100000000);
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->setDefault(16700000);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_FUN_001abdf0);
}
}
}

void thunk_FUN_001abca0(void) {
    FUN_001abca0();
}

void thunk_FUN_001abdf0(void) {
    FUN_001abdf0();
}

