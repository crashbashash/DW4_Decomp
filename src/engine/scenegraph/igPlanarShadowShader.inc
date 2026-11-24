namespace Gap {
namespace Sg {

igMetaObject *igPlanarShadowShader::_Meta;
igMetaField *igPlanarShadowShader::k_lights;
igMetaField *igPlanarShadowShader::k_mvmList;
igMetaField *igPlanarShadowShader::k_shadowPlane;
igMetaField *igPlanarShadowShader::k_shadowColor;
igMetaField *igPlanarShadowShader::k_shadowUseBlend;
igMetaField *igPlanarShadowShader::k_shadowUseStencil;
igMetaField *igPlanarShadowShader::k_mats;
igMetaField *igPlanarShadowShader::k_geoms;
igMetaField *igPlanarShadowShader::k_blendmats;
igMetaField *igPlanarShadowShader::k_savedBounds;
igMetaField *igPlanarShadowShader::k_unused;
igMetaField *igPlanarShadowShader::k_shadowColorAttr;
igMetaField *igPlanarShadowShader::k_stencilState;

igMetaObject *igPlanarShadowShader::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPlanarShadowShader::retrieveVTablePointer()
{
    igPlanarShadowShader temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}
namespace Gap {
namespace Sg {

void igPlanarShadowShader::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPlanarShadowShader::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igLightList::arkRegister, Gap::Attrs::igModelViewMatrixAttrList::arkRegister, Gap::Sg::igGeometryList::arkRegister, Gap::Attrs::igAttrList::arkRegister, igVolume_EnsureRegistered, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igStencilStateAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAttrSet::arkRegisterInternal,
        Gap::Sg::igAttrSet::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPlanarShadowShader",
        sizeof(igPlanarShadowShader),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

igMetaObject *igAttrSet::_Meta;
igMetaField *igAttrSet::k_attributes;
igMetaField *igAttrSet::k_trigger;

void igPlanarShadowShader::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_lights", "_mvmList", "_shadowPlane", "_shadowColor", "_shadowUseBlend", "_shadowUseStencil", "_mats", "_geoms", "_blendmats", "_savedBounds", "_unused", "_shadowColorAttr", "_stencilState" };
    static igMetaField **enumStorage[] = { &k_lights, &k_mvmList, &k_shadowPlane, &k_shadowColor, &k_shadowUseBlend, &k_shadowUseStencil, &k_mats, &k_geoms, &k_blendmats, &k_savedBounds, &k_unused, &k_shadowColorAttr, &k_stencilState };
    static int offsets[] = { 40, 44, 48, 64, 108, 109, 80, 84, 88, 92, 96, 100, 104 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 13);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igLightList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec4f(0.0f, 1.0f, 0.0f, 0.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Sg::igGeometryList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)igVolume_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)igVolume_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Attrs::igStencilStateAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

