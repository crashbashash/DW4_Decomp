static const char *g_igPsx2VisualContext_clearrenderdestinationTypePsx2Names[] = {
    "IG_GFX_CLEARRENDERDESTINATION_ONE_PSX2", "IG_GFX_CLEARRENDERDESTINATION_MULTIPLE_PSX2",
};
static int g_igPsx2VisualContext_clearrenderdestinationTypePsx2Values[] = {
    0, 1,
};
igMetaEnum *g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum;

int IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2_GetMetaEnum(void) {
    if (g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum == 0) {
        g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2", g_igPsx2VisualContext_clearrenderdestinationTypePsx2Names, g_igPsx2VisualContext_clearrenderdestinationTypePsx2Values, 2);
    }
    return (int)g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum;
}

static const char *g_igPsx2VisualContext_clippingTypePsx2Names[] = {
    "IG_GFX_CLIPPING_TYPE_FULL_PSX2", "IG_GFX_CLIPPING_TYPE_GUARDBAND_PSX2",
};
static int g_igPsx2VisualContext_clippingTypePsx2Values[] = {
    0, 1,
};
igMetaEnum *g_igPsx2VisualContext_clippingTypePsx2MetaEnum;

int IG_GFX_CLIPPING_TYPE_PSX2_GetMetaEnum(void) {
    if (g_igPsx2VisualContext_clippingTypePsx2MetaEnum == 0) {
        g_igPsx2VisualContext_clippingTypePsx2MetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_CLIPPING_TYPE_PSX2", g_igPsx2VisualContext_clippingTypePsx2Names, g_igPsx2VisualContext_clippingTypePsx2Values, 2);
    }
    return (int)g_igPsx2VisualContext_clippingTypePsx2MetaEnum;
}

namespace Gap {
namespace Gfx {

igMetaObject *igPsx2VisualContext::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igPsx2VisualContext::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2VisualContext::retrieveVTablePointer()
{
    igPsx2VisualContext temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igMemoryPool_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igTimer_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2VisualContext::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igIntList::arkRegister, Gap::Gfx::igPsx2VertexArray1_1::arkRegister, Gap::Gfx::igIndexArray::arkRegister, Gap::Gfx::igPrimLengthArray::arkRegister, igMatrixStack_EnsureRegistered, igPsx2ScissorExt_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igVisualContext::arkRegisterInternal,
        Gap::Gfx::igVisualContext::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2VisualContext",
        sizeof(igPsx2VisualContext),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

static int g_igPsx2VisualContext_alphaFuncDefault = 6;
static int g_igPsx2VisualContext_stencilFuncDefault = 2;
static int g_igPsx2VisualContext_mipmapMethodLDefault = 1;
static int g_igPsx2VisualContext_mipmapMethodKDefault = 1;
static int g_igPsx2VisualContext_destAlphaTestFuncDefault = 1;
static int g_igPsx2VisualContext_colorScalerStateDefault = 1;
static int g_igPsx2VisualContext_clearTypeDefault = 1;

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create, igRawRefMetaField_Create, igRawRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igBoolArrayMetaField::_instantiateFromPool, igBoolMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igBoolArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igEnumArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igEnumArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igRawRefMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igRawRefMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igEnumArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igEnumArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igEnumMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igRawRefMetaField_Create, igBoolMetaField_Create, igRawRefMetaField_Create, (FieldFactory)Gap::Core::igStructMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igEnumMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, (FieldFactory)Gap::Core::igUnsignedIntArrayMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igUnsignedLongMetaField_Create };
    static const char *names[] = { "_current", "_iContextOpen", "_pTexList", "_pClutList", "_pTexLoadedList", "_currentTex", "_iNextFreeTexID", "_currentCLUT", "_currentTextureFilter", "_currentTextureClampU", "_currentTextureClampV", "_currentTextureProjectiveState", "_texPageEnable", "_texStage", "_texEnable", "_texStageFunc", "_texCoordSource", "_texCoordIndex", "_texGenMat", "_iCLUT_I8", "_iCLUT_A8", "_iCLUT_IA16", "_iCLUT_IA8", "_pCLUT_I8", "_pCLUT_A8", "_pCLUT_IA16", "_pCLUT_IA8", "_pBufList", "_currentBuf", "_clearColor", "_clearDepth", "_uiClearColor", "_uiClearDepth", "_clearStencil", "_iDisplayWidth", "_iDisplayHeight", "_iViewportX", "_iViewportY", "_iViewportW", "_iViewportH", "_viewportNear", "_viewportFar", "_pVertexArray", "_pIndexArray", "_pStripLengthArray", "_vMask", "_currentColor", "_pDLists", "_currentDListHandle", "_dlistErrors", "_projMat", "_mvMat", "_texMat", "_texgenMat", "_blendMat0", "_blendMat1", "_blendMat2", "_blendMat3", "_invTransBlendMat0", "_invTransBlendMat1", "_invTransBlendMat2", "_invTransBlendMat3", "_bVertexBlendingEnabled", "_edgeAntiAliasEnable", "_alphaEnable", "_alphaFunc", "_alphaVal", "_bBlendingEnabled", "_blendSrcMode", "_blendDestMode", "_blendConst", "_clippingEnable", "_scissoringExt", "_scissorX", "_scissorY", "_scissorW", "_scissorH", "_colorMaskR", "_colorMaskG", "_colorMaskB", "_colorMaskA", "_shadingMode", "_stencilState", "_stencilRefVal", "_cullFaceEnable", "_cullFaceMode", "_bDepthWrite", "_depthTestEnable", "_depthTestFunc", "_depthWriteEnable", "_stencilFunc", "_renderMode", "_renderSides", "_fogEnable", "_fogDensity", "_fogMode", "_fogColor", "_fogNear", "_fogFar", "_pLightList", "_bLightingEnabled", "_currentMaterial", "_videoMode", "_bNormalizeNormalsState", "_matrixOptimizationEnable", "_statisticState", "_scaleToPower2Warning", "_mipmapMethodL", "_mipmapMethodK", "_mipmapL", "_mipmapK", "_renderlistMode", "_needsValidate", "_destAlphaTestState", "_destAlphaTestFunc", "_vertexProgramState", "_inverseTransposeCount", "_inverseTransposeNeedValidation", "_colorScalerState", "_colorScalerValue", "_textureMatrixState", "_colorClampState", "_materialSpecularState", "_bTextureColorComponent", "_bMultiPassNum", "_multiPassBlendState", "_multiPassBlendSrc", "_multiPassBlendDst", "_clutOptimization", "_maxStageNum", "_globalMinU", "_globalMinV", "_globalMaxU", "_globalMaxV", "_globalWrapState", "_globalWrapMode", "_textureStateFilter", "_textureMinFilter", "_textureMagFilter", "_pixelPipelineMode", "_clippingType", "_clearType", "_frameBufferTexture", "_alphaBlendingControl", "_alphaBlendingCorrection", "_ditherMatrix" };
    static igMetaField **enumStorage[] = { &k_current, &k_iContextOpen, &k_pTexList, &k_pClutList, &k_pTexLoadedList, &k_currentTex, &k_iNextFreeTexID, &k_currentCLUT, &k_currentTextureFilter, &k_currentTextureClampU, &k_currentTextureClampV, &k_currentTextureProjectiveState, &k_texPageEnable, &k_texStage, &k_texEnable, &k_texStageFunc, &k_texCoordSource, &k_texCoordIndex, &k_texGenMat, &k_iCLUT_I8, &k_iCLUT_A8, &k_iCLUT_IA16, &k_iCLUT_IA8, &k_pCLUT_I8, &k_pCLUT_A8, &k_pCLUT_IA16, &k_pCLUT_IA8, &k_pBufList, &k_currentBuf, &k_clearColor, &k_clearDepth, &k_uiClearColor, &k_uiClearDepth, &k_clearStencil, &k_iDisplayWidth, &k_iDisplayHeight, &k_iViewportX, &k_iViewportY, &k_iViewportW, &k_iViewportH, &k_viewportNear, &k_viewportFar, &k_pVertexArray, &k_pIndexArray, &k_pStripLengthArray, &k_vMask, &k_currentColor, &k_pDLists, &k_currentDListHandle, &k_dlistErrors, &k_projMat, &k_mvMat, &k_texMat, &k_texgenMat, &k_blendMat0, &k_blendMat1, &k_blendMat2, &k_blendMat3, &k_invTransBlendMat0, &k_invTransBlendMat1, &k_invTransBlendMat2, &k_invTransBlendMat3, &k_bVertexBlendingEnabled, &k_edgeAntiAliasEnable, &k_alphaEnable, &k_alphaFunc, &k_alphaVal, &k_bBlendingEnabled, &k_blendSrcMode, &k_blendDestMode, &k_blendConst, &k_clippingEnable, &k_scissoringExt, &k_scissorX, &k_scissorY, &k_scissorW, &k_scissorH, &k_colorMaskR, &k_colorMaskG, &k_colorMaskB, &k_colorMaskA, &k_shadingMode, &k_stencilState, &k_stencilRefVal, &k_cullFaceEnable, &k_cullFaceMode, &k_bDepthWrite, &k_depthTestEnable, &k_depthTestFunc, &k_depthWriteEnable, &k_stencilFunc, &k_renderMode, &k_renderSides, &k_fogEnable, &k_fogDensity, &k_fogMode, &k_fogColor, &k_fogNear, &k_fogFar, &k_pLightList, &k_bLightingEnabled, &k_currentMaterial, &k_videoMode, &k_bNormalizeNormalsState, &k_matrixOptimizationEnable, &k_statisticState, &k_scaleToPower2Warning, &k_mipmapMethodL, &k_mipmapMethodK, &k_mipmapL, &k_mipmapK, &k_renderlistMode, &k_needsValidate, &k_destAlphaTestState, &k_destAlphaTestFunc, &k_vertexProgramState, &k_inverseTransposeCount, &k_inverseTransposeNeedValidation, &k_colorScalerState, &k_colorScalerValue, &k_textureMatrixState, &k_colorClampState, &k_materialSpecularState, &k_bTextureColorComponent, &k_bMultiPassNum, &k_multiPassBlendState, &k_multiPassBlendSrc, &k_multiPassBlendDst, &k_clutOptimization, &k_maxStageNum, &k_globalMinU, &k_globalMinV, &k_globalMaxU, &k_globalMaxV, &k_globalWrapState, &k_globalWrapMode, &k_textureStateFilter, &k_textureMinFilter, &k_textureMagFilter, &k_pixelPipelineMode, &k_clippingType, &k_clearType, &k_frameBufferTexture, &k_alphaBlendingControl, &k_alphaBlendingCorrection, &k_ditherMatrix };
    static int offsets[] = { 321, 322, 324, 328, 332, 336, 340, 344, 348, 412, 476, 540, 556, 560, 564, 580, 644, 708, 772, 836, 840, 844, 848, 852, 856, 860, 864, 868, 872, 876, 892, 896, 900, 904, 908, 912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956, 960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020, 1021, 1022, 1024, 1028, 1032, 1036, 1100, 1164, 1228, 1232, 1236, 1240, 1244, 1248, 1252, 1253, 1254, 1255, 1256, 1260, 1264, 1268, 1272, 1276, 1277, 1280, 1284, 1288, 1292, 1296, 1300, 1304, 1308, 1312, 1328, 1332, 1336, 1340, 1344, 1348, 1372, 1373, 1376, 1380, 1384, 1388, 1392, 1396, 1400, 1404, 1408, 1412, 1416, 1420, 1424, 1428, 1432, 1448, 1449, 1450, 320, 1452, 1456, 1460, 1464, 1468, 1472, 1476, 1480, 1484, 1488, 1492, 1496, 1500, 1504, 1508, 1512, 1516, 1520, 1524, 1536, 1537, 1544 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 146);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(-1);
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_num = 16;
        metaField->setDefault(-1);
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_num = 16;
        metaField->setDefault(-1);
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_num = 16;
        metaField->setDefault(-1);
    }
    {
        igBoolArrayMetaField *metaField = (igBoolArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_num = 16;
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(1);
    }
    {
        igBoolArrayMetaField *metaField = (igBoolArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_num = 16;
    }
    {
        igEnumArrayMetaField *metaField = (igEnumArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_num = 16;
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumArrayMetaField *metaField = (igEnumArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_num = 16;
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_num = 16;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->setDefault(-1);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 28);
        metaField->setDefault(-1);
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 0.0f));
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 30);
        metaField->setDefault(1.0f);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 38);
        metaField->setDefault(640);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 39);
        metaField->setDefault(448);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 40);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 41);
        metaField->setDefault(1.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 42);
        metaField->_metaObject = (int)Gap::Gfx::igPsx2VertexArray1_1::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 43);
        metaField->_metaObject = (int)Gap::Gfx::igIndexArray::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 44);
        metaField->_metaObject = (int)Gap::Gfx::igPrimLengthArray::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 48);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 50);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 51);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 52);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 53);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 54);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 55);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 56);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 57);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 58);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 59);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 60);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 61);
        metaField->_metaObject = (int)igMatrixStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 65);
        metaField->setDefault(6);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumArrayMetaField *metaField = (igEnumArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 68);
        metaField->_num = 16;
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumArrayMetaField *metaField = (igEnumArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 69);
        metaField->_num = 16;
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 70);
        metaField->_num = 16;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 72);
        metaField->_metaObject = (int)igPsx2ScissorExt_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 75);
        metaField->setDefault(640);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 76);
        metaField->setDefault(448);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 77);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 78);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 79);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 80);
        metaField->setDefault(1);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 81);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 82);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 85);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 86);
        metaField->setDefault(1);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 88);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 90);
        metaField->setDefault(2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STENCIL_FUNCTION_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 91);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 92);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 95);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 96);
        metaField->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 0.0f));
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 97);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 98);
        metaField->setDefault(10000.0f);
    }
    {
        igStructMetaField *metaField = (igStructMetaField *)igMetaObject_GetFieldAt(metaObject, start + 102);
        metaField->_size = 24;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 105);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 106);
        metaField->setDefault(1);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 107);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 108);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 111);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 114);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 118);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 119);
        metaField->setDefault(igVec4f(0.5019607543945312f, 0.5019607543945312f, 0.5019607543945312f, 1.0f));
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 121);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 122);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 123);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 124);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 125);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 126);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 127);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 128);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 129);
        metaField->setDefault(16);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 130);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 131);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 132);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 133);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 134);
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 135);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_WRAP_GetMetaEnum;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 136);
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 137);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 138);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 139);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_PIXEL_PIPELINE_MODE_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 140);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_CLIPPING_TYPE_PSX2_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 141);
        metaField->setDefault(1);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2_GetMetaEnum;
    }
    {
        igUnsignedIntArrayMetaField *metaField = (igUnsignedIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 142);
        metaField->_num = 3;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 143);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 144);
        metaField->_persistent = 0;
    }
    {
        igUnsignedLongMetaField *metaField = (igUnsignedLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 145);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Gfx::igVisualContext::getClassMetaSafe;
}
}
}

