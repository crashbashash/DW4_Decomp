namespace Gap {
namespace Sg {

igMetaObject *igEnvironmentMapShader2::_Meta;
igMetaField *igEnvironmentMapShader2::k_envMapTexture;
igMetaField *igEnvironmentMapShader2::k_diffuseTextureBind;
igMetaField *igEnvironmentMapShader2::k_diffuseTextureCoordIndex;
igMetaField *igEnvironmentMapShader2::k_reflectionAmount;
igMetaField *igEnvironmentMapShader2::k_isTransparent;
igMetaField *igEnvironmentMapShader2::k_glossMapTexture;
igMetaField *igEnvironmentMapShader2::k_glossTextureCoordIndex;
igMetaField *igEnvironmentMapShader2::k_configured;
igMetaField *igEnvironmentMapShader2::k_attrPushLists;
igMetaField *igEnvironmentMapShader2::k_attrPopLists;
igMetaField *igEnvironmentMapShader2::k_useRenderPackage;
igMetaField *igEnvironmentMapShader2::k_discardUnusedImages;
igMetaField *igEnvironmentMapShader2::k_envMapTextureBind;
igMetaField *igEnvironmentMapShader2::k_envMapCoordSource;
igMetaField *igEnvironmentMapShader2::k_envMapTextureFunc;
igMetaField *igEnvironmentMapShader2::k_diffuseCoordSource;
igMetaField *igEnvironmentMapShader2::k_diffuseTextureFunc;
igMetaField *igEnvironmentMapShader2::k_diffuseBlendState;
igMetaField *igEnvironmentMapShader2::k_glossMapTextureBind;
igMetaField *igEnvironmentMapShader2::k_glossMapCoordSource;
igMetaField *igEnvironmentMapShader2::k_glossMapTextureFunc;

igMetaObject *igEnvironmentMapShader2::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igEnvironmentMapShader2::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnvironmentMapShader2::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igTextureCubeAttr::arkRegister, Gap::Attrs::igTextureBindAttr::arkRegister, Gap::Attrs::igTextureAttr::arkRegister, Gap::Attrs::igAttrListList::arkRegister, Gap::Attrs::igTextureBindAttr::arkRegister, Gap::Attrs::igTextureCoordSourceAttr::arkRegister, Gap::Attrs::igTextureFunctionAttr::arkRegister, Gap::Attrs::igBlendStateAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnvironmentMapShader2",
        sizeof(igEnvironmentMapShader2),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igEnvironmentMapShader2::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_envMapTexture", "_diffuseTextureBind", "_diffuseTextureCoordIndex", "_reflectionAmount", "_isTransparent", "_glossMapTexture", "_glossTextureCoordIndex", "_configured", "_attrPushLists", "_attrPopLists", "_useRenderPackage", "_discardUnusedImages", "_envMapTextureBind", "_envMapCoordSource", "_envMapTextureFunc", "_diffuseCoordSource", "_diffuseTextureFunc", "_diffuseBlendState", "_glossMapTextureBind", "_glossMapCoordSource", "_glossMapTextureFunc" };
    static igMetaField **enumStorage[] = { &k_envMapTexture, &k_diffuseTextureBind, &k_diffuseTextureCoordIndex, &k_reflectionAmount, &k_isTransparent, &k_glossMapTexture, &k_glossTextureCoordIndex, &k_configured, &k_attrPushLists, &k_attrPopLists, &k_useRenderPackage, &k_discardUnusedImages, &k_envMapTextureBind, &k_envMapCoordSource, &k_envMapTextureFunc, &k_diffuseCoordSource, &k_diffuseTextureFunc, &k_diffuseBlendState, &k_glossMapTextureBind, &k_glossMapCoordSource, &k_glossMapTextureFunc };
    static int offsets[] = { 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 73, 76, 80, 84, 88, 92, 96, 100, 104, 108 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 21);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igTextureCubeAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Attrs::igAttrListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Attrs::igAttrListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Attrs::igTextureCoordSourceAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_metaObject = (int)Gap::Attrs::igTextureFunctionAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_metaObject = (int)Gap::Attrs::igTextureCoordSourceAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_metaObject = (int)Gap::Attrs::igTextureFunctionAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)Gap::Attrs::igBlendStateAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_metaObject = (int)Gap::Attrs::igTextureCoordSourceAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->_metaObject = (int)Gap::Attrs::igTextureFunctionAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Sg::igPsx2EnvironmentMapShader::getClassMetaSafe;
}
}
}

