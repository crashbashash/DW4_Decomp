namespace Gap {
namespace Gfx {

igMetaObject *igVertexArray2::_Meta;
igMetaField *igVertexArray2::k_objList;
igMetaField *igVertexArray2::k_vertexStream;
igMetaField *igVertexArray2::k_internalBuffer;

igVertexArray2 *igVertexArray2::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexArray2 *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexArray2::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVertexArray2::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVertexArray2::retrieveVTablePointer()
{
    igVertexArray2 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVertexArray2::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexArray2::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igObjectList::arkRegister, Gap::Gfx::igVertexStream::arkRegister, Gap::Core::igObject::arkRegister, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexArray2",
        sizeof(igVertexArray2),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVertexArray2::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_objList", "_vertexStream", "_internalBuffer" };
    static igMetaField **enumStorage[] = { &k_objList, &k_vertexStream, &k_internalBuffer };
    static int offsets[] = { 16, 20, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gfx::igVertexStream::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2VertexArray2::getClassMetaSafe;
}
}
}

