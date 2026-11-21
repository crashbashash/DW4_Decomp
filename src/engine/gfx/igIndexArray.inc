namespace Gap {
namespace Gfx {

igMetaObject *igIndexArray::_Meta;
igMetaField *igIndexArray::k_indexData;
igMetaField *igIndexArray::k_numIndices;
igMetaField *igIndexArray::k_dataSize;
igMetaField *igIndexArray::k_usageFlags;
igMetaField *igIndexArray::k_memPool;

igMetaObject *igIndexArray::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igIndexArray::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igIndexArray::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIndexArray::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMemoryPool_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIndexArray",
        sizeof(igIndexArray),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igIndexArray::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igEnumMetaField_Create, igUnsignedIntMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_indexData", "_numIndices", "_dataSize", "_usageFlags", "_memPool" };
    static igMetaField **enumStorage[] = { &k_indexData, &k_numIndices, &k_dataSize, &k_usageFlags, &k_memPool };
    static int offsets[] = { 12, 16, 20, 24, 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_INDEX_DATA_SIZE_GetMetaEnum;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2IndexArray::getClassMetaSafe;
}
}
}

