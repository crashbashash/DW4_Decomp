static inline void releaseObjectRef(igObjectSlotView *o)
{
    IG_OBJECT_RELEASE(o);
}

namespace Gap {
namespace Gfx {

void igVisualContext::constructFields(int flag)
{
    igMemoryPool *p;
    igMemoryPool *pool;

    igObject::constructFields(flag);

    p = _defaultDriverDataMemoryPool;
    if (p != 0) {
        _driverDataMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDriverData);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDriverData);
            _driverDataMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _driverDataMemoryPool = p;
        }
    }
    p = _defaultVertexMemoryPool;
    if (p != 0) {
        _vertexMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleVertex);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleVertex);
            _vertexMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _vertexMemoryPool = p;
        }
    }
    p = _defaultInternalMemoryPool;
    if (p != 0) {
        _internalMemoryPool = (igMemoryPool *)p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        _internalMemoryPool = p;
    }
    p = _defaultTemporaryMemoryPool;
    if (p != 0) {
        _temporaryMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
            _temporaryMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _temporaryMemoryPool = p;
        }
    }
    p = _defaultImageMemoryPool;
    if (p != 0) {
        _imageMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleImage);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleImage);
            _imageMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _imageMemoryPool = p;
        }
    }
    p = _defaultTextureMemoryPool;
    if (p != 0) {
        _textureMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTexture);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTexture);
            _textureMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _textureMemoryPool = p;
        }
    }
    p = _defaultStatisticsMemoryPool;
    if (p != 0) {
        _statisticsMemoryPool = (igMemoryPool *)p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        _statisticsMemoryPool = p;
    }
    p = _defaultListMemoryPool;
    if (p != 0) {
        _listMemoryPool = p;
    } else {
        p = (igMemoryPool *)getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList);
        if (p != (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igMemoryPool *)getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList);
            _listMemoryPool = p;
        } else {
            p = (igMemoryPool *)getMemoryPool();
            _listMemoryPool = p;
        }
    }

    _timer = igTimer::_instantiateFromPool((igMemoryPoolView *)getInternalMemoryPool());
    ((igTimerDispatchView *)_timer.p)->Restart();

    pool = getListMemoryPool();
    ::igObject::release(_customStates.p);
    _customStates.p = (igCustomStateCollectionList *)igCustomStateCollectionList_Create((int)pool);
    pool = getListMemoryPool();
    ::igObject::release(_customFields.p);
    _customFields.p = (igCustomStateFieldList *)igCustomStateFieldList_Create((int)pool);
}

void igVisualContext::userConstruct(int flag)
{
    bool showFrameRate;
    bool commandLineFrame;
    void *properties;
    igTDataList<igVisualContext *> *list;
    int count;

    igObject::userConstruct(flag);
    if (DAT_00560758 == 0) {
        DAT_00560758 = (igTDataList<igVisualContext *> *)igVisualContextList_Create((int)(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    }
    _contextIndex = DAT_00560758->_count;
    list = DAT_00560758;
    count = list->count();
    if (count < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, 4);
    }
    list->_data[count] = this;
    properties = ((PropertyRoot *)g_objectSystem)->properties;
    showFrameRate = _showFrameRate;
    commandLineFrame = _commandLineFrameRate;
    igGetRegistryValue_Bool((::igRegistry *)properties, 4, "showFrameRate", (unsigned char *)&showFrameRate, showFrameRate, 1);
    igGetRegistryValue_Bool((::igRegistry *)properties, 4, "commandLineFrameRate", (unsigned char *)&commandLineFrame, commandLineFrame, 1);
    _showFrameRate = showFrameRate;
    _commandLineFrameRate = commandLineFrame;
}

void igVisualContext::userDestruct()
{
    int i;
    igTDataList<igVisualContext *> *list;

    _timer->release();
    i = DAT_00560758->find(this);
    if (i >= 0) {
        List_RemoveWordAt((::igDataList *)DAT_00560758, i);
    }
    list = DAT_00560758;
    if (list->_count == 0) {
        list->release();
        DAT_00560758 = 0;
    }
    igObject::releaseDefaults();
}

void igVisualContext::reset()
{

}

igMemoryPool *igVisualContext::getDriverDataMemoryPool() const
{
    return _driverDataMemoryPool;
}

igMemoryPool *igVisualContext::getVertexMemoryPool() const
{
    return _vertexMemoryPool;
}

igMemoryPool *igVisualContext::getInternalMemoryPool() const
{
    return _internalMemoryPool;
}

igMemoryPool *igVisualContext::getImageMemoryPool() const
{
    return _imageMemoryPool;
}

igMemoryPool *igVisualContext::getStatisticsMemoryPool() const
{
    return _statisticsMemoryPool;
}

igMemoryPool *igVisualContext::getListMemoryPool() const
{
    return _listMemoryPool;
}

void igVisualContext::setImageMemoryPool(igMemoryPool *pool)
{
    _defaultImageMemoryPool = pool;
}

void igVisualContext::setBlendingMatrices(const unsigned int matrixCount, const igMatrix44f *matrixArray)
{
    int zero[3];
    igMatrix44f *inverse;
    unsigned int i;

    _blendMatricesCount = matrixCount;
    _blendMatrices = matrixArray;
    if (_inverseTransposeCount < matrixCount) {
        if (_inverseTranspose != 0) {
            ((igMemoryPoolView *)getDriverDataMemoryPool())->Free(_inverseTranspose);
            _inverseTranspose = 0;
        }
        _inverseTranspose = (igMatrix44f *)((igMemoryPoolView *)getDriverDataMemoryPool())->AllocateAligned(matrixCount << 6, 0x10);
        _inverseTransposeCount = matrixCount;
    }
    inverse = _inverseTranspose;
    for (i = 0; i < matrixCount; i++) {
        igMatrix44f_Invert((float *)inverse, (const float *)(_blendMatrices + i));
        zero[0] = 0;
        zero[1] = 0;
        zero[2] = 0;
        igMatrix44f_SetTranslation((float *)inverse, (float *)zero);
        FUN_001903d0((float *)inverse);
        inverse += 1;
    }
    _blendIndex = _blendIndex + 1;
}

int igVisualContext::getBlendingMatricesCount()
{
    return _blendMatricesCount;
}
}
}

static inline Obj_165e50 *getAlloc(void *o) {
    Obj_165e50 *a = (Obj_165e50 *)((Gap::Core::igObject *)o)->getMemoryPool();
    if (g_useOwnerAllocator != 0) return a;
    return (Obj_165e50 *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
}

namespace Gap {
namespace Gfx {

igVertexArray *igVisualContext::softwareBlendVertex(const igVertexArray *vertexArray)
{
    /* matching construct: random sweep — the order of the local declarations */
    int k; int nb; igVertexArray *dst; igMatrix44f *buf; const igVec3f *q; int m; int i; int n; int j; igVec3f acc, t, nacc, nt;
    if (vertexArray != 0) {
        dst = igVertexArray::_instantiateFromPool((igMemoryPoolView *)getVertexMemoryPool());
        igVertexFormat flags(vertexArray->getVertexFormat());
        flags.setBlendWeightCount(0);
        flags.setBlendIndexCount(0);
        n = vertexArray->getCount();
        dst->configure(flags, n, vertexArray->getUsageFlags(), this);
        if (flags.hasVertexColors()) {
            for (i = 0; i < n; i++) {
                dst->setColor(i, vertexArray->getColor(i));
            }
        }
        for (j = 0; j < flags.getTextureCoordCount(); j++) {
            for (i = 0; i < n; i++) {
                dst->setTextureCoord(j, i, *vertexArray->getTextureCoord(j, i));
            }
        }
        nb = vertexArray->getVertexFormat().getBlendWeightCount();
        for (i = 0; i < n; i++) {
            const igVec3f *p = vertexArray->getPosition(i);
            acc = *p;
            for (j = 0; j < nb; j++) {
                float w = vertexArray->getWeight(j, i);
                if (!(w <= 0.0f)) {
                    Vec3f_TransformProjective((float *)&t, (const float *)p, (const float *)(_blendMatrices + vertexArray->getBlendMatrixIndex(j, i)));
                    t -= *p;
                    t *= w;
                    acc += t;
                }
            }
            dst->setPosition(i, acc);
        }
        if (flags.hasNormals()) {
            buf = (igMatrix44f *)poolOf(this, kIGMemoryPoolHandleTemporary)->Allocate(_blendMatricesCount << 6);
            for (i = 0; i < _blendMatricesCount; i++) {
                igMatrix44f *b = buf + i;
                igMatrix44f_Invert((float *)b, (const float *)(_blendMatrices + i));
                FUN_001903d0((float *)b);
            }
            for (k = 0; k < n; k++) {
                q = vertexArray->getNormal(k);
                nacc = *q;
                for (m = 0; m < nb; m++) {
                    float w = vertexArray->getWeight(m, k);
                    if (!(w <= 0.0f)) {
                        Vec3f_TransformDirection((float *)&nt, (const float *)q, (const float *)(buf + vertexArray->getBlendMatrixIndex(m, k)));
                        nt -= *q;
                        nt *= w;
                        nacc += nt;
                    }
                }
                nacc.normalize();
                dst->setNormal(k, nacc);
            }
            Memory_FreeBuffer(buf);
        }
        return dst;
    }
    return 0;
}

void igVisualContext::resetToDefault(int which)
{
    void *settings = ((SystemConfig *)g_objectSystem)->settings;
    int shadingMode;
    int cullMode;
    int fillMode;
    bool cullEnable;
    int i, n;
    igVec4f clear, white, diffuse, emissive, ambient, specular, fogColor, clearColor;

    if (which & 1) {
        setLightingState(false);
        setNormalizeNormalsState(false);
        clear.set(0.0f, 0.0f, 0.0f, 0.0f);
        setSceneAmbient(clear);
    }
    if (which & 2) {
        white.set(1.0f, 1.0f, 1.0f, 1.0f);
        setColor(white);
        setMaterialShininess(0.0f);
        diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
        setMaterialDiffuse(diffuse);
        emissive.set(0.0f, 0.0f, 0.0f, 1.0f);
        setMaterialEmissive(emissive);
        ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
        setMaterialAmbient(ambient);
        specular.set(0.0f, 0.0f, 0.0f, 1.0f);
        setMaterialSpecular(specular);
        setMaterialSpecularState(true);
        setMaterialColorMode(0);
    }
    if (which & 4) {
        n = getCapability(IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES);
        if (n > 512) n = 1;
        if (n > 16) n = 16;
        n = (n <= 0) ? 1 : n; /* ternary form: the if form schedules the loop init into the bgtz delay slot */
        i = 0;
        while (i < n) {
            setTextureStageState(i, false);
            setTextureStageFunc(i, 1);
            setTextureStageCoordSource(i, IG_GFX_TEXTURE_COORD_SOURCE_VERTEX, 0);
            setTextureMatrixState(i, false);
            i++;
        }
    }
    if (which & 8) {
        setBlendingState(false);
        setBlendingSourceDestination(IG_GFX_BLENDING_FUNCTION_SOURCE_ALPHA, IG_GFX_BLENDING_FUNCTION_ONE_MINUS_SOURCE_ALPHA);
    }
    if (which & 0x80) {
        setStencilState(false);
        setStencilRefVal(0);
        setStencilFunc(IG_GFX_STENCIL_FUNCTION_ALWAYS);
        setStencilReadMask(-1);
        setStencilWriteMask(-1);
        setStencilOps(IG_GFX_STENCIL_OPERATION_KEEP, IG_GFX_STENCIL_OPERATION_KEEP, IG_GFX_STENCIL_OPERATION_KEEP);
    }
    if (which & 0x10) {
        setFogState(false);
        setFogDensity(0.0f);
        setFogMode(IG_GFX_FOG_MODE_EXP2);
        fogColor.set(0.0f, 0.0f, 0.0f, 1.0f);
        setFogColor(fogColor);
        setFogNear(1.0f);
        setFogFar(1000.0f);
    }
    if (which & 0x20) {
        igGetRegistryValue_Int((::igRegistry *)settings, 4, "shadingMode", &shadingMode, 1, 1);
        setVertexMask(igVertexComponentFilter());
        clearColor.set(0.0f, 0.0f, 0.0f, 1.0f);
        setClearColor(clearColor);
        setClearDepth(1.0f);
        setClearStencil(0);
        setVertexBlendingState(false);
        setViewportClippingState(true);
        setColorMask(true, true, true, true);
        setShadingMode((IG_GFX_SHADING_MODE)shadingMode);
    }
    if (which & 0x40) {
        igGetRegistryValue_Bool((::igRegistry *)settings, 4, "cullEnable", (unsigned char *)&cullEnable, 0, 1);
        igGetRegistryValue_Int((::igRegistry *)settings, 4, "cullMode", &cullMode, 0, 1);
        igGetRegistryValue_Int((::igRegistry *)settings, 4, "fillMode", &fillMode, 0, 1);
        setAlphaTestState(false);
        setAlphaFunc(IG_GFX_ALPHA_FUNCTION_GEQUAL);
        setAlphaRefValue(0.0f);
        setCullFaceState(cullEnable);
        setCullFaceMode((IG_GFX_CULL_FACE_MODE)cullMode);
        setDepthTestState(true);
        setDepthTestFunction(3);
        setDepthWriteState(true);
        setRenderMode((IG_GFX_RENDER_MODE)fillMode);
        setDitherState(false);
        setScissorType(IG_GFX_SCISSOR_TYPE_EQUALS_VIEWPORT);
        setVertexArray(0, 0);
        for (i = 1; i < 16; i++)
            setVertexArray(0, i);
    }
}

void igVisualContext::setDitherState(bool enable)
{
    _ditherState = enable;
}

void igVisualContext::updateFrameRateDisplay(float frameTime, float drawTime)
{
    float temp_f4;
    double temp_s2;
    double temp_s1;

    DAT_005607a0[0] += frameTime;
    DAT_005607a8[0] += drawTime;
    DAT_005607b0[0] += 1;
    if (frameTime < DAT_0048a470[0]) {
        DAT_0048a470[0] = frameTime;
    }
    if (!(frameTime <= DAT_00560838[0])) {
        DAT_00560838[0] = frameTime;
    }
    if (!(DAT_005607a0[0] < 1.5f)) {
        temp_f4 = (float) DAT_005607b0[0];
        DAT_005607b8[0] = temp_f4 / DAT_005607a0[0];
        DAT_005607c0[0] = (1000.0f * DAT_005607a8[0]) / temp_f4;
        temp_s2 = fptodp(1.0f / DAT_00560838[0]);
        temp_s1 = fptodp(1.0f / DAT_0048a470[0]);
        sprintf((char *)g_gsEventCount, "[%2.0f:%2.0f] %3.0f fps/f", temp_s2, temp_s1, fptodp(DAT_005607b8[0]));
        DAT_005607a0[0] = 0.0f;
        DAT_005607a8[0] = 0.0f;
        DAT_005607b0[0] = 0;
        DAT_00560838[0] = 0.0f;
        DAT_0048a470[0] = (float) 0xF4240;
    }
    if (_commandLineFrameRate) {
        if (DAT_005607b0[0] == 0) {
            igReport_Printf("FRAME RATE:       %s\n", (char *)g_gsEventCount);
            igReport_Flush();
        }
    } else {
        outputText(0, 0, (const char *)g_gsEventCount);
    }
}

void igVisualContext::outputText(int x, int y, const char *str)
{

}

void igVisualContext::updatePrimitiveCountDisplay(float frameTime)
{

}

void igVisualContext::drawNonIndexed(IG_GFX_DRAW primType, int numPrimitives, int vertexOffset)
{
    igIndexArray *indexArray;

    indexArray = getIndexArray();
    if (indexArray != 0) {
        setIndexArray(0);
    }
    draw(primType, numPrimitives, vertexOffset);
    if (indexArray != 0) {
        setIndexArray(indexArray);
    }
}
}
}

igVisualContext *igVisualContext_FindFirst(void) {
    Gap::Gfx::igVisualContext *found;
    int i;

    found = 0;
    if (DAT_00560758 != 0) {
        for (i = 0; i < DAT_00560758->_count; i++) {
            if (DAT_00560758->_data[i]->isOfType(Gap::Gfx::igVisualContext::getClassMeta()) != 0) {
                found = DAT_00560758->_data[i];
                break;
            }
        }
    }
    return (igVisualContext *)found;
}

namespace Gap {
namespace Gfx {

void igVisualContext::loadDefaultDriverDatabase()
{
    int count;
    void *registry = ((ShaderSetup *)g_objectSystem)->registry;
    void *builder = ((ShaderSetup *)g_objectSystem)->builder;
    igSmartPointer<igIntList> list((igIntList *)igContextList_Create((int)getInternalMemoryPool()));
    bool found = false;

    ((Gap::Core::igRegistry *)registry)->getValue(4, "ignoreDriverDatabase", *(unsigned char *)&found, 0, 1);
    if (found) return;
    igIntList *l = list;
    count = l->_count;
    if (count < l->_capacity) {
        l->_count = l->getCount() + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(count + 1, 4);
    }
    ((int *)l->_data)[count] = (int)this;
    igDriverDatabase_GatherProperties(builder, (igTDataList<Gap::Gfx::igVisualContext *> *)(igIntList *)list);
    if (igRegistry_IsLoadingEnabled() != 0) {
        if (igDriverDatabase_Load((igDriverDatabase *)builder, (const char *)"", (const char *)"") != 0) igDriverDatabase_ApplyToRegistry((igDriverDatabase *)builder, (int)registry, 4, 0);
    }
    FUN_002daab0((igDriverDatabase *)builder, (int)registry, 4, 0);
}

void igVisualContext::setVertexPipelineMode(int mode)
{

}

int igVisualContext::getVertexPipelineMode() const
{
    return 0;
}

void igVisualContext::setPixelPipelineMode(IG_GFX_PIXEL_PIPELINE_MODE mode)
{

}

IG_GFX_PIXEL_PIPELINE_MODE igVisualContext::getPixelPipelineMode() const
{
    return IG_GFX_PIXEL_PIPELINE_MODE_DEFAULT;
}

/* Empty slot: returns 0 without touching the receiver. */
int igVisualContext::getLastError()
{
    return 0;
}
}
}

igSmartPointer<igObject> FUN_00167130(SlotObject_166fe0 *object) {
    return object->f12;
}

namespace Gap {
namespace Gfx {

igVertexArray2 *igVisualContext::getVertexArray(unsigned int stream)
{
    return _vertexArray2[stream];
}

void igVisualContext::setViewMatrixHint(const igMatrix44f &mat)
{
    igMatrix44f_Copy(_viewMatrixHint.m, mat.m);
    _viewMatrixDirty = true;
}

void igVisualContext::getViewMatrixHint(igMatrix44f &mat) const
{
    igMatrix44f_Copy(mat.m, _viewMatrixHint.m);
}

void igVisualContext::getViewMatrixInverse(igMatrix44f &mat)
{
    if (_viewMatrixDirty) {
        igMatrix44f_Invert(_viewMatrixInverse.m, _viewMatrixHint.m);
        _viewMatrixDirty = false;
    }
    igMatrix44f_Copy(mat.m, _viewMatrixInverse.m);
}
}
}

int Gap__Gfx__igVisualContextCapabilityManager__vfunc_23(igVisualContextCapabilityManager *self) {
    int result;
    void **visualContext;

    visualContext = (void **)(self->_visualContext);
    result = 0;
    if (visualContext != 0) {
        result = ((VisualContextQuerySlot *)(visualContext))->Query();
    }
    return result;
}

