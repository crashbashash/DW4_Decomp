namespace Gap {
namespace Attrs {

igMetaObject *igLightAttr::_Meta;
igMetaField *igLightAttr::k_lightType;
igMetaField *igLightAttr::k_lightId;
igMetaField *igLightAttr::k_position;
igMetaField *igLightAttr::k_ambient;
igMetaField *igLightAttr::k_diffuse;
igMetaField *igLightAttr::k_specular;
igMetaField *igLightAttr::k_direction;
igMetaField *igLightAttr::k_falloff;
igMetaField *igLightAttr::k_cutoff;
igMetaField *igLightAttr::k_attenuation;
igMetaField *igLightAttr::k_shininess;
igMetaField *igLightAttr::k_cachedPosition;
igMetaField *igLightAttr::k_cachedDirection;
igMetaField *igLightAttr::k_vc;
igMetaField *igLightAttr::k_changed;
igMetaField *igLightAttr::k_cacheable;

igMetaObject *igLightAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLightAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLightAttr::retrieveVTablePointer()
{
    igLightAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLightAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLightAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVisualContext_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLightAttr",
        sizeof(igLightAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

int g_igLightAttr_lightTypeDefault = 1;

namespace Gap {
namespace Attrs {

void igLightAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_lightType", "_lightId", "_position", "_ambient", "_diffuse", "_specular", "_direction", "_falloff", "_cutoff", "_attenuation", "_shininess", "_cachedPosition", "_cachedDirection", "_vc", "_changed", "_cacheable" };
    static igMetaField **enumStorage[] = { &k_lightType, &k_lightId, &k_position, &k_ambient, &k_diffuse, &k_specular, &k_direction, &k_falloff, &k_cutoff, &k_attenuation, &k_shininess, &k_cachedPosition, &k_cachedDirection, &k_vc, &k_changed, &k_cacheable };
    static int offsets[] = { 12, 16, 20, 32, 48, 64, 80, 92, 96, 100, 112, 116, 128, 140, 144, 145 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 16);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_LIGHT_TYPE_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 4;
        metaField->_shallowCopyMethod = 4;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(igVec4f(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(igVec4f(1.0f, 1.0f, 1.0f, 1.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 1.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(180.0f);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(igVec3f(1.0f, 0.0f, 0.0f));
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igLightAttr::lightChanged;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(igVec3f(0.0f, 0.0f, -1.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

