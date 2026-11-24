namespace Gap {
namespace Sg {

igMetaObject *igAnimationCombinerBoneInfo::_Meta;
igMetaField *igAnimationCombinerBoneInfo::k_animationState;
igMetaField *igAnimationCombinerBoneInfo::k_transformSource;
igMetaField *igAnimationCombinerBoneInfo::k_constantQuaternion;
igMetaField *igAnimationCombinerBoneInfo::k_constantTranslation;
igMetaField *igAnimationCombinerBoneInfo::k_priority;
igMetaField *igAnimationCombinerBoneInfo::k_useAnimationTranslation;
igMetaField *igAnimationCombinerBoneInfo::k_lastKeyframe;
igMetaField *igAnimationCombinerBoneInfo::k_reflect;

igAnimationCombinerBoneInfo *igAnimationCombinerBoneInfo::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAnimationCombinerBoneInfo *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAnimationCombinerBoneInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationCombinerBoneInfo::retrieveVTablePointer()
{
    igAnimationCombinerBoneInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationCombinerBoneInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationCombinerBoneInfo::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationState::arkRegister, Gap::Sg::igTransformSource::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationCombinerBoneInfo",
        sizeof(igAnimationCombinerBoneInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationCombinerBoneInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_animationState", "_transformSource", "_constantQuaternion", "_constantTranslation", "_priority", "_useAnimationTranslation", "_lastKeyframe", "_reflect" };
    static igMetaField **enumStorage[] = { &k_animationState, &k_transformSource, &k_constantQuaternion, &k_constantTranslation, &k_priority, &k_useAnimationTranslation, &k_lastKeyframe, &k_reflect };
    static int offsets[] = { 12, 16, 20, 36, 48, 52, 8, 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igAnimationState::getClassTypeLazy();
        metaField->_resetMethod = 2;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igTransformSource::getClassTypeLazy();
        metaField->_resetMethod = 2;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

