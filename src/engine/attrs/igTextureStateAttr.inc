namespace Gap {
namespace Attrs {

igMetaObject *igTextureStateAttr::_Meta;
igMetaField *igTextureStateAttr::k_enabled;
igMetaField *igTextureStateAttr::k_unitID;

igTextureStateAttr *igTextureStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureStateAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureStateAttr::retrieveVTablePointer()
{
    igTextureStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureStateAttr",
        sizeof(igTextureStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTextureStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_enabled", "_unitID" };
    static igMetaField **enumStorage[] = { &k_enabled, &k_unitID };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureStateAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

