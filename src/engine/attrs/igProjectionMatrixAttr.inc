namespace Gap {
namespace Attrs {

igMetaObject *igProjectionMatrixAttr::_Meta;
igMetaField *igProjectionMatrixAttr::k_m;

igProjectionMatrixAttr *igProjectionMatrixAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igProjectionMatrixAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igProjectionMatrixAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igProjectionMatrixAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igProjectionMatrixAttr::retrieveVTablePointer()
{
    igProjectionMatrixAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igProjectionMatrixAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igProjectionMatrixAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igProjectionMatrixAttr",
        sizeof(igProjectionMatrixAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igProjectionMatrixAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool };
    static const char *names[] = { "_m" };
    static igMetaField **enumStorage[] = { &k_m };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

