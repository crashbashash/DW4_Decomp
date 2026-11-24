namespace Gap {
namespace Sg {

igRenderPackage *igRenderPackage::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRenderPackage *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRenderPackage::_Meta;
igMetaField *igRenderPackage::k_stateAttrs;
igMetaField *igRenderPackage::k_cachedStateAttrs;
igMetaField *igRenderPackage::k_geomAttrs;
igMetaField *igRenderPackage::k_sortingCache;
igMetaField *igRenderPackage::k_distance;
igMetaField *igRenderPackage::k_theMass;

igMetaObject *igRenderPackage::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRenderPackage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRenderPackage::retrieveVTablePointer()
{
    igRenderPackage temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRenderPackage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRenderPackage::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igNonRefCountedAttrList::arkRegister, Gap::Sg::igRenderPackageList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRenderPackage",
        sizeof(igRenderPackage),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRenderPackage::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igRawRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_stateAttrs", "_cachedStateAttrs", "_geomAttrs", "_sortingCache", "_distance", "_theMass" };
    static igMetaField **enumStorage[] = { &k_stateAttrs, &k_cachedStateAttrs, &k_geomAttrs, &k_sortingCache, &k_distance, &k_theMass };
    static int offsets[] = { 8, 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackageList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

