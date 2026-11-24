namespace Gap {
namespace Sg {

igAnimation *igAnimation::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAnimation *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAnimation::_Meta;
igMetaField *igAnimation::k_priority;
igMetaField *igAnimation::k_bindingList;
igMetaField *igAnimation::k_trackList;
igMetaField *igAnimation::k_transitionList;
igMetaField *igAnimation::k_keyFrameTimeOffset;
igMetaField *igAnimation::k_startTime;
igMetaField *igAnimation::k_duration;
igMetaField *igAnimation::k_useAnimationTransBoolArray;

igMetaObject *igAnimation::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAnimation::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimation::retrieveVTablePointer()
{
    igAnimation temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimation::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimation::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationBindingList::arkRegister, Gap::Sg::igAnimationTrackList::arkRegister, igAnimationTransitionDefinitionList_EnsureRegistered, igBitMask_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimation",
        sizeof(igAnimation),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimation::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_priority", "_bindingList", "_trackList", "_transitionList", "_keyFrameTimeOffset", "_startTime", "_duration", "_useAnimationTransBoolArray" };
    static igMetaField **enumStorage[] = { &k_priority, &k_bindingList, &k_trackList, &k_transitionList, &k_keyFrameTimeOffset, &k_startTime, &k_duration, &k_useAnimationTransBoolArray };
    static int offsets[] = { 12, 16, 20, 24, 32, 40, 48, 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igAnimationBindingList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igAnimationTrackList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igAnimationTransitionDefinitionList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igBitMask_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

