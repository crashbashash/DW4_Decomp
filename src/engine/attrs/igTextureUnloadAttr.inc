namespace Gap {
namespace Attrs {

igMetaObject *igTextureUnloadAttr::_Meta;
igMetaField *igTextureUnloadAttr::k_texture;
igMetaField *igTextureUnloadAttr::k_unitID;

igMetaObject *igTextureUnloadAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureUnloadAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureUnloadAttr::retrieveVTablePointer()
{
    igTextureUnloadAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureUnloadAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureUnloadAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igTextureAttr_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureUnloadAttr",
        sizeof(igTextureUnloadAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igTextureUnloadAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_texture", "_unitID" };
    static igMetaField **enumStorage[] = { &k_texture, &k_unitID };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureUnloadAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

