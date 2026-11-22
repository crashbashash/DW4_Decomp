namespace Gap {
namespace Core {

igMetaObject *igInfoList::_Meta;

igInfoList *igInfoList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igInfoList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igInfoList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igInfoList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igInfoList::retrieveVTablePointer()
{
    igInfoList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igInfoList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInfoList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igInfo::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInfoList",
        sizeof(igInfoList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

