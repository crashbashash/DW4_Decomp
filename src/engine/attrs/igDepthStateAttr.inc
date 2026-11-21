namespace Gap {
namespace Attrs {

igMetaObject *igDepthStateAttr::_Meta;
igMetaField *igDepthStateAttr::k_enabled;

igDepthStateAttr *igDepthStateAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igDepthStateAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igDepthStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDepthStateAttr::retrieveVTablePointer()
{
    igDepthStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDepthStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDepthStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDepthStateAttr",
        sizeof(igDepthStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igDepthStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_enabled" };
    static igMetaField **enumStorage[] = { &k_enabled };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

