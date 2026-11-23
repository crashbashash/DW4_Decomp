void FUN_00170210(void *arg0) {
    *(int *)((char *)(arg0) + 144) = 0;
    *(int *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 4) = 0;
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 12) = 0x3F800000;
    *(int *)((char *)(arg0) + 64) = 0;
    *(int *)((char *)(arg0) + 68) = 0;
    *(int *)((char *)(arg0) + 72) = 0x3F800000;
    *(int *)((char *)(arg0) + 32) = 0x3F800000;
    *(int *)((char *)(arg0) + 36) = 0x3F800000;
    *(int *)((char *)(arg0) + 40) = 0x3F800000;
    *(int *)((char *)(arg0) + 44) = 0x3F800000;
    *(float *)((char *)(arg0) + 16) = (float) 0.600000024f;
    *(float *)((char *)(arg0) + 20) = (float) 0.600000024f;
    *(float *)((char *)(arg0) + 24) = (float) 0.600000024f;
    *(int *)((char *)(arg0) + 28) = 0x3F800000;
    *(int *)((char *)(arg0) + 48) = 0;
    *(int *)((char *)(arg0) + 52) = 0;
    *(int *)((char *)(arg0) + 56) = 0;
    *(int *)((char *)(arg0) + 60) = 0x3F800000;
    *(int *)((char *)(arg0) + 92) = 0x43340000;
    *(int *)((char *)(arg0) + 80) = 0x3F800000;
    *(int *)((char *)(arg0) + 84) = 0;
    *(int *)((char *)(arg0) + 88) = 0;
    *(int *)((char *)(arg0) + 76) = 0;
    *(char *)((char *)(arg0) + 148) = 0;
    *(int *)((char *)(arg0) + 152) = 0;
    *(int *)((char *)(arg0) + 124) = 0;
    *(int *)((char *)(arg0) + 96) = 0;
    *(int *)((char *)(arg0) + 100) = 0;
    *(int *)((char *)(arg0) + 104) = 0;
    *(int *)((char *)(arg0) + 112) = 0;
    *(int *)((char *)(arg0) + 116) = 0;
    *(int *)((char *)(arg0) + 120) = 0;
    *(int *)((char *)(arg0) + 108) = 8;
}

void FUN_001702c0(igPsx2VisualContext *vc) {
    int sp5C;
    int bi;
    Buf_17a070 *b;
    void *lights;
    int i;
    sp5C = 0x20;
    igGetRegistryValue_Int(*(igRegistry **)((char *)g_objectSystem + 56), 4, "IG_GFX_VC_LIGHT_ARRAY_SIZE", &sp5C, 0x20, 0);
    Buf_17a070 *r = (Buf_17a070 *)Memory_AllocateBufferDirect(0x14, (igMemoryPoolView *)((Gap::Gfx::igVisualContext *)vc)->getListMemoryPool());
    if (r != 0) {
        bi = (int)r;
        b = (Buf_17a070 *)bi;
        int n = sp5C;
        Owner_17a070 *ow;
        int k;
        int *old;
        int *tok;
        b->f8 = 0;
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool = pool;
        }
        tok = (int *)StringPool_Intern(g_stringPool, "IG_GFX_VC_LIGHT_ARRAY_SIZE");
        old = (int *)b->f8;
        if (old != 0) {
            int *h = old - 2;
            int c = old[-1] - 1;
            old[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
        }
        b->f8 = (int)tok;
        if (n == 0) n = 1;
        ow = (Owner_17a070 *)Memory_FindBufferOwner(b);
        b->f16 = ow->v228(n, 0xA0, 0x10);
        b->f12 = (short *)ow->v224(n, 2);
        b->s2 = n;
        b->s0 = n;
        b->s4 = n;
        for (k = 0; k < n; k++) b->f12[k] = (short)k;
        r = (Buf_17a070 *)bi;
    }
    vc->_pLightList = (int)r;
    lights = Memory_AllocateAlignedWithAllocator(0x70, 0x10, (igMemoryPoolView *)((Gap::Gfx::igVisualContext *)vc)->getInternalMemoryPool());
    if (lights != 0) FUN_001716c0(lights);
    vc->_currentMaterial = (int)lights;
    FUN_001716c0((void *)vc->_currentMaterial);
    DAT_00560850[0] = ((LightCapsDispatch *)vc)->getCapability(9);
    DAT_00560858[0] = ((PoolAllocDispatch *)((Gap::Gfx::igVisualContext *)vc)->getInternalMemoryPool())->allocate(DAT_00560850[0] * 4);
    for (i = 0; i < DAT_00560850[0]; i++) {
        ((int *)DAT_00560858[0])[i] = -1;
    }
    igMatrix44f_SetIdentity(g_gfxIdentityMatrix.m);
}

void FUN_00170510(Obj_170510 *o, int arg1) {
    int s0;
    T_170510 *t;
    char *s1;
    s0 = o->t->count - 1;
    while (-1 < s0) {
        if (o->t->Wanted(s0)) {
            o->f76(s0);
        }
        s0--;
    }
    if (arg1 == 0) {
        t = o->t;
        if (t != 0) {
            POOL();
            s1 = (char *)StringPool_Intern(g_stringPool, 0);
            STR_RELEASE(t->str);
            t->str = s1;
            Memory_FreeBuffer(t->buf);
            Memory_FreeBuffer(t->arr);
            if (&t->str != 0) {
                STR_RELEASE(t->str);
            }
            Memory_FreeBufferAliasB(t);
        }
        o->t = 0;
        Memory_FreeBuffer(DAT_00560858[0]);
        if (o->f1344 != 0) {
            Memory_FreeBufferAliasB(o->f1344);
        }
    }
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setLightingState(bool enb) {
    S0_1706d0 *arg0 = (S0_1706d0 *)this;
    if (arg0->f1340 == (enb & 0xFF)) {
        DAT_00560848[0] += 1;
    }
    if (g_igPsx2DisableExt_ext1Enabled != 0) {
        enb = 0;
    }
    arg0->f1340 = enb;
    if (arg0->f1340 == 1) {
        p2EnableCapability(8);
        return;
    }
    p2DisableCapability(8);
}

bool igPsx2VisualContext::getLightingState() const {
    return _bLightingEnabled;
}

int igPsx2VisualContext::createLight(IG_GFX_LIGHT_TYPE type) {
    Pool *p;
    int i;
    int idx;
    It_170750 *it;
    int v;
    p = ((Pool *)_pLightList);
    if (p->f4 <= 0) {
        p->f16 = (char *)Memory_ReallocateAlignedAlias(p->f16, (p->f0 + 4) * 0xA0, 0x10);
        memset(p->f16 + p->f0 * 0xA0, 0, 0x280);
        if (p->f2 < 4) {
            O_170750 *o = (O_170750 *)Memory_FindBufferOwner(p);
            p->f12 = (unsigned short *)o->vX((int)p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    idx = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    it = (It_170750 *)(((Pool *)_pLightList)->f16 + idx * 0xA0);
    FUN_00170210(it);
    it->f152 = type;
    switch (type) {
    case 0:
        it->f124 = 0;
        break;
    case 1:
        it->f124 = 1;
        break;
    case 2:
        it->f124 = 2;
        break;
    }
    return idx;
}

void igPsx2VisualContext::deleteLight(int lighthandle) {
    Obj_1708e0 *arg0 = (Obj_1708e0 *)this;
    E_1708e0 *e = arg0->f1336->f16 + lighthandle;
    Lst *l;
    if (e != 0 && e != 0) {
        if (e->f148 != 0) {
            arg0->vA(lighthandle, 0);
        }
        l = arg0->f1336;
        if (lighthandle < l->f0 && lighthandle >= 0) {
            if (l->f4 >= l->f2) {
                Buf *b = (Buf *)Memory_FindBufferOwner(l);
                l->f2 = l->f2 + 8;
                l->f12 = (short *)b->vB(l->f12, l->f2 * 2);
            }
            l->f12[l->f4] = lighthandle;
            l->f4 = l->f4 + 1;
        }
    }
}

bool igPsx2VisualContext::setLightState(int lightHandle, bool enable) {
    Obj_1709d0 *arg0 = (Obj_1709d0 *)this;
    Mgr *m = arg0->f1336;
    int i;
    Ent *e = m->ents + lightHandle;
    int off;
    if (e == 0) {
        return 0;
    }
    if (e->f148 == enable) {
        DAT_005608cc[0] += 1;
    }
    if (e->f148 == enable) {
        return 1;
    }
    if (enable) {
        for (i = 0; i < DAT_00560850[0]; i++) {
            off = i * 4;
            if (*(int *)((int)DAT_00560858[0] + off) < 0) {
                e->f144 = i;
                *(Ent **)((int)DAT_00560858[0] + off) = e;
                e->f148 = 1;
                FUN_00171690(arg0, e);
                p2EnableLight(i);
                return 1;
            }
        }
        return 0;
    }
    p2DisableLight(e->f144);
    e->f148 = 0;
    *(int *)((int)DAT_00560858[0] + e->f144 * 4) = -1;
    return 1;
}

bool igPsx2VisualContext::getLightState(int lightHandle) const {
    Ent *e = ((Obj_1709d0 *)this)->f1336->ents + lightHandle;
    return e->f148;
}

IG_GFX_LIGHT_TYPE igPsx2VisualContext::getLightType(int handle) const {
    void *arg0 = (void *)this;
    return (IG_GFX_LIGHT_TYPE)*(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (handle * 0xA0))) + 152);
}

void igPsx2VisualContext::setLightDiffuse(int handle, const igVec4f &d) {
    char *a3;
    float *t;
    int e;
    a3 = (char *)_pLightList;
    handle = *(int *)(a3 + 16) + handle * 0xA0;
    t = (float *)handle;
    if (t != 0) {
        e = 1;
        if (t[8] != d[0]) e = 0;
        if (e != 0) { e = 1; if (t[9] != d[1]) e = 0; }
        if (e != 0) { e = 1; if (t[10] != d[2]) e = 0; }
        if (e != 0) { e = 1; if (t[11] != d[3]) e = 0; }
        if (e != 0) {
            DAT_005608d0[0] += 1;
        }
        t[8] = d[0];
        t[9] = d[1];
        t[10] = d[2];
        t[11] = d[3];
        FUN_00171690((::igPsx2VisualContext *)this, t);
    }
}

void igPsx2VisualContext::setLightSpecular(int handle, const igVec4f &s) {
    Tab_170c30 *t;
    E_170c30 *e;
    int same;
    int old;
    int nw;
    t = (Tab_170c30 *)_pLightList;
    e = (E_170c30 *)(t->f10 + handle * 160);
    if (e != 0) {
        same = 1;
        if (e->v.x != s[0]) { same = 0; }
        if (same != 0) {
            same = 1;
            if (e->v.y != s[1]) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.z != s[2]) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.w != s[3]) { same = 0; }
        }
        if (same != 0) {
            DAT_005608d4[0] += 1;
        }
        e->v.x = s[0];
        e->v.y = s[1];
        e->v.z = s[2];
        e->v.w = s[3];
        old = e->flags;
        if (s[0] != 0.0f || s[1] != 0.0f || s[2] != 0.0f) {
            e->flags = e->flags | 1;
        } else {
            e->flags = old & ~1;
        }
        nw = e->flags;
        if (old != nw) {
            e->flags = nw | 8;
        }
        FUN_00171690((::igPsx2VisualContext *)this, e);
    }
}

void igPsx2VisualContext::setLightAmbient(int handle, const igVec4f &a) {
    O_170d80 *arg0 = (O_170d80 *)this;
    T_170d80 *t;
    E_170d80 *e;
    int same;
    int old;
    t = arg0->f1336;
    e = (E_170d80 *)((char *)t->f16 + handle * 160);
    if (e != 0) {
        same = 1;
        if (e->v0 != a[0]) same = 0;
        if (same) {
            same = 1;
            if (e->v1 != a[1]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v2 != a[2]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v3 != a[3]) same = 0;
        }
        if (same) {
            DAT_005609c8[0] = DAT_005609c8[0] + 1;
        }
        e->v0 = a[0];
        e->v1 = a[1];
        e->v2 = a[2];
        e->v3 = a[3];
        old = e->f108;
        if (a[0] != 0.0f || a[1] != 0.0f || a[2] != 0.0f) {
            e->f108 = e->f108 | 0x10;
        } else {
            e->f108 = old & ~0x10;
        }
        if (old != e->f108) {
            e->f108 = e->f108 | 8;
        }
        FUN_00171690(arg0, e);
    }
}

void igPsx2VisualContext::setLightPosition(int handle, const igVec3f &p) {
    float sp40[16];
    L_171100 *l = (L_171100 *)_pLightList;
    Ent_171100 *e = (Ent_171100 *)(l->base + handle * 0xA0);
    if (e != 0) {
        int same = 1;
        if (e->x != p[0]) same = 0;
        if (same != 0) { same = 1; if (e->y != p[1]) same = 0; }
        if (same != 0) { same = 1; if (e->z != p[2]) same = 0; }
        if (same != 0) DAT_005608dc[0] += 1;
        e->x = p[0];
        e->y = p[1];
        e->z = p[2];
        if (e->f152 != 0) {
            ((C_171100 *)this)->vX(1, sp40);
            Vec3f_TransformProjective((float *)((char *)e + 0x70), p.vec, sp40);
        }
        FUN_00171690(((C_171100 *)this), e);
    }
}

void igPsx2VisualContext::setLightCutoffAngle(int handle, float c) {
    struct Ctx_171220 *arg0 = (struct Ctx_171220 *)this;
    struct Item *it;
    unsigned int old;

    it = &arg0->list->data[handle];
    if (it != 0) {
        old = it->f108;
        if (it->f92 == c) {
            DAT_005608e4[0] += 1;
        }
        it->f92 = c;
        if (it->f152 == 2 && c != 180.0f) {
            it->f108 = it->f108 | 4;
        } else {
            it->f108 = it->f108 & ~4;
        }
        if (old != it->f108) {
            it->f108 = it->f108 | 8;
        }
        FUN_00171690(arg0, it);
    }
}

void igPsx2VisualContext::setLightFalloffRate(int handle, float e) {
    S_1712e0 *arg0 = (S_1712e0 *)this;
    float temp_f1;
    E_1712e0 *temp_a1;
    L_1712e0 *temp_a2;

    temp_a2 = arg0->f1336;
    temp_a1 = temp_a2->f16 + handle;
    if (temp_a1 != 0) {
        temp_f1 = 128.0f * e;
        if (temp_a1->f76 == temp_f1) {
            DAT_005608e8[0] += 1;
        }
        temp_a1->f76 = temp_f1;
        FUN_00171690(arg0, temp_a1);
    }
}

void igPsx2VisualContext::getLightDiffuse(int handle, igVec4f &d) const {
    void *temp_v1;

    temp_v1 = (void *)(((::igLightList *)_pLightList)->_data + (handle * 0xA0));
    d.vec[0] = (float) *(float *)((char *)(temp_v1) + 32);
    d.vec[1] = (float) *(float *)((char *)(temp_v1) + 36);
    d.vec[2] = (float) *(float *)((char *)(temp_v1) + 40);
    d.vec[3] = (float) *(float *)((char *)(temp_v1) + 44);
}

void igPsx2VisualContext::getLightAmbient(int handle, igVec4f &a) const {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(_pLightList) + 16) + (handle * 0xA0));
    a.vec[0] = (float) *(float *)((char *)(temp_v1) + 16);
    a.vec[1] = (float) *(float *)((char *)(temp_v1) + 20);
    a.vec[2] = (float) *(float *)((char *)(temp_v1) + 24);
    a.vec[3] = (float) *(float *)((char *)(temp_v1) + 28);
}

/* The reflected metadata types _diffuse as int[4], but the code reads floats. */
void igPsx2VisualContext::getLightSpecular(int handle, igVec4f &s) const {
    ::igLightAttr *temp_v1;

    temp_v1 = (::igLightAttr *)(((::igLightList *)_pLightList)->_data + (handle * 0xA0));
    s[0] = *(float *)&temp_v1->_diffuse[0];
    s[1] = *(float *)&temp_v1->_diffuse[1];
    s[2] = *(float *)&temp_v1->_diffuse[2];
    s[3] = *(float *)&temp_v1->_diffuse[3];
}

void igPsx2VisualContext::getLightPosition(int handle, igVec3f &p) const {
    float *temp_v1;

    temp_v1 = (float *)(((::igLightList *)_pLightList)->_data + (handle * 0xA0));
    p[0] = temp_v1[0];
    p[1] = temp_v1[1];
    p[2] = temp_v1[2];
}

void igPsx2VisualContext::getLightDirection(int handle, igVec3f &d) const {
    ::igLightAttr *temp_v1;

    temp_v1 = (::igLightAttr *)(((::igLightList *)_pLightList)->_data + (handle * 0xA0));
    d[0] = (float) *(float *)&temp_v1->_specular[0];
    d[1] = (float) *(float *)&temp_v1->_specular[1];
    d[2] = (float) *(float *)&temp_v1->_specular[2];
}

float igPsx2VisualContext::getLightFalloffRate(int handle) const {
    return 0.0f;
}

void igPsx2VisualContext::getLightAttenuation(int handle, igVec3f &a) const {
    char *p = (char *)(*(int *)((char *)(_pLightList) + 16) + (handle * 0xA0));
    float x, y, z;
    z = *(float *)(p + 88);
    y = *(float *)(p + 84);
    x = *(float *)(p + 80);
    a.vec[0] = x;
    a.vec[1] = y;
    a.vec[2] = z;
}

float igPsx2VisualContext::getLightCutoffAngle(int handle) const {
    void *arg0 = (void *)this;
    return *(float *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (handle * 0xA0))) + 92);
}
}
}

void FUN_00171690(void *arg0, void *arg1) {
    if (*(unsigned char *)((char *)(arg1) + 148) != 0) {
        p2SetLight(*(int *)((char *)(arg1) + 144), (p2Light *)arg1);
    }
}

void FUN_001716c0(void *arg0) {
    *(float *)((char *)(arg0) + 16) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 20) = (float) g_vec4Zero[1];
    *(float *)((char *)(arg0) + 24) = (float) g_vec4Zero[2];
    *(float *)((char *)(arg0) + 28) = (float) g_vec4Zero[3];
    *(float *)((char *)(arg0) + 0) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 4) = (float) g_vec4Zero[1];
    *(float *)((char *)(arg0) + 8) = (float) g_vec4Zero[2];
    *(float *)((char *)(arg0) + 12) = (float) g_vec4Zero[3];
    *(float *)((char *)(arg0) + 48) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 52) = (float) g_vec4Zero[1];
    *(float *)((char *)(arg0) + 56) = (float) g_vec4Zero[2];
    *(float *)((char *)(arg0) + 60) = (float) g_vec4Zero[3];
    *(float *)((char *)(arg0) + 32) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 36) = (float) g_vec4Zero[1];
    *(float *)((char *)(arg0) + 40) = (float) g_vec4Zero[2];
    *(float *)((char *)(arg0) + 44) = (float) g_vec4Zero[3];
    *(int *)((char *)(arg0) + 64) = 0;
    *(int *)((char *)(arg0) + 68) = 2;
    *(int *)((char *)(arg0) + 84) = 0;
    *(int *)((char *)(arg0) + 80) = 0;
}

static inline bool colorEqual(const float *a, const float *b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMaterialDiffuse(const igVec4f &d) {
    VisualContextColorView *arg0 = (VisualContextColorView *)this;
    float *cur = arg0->f1344->v;
    VisualColorBlock *p;
    if (colorEqual(cur, d.vec)) {
        DAT_005608f8[0] += 1;
    }
    p = arg0->f1344;
    p->v[0] = d[0];
    p->v[1] = d[1];
    p->v[2] = d[2];
    p->v[3] = d[3];
    FUN_00172330(arg0, arg0->f1344);
}

void igPsx2VisualContext::getMaterialDiffuse(igVec4f &d) const {
    ::igMaterialAttr *temp_v1;

    temp_v1 = (::igMaterialAttr *)_currentMaterial;
    d.vec[0] = (float) *(float *)&temp_v1->_diffuse[0];
    d.vec[1] = (float) *(float *)&temp_v1->_diffuse[1];
    d.vec[2] = (float) *(float *)&temp_v1->_diffuse[2];
    d.vec[3] = (float) *(float *)&temp_v1->_diffuse[3];
}

void igPsx2VisualContext::setMaterialAmbient(const igVec4f &a) {
    Obj_1718a0 *o = (Obj_1718a0 *)this;
    Sub *s;
    unsigned old, *f;
    bool eq;
    s = o->s;
    /* matching construct: C++ conversion trial — the four equality tests are one bool && chain */
    eq = s->v.x == a.vec[0] && s->v.y == a.vec[1] && s->v.z == a.vec[2] && s->v.w == a.vec[3];
    if (eq) DAT_005608fc[0]++;
    s = o->s;
    s->v.x = a.vec[0]; s->v.y = a.vec[1]; s->v.z = a.vec[2]; s->v.w = a.vec[3];
    s = o->s;
    f = &s->flags;
    old = s->flags;
    if (a.vec[0] != 0.0f || a.vec[1] != 0.0f || a.vec[2] != 0.0f) *f |= 4;
    else *f = old & ~4u;
    s = o->s;
    f = &s->flags;
    if (old != s->flags) *f = s->flags | 2;
    FUN_00172330(o, o->s);
}

void igPsx2VisualContext::getMaterialAmbient(igVec4f &a) const {
    void *temp_v1;

    temp_v1 = (void *)_currentMaterial;
    a.vec[0] = (float) *(float *)((char *)(temp_v1) + 0);
    a.vec[1] = (float) *(float *)((char *)(temp_v1) + 4);
    a.vec[2] = (float) *(float *)((char *)(temp_v1) + 8);
    a.vec[3] = (float) *(float *)((char *)(temp_v1) + 12);
}

void igPsx2VisualContext::setMaterialEmissive(const igVec4f &e) {
    struct S_171a10 *arg0 = (struct S_171a10 *)this;
    float *temp_a2;
    struct T_171a10 *temp_v1;
    int var_v0;
    struct T_171a10 *temp_v0;

    temp_v1 = arg0->f1344;
    var_v0 = 1;
    temp_a2 = temp_v1->v;
    if (temp_v1->v[0] != e[0]) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[1] != e[1]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[2] != e[2]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[3] != e[3]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        DAT_00560900[0] += 1;
    }
    temp_v0 = arg0->f1344;
    temp_v0->v[0] = e[0];
    temp_v0->v[1] = e[1];
    temp_v0->v[2] = e[2];
    temp_v0->v[3] = e[3];
    FUN_00172330(arg0, arg0->f1344);
}

void igPsx2VisualContext::getMaterialEmissive(igVec4f &d) const {
    ::igMaterialAttr *temp_v1;

    temp_v1 = (::igMaterialAttr *)_currentMaterial;
    d.vec[0] = (float) *(float *)&temp_v1->_emission[0];
    d.vec[1] = (float) *(float *)&temp_v1->_emission[1];
    d.vec[2] = (float) *(float *)&temp_v1->_emission[2];
    d.vec[3] = (float) *(float *)&temp_v1->_emission[3];
}

void igPsx2VisualContext::setMaterialSpecular(const igVec4f &s) {
    struct Psx2VisualContextView *arg0 = (struct Psx2VisualContextView *)this;
    struct VisualContextVec4 *p;
    struct VisualContextState *o;
    unsigned old;
    unsigned *fp;
    bool same;

    o = arg0->o;
    p = &o->v;
    same = p->x == s.vec[0] && p->y == s.vec[1] && p->z == s.vec[2] && p->w == s.vec[3];
    if (same) {
        DAT_00560904[0] += 1;
    }
    o = arg0->o;
    o->v.x = s.vec[0];
    o->v.y = s.vec[1];
    o->v.z = s.vec[2];
    o->v.w = s.vec[3];
    o = arg0->o;
    fp = &o->flags;
    old = *fp;
    if (s.vec[0] != 0.0f || s.vec[1] != 0.0f || s.vec[2] != 0.0f) {
        *fp = *fp | 1;
    } else {
        *fp = old & ~1;
    }
    o = arg0->o;
    fp = &o->flags;
    if (old != *fp) {
        *fp = *fp | 2;
    }
    FUN_00172330(arg0, arg0->o);
}

void igPsx2VisualContext::getMaterialSpecular(igVec4f &s) const {
    ::igMaterialAttr *temp_v1;

    temp_v1 = (::igMaterialAttr *)_currentMaterial;
    s.vec[0] = (float) *(float *)&temp_v1->_ambient[0];
    s.vec[1] = (float) *(float *)&temp_v1->_ambient[1];
    s.vec[2] = (float) *(float *)&temp_v1->_ambient[2];
    s.vec[3] = (float) *(float *)&temp_v1->_ambient[3];
}

void igPsx2VisualContext::setMaterialShininess(float sh) {
    S0_171c80 *arg0 = (S0_171c80 *)this;
    if (arg0->f1344->f64 == sh) {
        DAT_00560908[0] += 1;
    }
    arg0->f1344->f64 = sh;
    FUN_00172330(arg0, arg0->f1344);
}

float igPsx2VisualContext::getMaterialShininess() const {
    return *(float *)((char *)(_currentMaterial) + 64);
}

void igPsx2VisualContext::setMaterial(const igVec4f &ambient, const igVec4f &diffuse, const igVec4f &specular, const igVec4f &emission, const float shininess) {
    O_171cd0 *arg0 = (O_171cd0 *)this;
    V4_171cd0 *arg1 = (V4_171cd0 *)&ambient;
    V4_171cd0 *arg2 = (V4_171cd0 *)&diffuse;
    V4_171cd0 *arg3 = (V4_171cd0 *)&specular;
    V4_171cd0 *arg4 = (V4_171cd0 *)&emission;
    float fparg0 = shininess;
    EQ4(arg0->s, b, arg2, DAT_005608f8);
    EQ4(arg0->s, a, arg1, DAT_005608fc);
    EQ4(arg0->s, d, arg4, DAT_00560900);
    EQ4(arg0->s, c, arg3, DAT_00560904);
    if (arg0->s->e == fparg0) {
        DAT_00560908[0] += 1;
    }
    { St *t = arg0->s; t->b.x = arg2->x; t->b.y = arg2->y; t->b.z = arg2->z; t->b.w = arg2->w; }
    { St *t = arg0->s; t->a.x = arg1->x; t->a.y = arg1->y; t->a.z = arg1->z; t->a.w = arg1->w; }
    { St *t = arg0->s; t->d.x = arg4->x; t->d.y = arg4->y; t->d.z = arg4->z; t->d.w = arg4->w; }
    { St *t = arg0->s; t->c.x = arg3->x; t->c.y = arg3->y; t->c.z = arg3->z; t->c.w = arg3->w; }
    arg0->s->e = fparg0;
    {
        unsigned a2 = arg0->s->f;
        if (arg3->x != 0.0f || arg3->y != 0.0f || arg3->z != 0.0f) {
            arg0->s->f = arg0->s->f | 1;
        } else {
            arg0->s->f = a2 & ~1;
        }
        if (arg1->x != 0.0f || arg1->y != 0.0f || arg1->z != 0.0f) {
            arg0->s->f = arg0->s->f | 4;
        } else {
            arg0->s->f = arg0->s->f & ~4;
        }
        if (a2 != arg0->s->f) {
            arg0->s->f = arg0->s->f | 2;
        }
    }
    FUN_00172330(arg0, arg0->s);
}
}
}

void FUN_001720d0(struct O_1720d0 *arg0, int arg1) {
    if (arg0->p->f == arg1) {
        DAT_0056090c[0] += 1;
    }
    arg0->p->f = arg1;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMaterialSpecularState(bool enable)
{
    if (_materialSpecularState == (enable & 0xFF))
        DAT_00560910 += 1;
    _materialSpecularState = enable;
    p2SetMaterialSpecularState((unsigned char)enable);
}

void igPsx2VisualContext::setMaterialColorMode(int mode) {
    if (((MaterialState *)_currentMaterial)->blendMode == mode) {
        DAT_00560914[0] += 1;
    }
    ((MaterialState *)_currentMaterial)->blendMode = mode;
    switch (mode) {
    case 0:
        p2DisableCapability(12);
        p2SetLightingMode(0);
        return;
    case 1:
        p2EnableCapability(12);
        p2SetLightingMode(1);
        break;
    case 2:
        p2EnableCapability(12);
        p2SetLightingMode(4);
        break;
    case 3:
        p2EnableCapability(12);
        p2SetLightingMode(5);
        break;
    case 4:
        p2EnableCapability(12);
        p2SetLightingMode(3);
        break;
    case 5:
        p2EnableCapability(12);
        p2SetLightingMode(2);
        break;
    }
}

int igPsx2VisualContext::getMaterialColorMode() const {
    return *(int *)((char *)(_currentMaterial) + 84);
}

void igPsx2VisualContext::setSceneAmbient(const igVec4f &sceneAmbient) {
    struct H_172230 *arg0 = (struct H_172230 *)this;
    float *a2;
    struct O_172230 *o;
    int r;
    o = arg0->o;
    r = 1;
    a2 = o->v;
    if (o->v[0] != sceneAmbient[0]) r = 0;
    if (r != 0) { r = 1; if (a2[1] != sceneAmbient[1]) r = 0; }
    if (r != 0) { r = 1; if (a2[2] != sceneAmbient[2]) r = 0; }
    if (r != 0) { r = 1; if (a2[3] != sceneAmbient[3]) r = 0; }
    if (r != 0) {
        DAT_00560918[0] += 1;
    }
    o = arg0->o;
    o->v[0] = sceneAmbient[0];
    o->v[1] = sceneAmbient[1];
    o->v[2] = sceneAmbient[2];
    o->v[3] = sceneAmbient[3];
    p2SetLightingColor(sceneAmbient.vec);
}

void igPsx2VisualContext::getSceneAmbient(igVec4f &sceneAmbient) const {
    void *temp_v1;

    temp_v1 = (void *)(_currentMaterial);
    sceneAmbient.vec[0] = (float) *(float *)((char *)(temp_v1) + 88);
    sceneAmbient.vec[1] = (float) *(float *)((char *)(temp_v1) + 92);
    sceneAmbient.vec[2] = (float) *(float *)((char *)(temp_v1) + 96);
    sceneAmbient.vec[3] = (float) *(float *)((char *)(temp_v1) + 100);
}
}
}

void FUN_00172330(void *arg0, void *arg1) {
    p2SetMaterial(*(int *)((char *)arg1 + 80), (p2Material *)arg1);
    p2SetLightingColor((float *)(*(int *)((char *)arg0 + 1344) + 0x58));
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setStackSize(IG_GFX_MATRIX_STACK which, int depth) {
    switch (which) {
    case 0:
        if (depth >= _projMat->_count) ((Gap::Core::igDataList *)_projMat.p)->setCapacity(depth, 64);
        break;
    case 1:
        if (depth >= _mvMat->_count) ((Gap::Core::igDataList *)_mvMat.p)->setCapacity(depth, 64);
        break;
    case 2:
        if (depth >= _texMat->_count) ((Gap::Core::igDataList *)_texMat.p)->setCapacity(depth, 64);
        break;
    case 10:
        if (depth >= _blendMat0->_count) ((Gap::Core::igDataList *)_blendMat0.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat0->_count) ((Gap::Core::igDataList *)_invTransBlendMat0.p)->setCapacity(depth, 64);
        break;
    case 11:
        if (depth >= _blendMat1->_count) ((Gap::Core::igDataList *)_blendMat1.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat1->_count) ((Gap::Core::igDataList *)_invTransBlendMat1.p)->setCapacity(depth, 64);
        break;
    case 12:
        if (depth >= _blendMat2->_count) ((Gap::Core::igDataList *)_blendMat2.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat2->_count) ((Gap::Core::igDataList *)_invTransBlendMat2.p)->setCapacity(depth, 64);
        break;
    case 13:
        if (depth >= _blendMat3->_count) ((Gap::Core::igDataList *)_blendMat3.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat3->_count) ((Gap::Core::igDataList *)_invTransBlendMat3.p)->setCapacity(depth, 64);
        break;
    }
}

int igPsx2VisualContext::getStackSize(IG_GFX_MATRIX_STACK which) const {
    struct S_172550 *arg0 = (struct S_172550 *)this;
    switch (which) {
    case 0: return arg0->f972->f12;
    case 1: return arg0->f976->f12;
    case 2: return arg0->f980->f12;
    case 10: return arg0->f988->f12;
    case 11: return arg0->f992->f12;
    case 12: return arg0->f996->f12;
    case 13: return arg0->f1000->f12;
    default: return 0;
    }
}
}
}

static inline int count_of_172600(const L_172600 *list) { return list->count; }

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::pushMatrix(IG_GFX_MATRIX_STACK which) {
    S_172600 *arg0 = (S_172600 *)this;
    switch (which) {
    case 0:
        PUSH(l972);
        break;
    case 1:
        PUSH(l976);
        break;
    case 2:
        PUSH(l980);
        break;
    case 10:
        PUSH(l988);
        break;
    case 11:
        PUSH(l992);
        break;
    case 12:
        PUSH(l996);
        break;
    case 13:
        PUSH(l1000);
        break;
    }
}

void igPsx2VisualContext::popMatrix(IG_GFX_MATRIX_STACK which) {
    Obj_172910 *o = (Obj_172910 *)this;
    Mat_172910 m0, m1, m2, m3, m4;
    switch (which) {
    case 0:
        o->s[0]->count--;
        p2SetMatrix(3, (const float *)(o->s[0]->data + ((o->s[0]->count - 1) << 6)));
        break;
    case 1:
        o->s[1]->count--;
        p2SetMatrix(0, (const float *)(o->s[1]->data + ((o->s[1]->count - 1) << 6)));
        break;
    case 2: {
        Stk *s = o->s[2];
        s->count--;
        igMatrix44f_Copy((float *)&m0, (float *)(s->data + (s->count << 6)));
        p2SetMatrix(4, (const float *)(o->s[2]->data + ((o->s[2]->count - 1) << 6)));
        break; }
    case 10: { Stk *s = o->s[4]; s->count--; igMatrix44f_Copy((float *)&m1, (float *)(s->data + (s->count << 6))); break; }
    case 11: { Stk *s = o->s[5]; s->count--; igMatrix44f_Copy((float *)&m2, (float *)(s->data + (s->count << 6))); break; }
    case 12: { Stk *s = o->s[6]; s->count--; igMatrix44f_Copy((float *)&m3, (float *)(s->data + (s->count << 6))); break; }
    case 13: { Stk *s = o->s[7]; s->count--; igMatrix44f_Copy((float *)&m4, (float *)(s->data + (s->count << 6))); break; }
    }
}
}
}

static inline int n_of(const St_172b00 *list) { return list->n; }

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMatrix(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    char sp110[64];
    char spD0[64];
    char sp90[64];
    char sp50[64];
    St_172b00 *t;
    switch (which) {
    case 0:
        SET((St_172b00 *)_projMat.p, mat.m)
        t = (St_172b00 *)_projMat.p;
        p2SetMatrix(3, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 1:
        SET((St_172b00 *)_mvMat.p, mat.m)
        t = (St_172b00 *)_mvMat.p;
        p2SetMatrix(0, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 2:
        SET((St_172b00 *)_texMat.p, mat.m)
        t = (St_172b00 *)_texMat.p;
        p2SetMatrix(4, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 10:
        igMatrix44f_SetIdentity((float *)sp110);
        SETB((St_172b00 *)_blendMat0.p, mat.m)
        igMatrix44f_Invert((float *)sp110, mat.m);
        FUN_001903d0((float *)sp110);
        SET((St_172b00 *)_invTransBlendMat0.p, sp110)
        break;
    case 11:
        igMatrix44f_SetIdentity((float *)spD0);
        SETB((St_172b00 *)_blendMat1.p, mat.m)
        igMatrix44f_Invert((float *)spD0, mat.m);
        FUN_001903d0((float *)spD0);
        SET((St_172b00 *)_invTransBlendMat1.p, spD0)
        break;
    case 12:
        igMatrix44f_SetIdentity((float *)sp90);
        SETB((St_172b00 *)_blendMat2.p, mat.m)
        igMatrix44f_Invert((float *)sp90, mat.m);
        FUN_001903d0((float *)sp90);
        SET((St_172b00 *)_invTransBlendMat2.p, sp90)
        break;
    case 13:
        igMatrix44f_SetIdentity((float *)sp50);
        SETB((St_172b00 *)_blendMat3.p, mat.m)
        igMatrix44f_Invert((float *)sp50, mat.m);
        FUN_001903d0((float *)sp50);
        SET((St_172b00 *)_invTransBlendMat3.p, sp50)
        break;
    }
}

void igPsx2VisualContext::pushPreMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    char inverse0[64];
    char inverse1[64];
    char inverse2[64];
    char inverse3[64];
    St_172b00 *t;
    switch (which) {
    case 0:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_projMat, mat.m);
        t = (St_172b00 *)_projMat.p;
        p2SetMatrix(3, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 1:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_mvMat, mat.m);
        t = (St_172b00 *)_mvMat.p;
        p2SetMatrix(0, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 2:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_texMat, mat.m);
        t = (St_172b00 *)_texMat.p;
        p2SetMatrix(4, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 10:
        igMatrix44f_SetIdentity((float *)inverse0);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat0, mat.m);
        igMatrix44f_Invert((float *)inverse0, mat.m);
        FUN_001903d0((float *)inverse0);
        SET((St_172b00 *)_invTransBlendMat0.p, inverse0)
        break;
    case 11:
        igMatrix44f_SetIdentity((float *)inverse1);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat1, mat.m);
        igMatrix44f_Invert((float *)inverse1, mat.m);
        FUN_001903d0((float *)inverse1);
        SET((St_172b00 *)_invTransBlendMat1.p, inverse1)
        break;
    case 12:
        igMatrix44f_SetIdentity((float *)inverse2);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat2, mat.m);
        igMatrix44f_Invert((float *)inverse2, mat.m);
        FUN_001903d0((float *)inverse2);
        SET((St_172b00 *)_invTransBlendMat2.p, inverse2)
        break;
    case 13:
        igMatrix44f_SetIdentity((float *)inverse3);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat3, mat.m);
        igMatrix44f_Invert((float *)inverse3, mat.m);
        FUN_001903d0((float *)inverse3);
        SET((St_172b00 *)_invTransBlendMat3.p, inverse3)
        break;
    }
}

void igPsx2VisualContext::pushPostMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    char inverse0[64];
    char inverse1[64];
    char inverse2[64];
    char inverse3[64];
    St_172b00 *t;
    switch (which) {
    case 0:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_projMat, mat.m);
        t = (St_172b00 *)_projMat.p;
        p2SetMatrix(3, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 1:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_mvMat, mat.m);
        t = (St_172b00 *)_mvMat.p;
        p2SetMatrix(0, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 2:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_texMat, mat.m);
        t = (St_172b00 *)_texMat.p;
        p2SetMatrix(4, (const float *)(t->data + ((t->n - 1) << 6)));
        break;
    case 10:
        igMatrix44f_SetIdentity((float *)inverse0);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat0, mat.m);
        igMatrix44f_Invert((float *)inverse0, mat.m);
        FUN_001903d0((float *)inverse0);
        SET((St_172b00 *)_invTransBlendMat0.p, inverse0)
        break;
    case 11:
        igMatrix44f_SetIdentity((float *)inverse1);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat1, mat.m);
        igMatrix44f_Invert((float *)inverse1, mat.m);
        FUN_001903d0((float *)inverse1);
        SET((St_172b00 *)_invTransBlendMat1.p, inverse1)
        break;
    case 12:
        igMatrix44f_SetIdentity((float *)inverse2);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat2, mat.m);
        igMatrix44f_Invert((float *)inverse2, mat.m);
        FUN_001903d0((float *)inverse2);
        SET((St_172b00 *)_invTransBlendMat2.p, inverse2)
        break;
    case 13:
        igMatrix44f_SetIdentity((float *)inverse3);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat3, mat.m);
        igMatrix44f_Invert((float *)inverse3, mat.m);
        FUN_001903d0((float *)inverse3);
        SET((St_172b00 *)_invTransBlendMat3.p, inverse3)
        break;
    }
}
}
}

/* The matrix on top of a matrix stack, which a multiply hands back to the context's setMatrix. */
static inline igMatrix44f &stackTop(igMatrixStack *stack) {
    return *(igMatrix44f *)(stack->_data + ((stack->_count - 1) << 6));
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::preMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    switch (which) {
    case 0:
        igMatrixStack_PreMultiply((igMatrixStack *)_projMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_projMat));
        break;
    case 1:
        igMatrixStack_PreMultiply((igMatrixStack *)_mvMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_mvMat));
        break;
    case 2:
        igMatrixStack_PreMultiply((igMatrixStack *)_texMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_texMat));
        break;
    case 10:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat0, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat0));
        break;
    case 11:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat1, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat1));
        break;
    case 12:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat2, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat2));
        break;
    case 13:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat3, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat3));
        break;
    }
}

void igPsx2VisualContext::postMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    switch (which) {
    case 0:
        igMatrixStack_PostMultiply((igMatrixStack *)_projMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_projMat));
        break;
    case 1:
        igMatrixStack_PostMultiply((igMatrixStack *)_mvMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_mvMat));
        break;
    case 2:
        igMatrixStack_PostMultiply((igMatrixStack *)_texMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_texMat));
        break;
    case 10:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat0, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat0));
        break;
    case 11:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat1, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat1));
        break;
    case 12:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat2, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat2));
        break;
    case 13:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat3, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat3));
        break;
    }
}

void igPsx2VisualContext::getMatrix(IG_GFX_MATRIX_STACK which, igMatrix44f &mat) const {
    O_173d60 *o = (O_173d60 *)this;
    St_173d60 *s;
    switch (which) {
    case 0:  s = o->s972; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 1:  s = o->s976; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 2:  s = o->s980; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 10: s = o->s988; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 11: s = o->s992; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 12: s = o->s996; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 13: s = o->s1000; igMatrix44f_Copy(mat.m, (float *)(s->data + ((s->n - 1) << 6))); break;
    }
}

void igPsx2VisualContext::setMatrixPsx2(int stack, const float *matrix) {
    igTDataList<igMatrix44f> *texGen;
    int n;
    switch (stack) {
    case 14:
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        n = texGen->getCount();
        if (n == 0) {
            if (n < texGen->_capacity) texGen->_count = texGen->_count + 1;
            else ((Gap::Core::igDataList *)texGen)->resizeAndSetCount(n + 1, 64);
            igMatrix44f_Copy(texGen->_data[n].m, matrix);
        } else {
            igMatrix44f_Copy(texGen->_data[texGen->_count - 1].m, matrix);
        }
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        p2SetMatrix(5, texGen->_data[texGen->_count - 1].m);
        break;
    default:
        ((Obj_173ed0 *)this)->v203(stack, (void *)matrix);
        break;
    }
}

void igPsx2VisualContext::getMatrixPsx2(int stack, float *matrix) {
    igTDataList<igMatrix44f> *texGen;
    switch (stack) {
    case 14:
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        igMatrix44f_Copy(matrix, texGen->_data[texGen->_count - 1].m);
        break;
    default:
        ((A_173fd0 *)this)->vX(stack, (int)matrix);
        break;
    }
}

void igPsx2VisualContext::setTextureMatrixState(int stage, bool enable) {
    struct O_174030 *arg0 = (struct O_174030 *)this;
    if (arg0->f == enable) {
        DAT_0056091c[0] += 1;
    }
    arg0->f = enable;
    if (enable) {
        p2EnableCapability(0xD);
        return;
    }
    p2DisableCapability(0xD);
}
}
}

void FUN_00174090(void *arg0) {
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(0), (int)(4));
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(1), (int)(4));
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(2), (int)(4));
    ((DW4VC_740_6 *)(((char *)(arg0) + 0)))->vX(0, 0, *(int *)((char *)(arg0) + 908), *(int *)((char *)(arg0) + 912), 0.0f, 1.0f);
    ((DW4VC_864_1 *)(((char *)(arg0) + 0)))->vX((int)(-1));
    ((Gap::Gfx::igPsx2VisualContext *)arg0)->setMatrixOptimizationState(1);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::resetToDefault(int which) {
    void *a0 = (void *)this;
    float m[16];
    struct V4 { float x, y, z; int w; } v;
    VC104 *o;
    igVisualContext_ResetToDefault((igVisualContext_166400 *)a0, which);
    if (which & 4) {
        FUN_0017c880((::igPsx2VisualContext *)a0, ((VC596 *)a0)->vX(0), 1);
    }
    if (which & 0x40) {
        o = (VC104 *)((VC104 *)a0)->vX("igDecalExt");
        if (o != 0) {
            ((VC120 *)o)->vX(0);
        }
    }
    if (which & 2) {
        FUN_001720d0((O_1720d0 *)a0, 0);
    }
    if (which & 0x20) {
        FUN_00175090((S0_175090 *)a0, 2);
    }
    igMatrix44f_SetIdentity(m);
    igMatrix44f_SetIdentity(m);
    ((igPsx2VisualContext *)a0)->setMatrixPsx2(14, m);
    FUN_0016cc50((int)a0, 0);
    v.w = 0x3F800000;
    v.x = 0.501960754f;
    v.y = 0.501960754f;
    v.z = 0.501960754f;
    FUN_00175510((S_175510 *)a0, (float *)&v);
    FUN_001754b0((S1754 *)a0, 1);
    FUN_001755e0((S0_1755e0 *)a0, 1);
    FUN_001757c0((::igPsx2VisualContext *)a0, 0);
    p2DisableCapability(23);
    FUN_00175640((S_175640 *)a0, 0);
    FUN_00175670((O_175670 *)a0, 0);
    ((igPsx2VisualContext *)a0)->setTextureMatrixProjectiveState(0, 0);
    FUN_00175790((S_175790 *)a0, 0x71603524 | (0x40712635LL << 32));
    FUN_00174950(a0, 0);
    FUN_00169be0(a0, 1);
    ((VC696 *)a0)->vX();
}

void igPsx2VisualContext::setNormalizeNormalsState(bool bEnable) {
    S0_174300 *arg0 = (S0_174300 *)this;
    int temp_v1;

    temp_v1 = bEnable & 0xFF;
    if (arg0->f55C == temp_v1) {
        DAT_00560920[0] += 1;
    }
    arg0->f55C = bEnable;
    if (temp_v1 == 1) {
        p2EnableCapability(0x12);
        return;
    }
    p2DisableCapability(0x12);
}

bool igPsx2VisualContext::getNormalizeNormalsState() const {
    return _bNormalizeNormalsState;
}

void igPsx2VisualContext::setVertexBlendingState(bool enable) {
    S_174370 *arg0 = (S_174370 *)this;

    if (g_igPsx2DisableExt_ext6Enabled != 0) {
        enable = false;
    }
    if (arg0->f == enable) {
        DAT_005608a8[0] += 1;
    }
    arg0->f = enable;
}

bool igPsx2VisualContext::getVertexBlendingState() const {
    return _bVertexBlendingEnabled;
}

void igPsx2VisualContext::setBlendingState(bool enable) {
    struct S_1743c0 *arg0 = (struct S_1743c0 *)this;
    if (g_igPsx2DisableExt_ext2Enabled != 0) {
        enable = 0;
    }
    if (arg0->f1032 == (enable & 0xFF)) {
        DAT_00560924[0] += 1;
    }
    arg0->f1032 = enable;
    if (arg0->f1032 != 0) {
        p2EnableCapability(2);
        return;
    }
    p2DisableCapability(2);
}

bool igPsx2VisualContext::getBlendingState() const {
    return _bBlendingEnabled;
}

void igPsx2VisualContext::setBlendingSource(IG_GFX_BLENDING_FUNCTION srcMode) {
    int *arg0 = (int *)this;
    if (arg0[259] == srcMode) {
        DAT_00560928[0] += 1;
    }
    arg0[259] = srcMode;
    FUN_00174640((int)arg0, 0);
}

void igPsx2VisualContext::setBlendingDestination(IG_GFX_BLENDING_FUNCTION destMode) {
    struct S174470 *arg0 = (struct S174470 *)this;
    if (arg0->f == destMode) {
        DAT_00560968[0] += 1;
    }
    arg0->f = destMode;
    FUN_00174640((int)arg0, 0);
}

IG_GFX_BLENDING_FUNCTION igPsx2VisualContext::getBlendingSource() const {
    return _blendSrcMode[0];
}

IG_GFX_BLENDING_FUNCTION igPsx2VisualContext::getBlendingDestination() const {
    return _blendDestMode[0];
}

void igPsx2VisualContext::setBlendingSourceDestination(IG_GFX_BLENDING_FUNCTION srcMode, IG_GFX_BLENDING_FUNCTION destMode) {
    S_1744c0 *arg0 = (S_1744c0 *)this;
    if (arg0->f1036 == srcMode) {
        DAT_00560928[0] += 1;
    }
    if (arg0->f1100 == destMode) {
        DAT_00560968[0] += 1;
    }
    arg0->f1036 = srcMode;
    arg0->f1100 = destMode;
    FUN_00174640((int)arg0, 0);
}
}
}

void FUN_00174510(igPsx2VisualContext *self, IG_GFX_BLENDING_FUNCTION source, IG_GFX_BLENDING_FUNCTION destination, unsigned char blendConstant, int stage) {
    int n;
    int j;
    int off;
    char *p;
    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    off = n * 4;
    if (n < 8) {
        if (self->_blendSrcMode[n] == source) {
            DAT_00560928[n] += 1;
        }
        if (self->_blendDestMode[n] == destination) {
            DAT_00560968[n] += 1;
        }
        if (self->_blendConst[n] == (blendConstant & 0xFF)) {
            DAT_00560948[n] += 1;
        }
    }
    off = n * 4;
    p = (char *)(off + (int)self);
    *(int *)(p + 1036) = source;
    *(int *)(p + 1100) = destination;
    *(int *)(p + 1164) = blendConstant & 0xFF;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram = n;
    p2CurrentGsRegisters = (p2GsRegisterSet *)((int *)p2GsRegisterSets + j * 112);
    FUN_00174640((int)self, n);
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = p2GsRegisterSets;
}

void FUN_00174640(int arg0, int arg1) {
    struct E_174640 *tab;
    int var_a0 = 2, var_a1 = 2, var_a2 = 2, var_a3 = 0, var_a4 = -1;
    int base = (arg1 << 2) + arg0;
    int *temp_a5 = (int *)base;
    struct E_174640 *ent;

    tab = (struct E_174640 *)DAT_0048ac00[temp_a5[259]];
    if (tab != 0) {
        ent = tab + temp_a5[275];
        var_a4 = ent->e;
        var_a0 = ent->a;
        var_a1 = ent->b;
        var_a2 = ent->c;
        var_a3 = ent->d;
        if (var_a4 == -2) {
            var_a4 = temp_a5[291];
        }
    }
    if (var_a4 == -1) {
        var_a0 = 2;
        var_a3 = 0;
        var_a1 = 2;
        var_a2 = 2;
        var_a4 = 0x80;
    }
    p2SetBlendEquation(var_a0, var_a1, var_a2, var_a3, var_a4);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setAlphaTestState(bool enb)
{
    if (g_igPsx2DisableExt_ext7Enabled != 0)
        enb = 0;
    if (_alphaEnable == enb)
        DAT_0056098c += 1;
    _alphaEnable = enb;
    if (enb) {
        p2EnableCapability(3);
        FUN_001747f0((S_1747f0 *)this);
    } else {
        p2DisableCapability(3);
    }
}

bool igPsx2VisualContext::getAlphaTestState() const {
    return _alphaEnable;
}

void igPsx2VisualContext::setAlphaFunc(IG_GFX_ALPHA_FUNCTION afunc) {
    int *arg0 = (int *)this;
    if (arg0[256] == afunc) {
        DAT_00560998[0] += 1;
    }
    arg0[256] = afunc;
    FUN_001747f0((S_1747f0 *)arg0);
}

IG_GFX_ALPHA_FUNCTION igPsx2VisualContext::getAlphaFunc() const {
    return _alphaFunc;
}

void igPsx2VisualContext::setAlphaRefValue(float val) {
    struct S_1747b0 *arg0 = (struct S_1747b0 *)this;
    if (arg0->f == val) {
        DAT_0056099c[0] += 1;
    }
    arg0->f = val;
    FUN_001747f0((S_1747f0 *)arg0);
}

float igPsx2VisualContext::getAlphaRefValue() const {
    return _alphaVal;
}
}
}

void FUN_001747f0(S_1747f0 *s) { if (s->b == 1) { int a = (int)(128.0f * (float)s->f); p2SetAlphaTest(DAT_0048a500[s->i], a, 0); } }

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMatrixOptimizationState(bool enable) {
    int state;
    if (g_igPsx2DisableExt_ext11Enabled != 0) {
        enable = 0;
    }
    state = enable & 0xFF;
    if (_matrixOptimizationEnable == state) {
        DAT_005609a0[0] += 1;
    }
    _matrixOptimizationEnable = enable;
    if (state == 1) {
        p2DisableCapability(0x13);
        return;
    }
    p2EnableCapability(0x13);
}

bool igPsx2VisualContext::getMatrixOptimizationState()
{
    return *(bool *)&_matrixOptimizationEnable;
}

void igPsx2VisualContext::setViewportClippingState(bool enable) {
    O_1748d0 *o = (O_1748d0 *)this;
    if (g_igPsx2DisableExt_ext8Enabled != 0) enable = 0;
    if (o->v == enable) DAT_005608b8[0] += 1;
    o->v = enable;
    if (enable == 1) p2EnableCapability(6);
    else p2DisableCapability(6);
}

bool igPsx2VisualContext::getViewportClippingState() const {
    return _clippingEnable;
}
}
}

void FUN_00174950(void *d0, int arg1) {
    if (arg1 == 1) {
        p2EnableCapability(0x19);
        return;
    }
    p2DisableCapability(0x19);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setColorMask(bool r, bool g, bool b, bool a) {
    *(char *)((char *)((::igPsx2VisualContext *)this) + 1252) = r;
    *(char *)((char *)((::igPsx2VisualContext *)this) + 1253) = g;
    *(char *)((char *)((::igPsx2VisualContext *)this) + 1254) = b;
    *(char *)((char *)((::igPsx2VisualContext *)this) + 1255) = a;
    p2SetColourMask(r, g, b, a);
}

void igPsx2VisualContext::getColorMask(bool &r, bool &g, bool &b, bool &a) const {
    r = _colorMaskR;
    g = _colorMaskG;
    b = _colorMaskB;
    a = _colorMaskA;
}

void igPsx2VisualContext::setShadingMode(IG_GFX_SHADING_MODE mode) {
    S_1749f0 *arg0 = (S_1749f0 *)this;
    if (arg0->f == mode) {
        DAT_005608b0[0] += 1;
    }
    arg0->f = mode;
    if (DAT_0048a530[mode] == 1) {
        p2DisableCapability(0x11);
        return;
    }
    p2EnableCapability(0x11);
}

IG_GFX_SHADING_MODE igPsx2VisualContext::getShadingMode() const {
    return _shadingMode;
}

void igPsx2VisualContext::setCullFaceState(bool enable) {
    struct S_174a70 *arg0 = (struct S_174a70 *)this;

    if (g_igPsx2DisableExt_ext9Enabled != 0) {
        enable = false;
    }
    if (arg0->f1268 == enable) {
        DAT_005609a4[0] += 1;
    }
    arg0->f1268 = enable;
    if (enable) {
        p2EnableCapability(DAT_0048a538[arg0->f1272]);
        return;
    }
    p2DisableCapability(DAT_0048a538[arg0->f1272]);
}

bool igPsx2VisualContext::getCullFaceState() const {
    return _cullFaceEnable;
}

void igPsx2VisualContext::setCullFaceMode(IG_GFX_CULL_FACE_MODE m) {
    int temp_a0;

    temp_a0 = _cullFaceMode;
    if ((temp_a0 != m) && (_cullFaceEnable != 0)) {
        p2DisableCapability(DAT_0048a538[temp_a0]);
        p2EnableCapability(DAT_0048a538[m]);
    }
    if (_cullFaceMode == m) {
        DAT_005609a8[0] += 1;
    }
    _cullFaceMode = m;
}

IG_GFX_CULL_FACE_MODE igPsx2VisualContext::getCullFaceMode() const {
    return _cullFaceMode;
}

void igPsx2VisualContext::setDepthTestState(bool enable) {
    struct S_174bc0 *s = (struct S_174bc0 *)this;
    if (g_igPsx2DisableExt_ext5Enabled != 0) {
        enable = false;
    }
    if (s->f == enable) {
        DAT_005609ac[0] += 1;
    }
    if (s->f != enable) {
        s->f = enable;
        if (enable) {
            p2EnableCapability(0);
            FUN_00174db0(s);
            return;
        }
        p2DisableCapability(0);
    }
}

bool igPsx2VisualContext::getDepthTestState() const {
    return _depthTestEnable;
}

void igPsx2VisualContext::setDepthTestFunction(int func) {
    S_174c50 *arg0 = (S_174c50 *)this;
    if (arg0->f1280 == func) {
        DAT_005609b0[0] += 1;
    }
    arg0->f1280 = func;
    FUN_00174db0(arg0);
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2147483648.0f * arg0->f892);
    } else {
        arg0->f900 = (unsigned)(2147483648.0f * (1.0f - arg0->f892));
    }
}

int igPsx2VisualContext::getDepthTestFunction() const {
    return _depthTestFunc;
}

void igPsx2VisualContext::setDepthWriteState(bool enable) {
    struct S_174d70 *arg0 = (struct S_174d70 *)this;
    if (arg0->b == (enable & 0xFF)) {
        DAT_005609b4[0] += 1;
    }
    arg0->b = enable;
    FUN_00174db0(arg0);
}

bool igPsx2VisualContext::getDepthWriteState() const {
    return _bDepthWrite;
}
}
}

void FUN_00174db0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 1276) == 1) {
        p2SetDepthFunction(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 0);
        return;
    }
    p2SetDepthFunction(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 1);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setStencilState(bool enable) {
    S_174e20 *arg0 = (S_174e20 *)this;
    if (arg0->f1260 == enable) {
        DAT_005609b8[0] += 1;
    }
    arg0->f1260 = enable;
    if (enable && (arg0->f1288 != 7)) {
        p2EnableCapability(4);
    } else {
        p2DisableCapability(4);
    }
}

bool igPsx2VisualContext::getStencilState() const {
    return _stencilState != 0;
}

void igPsx2VisualContext::setStencilRefVal(unsigned int stenRef) {
    int *arg0 = (int *)this;
    if (arg0[316] == stenRef) {
        DAT_005609bc[0] += 1;
    }
    arg0[316] = stenRef;
    p2SetDestinationAlphaMode(arg0[316] & 1);
}

unsigned igPsx2VisualContext::getStencilRefVal() const {
    return _stencilRefVal;
}

void igPsx2VisualContext::setStencilFunc(IG_GFX_STENCIL_FUNCTION stenFunc) {
    switch (stenFunc) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if ((_stencilState != 0) && (p2IsCapabilityEnabled(4) == 0)) {
            p2EnableCapability(4);
        }
        break;
    case 7:
        p2DisableCapability(4);
        break;
    }
    if (_stencilFunc == stenFunc) {
        DAT_005609c0[0] += 1;
    }
    _stencilFunc = stenFunc;
}

IG_GFX_STENCIL_FUNCTION igPsx2VisualContext::getStencilFunc() const {
    return _stencilFunc;
}

void igPsx2VisualContext::setStencilOps(IG_GFX_STENCIL_OPERATION sfail, IG_GFX_STENCIL_OPERATION zpass, IG_GFX_STENCIL_OPERATION zfail) {
}

void igPsx2VisualContext::getStencilOps(IG_GFX_STENCIL_OPERATION &sfail, IG_GFX_STENCIL_OPERATION &zpass, IG_GFX_STENCIL_OPERATION &zfail) const {

}

void igPsx2VisualContext::setStencilReadMask(unsigned int stenRef) {
}

unsigned igPsx2VisualContext::getStencilReadMask() const {
    return -1;
}

void igPsx2VisualContext::setStencilWriteMask(unsigned int stenRef) {
}

unsigned igPsx2VisualContext::getStencilWriteMask() const {
    return -1;
}

void igPsx2VisualContext::setRenderMode(IG_GFX_RENDER_MODE mode) {
    S_175000 *arg0 = (S_175000 *)this;
    if (arg0->f1292 == mode) {
        DAT_005609c4[0] += 1;
    }
    arg0->f1292 = mode;
    if (mode == 0) {
        p2SetPolygonMode(2);
    } else if (mode == 1) {
        p2SetPolygonMode(1);
    } else if (mode == 2) {
        p2SetPolygonMode(0);
    }
}

IG_GFX_RENDER_MODE igPsx2VisualContext::getRenderMode() const {
    return _renderMode;
}
}
}

void FUN_00175090(S0_175090 *arg0, int arg1) {
    if (arg0->f510 == arg1) {
        DAT_005609c8[0] += 1;
    }
    arg0->f510 = arg1;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setFogState(bool enable) {
    struct S_1750c0 *arg0 = (struct S_1750c0 *)this;
    if (g_igPsx2DisableExt_ext4Enabled != 0) {
        enable = false;
    }
    if (arg0->mode == enable) {
        DAT_005609cc[0] += 1;
    }
    arg0->mode = enable;
    if (enable) {
        p2EnableCapability(7);
        return;
    }
    p2DisableCapability(7);
}

bool igPsx2VisualContext::getFogState() const {
    return _fogEnable;
}

void igPsx2VisualContext::setFogDensity(float density) {
    struct S_175140 *arg0 = (struct S_175140 *)this;
    int i;
    if (arg0->f1304 == density) {
        DAT_005609d0[0] += 1;
    }
    arg0->f1304 = density;
    i = arg0->f1308;
    p2SetFog(DAT_0048a560[i], i, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogDensity() const {
    return _fogDensity;
}

void igPsx2VisualContext::setFogMode(IG_GFX_FOG_MODE mode) {
    struct S1304 *arg0 = (struct S1304 *)this;
    if (arg0->f1308 == mode) {
        DAT_005609d4[0] += 1;
    }
    arg0->f1308 = mode;
    p2SetFog(DAT_0048a560[arg0->f1308], arg0->f1308, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

IG_GFX_FOG_MODE igPsx2VisualContext::getFogMode() const {
    return _fogMode;
}

void igPsx2VisualContext::setFogColor(const igVec4f &color) {
    if (_fogColor == color) {
        DAT_005609d8[0] += 1;
    }
    _fogColor = color;
    p2SetFogColour((color)[0], (color)[1], (color)[2]);
}

void igPsx2VisualContext::getFogColor(igVec4f &color) const {
    color.vec[0] = (float) _fogColor[0];
    color.vec[1] = (float) *(float *)((char *)((::igPsx2VisualContext *)this) + 1316);
    color.vec[2] = (float) *(float *)((char *)((::igPsx2VisualContext *)this) + 1320);
    color.vec[3] = (float) *(float *)((char *)((::igPsx2VisualContext *)this) + 1324);
}

void igPsx2VisualContext::setFogNear(float fogNear) {
    struct S_175310 *arg0 = (struct S_175310 *)this;
    int temp_a1;

    if (arg0->f1328 == fogNear) {
        DAT_005609dc[0] += 1;
    }
    arg0->f1328 = fogNear;
    temp_a1 = arg0->i1308;
    p2SetFog(*(int *)((char *)&DAT_0048a560[0] + (temp_a1 * 4)), temp_a1, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogNear() const {
    return _fogNear;
}

void igPsx2VisualContext::setFogFar(float fogFar) {
    int temp_a1;

    if (_fogFar == fogFar) {
        DAT_005609e0[0] += 1;
    }
    _fogFar = fogFar;
    temp_a1 = _fogMode;
    p2SetFog(DAT_0048a560[temp_a1], temp_a1, _fogNear, _fogFar, _fogDensity, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogFar() const {
    return _fogFar;
}

igResult igPsx2VisualContext::setVideoMode(igVideoFormat &pFormat) {
    if (_iContextOpen == 1) {
        return g_resultFailure;
    } else if (&pFormat == 0) {
        return g_resultFailure;
    } else {
        _videoMode._bFullScreen = pFormat._bFullScreen;
        _videoMode._bInterlaced = pFormat._bInterlaced;
        _videoMode._iFieldCount = pFormat._iFieldCount;
        _videoMode._iFieldSize = pFormat._iFieldSize;
        _videoMode._fRefreshRate = pFormat._fRefreshRate;
        _videoMode._iSwapInterval = pFormat._iSwapInterval;
        _videoMode._iVideoType = pFormat._iVideoType;
        return g_resultSuccess;
    }
}

void igPsx2VisualContext::getVideoMode(igVideoFormat &pMode) {
    igVideoFormat *videoMode = &_videoMode;
    pMode._bFullScreen = videoMode->_bFullScreen;
    pMode._bInterlaced = videoMode->_bInterlaced;
    pMode._iFieldCount = videoMode->_iFieldCount;
    pMode._iFieldSize = videoMode->_iFieldSize;
    pMode._fRefreshRate = videoMode->_fRefreshRate;
    pMode._iSwapInterval = videoMode->_iSwapInterval;
    pMode._iVideoType = videoMode->_iVideoType;
}
}
}

int FUN_001754b0(struct S1754 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_005609e4[0] += 1;
    }
    arg0->f = arg1;
    return p2SetColorScaler(DAT_0048a520[arg1], (float *)((char *)arg0 + 0x598)) != 0;
}

void FUN_00175510(struct S_175510 *arg0, float *arg1) {
    int r = 1;
    if (arg0->v[0] != arg1[0]) r = 0;
    if (r != 0) { r = 1; if (arg0->v[1] != arg1[1]) r = 0; }
    if (r != 0) { r = 1; if (arg0->v[2] != arg1[2]) r = 0; }
    if (r != 0) { r = 1; if (arg0->v[3] != arg1[3]) r = 0; }
    if (r != 0) {
        DAT_005609e8[0] += 1;
    }
    arg0->v[0] = arg1[0];
    arg0->v[1] = arg1[1];
    arg0->v[2] = arg1[2];
    arg0->v[3] = arg1[3];
    p2SetColorScaler(DAT_0048a520[arg0->idx], arg0->v);
}

void FUN_001755e0(S0_1755e0 *arg0, int arg1) {
    if (arg0->f1449 == (arg1 & 0xFF)) {
        DAT_005609ec[0] += 1;
    }
    arg0->f1449 = arg1;
    if (arg1 != 0) {
        p2SetColourClamp(1);
        return;
    }
    p2SetColourClamp(0);
}

void FUN_00175640(struct S_175640 *arg0, int arg1) {
    if (arg0->v == (unsigned char)arg1) {
        DAT_005609f0[0] += 1;
    }
    arg0->v = arg1;
    p2SetPixelAlphaBlend(arg1);
}

void FUN_00175670(struct O_175670 *arg0, int arg1) {
    if (arg0->f == (unsigned char)arg1) {
        DAT_005609f4[0] += 1;
    }
    arg0->f = arg1;
    p2SetFrameBufferAlpha(arg1);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setPixelPipelineMode(IG_GFX_PIXEL_PIPELINE_MODE mode) {
    if (_pixelPipelineMode == mode) {
        DAT_005609f8++;
    }
    _pixelPipelineMode = mode;
    if (_bMultiPassNum > 1 && _pixelPipelineMode == 3) {
        if (p2IsCapabilityEnabled(23) == 0) {
            p2EnableCapability(23);
        }
    } else {
        if (p2IsCapabilityEnabled(23) != 0) {
            p2DisableCapability(23);
        }
    }
}

void igPsx2VisualContext::setDitherState(bool enable) {
    if (_ditherState == enable) {
        DAT_005609fc[0] += 1;
    }
    _ditherState = enable;
    if (enable) {
        p2EnableCapability(0xB);
    } else {
        p2DisableCapability(0xB);
    }
}
}
}

void FUN_00175790(struct S_175790 *arg0, long long arg1) {
    if (arg0->v == arg1) {
        DAT_00560a00[0] += 1;
    }
    arg0->v = arg1;
    p2SetDitherMatrix(arg1);
}

void FUN_001757c0(igPsx2VisualContext *arg0, int arg1) {
    if (arg0->_bMultiPassNum == arg1) {
        DAT_00560a04[0] += 1;
    }
    arg0->_bMultiPassNum = arg1;
    p2SetPassCount(arg0->_bMultiPassNum);
    if (arg0->_bMultiPassNum > 1 && arg0->_pixelPipelineMode == 3) {
        if (p2IsCapabilityEnabled(0x17) == 0) {
            p2EnableCapability(0x17);
        }
    } else if (p2IsCapabilityEnabled(0x17) != 0) {
        p2DisableCapability(0x17);
    }
}

