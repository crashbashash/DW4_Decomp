namespace Gap {
namespace Gfx {

igMetaObject *igVertexArray1_1::_Meta;
igMetaField *igVertexArray1_1::k_vertexFormat;
igMetaField *igVertexArray1_1::k_blendWeights;
igMetaField *igVertexArray1_1::k_blendIndices;
igMetaField *igVertexArray1_1::k_blendIndex;
igMetaField *igVertexArray1_1::k_pointSpriteSize;
igMetaField *igVertexArray1_1::k_memPool;

igVertexArray1_1 *igVertexArray1_1::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexArray1_1 *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexArray1_1::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igVertexArray1_1::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexArray1_1::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMemoryPool_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Gfx::igVertexArray::arkRegisterInternal,
        Gap::Gfx::igVertexArray::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexArray1_1",
        sizeof(igVertexArray1_1),
        0,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Gfx::igVertexArray1_1::arkRegisterUser,
        regFunctions
    );
}

void igVertexArray1_1::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igStructMetaField::_instantiateFromPool, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_vertexFormat", "_blendWeights", "_blendIndices", "_blendIndex", "_pointSpriteSize", "_memPool" };
    static igMetaField **enumStorage[] = { &k_vertexFormat, &k_blendWeights, &k_blendIndices, &k_blendIndex, &k_pointSpriteSize, &k_memPool };
    static int offsets[] = { 28, 32, 36, 40, 44, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igStructMetaField *metaField = (igStructMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_size = 4;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igFloatMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_memType = (int)Gap::Core::igFloatMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2VertexArray1_1::getClassMetaSafe;
}
}
}

