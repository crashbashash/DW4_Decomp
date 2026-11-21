namespace Gap {
namespace Attrs {

igMetaObject *igBlendMatrixPaletteAttr::_Meta;
igMetaField *igBlendMatrixPaletteAttr::k_matrixCache;
igMetaField *igBlendMatrixPaletteAttr::k_matrixIndices;
igMetaField *igBlendMatrixPaletteAttr::k_currentMatrixCount;
igMetaField *igBlendMatrixPaletteAttr::k_capacity;

igBlendMatrixPaletteAttr *igBlendMatrixPaletteAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBlendMatrixPaletteAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBlendMatrixPaletteAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBlendMatrixPaletteAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendMatrixPaletteAttr::retrieveVTablePointer()
{
    igBlendMatrixPaletteAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendMatrixPaletteAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendMatrixPaletteAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendMatrixPaletteAttr",
        sizeof(igBlendMatrixPaletteAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igBlendMatrixPaletteAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_matrixCache", "_matrixIndices", "_currentMatrixCount", "_capacity" };
    static igMetaField **enumStorage[] = { &k_matrixCache, &k_matrixIndices, &k_currentMatrixCount, &k_capacity };
    static int offsets[] = { 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igUnsignedIntMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

