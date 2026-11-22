namespace Gap {
namespace Gfx {

igMetaObject *igPsx2Image::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2Image::retrieveVTablePointer()
{
    igPsx2Image temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2Image::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2Image::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igMemoryImage::arkRegisterInternal,
        Gap::Gfx::igMemoryImage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2Image",
        sizeof(igPsx2Image),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPsx2Image::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    *(void (**)())&metaObject->_writeProxy = (void (*)())igImage::getClassMetaSafe;
}
}
}

