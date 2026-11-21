namespace Gap {
namespace Attrs {

igMetaObject *igTimeAttr::_Meta;
igMetaField *igTimeAttr::k_time;

igTimeAttr *igTimeAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTimeAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTimeAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTimeAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTimeAttr::retrieveVTablePointer()
{
    igTimeAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTimeAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTimeAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTimeAttr",
        sizeof(igTimeAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTimeAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_time" };
    static igMetaField **enumStorage[] = { &k_time };
    static int offsets[] = { 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

