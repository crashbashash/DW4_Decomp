namespace Gap {
namespace Gfx {

igMetaObject *igVertexArray2Helper::_Meta;
igMetaField *igVertexArray2Helper::k_vertexArray;

igVertexArray2Helper *igVertexArray2Helper::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexArray2Helper *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexArray2Helper::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVertexArray2Helper::retrieveVTablePointer()
{
    igVertexArray2Helper temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVertexArray2Helper::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexArray2Helper::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igVertexArray2::arkRegister, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexArray2Helper",
        sizeof(igVertexArray2Helper),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVertexArray2Helper::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_vertexArray" };
    static igMetaField **enumStorage[] = { &k_vertexArray };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gfx::igVertexArray2::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

