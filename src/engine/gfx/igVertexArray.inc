namespace Gap {
namespace Gfx {

igMetaObject *igVertexArray::_Meta;
igMetaField *igVertexArray::k_vdata;
igMetaField *igVertexArray::k_numVerts;
igMetaField *igVertexArray::k_vtype;
igMetaField *igVertexArray::k_usageFlags;

igVertexArray *igVertexArray::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexArray *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexArray::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVertexArray::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igVertexArray::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexArray::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexArray",
        sizeof(igVertexArray),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igVertexArray::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_vdata", "_numVerts", "_vtype", "_usageFlags" };
    static igMetaField **enumStorage[] = { &k_vdata, &k_numVerts, &k_vtype, &k_usageFlags };
    static int offsets[] = { 8, 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igMemoryRefMetaField::getMetaField();
        metaField->_deepCopyMethod = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())igPsx2VertexArray1_1_GetMetaObjectFunction;
}
}
}

