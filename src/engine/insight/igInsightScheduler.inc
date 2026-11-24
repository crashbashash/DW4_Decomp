namespace Gap {
namespace Insight {

igMetaObject *igInsightScheduler::_Meta;

igMetaObject *igInsightScheduler::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igInsightScheduler::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igInsightScheduler::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInsightScheduler::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInsightScheduler",
        sizeof(igInsightScheduler),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igInsightScheduler::arkRegisterInitialize()
{
    _Meta->_abstractProxy = (int)&Gap::Insight::igSerialScheduler::getClassMetaSafe;
}
}
}

