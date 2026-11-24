namespace Gap {
namespace Insight {

igMetaObject *igInfoManagerOrderedList::_Meta;

igMetaObject *igInfoManagerOrderedList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igInfoManagerOrderedList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igInfoManagerOrderedList::retrieveVTablePointer()
{
    igInfoManagerOrderedList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igInfoManagerOrderedList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInfoManagerOrderedList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Insight::igInfoManager::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDependencyOrderedList::arkRegisterInternal,
        Gap::Core::igDependencyOrderedList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInfoManagerOrderedList",
        sizeof(igInfoManagerOrderedList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}
