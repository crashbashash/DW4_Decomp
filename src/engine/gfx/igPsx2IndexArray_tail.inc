namespace Gap {
namespace Gfx {

igMetaObject *igPsx2IndexArray::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2IndexArray::retrieveVTablePointer()
{
    igPsx2IndexArray temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2IndexArray::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2IndexArray::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igIndexArray::arkRegisterInternal,
        Gap::Gfx::igIndexArray::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2IndexArray",
        sizeof(igPsx2IndexArray),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPsx2IndexArray::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    *(void (**)())&metaObject->_writeProxy = (void (*)())Gap::Gfx::igIndexArray::getClassMetaSafe;
}
}
}

