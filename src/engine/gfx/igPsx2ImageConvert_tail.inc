namespace Gap {
namespace Gfx {

igMetaObject *igPsx2ImageConvert::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2ImageConvert::retrieveVTablePointer()
{
    igPsx2ImageConvert temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2ImageConvert::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2ImageConvert::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igImageConvert::arkRegisterInternal,
        Gap::Gfx::igImageConvert::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2ImageConvert",
        sizeof(igPsx2ImageConvert),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPsx2ImageConvert::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    *(void (**)())&metaObject->_writeProxy = (void (*)())Gap::Gfx::igImageConvert::getClassMetaSafe;
}
}
}

