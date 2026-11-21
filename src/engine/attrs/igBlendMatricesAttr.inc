namespace Gap {
namespace Attrs {

igMetaObject *igBlendMatricesAttr::_Meta;
igMetaField *igBlendMatricesAttr::k_matrixCache;
igMetaField *igBlendMatricesAttr::k_currentMatrixCount;
igMetaField *igBlendMatricesAttr::k_matrixCacheCapacity;

igBlendMatricesAttr *igBlendMatricesAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBlendMatricesAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBlendMatricesAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendMatricesAttr::retrieveVTablePointer()
{
    igBlendMatricesAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendMatricesAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendMatricesAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendMatricesAttr",
        sizeof(igBlendMatricesAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igBlendMatricesAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_matrixCache", "_currentMatrixCount", "_matrixCacheCapacity" };
    static igMetaField **enumStorage[] = { &k_matrixCache, &k_currentMatrixCount, &k_matrixCacheCapacity };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

