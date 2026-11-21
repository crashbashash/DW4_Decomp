namespace Gap {
namespace Attrs {

igMetaObject *igNonRefCountedAttrList::_Meta;

igMetaObject *igNonRefCountedAttrList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igNonRefCountedAttrList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNonRefCountedAttrList::retrieveVTablePointer()
{
    igNonRefCountedAttrList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedAttrList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNonRefCountedAttrList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNonRefCountedAttrList",
        sizeof(igNonRefCountedAttrList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

