namespace Gap {
namespace Insight {

igMetaObject *igMessageDispatcher::_Meta;

igMetaObject *igMessageDispatcher::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMessageDispatcher::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igMessageDispatcher::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMessageDispatcher::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMessageDispatcher",
        sizeof(igMessageDispatcher),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igMessageDispatcher::arkRegisterInitialize()
{
    _Meta->_abstractProxy = (int)&Gap::Insight::igFilterMessageDispatcher::getClassMetaSafe;
}
}
}

