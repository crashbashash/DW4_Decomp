namespace Gap {
namespace Bec {

igMetaObject *beUnicodeObjList::_Meta;

igMetaObject *beUnicodeObjList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beUnicodeObjList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beUnicodeObjList::retrieveVTablePointer()
{
    beUnicodeObjList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beUnicodeObjList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beUnicodeObjList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beUnicodeObj::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beUnicodeObjList",
        sizeof(beUnicodeObjList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

