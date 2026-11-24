namespace Gap {
namespace Sg {

igMetaObject *igAnimationTransitionPoint::_Meta;
igMetaField *igAnimationTransitionPoint::k_transitionTime;
igMetaField *igAnimationTransitionPoint::k_transitionParams;

igMetaObject *igAnimationTransitionPoint::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationTransitionPoint::retrieveVTablePointer()
{
    igAnimationTransitionPoint temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationTransitionPoint::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationTransitionPoint::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationTransitionParams::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationTransitionPoint",
        sizeof(igAnimationTransitionPoint),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationTransitionPoint::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_transitionTime", "_transitionParams" };
    static igMetaField **enumStorage[] = { &k_transitionTime, &k_transitionParams };
    static int offsets[] = { 8, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igAnimationTransitionParams::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

