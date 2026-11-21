namespace Gap {
namespace Attrs {

igMetaObject *igMatrixOptStateAttr::_Meta;
igMetaField *igMatrixOptStateAttr::k_enabled;

igMatrixOptStateAttr *igMatrixOptStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMatrixOptStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMatrixOptStateAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMatrixOptStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMatrixOptStateAttr::retrieveVTablePointer()
{
    igMatrixOptStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMatrixOptStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMatrixOptStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMatrixOptStateAttr",
        sizeof(igMatrixOptStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igMatrixOptStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_enabled" };
    static igMetaField **enumStorage[] = { &k_enabled };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

