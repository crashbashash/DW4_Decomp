namespace Gap {
namespace Gfx {

igMetaObject *igPsx2VertexArray2::_Meta;

igMetaObject *igPsx2VertexArray2::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2VertexArray2::retrieveVTablePointer()
{
    igPsx2VertexArray2 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2VertexArray2::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2VertexArray2::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igVertexArray2::arkRegisterInternal,
        Gap::Gfx::igVertexArray2::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2VertexArray2",
        sizeof(igPsx2VertexArray2),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPsx2VertexArray2::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    *(void (**)())&metaObject->_writeProxy = (void (*)())Gap::Gfx::igVertexArray2::getClassMetaSafe;
}
}
}

