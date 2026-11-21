namespace Gap {
namespace Attrs {

igMetaObject *igColorMaskAttr::_Meta;
igMetaField *igColorMaskAttr::k_red;
igMetaField *igColorMaskAttr::k_green;
igMetaField *igColorMaskAttr::k_blue;
igMetaField *igColorMaskAttr::k_alpha;
igMetaField *igColorMaskAttr::k_unused;

igColorMaskAttr *igColorMaskAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igColorMaskAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igColorMaskAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igColorMaskAttr::retrieveVTablePointer()
{
    igColorMaskAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igColorMaskAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igColorMaskAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igColorMaskAttr",
        sizeof(igColorMaskAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igColorMaskAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_red", "_green", "_blue", "_alpha", "_unused" };
    static igMetaField **enumStorage[] = { &k_red, &k_green, &k_blue, &k_alpha, &k_unused };
    static int offsets[] = { 12, 13, 14, 15, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

