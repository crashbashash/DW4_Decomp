namespace Gap {
namespace Insight {

igMetaObject *igInsightPluginList::_Meta;

igMetaObject *igInsightPluginList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igInsightPluginList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igInsightPluginList::retrieveVTablePointer()
{
    igInsightPluginList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igInsightPluginList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInsightPluginList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Insight::igInsightPlugin::arkRegister, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInsightPluginList",
        sizeof(igInsightPluginList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

