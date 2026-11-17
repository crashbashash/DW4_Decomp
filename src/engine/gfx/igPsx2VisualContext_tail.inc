static const char *g_igPsx2VisualContext_clearrenderdestinationTypePsx2Names[] = {
    "IG_GFX_CLEARRENDERDESTINATION_ONE_PSX2", "IG_GFX_CLEARRENDERDESTINATION_MULTIPLE_PSX2",
};
static int g_igPsx2VisualContext_clearrenderdestinationTypePsx2Values[] = {
    0, 1,
};
igMetaEnum *g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum;

int FUN_001506b0(void) {
    if (g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum == 0) {
        g_igPsx2VisualContext_clearrenderdestinationTypePsx2MetaEnum = igMetaEnum_Create("IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2", g_igPsx2VisualContext_clearrenderdestinationTypePsx2Names, g_igPsx2VisualContext_clearrenderdestinationTypePsx2Values, 2);
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

int FUN_00150710(void) {
    if (g_igPsx2VisualContext_clippingTypePsx2MetaEnum == 0) {
        g_igPsx2VisualContext_clippingTypePsx2MetaEnum = igMetaEnum_Create("IG_GFX_CLIPPING_TYPE_PSX2", g_igPsx2VisualContext_clippingTypePsx2Names, g_igPsx2VisualContext_clippingTypePsx2Values, 2);
    }
    return (int)g_igPsx2VisualContext_clippingTypePsx2MetaEnum;
}

igMetaObject *FUN_00150770(void) {
    if (g_igPsx2VisualContext_metaObject == 0) {
        g_igPsx2VisualContext_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPsx2VisualContext_metaObject;
}

igMetaObject *igPsx2VisualContext_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VisualContext_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001511a0();
    return g_igPsx2VisualContext_metaObject;
}

int igPsx2VisualContext_GetVTable(void) {
    struct VTableProbe s;
    char *p;
    char *q;
    int r;
    p = (char *)&s;
    FUN_001510e0((igVisualContext *)p);
    s.vt = &g_igPsx2VisualContext_vtable[0];
    q = (char *)&s + 332;
    igSmartPointer_igIntList_Construct((int *)q);
    FUN_001510a0((int)((char *)&s + 772));
    FUN_00151090((int)(p + 876));
    FUN_00151080((int *)(p + 940));
    FUN_00151070((int *)(p + 944));
    FUN_00151060((int *)(p + 948));
    FUN_00151050((int *)(p + 972));
    FUN_00151050((int *)(p + 976));
    FUN_00151050((int *)(p + 980));
    FUN_00151050((int *)(p + 984));
    FUN_00151050((int *)(p + 988));
    FUN_00151050((int *)(p + 992));
    FUN_00151050((int *)(p + 996));
    FUN_00151050((int *)(p + 1000));
    FUN_00151050((int *)(p + 1004));
    FUN_00151050((int *)(p + 1008));
    FUN_00151050((int *)(p + 1012));
    FUN_00151050((int *)(p + 1016));
    FUN_00151090((int)(p + 1312));
    FUN_00151030(p + 1348);
    FUN_00151090((int)(p + 1432));
    r = *(int *)((char *)&s + *(int *)((char *)g_objectSystem + 916));
    s.vt = &g_igPsx2VisualContext_vtable[0];
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1016), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1012), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1008), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1004), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1000), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 996), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 992), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 988), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 984), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 980), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 976), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 972), -1);
    FUN_00137260((char *)&s + 948, -1);
    FUN_001372e0((char *)&s + 944, -1);
    FUN_00150f30((O_1506b0 *)((char *)&s + 940), -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)q, -1);
    FUN_00150af0((Obj_1506b0 *)&s, 0);
    return r;
}

igSmartPointer<igObject> *igSmartPointer_igMemoryPool_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void **FUN_00150a70(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

Obj_1506b0 *FUN_00150af0(Obj_1506b0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00525e50;
        arg0->rel(&arg0->m308);
        arg0->rel(&arg0->m304);
        __destroy_arr((char *)arg0 + 240, (void *)&FUN_00137360, 4, 16);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m44);
        arg0->rel(&arg0->m40);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        arg0->rel(&arg0->m28);
        arg0->rel(&arg0->m24);
        if (arg0) {
            arg0->vt = DAT_00530a10;
            arg0->rel(&arg0->m16);
            arg0->rel(&arg0->m8);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igIntList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

O_1506b0 *FUN_00150f30(O_1506b0 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0_1506b0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00150fb0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void *FUN_00151030(void *arg0) {
    *(int *)((char *)(arg0) + 20) = 0;
    *(char *)((char *)(arg0) + 0) = 0;
    *(char *)((char *)(arg0) + 1) = 0;
    *(int *)((char *)(arg0) + 12) = 0;
    *(int *)((char *)(arg0) + 16) = 0;
    return arg0;
}

int *FUN_00151050(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151060(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151070(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int FUN_00151090(int a) { return a; }

int FUN_001510a0(int arg0) {
    igMatrix44f_SetIdentity((float *)arg0);
    return arg0;
}

int *igSmartPointer_igIntList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001510e0(igVisualContext *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&DAT_00530a10[0]);
    arg0->_pExtList = 0;
    arg0->_pExtInstances = 0;
    arg0->_vtable = (int)(&DAT_00525e50[0]);
    arg0->_driverDataMemoryPool = 0;
    arg0->_vertexMemoryPool = 0;
    arg0->_internalMemoryPool = 0;
    arg0->_temporaryMemoryPool = 0;
    arg0->_imageMemoryPool = 0;
    arg0->_textureMemoryPool = 0;
    arg0->_statisticsMemoryPool = 0;
    arg0->_listMemoryPool = 0;
    arg0->_timer = 0;
    igMatrix44f_SetIdentity(&arg0->_viewMatrixHint[0]);
    igMatrix44f_SetIdentity(&arg0->_viewMatrixInverse[0]);
    __construct_array(&arg0->_vertexArray2[0], FUN_00151190, &FUN_00137360, 4, 0x10);
    arg0->_customStates = 0;
    arg0->_customFields = 0;
    return arg0;
}

int *FUN_00151190(int *arg0) {
    *arg0 = 0;
    return arg0;
}

void FUN_001511a0(void)
{
    igMetaObject_RunStaticInit(igPsx2VisualContext_Register);
}

static igMetaObjectCallback g_igPsx2VisualContext_callbackList[] = { igIntList_EnsureRegistered, FUN_001525e0, igIndexArray_EnsureRegistered, FUN_0014c0d0, FUN_001e4820, FUN_00153000, 0 };

CallbackArray *igPsx2VisualContext_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2VisualContext_metaObject,
        igVisualContext_Register,
        FUN_00151230,
        thunk_igPsx2VisualContext_GetMetaObject,
        "igPsx2VisualContext",
        0x618, /* instance size */
        igPsx2VisualContext_GetVTable,
        &igPsx2VisualContext_InitFields,
        0, /* extra callback item */
        g_igPsx2VisualContext_callbackList /* callback list */
    );
}

igMetaObject *FUN_00151230(void) {
    return g_igVisualContext_metaObject;
}

static FieldFactory g_igPsx2VisualContext_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igBoolArrayMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolArrayMetaField_Create,
    (FieldFactory)igEnumArrayMetaField_Create,
    (FieldFactory)igEnumArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumArrayMetaField_Create,
    (FieldFactory)igEnumArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igStructMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntArrayMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
};
static const char *g_igPsx2VisualContext_fieldTable[] = {
    "_current",
    "_iContextOpen",
    "_pTexList",
    "_pClutList",
    "_pTexLoadedList",
    "_currentTex",
    "_iNextFreeTexID",
    "_currentCLUT",
    "_currentTextureFilter",
    "_currentTextureClampU",
    "_currentTextureClampV",
    "_currentTextureProjectiveState",
    "_texPageEnable",
    "_texStage",
    "_texEnable",
    "_texStageFunc",
    "_texCoordSource",
    "_texCoordIndex",
    "_texGenMat",
    "_iCLUT_I8",
    "_iCLUT_A8",
    "_iCLUT_IA16",
    "_iCLUT_IA8",
    "_pCLUT_I8",
    "_pCLUT_A8",
    "_pCLUT_IA16",
    "_pCLUT_IA8",
    "_pBufList",
    "_currentBuf",
    "_clearColor",
    "_clearDepth",
    "_uiClearColor",
    "_uiClearDepth",
    "_clearStencil",
    "_iDisplayWidth",
    "_iDisplayHeight",
    "_iViewportX",
    "_iViewportY",
    "_iViewportW",
    "_iViewportH",
    "_viewportNear",
    "_viewportFar",
    "_pVertexArray",
    "_pIndexArray",
    "_pStripLengthArray",
    "_vMask",
    "_currentColor",
    "_pDLists",
    "_currentDListHandle",
    "_dlistErrors",
    "_projMat",
    "_mvMat",
    "_texMat",
    "_texgenMat",
    "_blendMat0",
    "_blendMat1",
    "_blendMat2",
    "_blendMat3",
    "_invTransBlendMat0",
    "_invTransBlendMat1",
    "_invTransBlendMat2",
    "_invTransBlendMat3",
    "_bVertexBlendingEnabled",
    "_edgeAntiAliasEnable",
    "_alphaEnable",
    "_alphaFunc",
    "_alphaVal",
    "_bBlendingEnabled",
    "_blendSrcMode",
    "_blendDestMode",
    "_blendConst",
    "_clippingEnable",
    "_scissoringExt",
    "_scissorX",
    "_scissorY",
    "_scissorW",
    "_scissorH",
    "_colorMaskR",
    "_colorMaskG",
    "_colorMaskB",
    "_colorMaskA",
    "_shadingMode",
    "_stencilState",
    "_stencilRefVal",
    "_cullFaceEnable",
    "_cullFaceMode",
    "_bDepthWrite",
    "_depthTestEnable",
    "_depthTestFunc",
    "_depthWriteEnable",
    "_stencilFunc",
    "_renderMode",
    "_renderSides",
    "_fogEnable",
    "_fogDensity",
    "_fogMode",
    "_fogColor",
    "_fogNear",
    "_fogFar",
    "_pLightList",
    "_bLightingEnabled",
    "_currentMaterial",
    "_videoMode",
    "_bNormalizeNormalsState",
    "_matrixOptimizationEnable",
    "_statisticState",
    "_scaleToPower2Warning",
    "_mipmapMethodL",
    "_mipmapMethodK",
    "_mipmapL",
    "_mipmapK",
    "_renderlistMode",
    "_needsValidate",
    "_destAlphaTestState",
    "_destAlphaTestFunc",
    "_vertexProgramState",
    "_inverseTransposeCount",
    "_inverseTransposeNeedValidation",
    "_colorScalerState",
    "_colorScalerValue",
    "_textureMatrixState",
    "_colorClampState",
    "_materialSpecularState",
    "_bTextureColorComponent",
    "_bMultiPassNum",
    "_multiPassBlendState",
    "_multiPassBlendSrc",
    "_multiPassBlendDst",
    "_clutOptimization",
    "_maxStageNum",
    "_globalMinU",
    "_globalMinV",
    "_globalMaxU",
    "_globalMaxV",
    "_globalWrapState",
    "_globalWrapMode",
    "_textureStateFilter",
    "_textureMinFilter",
    "_textureMagFilter",
    "_pixelPipelineMode",
    "_clippingType",
    "_clearType",
    "_frameBufferTexture",
    "_alphaBlendingControl",
    "_alphaBlendingCorrection",
    "_ditherMatrix",
};
static igMetaField **g_igPsx2VisualContext_fieldHandles[] = {
    &g_igPsx2VisualContext_currentMetaField,
    &g_igPsx2VisualContext_iContextOpenMetaField,
    &g_igPsx2VisualContext_pTexListMetaField,
    &g_igPsx2VisualContext_pClutListMetaField,
    &g_igPsx2VisualContext_pTexLoadedListMetaField,
    &g_igPsx2VisualContext_currentTexMetaField,
    &g_igPsx2VisualContext_iNextFreeTexIDMetaField,
    &g_igPsx2VisualContext_currentCLUTMetaField,
    &g_igPsx2VisualContext_currentTextureFilterMetaField,
    &g_igPsx2VisualContext_currentTextureClampUMetaField,
    &g_igPsx2VisualContext_currentTextureClampVMetaField,
    &g_igPsx2VisualContext_currentTextureProjectiveStateMetaField,
    &g_igPsx2VisualContext_texPageEnableMetaField,
    &g_igPsx2VisualContext_texStageMetaField,
    &g_igPsx2VisualContext_texEnableMetaField,
    &g_igPsx2VisualContext_texStageFuncMetaField,
    &g_igPsx2VisualContext_texCoordSourceMetaField,
    &g_igPsx2VisualContext_texCoordIndexMetaField,
    &g_igPsx2VisualContext_texGenMatMetaField,
    &g_igPsx2VisualContext_iCLUT_I8MetaField,
    &g_igPsx2VisualContext_iCLUT_A8MetaField,
    &g_igPsx2VisualContext_iCLUT_IA16MetaField,
    &g_igPsx2VisualContext_iCLUT_IA8MetaField,
    &g_igPsx2VisualContext_pCLUT_I8MetaField,
    &g_igPsx2VisualContext_pCLUT_A8MetaField,
    &g_igPsx2VisualContext_pCLUT_IA16MetaField,
    &g_igPsx2VisualContext_pCLUT_IA8MetaField,
    &g_igPsx2VisualContext_pBufListMetaField,
    &g_igPsx2VisualContext_currentBufMetaField,
    &g_igPsx2VisualContext_clearColorMetaField,
    &g_igPsx2VisualContext_clearDepthMetaField,
    &g_igPsx2VisualContext_uiClearColorMetaField,
    &g_igPsx2VisualContext_uiClearDepthMetaField,
    &g_igPsx2VisualContext_clearStencilMetaField,
    &g_igPsx2VisualContext_iDisplayWidthMetaField,
    &g_igPsx2VisualContext_iDisplayHeightMetaField,
    &g_igPsx2VisualContext_iViewportXMetaField,
    &g_igPsx2VisualContext_iViewportYMetaField,
    &g_igPsx2VisualContext_iViewportWMetaField,
    &g_igPsx2VisualContext_iViewportHMetaField,
    &g_igPsx2VisualContext_viewportNearMetaField,
    &g_igPsx2VisualContext_viewportFarMetaField,
    &g_igPsx2VisualContext_pVertexArrayMetaField,
    &g_igPsx2VisualContext_pIndexArrayMetaField,
    &g_igPsx2VisualContext_pStripLengthArrayMetaField,
    &g_igPsx2VisualContext_vMaskMetaField,
    &g_igPsx2VisualContext_currentColorMetaField,
    &g_igPsx2VisualContext_pDListsMetaField,
    &g_igPsx2VisualContext_currentDListHandleMetaField,
    &g_igPsx2VisualContext_dlistErrorsMetaField,
    &g_igPsx2VisualContext_projMatMetaField,
    &g_igPsx2VisualContext_mvMatMetaField,
    &g_igPsx2VisualContext_texMatMetaField,
    &g_igPsx2VisualContext_texgenMatMetaField,
    &g_igPsx2VisualContext_blendMat0MetaField,
    &g_igPsx2VisualContext_blendMat1MetaField,
    &g_igPsx2VisualContext_blendMat2MetaField,
    &g_igPsx2VisualContext_blendMat3MetaField,
    &g_igPsx2VisualContext_invTransBlendMat0MetaField,
    &g_igPsx2VisualContext_invTransBlendMat1MetaField,
    &g_igPsx2VisualContext_invTransBlendMat2MetaField,
    &g_igPsx2VisualContext_invTransBlendMat3MetaField,
    &g_igPsx2VisualContext_bVertexBlendingEnabledMetaField,
    &g_igPsx2VisualContext_edgeAntiAliasEnableMetaField,
    &g_igPsx2VisualContext_alphaEnableMetaField,
    &g_igPsx2VisualContext_alphaFuncMetaField,
    &g_igPsx2VisualContext_alphaValMetaField,
    &g_igPsx2VisualContext_bBlendingEnabledMetaField,
    &g_igPsx2VisualContext_blendSrcModeMetaField,
    &g_igPsx2VisualContext_blendDestModeMetaField,
    &g_igPsx2VisualContext_blendConstMetaField,
    &g_igPsx2VisualContext_clippingEnableMetaField,
    &g_igPsx2VisualContext_scissoringExtMetaField,
    &g_igPsx2VisualContext_scissorXMetaField,
    &g_igPsx2VisualContext_scissorYMetaField,
    &g_igPsx2VisualContext_scissorWMetaField,
    &g_igPsx2VisualContext_scissorHMetaField,
    &g_igPsx2VisualContext_colorMaskRMetaField,
    &g_igPsx2VisualContext_colorMaskGMetaField,
    &g_igPsx2VisualContext_colorMaskBMetaField,
    &g_igPsx2VisualContext_colorMaskAMetaField,
    &g_igPsx2VisualContext_shadingModeMetaField,
    &g_igPsx2VisualContext_stencilStateMetaField,
    &g_igPsx2VisualContext_stencilRefValMetaField,
    &g_igPsx2VisualContext_cullFaceEnableMetaField,
    &g_igPsx2VisualContext_cullFaceModeMetaField,
    &g_igPsx2VisualContext_bDepthWriteMetaField,
    &g_igPsx2VisualContext_depthTestEnableMetaField,
    &g_igPsx2VisualContext_depthTestFuncMetaField,
    &g_igPsx2VisualContext_depthWriteEnableMetaField,
    &g_igPsx2VisualContext_stencilFuncMetaField,
    &g_igPsx2VisualContext_renderModeMetaField,
    &g_igPsx2VisualContext_renderSidesMetaField,
    &g_igPsx2VisualContext_fogEnableMetaField,
    &g_igPsx2VisualContext_fogDensityMetaField,
    &g_igPsx2VisualContext_fogModeMetaField,
    &g_igPsx2VisualContext_fogColorMetaField,
    &g_igPsx2VisualContext_fogNearMetaField,
    &g_igPsx2VisualContext_fogFarMetaField,
    &g_igPsx2VisualContext_pLightListMetaField,
    &g_igPsx2VisualContext_bLightingEnabledMetaField,
    &g_igPsx2VisualContext_currentMaterialMetaField,
    &g_igPsx2VisualContext_videoModeMetaField,
    &g_igPsx2VisualContext_bNormalizeNormalsStateMetaField,
    &g_igPsx2VisualContext_matrixOptimizationEnableMetaField,
    &g_igPsx2VisualContext_statisticStateMetaField,
    &g_igPsx2VisualContext_scaleToPower2WarningMetaField,
    &g_igPsx2VisualContext_mipmapMethodLMetaField,
    &g_igPsx2VisualContext_mipmapMethodKMetaField,
    &g_igPsx2VisualContext_mipmapLMetaField,
    &g_igPsx2VisualContext_mipmapKMetaField,
    &g_igPsx2VisualContext_renderlistModeMetaField,
    &g_igPsx2VisualContext_needsValidateMetaField,
    &g_igPsx2VisualContext_destAlphaTestStateMetaField,
    &g_igPsx2VisualContext_destAlphaTestFuncMetaField,
    &g_igPsx2VisualContext_vertexProgramStateMetaField,
    &g_igPsx2VisualContext_inverseTransposeCountMetaField,
    &g_igPsx2VisualContext_inverseTransposeNeedValidationMetaField,
    &g_igPsx2VisualContext_colorScalerStateMetaField,
    &g_igPsx2VisualContext_colorScalerValueMetaField,
    &g_igPsx2VisualContext_textureMatrixStateMetaField,
    &g_igPsx2VisualContext_colorClampStateMetaField,
    &g_igPsx2VisualContext_materialSpecularStateMetaField,
    &g_igPsx2VisualContext_bTextureColorComponentMetaField,
    &g_igPsx2VisualContext_bMultiPassNumMetaField,
    &g_igPsx2VisualContext_multiPassBlendStateMetaField,
    &g_igPsx2VisualContext_multiPassBlendSrcMetaField,
    &g_igPsx2VisualContext_multiPassBlendDstMetaField,
    &g_igPsx2VisualContext_clutOptimizationMetaField,
    &g_igPsx2VisualContext_maxStageNumMetaField,
    &g_igPsx2VisualContext_globalMinUMetaField,
    &g_igPsx2VisualContext_globalMinVMetaField,
    &g_igPsx2VisualContext_globalMaxUMetaField,
    &g_igPsx2VisualContext_globalMaxVMetaField,
    &g_igPsx2VisualContext_globalWrapStateMetaField,
    &g_igPsx2VisualContext_globalWrapModeMetaField,
    &g_igPsx2VisualContext_textureStateFilterMetaField,
    &g_igPsx2VisualContext_textureMinFilterMetaField,
    &g_igPsx2VisualContext_textureMagFilterMetaField,
    &g_igPsx2VisualContext_pixelPipelineModeMetaField,
    &g_igPsx2VisualContext_clippingTypeMetaField,
    &g_igPsx2VisualContext_clearTypeMetaField,
    &g_igPsx2VisualContext_frameBufferTextureMetaField,
    &g_igPsx2VisualContext_alphaBlendingControlMetaField,
    &g_igPsx2VisualContext_alphaBlendingCorrectionMetaField,
    &g_igPsx2VisualContext_ditherMatrixMetaField,
};
static int g_igPsx2VisualContext_fieldOffsets[] = {
    321,
    322,
    324,
    328,
    332,
    336,
    340,
    344,
    348,
    412,
    476,
    540,
    556,
    560,
    564,
    580,
    644,
    708,
    772,
    836,
    840,
    844,
    848,
    852,
    856,
    860,
    864,
    868,
    872,
    876,
    892,
    896,
    900,
    904,
    908,
    912,
    916,
    920,
    924,
    928,
    932,
    936,
    940,
    944,
    948,
    952,
    956,
    960,
    964,
    968,
    972,
    976,
    980,
    984,
    988,
    992,
    996,
    1000,
    1004,
    1008,
    1012,
    1016,
    1020,
    1021,
    1022,
    1024,
    1028,
    1032,
    1036,
    1100,
    1164,
    1228,
    1232,
    1236,
    1240,
    1244,
    1248,
    1252,
    1253,
    1254,
    1255,
    1256,
    1260,
    1264,
    1268,
    1272,
    1276,
    1277,
    1280,
    1284,
    1288,
    1292,
    1296,
    1300,
    1304,
    1308,
    1312,
    1328,
    1332,
    1336,
    1340,
    1344,
    1348,
    1372,
    1373,
    1376,
    1380,
    1384,
    1388,
    1392,
    1396,
    1400,
    1404,
    1408,
    1412,
    1416,
    1420,
    1424,
    1428,
    1432,
    1448,
    1449,
    1450,
    320,
    1452,
    1456,
    1460,
    1464,
    1468,
    1472,
    1476,
    1480,
    1484,
    1488,
    1492,
    1496,
    1500,
    1504,
    1508,
    1512,
    1516,
    1520,
    1524,
    1536,
    1537,
    1544,
};

static int g_igPsx2VisualContext_alphaFuncDefault = 6;
static int g_igPsx2VisualContext_stencilFuncDefault = 2;
static int g_igPsx2VisualContext_mipmapMethodLDefault = 1;
static int g_igPsx2VisualContext_mipmapMethodKDefault = 1;
static int g_igPsx2VisualContext_destAlphaTestFuncDefault = 1;
static int g_igPsx2VisualContext_colorScalerStateDefault = 1;
static int g_igPsx2VisualContext_clearTypeDefault = 1;

void igPsx2VisualContext_InitFields(void) {
    igMetaField *temp_a0;
    igMetaField *temp_a0_2;
    igMetaField *temp_a0_3;
    igMetaField *temp_s2;
    igMetaField *temp_s2_10;
    igMetaField *temp_s2_11;
    igMetaField *temp_s2_12;
    igMetaField *temp_s2_13;
    igMetaField *temp_s2_14;
    igMetaField *temp_s2_15;
    igMetaField *temp_s2_16;
    igMetaField *temp_s2_17;
    igMetaField *temp_s2_18;
    igMetaField *temp_s2_19;
    igMetaField *temp_s2_20;
    igMetaField *temp_s2_21;
    igMetaField *temp_s2_2;
    igMetaField *temp_s2_3;
    igMetaField *temp_s2_4;
    igMetaField *temp_s2_5;
    igMetaField *temp_s2_6;
    igMetaField *temp_s2_7;
    igMetaField *temp_s2_8;
    igMetaField *temp_s2_9;
    igMetaField *temp_v0;
    igMetaField *temp_v0_10;
    igMetaField *temp_v0_11;
    igMetaField *temp_v0_12;
    igMetaField *temp_v0_13;
    igMetaField *temp_v0_14;
    igMetaField *temp_v0_15;
    igMetaField *temp_v0_16;
    igMetaField *temp_v0_17;
    igMetaField *temp_v0_18;
    igMetaField *temp_v0_19;
    igMetaField *temp_v0_20;
    igMetaField *temp_v0_21;
    igMetaField *temp_v0_22;
    igMetaField *temp_v0_23;
    igMetaField *temp_v0_24;
    igMetaField *temp_v0_25;
    igMetaField *temp_v0_26;
    igMetaField *temp_v0_27;
    igMetaField *temp_v0_28;
    igMetaField *temp_v0_29;
    igMetaField *temp_v0_2;
    igMetaField *temp_v0_30;
    igMetaField *temp_v0_31;
    igMetaField *temp_v0_32;
    igMetaField *temp_v0_33;
    igMetaField *temp_v0_34;
    igMetaField *temp_v0_35;
    igMetaField *temp_v0_36;
    igMetaField *temp_v0_3;
    igMetaField *temp_v0_4;
    igMetaField *temp_v0_5;
    igMetaField *temp_v0_6;
    igMetaField *temp_v0_7;
    igMetaField *temp_v0_8;
    igMetaField *temp_v0_9;
    int sp60[4];
    int sp50[4];
    float sp40[4];
    int fieldStart;
    igMetaObject *meta;

    meta = g_igPsx2VisualContext_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2VisualContext_ctorTable, 0x92);
    temp_s2 = igMetaObject_GetFieldAt(meta, fieldStart + 4);
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 5), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 7), -1);
    temp_v0 = igMetaObject_GetFieldAt(meta, fieldStart + 8);
    ((igIntArrayMetaField *)temp_v0)->_num = 0x10;
    igIntArrayMetaField_SetDefaultValue(temp_v0, -1);
    temp_v0_2 = igMetaObject_GetFieldAt(meta, fieldStart + 9);
    ((igIntArrayMetaField *)temp_v0_2)->_num = 0x10;
    igIntArrayMetaField_SetDefaultValue(temp_v0_2, -1);
    temp_v0_3 = igMetaObject_GetFieldAt(meta, fieldStart + 0xA);
    ((igIntArrayMetaField *)temp_v0_3)->_num = 0x10;
    igIntArrayMetaField_SetDefaultValue(temp_v0_3, -1);
    temp_v0_4 = igMetaObject_GetFieldAt(meta, fieldStart + 0xB);
    ((igBoolArrayMetaField *)temp_v0_4)->_num = 0x10;
    igBoolArrayMetaField_SetDefaultAll((igBoolArrayMetaField *)temp_v0_4, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0xC), 1);
    { igMetaField *q = igMetaObject_GetFieldAt(meta, fieldStart + 0xE); ((igBoolArrayMetaField *)q)->_num = 0x10; }
    temp_v0_5 = igMetaObject_GetFieldAt(meta, fieldStart + 0xF);
    ((igEnumArrayMetaField *)temp_v0_5)->_num = 0x10;
    igEnumArrayMetaField_SetDefault(temp_v0_5, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_5)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_6 = igMetaObject_GetFieldAt(meta, fieldStart + 0x10);
    ((igEnumArrayMetaField *)temp_v0_6)->_num = 0x10;
    igEnumArrayMetaField_SetDefault(temp_v0_6, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_6)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    { igMetaField *q = igMetaObject_GetFieldAt(meta, fieldStart + 0x11); ((igIntArrayMetaField *)q)->_num = 0x10; }
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x13), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x14), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x15), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x16), -1);
    temp_s2_2 = igMetaObject_GetFieldAt(meta, fieldStart + 0x17);
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_3 = igMetaObject_GetFieldAt(meta, fieldStart + 0x18);
    ((igMemoryRefMetaField *)temp_s2_3)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_4 = igMetaObject_GetFieldAt(meta, fieldStart + 0x19);
    ((igMemoryRefMetaField *)temp_s2_4)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_5 = igMetaObject_GetFieldAt(meta, fieldStart + 0x1A);
    ((igMemoryRefMetaField *)temp_s2_5)->_memType = igIntMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x1C), -1);
    temp_a0 = igMetaObject_GetFieldAt(meta, fieldStart + 0x1D);
    sp60[0] = 0;
    sp60[1] = 0;
    sp60[2] = 0;
    sp60[3] = 0;
    igVec4fMetaField_SetDefault(temp_a0, (const float *)sp60);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x1E), 1.0f);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x26), 0x280);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x27), 0x1C0);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x28), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x29), 1.0f);
    temp_s2_6 = igMetaObject_GetFieldAt(meta, fieldStart + 0x2A);
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_00152370();
    temp_s2_7 = igMetaObject_GetFieldAt(meta, fieldStart + 0x2B);
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_0014d7f0();
    temp_s2_8 = igMetaObject_GetFieldAt(meta, fieldStart + 0x2C);
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_0014c030();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x30), -1);
    temp_s2_9 = igMetaObject_GetFieldAt(meta, fieldStart + 0x32);
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = igMetaObject_GetFieldAt(meta, fieldStart + 0x33);
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = igMetaObject_GetFieldAt(meta, fieldStart + 0x34);
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = igMetaObject_GetFieldAt(meta, fieldStart + 0x35);
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = igMetaObject_GetFieldAt(meta, fieldStart + 0x36);
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = igMetaObject_GetFieldAt(meta, fieldStart + 0x37);
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = igMetaObject_GetFieldAt(meta, fieldStart + 0x38);
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = igMetaObject_GetFieldAt(meta, fieldStart + 0x39);
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_16)->_construct = 1;
    temp_s2_17 = igMetaObject_GetFieldAt(meta, fieldStart + 0x3A);
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = igMetaObject_GetFieldAt(meta, fieldStart + 0x3B);
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = igMetaObject_GetFieldAt(meta, fieldStart + 0x3C);
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = igMetaObject_GetFieldAt(meta, fieldStart + 0x3D);
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_20)->_construct = 1;
    temp_v0_7 = igMetaObject_GetFieldAt(meta, fieldStart + 0x41);
    igEnumMetaField_SetDefaultValue(temp_v0_7, g_igPsx2VisualContext_alphaFuncDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_8 = igMetaObject_GetFieldAt(meta, fieldStart + 0x44);
    ((igEnumArrayMetaField *)temp_v0_8)->_num = 0x10;
    igEnumArrayMetaField_SetDefault(temp_v0_8, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_8)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_9 = igMetaObject_GetFieldAt(meta, fieldStart + 0x45);
    ((igEnumArrayMetaField *)temp_v0_9)->_num = 0x10;
    igEnumArrayMetaField_SetDefault(temp_v0_9, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_9)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    { igMetaField *q = igMetaObject_GetFieldAt(meta, fieldStart + 0x46); ((igIntArrayMetaField *)q)->_num = 0x10; }
    temp_s2_21 = igMetaObject_GetFieldAt(meta, fieldStart + 0x48);
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)FUN_00152e80();
    ((igObjectRefMetaField *)temp_s2_21)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x4B), 0x280);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x4C), 0x1C0);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x4D), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x4E), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x4F), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x50), 1);
    temp_v0_10 = igMetaObject_GetFieldAt(meta, fieldStart + 0x51);
    igEnumMetaField_SetDefaultValue(temp_v0_10, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_10)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_11 = igMetaObject_GetFieldAt(meta, fieldStart + 0x52);
    igEnumMetaField_SetDefaultValue(temp_v0_11, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_11)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_12 = igMetaObject_GetFieldAt(meta, fieldStart + 0x55);
    igEnumMetaField_SetDefaultValue(temp_v0_12, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_12)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x56), 1);
    temp_v0_13 = igMetaObject_GetFieldAt(meta, fieldStart + 0x58);
    igEnumMetaField_SetDefaultValue(temp_v0_13, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_13)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_14 = igMetaObject_GetFieldAt(meta, fieldStart + 0x5A);
    igEnumMetaField_SetDefaultValue(temp_v0_14, g_igPsx2VisualContext_stencilFuncDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_14)->_getMetaEnumFunction = FUN_00149500;
    temp_v0_15 = igMetaObject_GetFieldAt(meta, fieldStart + 0x5B);
    igEnumMetaField_SetDefaultValue(temp_v0_15, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_15)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_16 = igMetaObject_GetFieldAt(meta, fieldStart + 0x5C);
    igEnumMetaField_SetDefaultValue(temp_v0_16, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_16)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_17 = igMetaObject_GetFieldAt(meta, fieldStart + 0x5F);
    igEnumMetaField_SetDefaultValue(temp_v0_17, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_17)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_a0_2 = igMetaObject_GetFieldAt(meta, fieldStart + 0x60);
    sp50[0] = 0;
    sp50[1] = 0;
    sp50[2] = 0;
    sp50[3] = 0;
    igVec4fMetaField_SetDefault(temp_a0_2, (const float *)sp50);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x61), 1.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 0x62), 10000.0f);
    { igMetaField *q = igMetaObject_GetFieldAt(meta, fieldStart + 0x66); ((igMetaField *)q)->_size = 0x18; }
    temp_v0_18 = igMetaObject_GetFieldAt(meta, fieldStart + 0x69);
    igEnumMetaField_SetDefaultValue(temp_v0_18, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_18)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x6A), 1);
    temp_v0_19 = igMetaObject_GetFieldAt(meta, fieldStart + 0x6B);
    igEnumMetaField_SetDefaultValue(temp_v0_19, g_igPsx2VisualContext_mipmapMethodLDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_19)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_20 = igMetaObject_GetFieldAt(meta, fieldStart + 0x6C);
    igEnumMetaField_SetDefaultValue(temp_v0_20, g_igPsx2VisualContext_mipmapMethodKDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_20)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_21 = igMetaObject_GetFieldAt(meta, fieldStart + 0x6F);
    igEnumMetaField_SetDefaultValue(temp_v0_21, 0);
    *(int (**)())&((igEnumMetaField *)temp_v0_21)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_22 = igMetaObject_GetFieldAt(meta, fieldStart + 0x72);
    igEnumMetaField_SetDefaultValue(temp_v0_22, g_igPsx2VisualContext_destAlphaTestFuncDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_22)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_23 = igMetaObject_GetFieldAt(meta, fieldStart + 0x76);
    igEnumMetaField_SetDefaultValue(temp_v0_23, g_igPsx2VisualContext_colorScalerStateDefault);
    *(int (**)())&((igEnumMetaField *)temp_v0_23)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_a0_3 = igMetaObject_GetFieldAt(meta, fieldStart + 0x77);
    sp40[3] = 1.0f;
    sp40[0] = 0.501960754f;
    sp40[1] = 0.501960754f;
    sp40[2] = 0.501960754f;
    igVec4fMetaField_SetDefault(temp_a0_3, sp40);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x79), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 0x7A), 1);
    temp_v0_24 = igMetaObject_GetFieldAt(meta, fieldStart + 0x7B);
    igBoolMetaField_SetDefaultValue(temp_v0_24, 1);
    ((igMetaField *)temp_v0_24)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x7C))->_persistent = 0;
    temp_v0_25 = igMetaObject_GetFieldAt(meta, fieldStart + 0x7D);
    igBoolMetaField_SetDefaultValue(temp_v0_25, 1);
    ((igMetaField *)temp_v0_25)->_persistent = 0;
    temp_v0_26 = igMetaObject_GetFieldAt(meta, fieldStart + 0x7E);
    igEnumMetaField_SetDefaultValue(temp_v0_26, 0);
    ((igMetaField *)temp_v0_26)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_26)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_27 = igMetaObject_GetFieldAt(meta, fieldStart + 0x7F);
    igEnumMetaField_SetDefaultValue(temp_v0_27, 0);
    ((igMetaField *)temp_v0_27)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_27)->_getMetaEnumFunction = (int (*)())igMetaEnum_GetEmpty;
    temp_v0_28 = igMetaObject_GetFieldAt(meta, fieldStart + 0x80);
    igBoolMetaField_SetDefaultValue(temp_v0_28, 1);
    ((igMetaField *)temp_v0_28)->_persistent = 0;
    temp_v0_29 = igMetaObject_GetFieldAt(meta, fieldStart + 0x81);
    igIntMetaField_SetDefault(temp_v0_29, 0x10);
    ((igMetaField *)temp_v0_29)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x82))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x83))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x84))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x85))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x86))->_persistent = 0;
    temp_v0_30 = igMetaObject_GetFieldAt(meta, fieldStart + 0x87);
    igEnumMetaField_SetDefaultValue(temp_v0_30, 0);
    ((igMetaField *)temp_v0_30)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_30)->_getMetaEnumFunction = FUN_00149920;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x88))->_persistent = 0;
    temp_v0_31 = igMetaObject_GetFieldAt(meta, fieldStart + 0x89);
    igEnumMetaField_SetDefaultValue(temp_v0_31, 0);
    ((igMetaField *)temp_v0_31)->_persistent = 0;
    *(igMetaEnum *(**)())&((igEnumMetaField *)temp_v0_31)->_getMetaEnumFunction = IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    temp_v0_32 = igMetaObject_GetFieldAt(meta, fieldStart + 0x8A);
    igEnumMetaField_SetDefaultValue(temp_v0_32, 0);
    ((igMetaField *)temp_v0_32)->_persistent = 0;
    *(igMetaEnum *(**)())&((igEnumMetaField *)temp_v0_32)->_getMetaEnumFunction = IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    temp_v0_33 = igMetaObject_GetFieldAt(meta, fieldStart + 0x8B);
    igEnumMetaField_SetDefaultValue(temp_v0_33, 0);
    ((igMetaField *)temp_v0_33)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_33)->_getMetaEnumFunction = FUN_00149800;
    temp_v0_34 = igMetaObject_GetFieldAt(meta, fieldStart + 0x8C);
    igEnumMetaField_SetDefaultValue(temp_v0_34, 0);
    ((igMetaField *)temp_v0_34)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_34)->_getMetaEnumFunction = FUN_00150710;
    temp_v0_35 = igMetaObject_GetFieldAt(meta, fieldStart + 0x8D);
    igEnumMetaField_SetDefaultValue(temp_v0_35, g_igPsx2VisualContext_clearTypeDefault);
    ((igMetaField *)temp_v0_35)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_35)->_getMetaEnumFunction = FUN_001506b0;
    temp_v0_36 = igMetaObject_GetFieldAt(meta, fieldStart + 0x8E);
    ((igUnsignedIntArrayMetaField *)temp_v0_36)->_num = 3;
    ((igMetaField *)temp_v0_36)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x8F))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x90))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, fieldStart + 0x91))->_persistent = 0;
    igMetaObject_NameFields(meta, g_igPsx2VisualContext_fieldTable, g_igPsx2VisualContext_fieldHandles, g_igPsx2VisualContext_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPsx2VisualContext_metaObject) + 64) = (int)(&thunk_igVisualContext_GetMetaObject);
}

