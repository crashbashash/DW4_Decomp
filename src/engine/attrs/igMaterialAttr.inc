namespace Gap {
namespace Attrs {

igMetaObject *igMaterialAttr::_Meta;
igMetaField *igMaterialAttr::k_shininess;
igMetaField *igMaterialAttr::k_diffuse;
igMetaField *igMaterialAttr::k_ambient;
igMetaField *igMaterialAttr::k_emission;
igMetaField *igMaterialAttr::k_specular;
igMetaField *igMaterialAttr::k_flags;

igMetaObject *igMaterialAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMaterialAttr::retrieveVTablePointer()
{
    igMaterialAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMaterialAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMaterialAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMaterialAttr",
        sizeof(igMaterialAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igMaterialAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_shininess", "_diffuse", "_ambient", "_emission", "_specular", "_flags" };
    static igMetaField **enumStorage[] = { &k_shininess, &k_diffuse, &k_ambient, &k_emission, &k_specular, &k_flags };
    static int offsets[] = { 12, 16, 32, 48, 64, 80 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

