namespace Gap {
namespace Attrs {

igMetaObject *igStencilStateAttr::_Meta;
igMetaField *igStencilStateAttr::k_enabled;

igMetaObject *igStencilStateAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igStencilStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStencilStateAttr::retrieveVTablePointer()
{
    igStencilStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStencilStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStencilStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStencilStateAttr",
        sizeof(igStencilStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igStencilStateAttr::arkRegisterInitialize()
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

