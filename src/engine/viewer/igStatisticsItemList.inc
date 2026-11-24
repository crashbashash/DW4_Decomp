namespace Gap {
namespace Viewer {

igMetaObject *igStatisticsItemList::_Meta;

igMetaObject *igStatisticsItemList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igStatisticsItemList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStatisticsItemList::retrieveVTablePointer()
{
    igStatisticsItemList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStatisticsItemList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStatisticsItemList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igStatisticsItem::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStatisticsItemList",
        sizeof(igStatisticsItemList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

