namespace Gap {
namespace Attrs {

igMetaObject *igBlendStateAttr::_Meta;
igMetaField *igBlendStateAttr::k_enabled;

igBlendStateAttr *igBlendStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBlendStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBlendStateAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBlendStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendStateAttr::retrieveVTablePointer()
{
    igBlendStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendStateAttr",
        sizeof(igBlendStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igBlendStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_enabled" };
    static igMetaField **enumStorage[] = { &k_enabled };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

