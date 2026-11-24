namespace Gap {
namespace Sg {

igGeometry *igGeometry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igGeometry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igGeometry::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGeometry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGeometry::retrieveVTablePointer()
{
    igGeometry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGeometry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometry::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igRenderListAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAttrSet::arkRegisterInternal,
        Gap::Sg::igAttrSet::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometry",
        sizeof(igGeometry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        thunk_FUN_001c51d0,
        regFunctions
    );
}

void igGeometry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_renderList" };
    static igMetaField **enumStorage[] = { &k_renderList };
    static int offsets[] = { 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_FindFieldByName(metaObject, "_trigger");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igBoolMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(1);
        metaField->_externalEnumStorage = (int)&k_trigger;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igRenderListAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

void thunk_FUN_001c51d0(void) {
    Gap::Sg::igGeometry::userRegister();
}

