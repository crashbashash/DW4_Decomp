namespace Gap {
namespace Attrs {

igMetaObject *igImageMipMapList::_Meta;

igMetaObject *igImageMipMapList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igImageMipMapList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igImageMipMapList::retrieveVTablePointer()
{
    igImageMipMapList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igImageMipMapList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igImageMipMapList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igImage::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igImageMipMapList",
        sizeof(igImageMipMapList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

