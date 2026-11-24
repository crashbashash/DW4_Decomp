namespace Gap {
namespace Bec {

igMetaObject *beMessengerArgDataList::_Meta;

igMetaObject *beMessengerArgDataList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beMessengerArgDataList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMessengerArgDataList::retrieveVTablePointer()
{
    beMessengerArgDataList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMessengerArgDataList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMessengerArgDataList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beMessengerArgData::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMessengerArgDataList",
        sizeof(beMessengerArgDataList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

