namespace Gap {
namespace Sg {

igAttrSet *igAttrSet::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAttrSet *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAttrSet::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAttrSet::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAttrSet::retrieveVTablePointer()
{
    igAttrSet temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAttrSet::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAttrSet::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igAttrList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAttrSet",
        sizeof(igAttrSet),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAttrSet::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_attributes", "_trigger" };
    static igMetaField **enumStorage[] = { &k_attributes, &k_trigger };
    static int offsets[] = { 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

