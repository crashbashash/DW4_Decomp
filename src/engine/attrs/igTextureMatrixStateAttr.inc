namespace Gap {
namespace Attrs {

igMetaObject *igTextureMatrixStateAttr::_Meta;
igMetaField *igTextureMatrixStateAttr::k_enabled;
igMetaField *igTextureMatrixStateAttr::k_unitID;

igTextureMatrixStateAttr *igTextureMatrixStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureMatrixStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureMatrixStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureMatrixStateAttr::retrieveVTablePointer()
{
    igTextureMatrixStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureMatrixStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureMatrixStateAttr",
        sizeof(igTextureMatrixStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTextureMatrixStateAttr::arkRegisterInitialize()
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
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureMatrixStateAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

