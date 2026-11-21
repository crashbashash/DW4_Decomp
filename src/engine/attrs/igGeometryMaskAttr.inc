namespace Gap {
namespace Attrs {

igMetaObject *igGeometryMaskAttr::_Meta;
igMetaField *igGeometryMaskAttr::k_mask;

igGeometryMaskAttr *igGeometryMaskAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igGeometryMaskAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igGeometryMaskAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGeometryMaskAttr::retrieveVTablePointer()
{
    igGeometryMaskAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGeometryMaskAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometryMaskAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometryMaskAttr",
        sizeof(igGeometryMaskAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igGeometryMaskAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create };
    static const char *names[] = { "_mask" };
    static igMetaField **enumStorage[] = { &k_mask };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

