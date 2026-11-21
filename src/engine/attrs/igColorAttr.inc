namespace Gap {
namespace Attrs {

igMetaObject *igColorAttr::_Meta;
igMetaField *igColorAttr::k_color;
igMetaField *igColorAttr::k_colorPacked;

igColorAttr *igColorAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igColorAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igColorAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igColorAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igColorAttr::retrieveVTablePointer()
{
    igColorAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igColorAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igColorAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igColorAttr",
        sizeof(igColorAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igColorAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_color", "_colorPacked" };
    static igMetaField **enumStorage[] = { &k_color, &k_colorPacked };
    static int offsets[] = { 12, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igVec4f(1.0f, 1.0f, 1.0f, 1.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igColorAttr::colorChanged;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

