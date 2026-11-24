namespace Gap {
namespace Sg {

igMetaObject *igProjectiveShadowShader::_Meta;
igMetaField *igProjectiveShadowShader::k_lightPos;
igMetaField *igProjectiveShadowShader::k_lightDir;
igMetaField *igProjectiveShadowShader::k_cutoff;
igMetaField *igProjectiveShadowShader::k_shadowCasters;
igMetaField *igProjectiveShadowShader::k_shadowReceivers;
igMetaField *igProjectiveShadowShader::k_shadowFactor;
igMetaField *igProjectiveShadowShader::k_shadowTexW;
igMetaField *igProjectiveShadowShader::k_shadowTexH;
igMetaField *igProjectiveShadowShader::k_shadowLightness;
igMetaField *igProjectiveShadowShader::k_viewToProjectedLightTextureMatrixpAttrList;
igMetaField *igProjectiveShadowShader::k_lightMVMAttr;
igMetaField *igProjectiveShadowShader::k_lightProjAttr;
igMetaField *igProjectiveShadowShader::k_blurMVMAttr;
igMetaField *igProjectiveShadowShader::k_blurProjAttr;
igMetaField *igProjectiveShadowShader::k_inited;
igMetaField *igProjectiveShadowShader::k_quadsGeom;
igMetaField *igProjectiveShadowShader::k_unused;
igMetaField *igProjectiveShadowShader::k_shadowColor;
igMetaField *igProjectiveShadowShader::k_blurState;
igMetaField *igProjectiveShadowShader::k_zNear;
igMetaField *igProjectiveShadowShader::k_zFar;
igMetaField *igProjectiveShadowShader::k_upVector;
igMetaField *igProjectiveShadowShader::k_viewToProjectedLightTextureMatrix;
igMetaField *igProjectiveShadowShader::k_drawReceiver;
igMetaField *igProjectiveShadowShader::k_updateShadowMap;
igMetaField *igProjectiveShadowShader::k_pShadowTexRD;
igMetaField *igProjectiveShadowShader::k_pSetShadowTexRD;
igMetaField *igProjectiveShadowShader::k_pShadowTex;
igMetaField *igProjectiveShadowShader::k_pShadowTexBind;
igMetaField *igProjectiveShadowShader::k_pBlurTexRD;
igMetaField *igProjectiveShadowShader::k_pSetBlurTexRD;
igMetaField *igProjectiveShadowShader::k_pBlurTex;
igMetaField *igProjectiveShadowShader::k_pBlurTexBind;
igMetaField *igProjectiveShadowShader::k_shadowCopyBack;
igMetaField *igProjectiveShadowShader::k_shadowCopyBackImage;
igMetaField *igProjectiveShadowShader::k_shadowViewport;
igMetaField *igProjectiveShadowShader::k_shadowInnerViewport;
igMetaField *igProjectiveShadowShader::k_light;
igMetaField *igProjectiveShadowShader::k_pShadowTexBind1;
igMetaField *igProjectiveShadowShader::k_useOrthographic;
igMetaField *igProjectiveShadowShader::k_top;
igMetaField *igProjectiveShadowShader::k_bottom;
igMetaField *igProjectiveShadowShader::k_right;
igMetaField *igProjectiveShadowShader::k_left;
igMetaField *igProjectiveShadowShader::k_unloadShadowTexRD;
igMetaField *igProjectiveShadowShader::k_unloadBlurTexRD;
igMetaField *igProjectiveShadowShader::k_releaseRenderDestinationAfterDraw;
igMetaField *igProjectiveShadowShader::k_useShadowFactor;
}
}

igMetaObject *igProjectiveShadowShader_GetOrCreateMetaObject(void) {
    if (Gap::Sg::igProjectiveShadowShader::getClassMeta() == 0) {
        g_igProjectiveShadowShader_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return Gap::Sg::igProjectiveShadowShader::getClassMeta();
}

namespace Gap {
namespace Sg {

igMetaObject *igProjectiveShadowShader::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igProjectiveShadowShader::retrieveVTablePointer()
{
    igProjectiveShadowShader temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igProjectiveShadowShader::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igProjectiveShadowShader::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igNodeList::arkRegister, Gap::Attrs::igNonRefCountedAttrList::arkRegister, Gap::Attrs::igModelViewMatrixAttr::arkRegister, Gap::Attrs::igProjectionMatrixAttr::arkRegister, Gap::Sg::igGeometry::arkRegister, Gap::Attrs::igGeometryAttr::arkRegister, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igTextureMatrixAttr::arkRegister, Gap::Attrs::igRenderDestinationAttr::arkRegister, Gap::Attrs::igSetRenderDestinationAttr::arkRegister, Gap::Attrs::igTextureAttr::arkRegister, Gap::Attrs::igTextureBindAttr::arkRegister, Gap::Attrs::igCopyRenderDestinationAttr::arkRegister, Gap::Gfx::igImage::arkRegister, Gap::Attrs::igViewportAttr::arkRegister, Gap::Attrs::igLightAttr::arkRegister, Gap::Attrs::igTextureUnloadAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igProjectiveShadowShader",
        sizeof(igProjectiveShadowShader),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igProjectiveShadowShader::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igIntMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_lightPos", "_lightDir", "_cutoff", "_shadowCasters", "_shadowReceivers", "_shadowFactor", "_shadowTexW", "_shadowTexH", "_shadowLightness", "_viewToProjectedLightTextureMatrixpAttrList", "_lightMVMAttr", "_lightProjAttr", "_blurMVMAttr", "_blurProjAttr", "_inited", "_quadsGeom", "_unused", "_shadowColor", "_blurState", "_zNear", "_zFar", "_upVector", "_viewToProjectedLightTextureMatrix", "_drawReceiver", "_updateShadowMap", "_pShadowTexRD", "_pSetShadowTexRD", "_pShadowTex", "_pShadowTexBind", "_pBlurTexRD", "_pSetBlurTexRD", "_pBlurTex", "_pBlurTexBind", "_shadowCopyBack", "_shadowCopyBackImage", "_shadowViewport", "_shadowInnerViewport", "_light", "_pShadowTexBind1", "_useOrthographic", "_top", "_bottom", "_right", "_left", "_unloadShadowTexRD", "_unloadBlurTexRD", "_releaseRenderDestinationAfterDraw", "_useShadowFactor" };
    static igMetaField **enumStorage[] = { &k_lightPos, &k_lightDir, &k_cutoff, &k_shadowCasters, &k_shadowReceivers, &k_shadowFactor, &k_shadowTexW, &k_shadowTexH, &k_shadowLightness, &k_viewToProjectedLightTextureMatrixpAttrList, &k_lightMVMAttr, &k_lightProjAttr, &k_blurMVMAttr, &k_blurProjAttr, &k_inited, &k_quadsGeom, &k_unused, &k_shadowColor, &k_blurState, &k_zNear, &k_zFar, &k_upVector, &k_viewToProjectedLightTextureMatrix, &k_drawReceiver, &k_updateShadowMap, &k_pShadowTexRD, &k_pSetShadowTexRD, &k_pShadowTex, &k_pShadowTexBind, &k_pBlurTexRD, &k_pSetBlurTexRD, &k_pBlurTex, &k_pBlurTexBind, &k_shadowCopyBack, &k_shadowCopyBackImage, &k_shadowViewport, &k_shadowInnerViewport, &k_light, &k_pShadowTexBind1, &k_useOrthographic, &k_top, &k_bottom, &k_right, &k_left, &k_unloadShadowTexRD, &k_unloadBlurTexRD, &k_releaseRenderDestinationAfterDraw, &k_useShadowFactor };
    static int offsets[] = { 32, 44, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 144, 148, 149, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 237 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 48);
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igVec3f(0.0f, 4.0f, 0.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, -1.0f, 0.0f));
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(30.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(0.30000001192092896f);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(128);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(128);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(0.5f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)Gap::Attrs::igProjectionMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Attrs::igProjectionMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(0);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_metaObject = (int)Gap::Sg::igGeometry::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->setDefault(1);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->setDefault(0.10000000149011612f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->setDefault(1000.0f);
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->setDefault(igVec3f(1.0f, 0.0f, 0.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->_metaObject = (int)Gap::Attrs::igTextureMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_metaObject = (int)Gap::Attrs::igRenderDestinationAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->_metaObject = (int)Gap::Attrs::igSetRenderDestinationAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 27);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 28);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->_metaObject = (int)Gap::Attrs::igRenderDestinationAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 30);
        metaField->_metaObject = (int)Gap::Attrs::igSetRenderDestinationAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 31);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 32);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 33);
        metaField->_metaObject = (int)Gap::Attrs::igCopyRenderDestinationAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 34);
        metaField->_metaObject = (int)Gap::Gfx::igImage::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 35);
        metaField->_metaObject = (int)Gap::Attrs::igViewportAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 36);
        metaField->_metaObject = (int)Gap::Attrs::igViewportAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 37);
        metaField->_metaObject = (int)Gap::Attrs::igLightAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 38);
        metaField->_metaObject = (int)Gap::Attrs::igTextureBindAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 40);
        metaField->setDefault(5.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 41);
        metaField->setDefault(-5.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 42);
        metaField->setDefault(5.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 43);
        metaField->setDefault(-5.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 44);
        metaField->_metaObject = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 45);
        metaField->_metaObject = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 47);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

