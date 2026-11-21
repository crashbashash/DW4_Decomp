namespace Gap {
namespace Attrs {

igMetaObject *igTextureCoordSourceAttr::_Meta;
igMetaField *igTextureCoordSourceAttr::k_mode;
igMetaField *igTextureCoordSourceAttr::k_texCoordIndex;
igMetaField *igTextureCoordSourceAttr::k_unitID;

igTextureCoordSourceAttr *igTextureCoordSourceAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureCoordSourceAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureCoordSourceAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureCoordSourceAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureCoordSourceAttr::retrieveVTablePointer()
{
    igTextureCoordSourceAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureCoordSourceAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureCoordSourceAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureCoordSourceAttr",
        sizeof(igTextureCoordSourceAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTextureCoordSourceAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_mode", "_texCoordIndex", "_unitID" };
    static igMetaField **enumStorage[] = { &k_mode, &k_texCoordIndex, &k_unitID };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_COORD_SOURCE_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureCoordSourceAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

