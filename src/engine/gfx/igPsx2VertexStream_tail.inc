namespace Gap {
namespace Gfx {

igMetaObject *igPsx2VertexStream::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2VertexStream::retrieveVTablePointer()
{
    igPsx2VertexStream temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2VertexStream::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2VertexStream::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igVertexStream::arkRegisterInternal,
        Gap::Gfx::igVertexStream::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2VertexStream",
        sizeof(igPsx2VertexStream),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Gfx::igPsx2VertexStream::arkRegisterUser,
        0
    );
}

void igPsx2VertexStream::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igUnsignedLongMetaField_Create, (FieldFactory)Gap::Core::igUnsignedIntArrayMetaField::_instantiateFromPool, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create };
    static const char *names[] = { "_scaleAlphaState", "_syncSequence", "_textureCoordCompiled", "_multipassCompiled", "_blendMatrixCount", "_blendIndexCount", "_vertexCountCompiled", "_renderListHandle", "_dmaBuffer", "_dmaBufferStruct" };
    static igMetaField **enumStorage[] = { &k_scaleAlphaState, &k_syncSequence, &k_textureCoordCompiled, &k_multipassCompiled, &k_blendMatrixCount, &k_blendIndexCount, &k_vertexCountCompiled, &k_renderListHandle, &k_dmaBuffer, &k_dmaBufferStruct };
    static int offsets[] = { 36, 40, 48, 112, 116, 120, 124, 128, 132, 136 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 10);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    {
        igUnsignedLongMetaField *metaField = (igUnsignedLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_persistent = 0;
    }
    {
        igUnsignedIntArrayMetaField *metaField = (igUnsignedIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_num = 16;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_persistent = 0;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igPsx2VertexStream::arkRegisterUser()
{
    userRegister();
}
}
}

