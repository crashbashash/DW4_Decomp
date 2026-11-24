namespace Gap {
namespace Sg {

igMetaObject *igAnimationStatePool::_Meta;

igAnimationStatePool *igAnimationStatePool::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAnimationStatePool *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAnimationStatePool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationStatePool::retrieveVTablePointer()
{
    igAnimationStatePool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationStatePool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationStatePool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationState::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationStatePool",
        sizeof(igAnimationStatePool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

