namespace Gap {
namespace Sg {

igMetaObject *igAnimationTransitionParams::_Meta;
igMetaField *igAnimationTransitionParams::k_startRatio;
igMetaField *igAnimationTransitionParams::k_endRatio;
igMetaField *igAnimationTransitionParams::k_duration;
igMetaField *igAnimationTransitionParams::k_targetStartTime;

igMetaObject *igAnimationTransitionParams::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAnimationTransitionParams::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationTransitionParams::retrieveVTablePointer()
{
    igAnimationTransitionParams temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationTransitionParams::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationTransitionParams::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationTransitionParams",
        sizeof(igAnimationTransitionParams),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igAnimationTransitionParams::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_startRatio", "_endRatio", "_duration", "_targetStartTime" };
    static igMetaField **enumStorage[] = { &k_startRatio, &k_endRatio, &k_duration, &k_targetStartTime };
    static int offsets[] = { 8, 12, 16, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

