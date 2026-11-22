namespace Gap {
namespace Core {

igMetaObject *igPsx2Folder::_Meta;

igMetaObject *igPsx2Folder::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2Folder::retrieveVTablePointer()
{
    igPsx2Folder temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2Folder::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2Folder::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igFolder::arkRegisterInternal,
        Gap::Core::igFolder::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2Folder",
        sizeof(igPsx2Folder),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

