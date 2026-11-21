namespace Gap {
namespace Attrs {

igMetaObject *igClearAttr::_Meta;
igMetaField *igClearAttr::k_clearMode;
igMetaField *igClearAttr::k_color;
igMetaField *igClearAttr::k_accum;
igMetaField *igClearAttr::k_depth;
igMetaField *igClearAttr::k_stencil;
igMetaField *igClearAttr::k_colorPacked;
igMetaField *igClearAttr::k_depthF;

igClearAttr *igClearAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igClearAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igClearAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igClearAttr::retrieveVTablePointer()
{
    igClearAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igClearAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igClearAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igClearAttr",
        sizeof(igClearAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igClearAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igDoubleMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igFloatMetaField_Create };
    static const char *names[] = { "_clearMode", "_color", "_accum", "_depth", "_stencil", "_colorPacked", "_depthF" };
    static igMetaField **enumStorage[] = { &k_clearMode, &k_color, &k_accum, &k_depth, &k_stencil, &k_colorPacked, &k_depthF };
    static int offsets[] = { 12, 16, 32, 48, 56, 60, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 0.0f));
    }
    {
        igDoubleMetaField *metaField = (igDoubleMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1.0);
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(1.0f);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

