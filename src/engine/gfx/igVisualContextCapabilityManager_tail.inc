static inline void releaseObjectRef(igObjectSlotView *o)
{
    IG_OBJECT_RELEASE(o);
}

void igVisualContext_constructFields(igVisualContextFieldsView *self, int flags)
{
    igObjectSlotView *p;
    int pool;

    Gap__Core__igObject__constructFields((igObject *)self, flags);

    p = g_igVisualContext_defaultDriverDataMemoryPool[0];
    if (p != 0) {
        self->driverDataMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDriverData);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDriverData);
            self->driverDataMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->driverDataMemoryPool = p;
        }
    }
    p = g_igVisualContext_defaultVertexMemoryPool[0];
    if (p != 0) {
        self->vertexMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleVertex);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleVertex);
            self->vertexMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->vertexMemoryPool = p;
        }
    }
    p = g_igVisualContext_defaultInternalMemoryPool[0];
    if (p != 0) {
        self->internalMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        self->internalMemoryPool = p;
    }
    p = g_igVisualContext_defaultTemporaryMemoryPool[0];
    if (p != 0) {
        self->temporaryMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
            self->temporaryMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->temporaryMemoryPool = p;
        }
    }
    p = g_igVisualContext_defaultImageMemoryPool[0];
    if (p != 0) {
        self->imageMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleImage);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleImage);
            self->imageMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->imageMemoryPool = p;
        }
    }
    p = g_igVisualContext_defaultTextureMemoryPool[0];
    if (p != 0) {
        self->textureMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTexture);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTexture);
            self->textureMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->textureMemoryPool = p;
        }
    }
    p = g_igVisualContext_defaultStatisticsMemoryPool[0];
    if (p != 0) {
        self->statisticsMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        self->statisticsMemoryPool = p;
    }
    p = g_igVisualContext_defaultListMemoryPool[0];
    if (p != 0) {
        self->listMemoryPool = p;
    } else {
        p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
        p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList);
        if (p != (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault)) {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            p = g_useOwnerAllocator != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList);
            self->listMemoryPool = p;
        } else {
            p = (igObjectSlotView *)((Gap::Core::igObject *)self)->getMemoryPool();
            self->listMemoryPool = p;
        }
    }

    self->timer = (igObjectSlotView *)Gap::Core::igTimer::_instantiateFromPool((igMemoryPoolView *)igVisualContext_GetInternalMemoryPool((int *)self));
    ((igTimerDispatchView *)self->timer.p)->Restart();

    pool = igVisualContext_GetListMemoryPool((int *)self);
    releaseObjectRef(self->customStates);
    self->customStates = (igObjectSlotView *)igCustomStateCollectionList_Create(pool);
    pool = igVisualContext_GetListMemoryPool((int *)self);
    releaseObjectRef(self->customFields);
    self->customFields = (igObjectSlotView *)igCustomStateFieldList_Create(pool);
}

void FUN_00165a80(VisualContextCapabilityManager *self) {
    unsigned char showFrameRate;
    unsigned char commandLineFrame;
    void *properties;
    ManagerList *list;
    int count;

    Gap__Core__igObject__userConstruct((igObject *)self);
    if (DAT_00560758 == 0) {
        DAT_00560758 = (igTDataList<VisualContextCapabilityManager *> *)igVisualContextList_Create((int)(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    }
    self->index = DAT_00560758->_count;
    list = DAT_00560758;
    count = list->count();
    if (count < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, 4);
    }
    list->_data[count] = self;
    properties = ((PropertyRoot *)g_objectSystem)->properties;
    showFrameRate = self->showFrameRate;
    commandLineFrame = self->commandLineFrame;
    igGetRegistryValue_Bool((igRegistry *)properties, 4, "showFrameRate", &showFrameRate, showFrameRate, 1);
    igGetRegistryValue_Bool((igRegistry *)properties, 4, "commandLineFrameRate", &commandLineFrame, commandLineFrame, 1);
    self->showFrameRate = showFrameRate;
    self->commandLineFrame = commandLineFrame;
}

void FUN_00165bb0(char *arg0) {
    int i;
    RefObj *o;
    RefObj *l;
    o = *(RefObj **)(arg0 + 56);
    --o->references;
    if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)o);
    }
    K key(arg0);
    i = Finder::Find(((RefObj *)DAT_00560758), key);
    if (i >= 0) {
        List_RemoveWordAt((igDataList *)(((RefObj *)DAT_00560758)), i);
    }
    l = ((RefObj *)DAT_00560758);
    if (l->count == 0) {
        --l->references;
        if (((unsigned long long)((long long)l->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)l);
        }
        DAT_00560758 = 0;
    }
    igObject_ReleaseDefaults((igObject *)arg0);
}

void igVisualContext_Reset(void *arg0)
{
}

int igVisualContext_GetDriverDataMemoryPool(int *p)
{
    return *(int *)((char *)p + 24);
}

int igVisualContext_GetVertexMemoryPool(int *p)
{
    return *(int *)((char *)p + 28);
}

int igVisualContext_GetInternalMemoryPool(int *p)
{
    return *(int *)((char *)p + 32);
}

int igVisualContext_GetImageMemoryPool(int *p)
{
    return *(int *)((char *)p + 40);
}

int igVisualContext_GetStatisticsMemoryPool(int *p)
{
    return *(int *)((char *)p + 48);
}

int igVisualContext_GetListMemoryPool(int *p)
{
    return *(int *)((char *)p + 52);
}

void igVisualContext_SetImageMemoryPool(int pool) {
    g_igVisualContext_defaultImageMemoryPool[0] = (igObjectSlotView *)pool;
}

void igVisualContext_SetBlendingMatrices(O_165d30 *arg0, unsigned int arg1, int arg2) {
    int v[3];
    void *s0;
    int off;
    int src;
    char *s1;
    unsigned int i;

    arg0->f72 = arg1;
    arg0->f84 = arg2;
    if (arg0->f88 < arg1) {
        s0 = arg0->f80;
        if (s0 != 0) {
            ((V1 *)igVisualContext_GetDriverDataMemoryPool((int *)arg0))->v264(s0);
            arg0->f80 = 0;
        }
        arg0->f80 = ((V2_165d30 *)igVisualContext_GetDriverDataMemoryPool((int *)arg0))->v220(arg1 << 6, 0x10);
        arg0->f88 = arg1;
    }
    s1 = (char *)arg0->f80;
    for (i = 0; i < arg1; i++) {
        off = i << 6;
        igMatrix44f_Invert((float *)s1, (const float *)(arg0->f84 + off));
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
        igMatrix44f_SetTranslation((float *)s1, (float *)v);
        FUN_001903d0((float *)s1);
        s1 += 0x40;
    }
    arg0->f76 = arg0->f76 + 1;
}

int igVisualContext_GetBlendingMatricesCount(igVisualContext *self) {
    return self->_blendMatricesCount;
}

static inline Obj_165e50 *getAlloc(void *o) {
    Obj_165e50 *a = (Obj_165e50 *)((Gap::Core::igObject *)o)->getMemoryPool();
    if (g_useOwnerAllocator != 0) return a;
    return (Obj_165e50 *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
}

void *FUN_00165e50(Self *self, Obj_165e50 *src) {
    /* matching construct: random sweep — the order of the local declarations */
    int k; int nb; Obj_165e50 *dst; Mat *buf; V_165e50 *q; int m; int i; int n; int j; Fl flags; V_165e50 acc, t, nacc, nt; Obj_165e50 *al;
    if (src != 0) {
    dst = (Obj_165e50 *)Gap::Gfx::igVertexArray::_instantiateFromPool((igMemoryPoolView *)igVisualContext_GetVertexMemoryPool((int *)self));
    flags = *src->v100();
    flags.b &= ~0xF0;
    flags.b &= ~0xF00;
    n = src->count;
    dst->v96((int *)&flags, n, src->count2, self);
    if (flags.b & 4) {
        for (i = 0; i < n; i++) {
            dst->v164(i, src->v172(i));
        }
    }
    for (j = 0; j < (int)(((unsigned)(flags.b & 0xF0000) >> 16) & 0xFF); j++) {
        for (i = 0; i < n; i++) {
            dst->v200(j, i, src->v208(j, i));
        }
    }
    nb = ((unsigned)(src->v100()->b & 0xF0) >> 4) & 0xFF;
    for (i = 0; i < n; i++) {
        V_165e50 *p = src->v124(i);
        acc = *p;
        for (j = 0; j < nb; j++) {
            float w = src->v184(j, i);
            if (!(w <= 0.0f)) {
                Vec3f_TransformProjective((float *)&t, (const float *)p, (const float *)(self->mats + (src->v196(j, i))));
                t -= *p;
                t *= w;
                acc += t;
            }
        }
        dst->v116(i, &acc);
    }
    if (flags.b & 2) {
        buf = getAlloc(self)->v216(self->matCount << 6);
        for (i = 0; i < self->matCount; i++) {
            Mat *b = buf + i;
            igMatrix44f_Invert((float *)b, (const float *)(self->mats + i));
            FUN_001903d0((float *)b);
        }
        for (k = 0; k < n; k++) {
            q = src->v136(k);
            nacc = *q;
            for (m = 0; m < nb; m++) {
                float w = src->v184(m, k);
                if (!(w <= 0.0f)) {
                    Vec3f_TransformDirection((float *)&nt, (const float *)q, (const float *)(buf + (src->v196(m, k))));
                    nt -= *q;
                    nt *= w;
                    nacc += nt;
                }
            }
            nacc.normalize();
            dst->v128(k, &nacc);
        }
        Memory_FreeBuffer(buf);
    }
    return dst;
    }
    return 0;
}

void igVisualContext_ResetToDefault(igVisualContext_166400 *ctx, int flags)
{
    void *settings = ((SystemConfig *)g_objectSystem)->settings;
    int shadingMode;
    int cullMode;
    int fillMode;
    unsigned char cullEnable;
    int i, n;
    Vec4 clear, white, tint, ambient, diffuse, specular, lightDir, colour;
    int hot;

    if (flags & 1) {
        ctx->vfunc_73(0);
        ctx->vfunc_111(0);
        clear.x = 0.0f; clear.y = 0.0f; clear.z = 0.0f; clear.w = 0.0f;
        ctx->vfunc_113(&clear);
    }
    if (flags & 2) {
        white.x = 1.0f; white.y = 1.0f; white.z = 1.0f; white.w = 1.0f;
        ctx->vfunc_63(&white);
        ctx->vfunc_96(0.0f);
        tint.x = 1.0f; tint.y = 1.0f; tint.z = 1.0f; tint.w = 1.0f;
        ctx->vfunc_100(&tint);
        ambient.x = 0.0f; ambient.y = 0.0f; ambient.z = 0.0f; ambient.w = 1.0f;
        ctx->vfunc_102(&ambient);
        diffuse.x = 0.0f; diffuse.y = 0.0f; diffuse.z = 0.0f; diffuse.w = 1.0f;
        ctx->vfunc_104(&diffuse);
        specular.x = 0.0f; specular.y = 0.0f; specular.z = 0.0f; specular.w = 1.0f;
        ctx->vfunc_106(&specular);
        ctx->vfunc_108(1);
        ctx->vfunc_98(0);
    }
    if (flags & 4) {
        n = ctx->vfunc_35(8);
        if (n > 512) n = 1;
        if (n > 16) n = 16;
        n = (n <= 0) ? 1 : n; /* ternary form: the if form schedules the loop init into the bgtz delay slot */
        i = 0;
        while (i < n) {
            ctx->vfunc_115(i, 0);
            ctx->vfunc_146(i, 1);
            ctx->vfunc_148(i, 0, 0);
            ctx->vfunc_207(i, 0);
            i++;
        }
    }
    if (flags & 8) {
        ctx->vfunc_150(0);
        ctx->vfunc_156(4, 5);
    }
    if (flags & 0x80) {
        ctx->vfunc_157(0);
        ctx->vfunc_159(0);
        ctx->vfunc_161(7);
        ctx->vfunc_165(-1);
        ctx->vfunc_167(-1);
        ctx->vfunc_163(0, 0, 0);
    }
    if (flags & 0x10) {
        ctx->vfunc_239(0);
        ctx->vfunc_241(0.0f);
        ctx->vfunc_243(2);
        lightDir.x = 0.0f; lightDir.y = 0.0f; lightDir.z = 0.0f; lightDir.w = 1.0f;
        ctx->vfunc_245(&lightDir);
        ctx->vfunc_247(1.0f);
        ctx->vfunc_249(1000.0f);
    }
    if (flags & 0x20) {
        igGetRegistryValue_Int((igRegistry *)settings, 4, "shadingMode", &shadingMode, 1, 1);
        hot = -1;
        ctx->vfunc_67(&hot);
        colour.x = 0.0f; colour.y = 0.0f; colour.z = 0.0f; colour.w = 1.0f;
        ctx->vfunc_175(&colour);
        ctx->vfunc_179(1.0f);
        ctx->vfunc_181(0);
        ctx->vfunc_209(0);
        ctx->vfunc_221(1);
        ctx->vfunc_223(1, 1, 1, 1);
        ctx->vfunc_225(shadingMode);
    }
    if (flags & 0x40) {
        igGetRegistryValue_Bool((igRegistry *)settings, 4, "cullEnable", &cullEnable, 0, 1);
        igGetRegistryValue_Int((igRegistry *)settings, 4, "cullMode", &cullMode, 0, 1);
        igGetRegistryValue_Int((igRegistry *)settings, 4, "fillMode", &fillMode, 0, 1);
        ctx->vfunc_215(0);
        ctx->vfunc_217(6);
        ctx->vfunc_219(0.0f);
        ctx->vfunc_227(cullEnable);
        ctx->vfunc_229(cullMode);
        ctx->vfunc_231(1);
        ctx->vfunc_233(3);
        ctx->vfunc_235(1);
        ctx->vfunc_237(fillMode);
        ctx->vfunc_143(0);
        ctx->vfunc_188(0);
        ctx->vfunc_259(0, 0);
        for (i = 1; i < 16; i++)
            ctx->vfunc_259(0, i);
    }
}

void FUN_00166a60(void *arg0, char arg1) {
    *(char *)((char *)(arg0) + 312) = arg1;
}

void igVisualContext_UpdateFrameRateDisplay(void *arg0_, float fparg0, float fparg1) {
    C_166a70 *arg0 = (C_166a70 *)arg0_;
    float temp_f4;
    double temp_s2;
    double temp_s1;

    DAT_005607a0[0] += fparg0;
    DAT_005607a8[0] += fparg1;
    DAT_005607b0[0] += 1;
    if (fparg0 < DAT_0048a470[0]) {
        DAT_0048a470[0] = fparg0;
    }
    if (!(fparg0 <= DAT_00560838[0])) {
        DAT_00560838[0] = fparg0;
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
    if (arg0->f61 != 0) {
        if (DAT_005607b0[0] == 0) {
            igReport_Printf("FRAME RATE:       %s\n", (char *)g_gsEventCount);
            igReport_Flush();
        }
    } else {
        arg0->vX(0, 0, (int *)g_gsEventCount);
    }
}

void igVisualContext_OutputText(void) {

}

void igVisualContext_UpdatePrimitiveCountDisplay(void) {

}

void igVisualContext_DrawNonIndexed(void **arg0, int arg1, int arg2, int arg3) {
    int temp_v0;

    temp_v0 = ((DW4VC_248_0 *)(arg0))->vX();
    if (temp_v0 != 0) {
        ((DW4VC_240_1 *)(arg0))->vX((int)(0));
    }
    ((DW4VC_284_3 *)(arg0))->vX((int)(arg1), (int)(arg2), (int)(arg3));
    if (temp_v0 != 0) {
        ((DW4VC_240_1 *)(arg0))->vX((int)(temp_v0));
    }
}

igVisualContext *igVisualContext_FindFirst(void) {
    int r;
    int i;

    r = 0;
    if (((L_166d40 *)DAT_00560758) != 0) {
        for (i = 0; i < ((L_166d40 *)DAT_00560758)->count; i++) {
            if (((Gap::Core::igObject *)(((L_166d40 *)DAT_00560758)->items[i]))->isOfType(g_igVisualContext_metaObject) != 0) {
                r = ((L_166d40 *)DAT_00560758)->items[i];
                break;
            }
        }
    }
    return (igVisualContext *)r;
}

static inline int countOf(const igIntList *list) { return list->_count; }

void igVisualContext_LoadDefaultDriverDatabase(int value)
{
    int count;
    void *registry = ((ShaderSetup *)g_objectSystem)->registry;
    void *builder = ((ShaderSetup *)g_objectSystem)->builder;
    igSmartPointer<igIntList> list((igIntList *)igContextList_Create((int)igVisualContext_GetInternalMemoryPool((int *)value)));
    bool found = false;

    igRegistry_GetValueBool((igRegistry *)registry, 4, "ignoreDriverDatabase", (unsigned char *)&found, 0, 1);
    if (found) return;
    igIntList *l = list;
    count = l->_count;
    if (count < l->_capacity) {
        l->_count = countOf(l) + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(count + 1, 4);
    }
    ((int *)l->_data)[count] = value;
    igDriverDatabase_GatherProperties(builder, (igTDataList<igVisualContextView *> *)(igIntList *)list);
    if (igRegistry_IsLoadingEnabled() != 0) {
        if (igDriverDatabase_Load((igDriverDatabase *)builder, (const char *)"", (const char *)"") != 0) igDriverDatabase_ApplyToRegistry((igDriverDatabase *)builder, (int)registry, 4, 0);
    }
    FUN_002daab0((igDriverDatabase *)builder, (int)registry, 4, 0);
}

void igVisualContext_SetVertexPipelineMode(void) {

}

int igVisualContext_GetVertexPipelineMode(void) {
    return 0;
}

void FUN_00166fb0(void) {

}

int FUN_00166fc0(void) {
    return 0;
}

/* Empty slot: returns 0 without touching the receiver. */
int igVisualContext_GetLastError(void) {
    return 0;
}

igSmartPointer<igObject> FUN_00167130(SlotObject_166fe0 *object) {
    return object->f12;
}

int igVisualContext_GetVertexArray2(int arg0, int arg1)
{
  int new_var;
  new_var = arg1 * 4;
  return *((int *) (((char *) (new_var + arg0)) + 240));
}

void igVisualContext_SetViewMatrixHint(MatrixInverseCache *self, const float *matrix) {
    igMatrix44f_Copy(self->matrix, matrix);
    self->inverseDirty = 1;
}

void igVisualContext_GetViewMatrixHint(char * arg0, int arg1) {
    igMatrix44f_Copy((float *)arg1, (float *)((arg0 + 108)));
}

void igVisualContext_GetViewMatrixInverse(MatrixInverseCache *self, float *out) {
    if (self->inverseDirty) {
        igMatrix44f_Invert(self->inverse, self->matrix);
        self->inverseDirty = 0;
    }
    igMatrix44f_Copy(out, self->inverse);
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

