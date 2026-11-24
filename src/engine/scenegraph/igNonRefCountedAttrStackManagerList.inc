namespace Gap {
namespace Sg {

igNonRefCountedAttrStackManagerList *igNonRefCountedAttrStackManagerList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igNonRefCountedAttrStackManagerList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igNonRefCountedAttrStackManagerList::_Meta;

igMetaObject *igNonRefCountedAttrStackManagerList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNonRefCountedAttrStackManagerList::retrieveVTablePointer()
{
    igNonRefCountedAttrStackManagerList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedAttrStackManagerList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNonRefCountedAttrStackManagerList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAttrStackManager::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNonRefCountedAttrStackManagerList",
        sizeof(igNonRefCountedAttrStackManagerList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

