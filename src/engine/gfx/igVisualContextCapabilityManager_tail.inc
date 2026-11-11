static inline void retain(igObjectSlotView *o)
{
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}

static inline void release_164f50(igObjectSlotView *o)
{
    IG_OBJECT_RELEASE(o);
}

/* Slot fill with a selector fallback: shared pool if present, else the owner's
 * allocator (or the selector's allocator when the engine flag is clear). */
static inline void fill_pool_slot(void *self, igObjectSlotView **slot, igObjectSlotView *shared, int *selector)
{
    igObjectSlotView *p = shared;
    if (p != 0) {
        retain(p);
        release_164f50(*slot);
        *slot = p;
    } else {
        igObjectSlotView *a = (igObjectSlotView *)igObject_GetAllocator(self);
        a = GPR_00554c14 != 0 ? a : (igObjectSlotView *)Memory_GetAllocatorBySelector(selector[0]);
        if (a != (igObjectSlotView *)Memory_GetAllocatorBySelector(DAT_00587020[0])) {
            p = (igObjectSlotView *)igObject_GetAllocator(self);
            p = GPR_00554c14 != 0 ? p : (igObjectSlotView *)Memory_GetAllocatorBySelector(selector[0]);
            retain(p);
            release_164f50(*slot);
            *slot = p;
        } else {
            p = (igObjectSlotView *)igObject_GetAllocator(self);
            retain(p);
            release_164f50(*slot);
            *slot = p;
        }
    }
}

/* Slot fill without a selector: shared pool if present, else the owner's allocator. */
static inline void fill_pool_slot_plain(void *self, igObjectSlotView **slot, igObjectSlotView *shared)
{
    igObjectSlotView *p = shared;
    if (p != 0) {
        retain(p);
        release_164f50(*slot);
        *slot = p;
    } else {
        p = (igObjectSlotView *)igObject_GetAllocator(self);
        retain(p);
        release_164f50(*slot);
        *slot = p;
    }
}

void FUN_00164f50(igVisualContextCapabilityManager_164f50 *self)
{
    igObjectSlotView *caps;
    int arg;

    Gap__Core__igObject__vfunc_01(self);

    fill_pool_slot(self, &self->pool24, g_pool_00560760[0], DAT_005870b8);
    fill_pool_slot(self, &self->pool28, g_pool_00560768[0], DAT_00587068);
    fill_pool_slot_plain(self, &self->pool32, g_pool_00560770[0]);
    fill_pool_slot(self, &self->pool36, g_pool_00560778[0], DAT_00587060);
    fill_pool_slot(self, &self->pool40, g_pool_00560780[0], DAT_005870e8);
    fill_pool_slot(self, &self->pool44, g_pool_00560788[0], DAT_00587078);
    fill_pool_slot_plain(self, &self->pool48, g_pool_00560790[0]);
    fill_pool_slot(self, &self->pool52, g_pool_00560798[0], DAT_00587058);

    caps = FUN_002b79d0(FUN_00165ce0((int *)self));
    retain(caps);
    release_164f50(self->capabilities56);
    self->capabilities56 = caps;
    self->capabilities56->vfunc_29();

    arg = FUN_00165d10((int *)self);
    release_164f50(self->helper304);
    self->helper304 = (igObjectSlotView *)FUN_0014ee00(arg);
    arg = FUN_00165d10((int *)self);
    release_164f50(self->helper308);
    self->helper308 = (igObjectSlotView *)FUN_0014e930(arg);
}

void FUN_00165a80(VisualContextCapabilityManager *self) {
    unsigned char showFrameRate;
    unsigned char commandLineFrame;
    void *properties;
    ManagerList *list;
    int count;

    Gap__Core__igObject__vfunc_07(self);
    if (DAT_00560758 == 0) {
        DAT_00560758 = (igTDataList<VisualContextCapabilityManager *> *)FUN_00149ea0((int)(Memory_GetAllocatorBySelector(DAT_00587038)));
    }
    self->index = DAT_00560758->_count;
    list = DAT_00560758;
    count = list->count();
    if (count < list->_capacity) {
        list->_count = list->_count + 1;
    } else {
        List_Resize(list, count + 1, 4);
    }
    list->_data[count] = self;
    properties = ((PropertyRoot *)DAT_00586dc8[0])->properties;
    showFrameRate = self->showFrameRate;
    commandLineFrame = self->commandLineFrame;
    thunk_FUN_00306e50(properties, 4, DAT_004df0a0, &showFrameRate, showFrameRate, 1);
    thunk_FUN_00306e50(properties, 4, DAT_004df0b0, &commandLineFrame, commandLineFrame, 1);
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
        igObject_Destroy(o);
    }
    K key(arg0);
    i = Finder::Find(((RefObj *)DAT_00560758), key);
    if (i >= 0) {
        List_RemoveWordAt(((RefObj *)DAT_00560758), i);
    }
    l = ((RefObj *)DAT_00560758);
    if (l->count == 0) {
        --l->references;
        if (((unsigned long long)((long long)l->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(l);
        }
        DAT_00560758 = 0;
    }
    Gap__Core__igObject__vfunc_10(arg0);
}

void FUN_00165cb0(void *arg0)
{
}

int FUN_00165cc0(int *p)
{
    return *(int *)((char *)p + 24);
}

int FUN_00165cd0(int *p)
{
    return *(int *)((char *)p + 28);
}

int FUN_00165ce0(int *p)
{
    return *(int *)((char *)p + 32);
}

int FUN_00165cf0(int *p)
{
    return *(int *)((char *)p + 40);
}

int FUN_00165d00(int *p)
{
    return *(int *)((char *)p + 48);
}

int FUN_00165d10(int *p)
{
    return *(int *)((char *)p + 52);
}

void FUN_00165d20(int arg0) {
    *(int *)0x560780 = arg0;
}

void FUN_00165d30(O_165d30 *arg0, unsigned int arg1, int arg2) {
    int sp5C;
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
            ((V1 *)FUN_00165cc0((int *)arg0))->v264(s0);
            arg0->f80 = 0;
        }
        arg0->f80 = ((V2_165d30 *)FUN_00165cc0((int *)arg0))->v220(arg1 << 6, 0x10);
        arg0->f88 = arg1;
    }
    s1 = (char *)arg0->f80;
    for (i = 0; i < arg1; i++) {
        off = i << 6;
        FUN_00191f30(&sp5C, s1, arg0->f84 + off);
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
        Matrix44_SetTranslation(s1, v);
        FUN_001903d0(s1);
        s1 += 0x40;
    }
    arg0->f76 = arg0->f76 + 1;
}

int FUN_00165e40(void *arg0) {
    return *(int *)((char *)(arg0) + 72);
}

static inline Obj_165e50 *getAlloc(void *o) {
    Obj_165e50 *a = (Obj_165e50 *)igObject_GetAllocator(o);
    if (GPR_00554c14 != 0) return a;
    return (Obj_165e50 *)Memory_GetAllocatorBySelector(DAT_00587060[0]);
}

void *FUN_00165e50(Self *self, Obj_165e50 *src) {
    /* matching construct: random sweep — the order of the local declarations */
    int k; int nb; Obj_165e50 *dst; Mat *buf; V_165e50 *q; int m; int i; int n; int j; Fl flags; int scratch; V_165e50 acc, t, nacc, nt; Obj_165e50 *al;
    if (src != 0) {
    dst = (Obj_165e50 *)FUN_0014b940(FUN_00165cd0((int *)self));
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
                FUN_00192fc0(&t, p, self->mats + (src->v196(j, i)));
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
            FUN_00191f30(&scratch, b, self->mats + i);
            FUN_001903d0(b);
        }
        for (k = 0; k < n; k++) {
            q = src->v136(k);
            nacc = *q;
            for (m = 0; m < nb; m++) {
                float w = src->v184(m, k);
                if (!(w <= 0.0f)) {
                    FUN_00192f50(&nt, q, buf + (src->v196(m, k)));
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

void FUN_00166400(igVisualContext_166400 *ctx, int flags)
{
    void *settings = ((SystemConfig *)DAT_00586dc8[0])->settings;
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
        thunk_FUN_003065f0(settings, 4, DAT_004df0c8, &shadingMode, 1, 1);
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
        thunk_FUN_00306e50(settings, 4, DAT_004df0d8, &cullEnable, 0, 1);
        thunk_FUN_003065f0(settings, 4, DAT_004df0e8, &cullMode, 0, 1);
        thunk_FUN_003065f0(settings, 4, DAT_004df0f8, &fillMode, 0, 1);
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

void FUN_00166a70(void *arg0_, float fparg0, float fparg1) {
    C_166a70 *arg0 = (C_166a70 *)arg0_;
    float temp_f4;
    int temp_s2;
    int temp_s1;

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
        sprintf(&DAT_005607d0[0], &DAT_004df110[0], temp_s2, temp_s1, fptodp(DAT_005607b8[0]));
        DAT_005607a0[0] = 0.0f;
        DAT_005607a8[0] = 0.0f;
        DAT_005607b0[0] = 0;
        DAT_00560838[0] = 0.0f;
        DAT_0048a470[0] = (float) 0xF4240;
    }
    if (arg0->f61 != 0) {
        if (DAT_005607b0[0] == 0) {
            FUN_00304430(&DAT_004df130[0], &DAT_005607d0[0]);
            FUN_00304680();
        }
    } else {
        arg0->vX(0, 0, &DAT_005607d0[0]);
    }
}

void FUN_00166c70(void) {

}

void FUN_00166c80(void) {

}

void FUN_00166c90(void **arg0, int arg1, int arg2, int arg3) {
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

int FUN_00166d40(void) {
    int r;
    int i;

    r = 0;
    if (((L_166d40 *)DAT_00560758) != 0) {
        for (i = 0; i < ((L_166d40 *)DAT_00560758)->count; i++) {
            if (igObject_IsKindOf(((L_166d40 *)DAT_00560758)->items[i], DAT_0055f8e8[0]) != 0) {
                r = ((L_166d40 *)DAT_00560758)->items[i];
                break;
            }
        }
    }
    return r;
}

static inline int countOf(const igIntList *list) { return list->_count; }

void FUN_00166de0(int value)
{
    int count;
    void *registry = ((ShaderSetup *)DAT_00586dc8[0])->registry;
    void *builder = ((ShaderSetup *)DAT_00586dc8[0])->builder;
    igSmartPointer<igIntList> list(FUN_002cba00((void *)(FUN_00165ce0((int *)value))));
    bool found = false;

    FUN_00306e50(registry, 4, DAT_004df150, &found, 0, 1);
    if (found) return;
    igIntList *l = list;
    count = l->_count;
    if (count < l->_capacity) {
        l->_count = countOf(l) + 1;
    } else {
        List_Resize(l, count + 1, 4);
    }
    ((int *)l->_data)[count] = value;
    FUN_002da010(builder, list);
    if (FUN_00305cf0() != 0) {
        if (FUN_002da1c0(builder, (const char *)DAT_004dc870, (const char *)DAT_004dc870) != 0) FUN_002da990(builder, registry, 4, 0);
    }
    FUN_002daab0(builder, registry, 4, 0);
}

void FUN_00166f90(void) {

}

int FUN_00166fa0(void) {
    return 0;
}

void FUN_00166fb0(void) {

}

int FUN_00166fc0(void) {
    return 0;
}

/* Empty slot: returns 0 without touching the receiver. */
int FUN_00166fd0(void) {
    return 0;
}

void FUN_00167130(int **arg0, int *arg1) {
    int *a;
    *arg0 = (int *)arg1[3];
    a = *arg0;
    if (a != 0) {
        a[1] = a[1] + 1;
    }
}

int FUN_00167160(int arg0, int arg1)
{
  int new_var;
  new_var = arg1 * 4;
  return *((int *) (((char *) (new_var + arg0)) + 240));
}

void FUN_00167170(void *arg0) {
    Matrix44_Copy((char *)arg0 + 0x6C);
    *(char *)((char *)(arg0) + 236) = 1;
}

void FUN_001671a0(char * arg0, int arg1) {
    Matrix44_Copy((float *)arg1, (float *)((arg0 + 108)));
}

void FUN_001671b0(MatrixInverseCache *self, float *out) {
    if (self->inverseDirty) {
        igResult result;
        FUN_00191f30(&result, self->inverse, self->matrix);
        self->inverseDirty = 0;
    }
    Matrix44_Copy(out, self->inverse);
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

