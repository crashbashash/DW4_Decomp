namespace Gap {
namespace Sg {

igMetaObject *igAnimationCombinerBoneInfoPool::_Meta;

igAnimationCombinerBoneInfoPool *igAnimationCombinerBoneInfoPool::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAnimationCombinerBoneInfoPool *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAnimationCombinerBoneInfoPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationCombinerBoneInfoPool::retrieveVTablePointer()
{
    igAnimationCombinerBoneInfoPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationCombinerBoneInfoPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationCombinerBoneInfoPool::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationCombinerBoneInfo::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igObjectPool::arkRegisterInternal,
        Gap::Sg::igObjectPool::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationCombinerBoneInfoPool",
        sizeof(igAnimationCombinerBoneInfoPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

