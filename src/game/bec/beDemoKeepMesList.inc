namespace Gap {
namespace Bec {

igMetaObject *beDemoKeepMesList::_Meta;

igMetaObject *beDemoKeepMesList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beDemoKeepMesList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDemoKeepMesList::retrieveVTablePointer()
{
    beDemoKeepMesList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDemoKeepMesList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDemoKeepMesList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beDemoKeepMes::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDemoKeepMesList",
        sizeof(beDemoKeepMesList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

