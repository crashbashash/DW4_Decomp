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
            s1 = (char *)StringPool_Intern(g_stringPool[0], 0);
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

void Gap__Gfx__igPsx2VisualContext__vfunc_75(S0_1706d0 *arg0, int arg1) {
    if (arg0->f1340 == (arg1 & 0xFF)) {
        DAT_00560848[0] += 1;
    }
    if (GPR_00554b44 != 0) {
        arg1 = 0;
    }
    arg0->f1340 = arg1;
    if (arg0->f1340 == 1) {
        p2EnableCapability(8, arg1);
        return;
    }
    p2DisableCapability(8, arg1);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_76(void *arg0) {
    return *(int *)((char *)(arg0) + 1340);
}

unsigned short Gap__Gfx__igPsx2VisualContext__vfunc_77(Obj_170750 *arg0, int arg1) {
    Pool *p;
    int i;
    unsigned short idx;
    It_170750 *it;
    int v;
    p = arg0->f1336;
    if (p->f4 <= 0) {
        p->f16 = (char *)thunk_Memory_ReallocateAligned(p->f16, (p->f0 + 4) * 0xA0, 0x10);
        memset(p->f16 + p->f0 * 0xA0, 0, 0x280);
        if (p->f2 < 4) {
            O_170750 *o = (O_170750 *)Memory_FindBufferOwner(p);
            p->f12 = (short *)o->vX((int)p->f12, 8);
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
    it = (It_170750 *)(arg0->f1336->f16 + idx * 0xA0);
    FUN_00170210(it);
    it->f152 = arg1;
    switch (arg1) {
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

void Gap__Gfx__igPsx2VisualContext__vfunc_78(Obj_1708e0 *arg0, int arg1) {
    E_1708e0 *e = arg0->f1336->f16 + arg1;
    Lst *l;
    if (e != 0 && e != 0) {
        if (e->f148 != 0) {
            arg0->vA(arg1, 0);
        }
        l = arg0->f1336;
        if (arg1 < l->f0 && arg1 >= 0) {
            if (l->f4 >= l->f2) {
                Buf *b = (Buf *)Memory_FindBufferOwner(l);
                l->f2 = l->f2 + 8;
                l->f12 = (short *)b->vB(l->f12, l->f2 * 2);
            }
            l->f12[l->f4] = arg1;
            l->f4 = l->f4 + 1;
        }
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_79(Obj_1709d0 *arg0, int arg1, int arg2) {
    Mgr *m = arg0->f1336;
    int i;
    Ent *e = m->ents + arg1;
    int off;
    int flag;
    if (e == 0) {
        return 0;
    }
    flag = arg2 & 0xFF;
    if (e->f148 == flag) {
        DAT_005608cc[0] += 1;
    }
    if (e->f148 == flag) {
        return 1;
    }
    if (arg2 != 0) {
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
    p2DisableLight(e->f144, arg1, arg2, m);
    e->f148 = 0;
    *(int *)((int)DAT_00560858[0] + e->f144 * 4) = -1;
    return 1;
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_80(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (arg1 * 0xA0))) + 148);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_81(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (arg1 * 0xA0))) + 152);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_82(char *arg0, int arg1, float *arg2) {
    char *a3;
    float *t;
    int e;
    a3 = *(char **)(arg0 + 1336);
    arg1 = *(int *)(a3 + 16) + arg1 * 0xA0;
    t = (float *)arg1;
    if (t != 0) {
        e = 1;
        if (t[8] != arg2[0]) e = 0;
        if (e != 0) { e = 1; if (t[9] != arg2[1]) e = 0; }
        if (e != 0) { e = 1; if (t[10] != arg2[2]) e = 0; }
        if (e != 0) { e = 1; if (t[11] != arg2[3]) e = 0; }
        if (e != 0) {
            DAT_005608d0[0] += 1;
        }
        t[8] = arg2[0];
        t[9] = arg2[1];
        t[10] = arg2[2];
        t[11] = arg2[3];
        FUN_00171690(arg0, t);
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_86(A_170c30 *arg0, int arg1, V4_170c30 *arg2) {
    Tab_170c30 *t;
    E_170c30 *e;
    int same;
    int old;
    int nw;
    t = arg0->f538;
    e = (E_170c30 *)(t->f10 + arg1 * 160);
    if (e != 0) {
        same = 1;
        if (e->v.x != arg2->x) { same = 0; }
        if (same != 0) {
            same = 1;
            if (e->v.y != arg2->y) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.z != arg2->z) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.w != arg2->w) { same = 0; }
        }
        if (same != 0) {
            DAT_005608d4[0] += 1;
        }
        e->v.x = arg2->x;
        e->v.y = arg2->y;
        e->v.z = arg2->z;
        e->v.w = arg2->w;
        old = e->flags;
        if (arg2->x != 0.0f || arg2->y != 0.0f || arg2->z != 0.0f) {
            e->flags = e->flags | 1;
        } else {
            e->flags = old & ~1;
        }
        nw = e->flags;
        if (old != nw) {
            e->flags = nw | 8;
        }
        FUN_00171690(arg0, e);
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_84(O_170d80 *arg0, int arg1, float *arg2) {
    T_170d80 *t;
    E_170d80 *e;
    int same;
    int old;
    t = arg0->f1336;
    e = (E_170d80 *)((char *)t->f16 + arg1 * 160);
    if (e != 0) {
        same = 1;
        if (e->v0 != arg2[0]) same = 0;
        if (same) {
            same = 1;
            if (e->v1 != arg2[1]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v2 != arg2[2]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v3 != arg2[3]) same = 0;
        }
        if (same) {
            DAT_005609c8[0] = DAT_005609c8[0] + 1;
        }
        e->v0 = arg2[0];
        e->v1 = arg2[1];
        e->v2 = arg2[2];
        e->v3 = arg2[3];
        old = e->f108;
        if (arg2[0] != 0.0f || arg2[1] != 0.0f || arg2[2] != 0.0f) {
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

void Gap__Gfx__igPsx2VisualContext__vfunc_88(C_171100 *arg0, int arg1, float *arg2) {
    float sp40[16];
    L_171100 *l = *(L_171100 **)((char *)arg0 + 1336);
    Ent_171100 *e = (Ent_171100 *)(l->base + arg1 * 0xA0);
    if (e != 0) {
        int same = 1;
        if (e->x != arg2[0]) same = 0;
        if (same != 0) { same = 1; if (e->y != arg2[1]) same = 0; }
        if (same != 0) { same = 1; if (e->z != arg2[2]) same = 0; }
        if (same != 0) DAT_005608dc[0] += 1;
        e->x = arg2[0];
        e->y = arg2[1];
        e->z = arg2[2];
        if (e->f152 != 0) {
            arg0->vX(1, sp40);
            Vec3f_TransformProjective((char *)e + 0x70, arg2, sp40);
        }
        FUN_00171690(arg0, e);
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_92(struct Ctx_171220 *arg0, int arg1, float fparg0) {
    struct Item *it;
    unsigned int old;

    it = &arg0->list->data[arg1];
    if (it != 0) {
        old = it->f108;
        if (it->f92 == fparg0) {
            DAT_005608e4[0] += 1;
        }
        it->f92 = fparg0;
        if (it->f152 == 2 && fparg0 != 180.0f) {
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

void Gap__Gfx__igPsx2VisualContext__vfunc_94(S_1712e0 *arg0, int arg1, float fparg0) {
    float temp_f1;
    E_1712e0 *temp_a1;
    L_1712e0 *temp_a2;

    temp_a2 = arg0->f1336;
    temp_a1 = temp_a2->f16 + arg1;
    if (temp_a1 != 0) {
        temp_f1 = 128.0f * fparg0;
        if (temp_a1->f76 == temp_f1) {
            DAT_005608e8[0] += 1;
        }
        temp_a1->f76 = temp_f1;
        FUN_00171690(arg0, temp_a1);
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_83(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 32);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 36);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 40);
    *(float *)((char *)(arg2) + 12) = (float) *(float *)((char *)(temp_v1) + 44);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_85(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_pLightList) + 16) + (arg1 * 0xA0));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 16);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 20);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 24);
    *(float *)((char *)(arg2) + 12) = (float) *(float *)((char *)(temp_v1) + 28);
}

/* The reflected metadata types _diffuse as int[4], but the code reads floats. */
void Gap__Gfx__igPsx2VisualContext__vfunc_87(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    igLightAttr *temp_v1;

    temp_v1 = (igLightAttr *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = *(float *)&temp_v1->_diffuse[0];
    arg2[1] = *(float *)&temp_v1->_diffuse[1];
    arg2[2] = *(float *)&temp_v1->_diffuse[2];
    arg2[3] = *(float *)&temp_v1->_diffuse[3];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_89(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    float *temp_v1;

    temp_v1 = (float *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_91(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    igLightAttr *temp_v1;

    temp_v1 = (igLightAttr *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = (float) *(float *)&temp_v1->_specular[0];
    arg2[1] = (float) *(float *)&temp_v1->_specular[1];
    arg2[2] = (float) *(float *)&temp_v1->_specular[2];
}

float Gap__Gfx__igPsx2VisualContext__vfunc_95(void) {
    return 0.0f;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_97(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    char *p = (char *)(*(int *)((char *)(arg0->_pLightList) + 16) + (arg1 * 0xA0));
    float x, y, z;
    z = *(float *)(p + 88);
    y = *(float *)(p + 84);
    x = *(float *)(p + 80);
    *(float *)((char *)arg2 + 0) = x;
    *(float *)((char *)arg2 + 4) = y;
    *(float *)((char *)arg2 + 8) = z;
}

float Gap__Gfx__igPsx2VisualContext__vfunc_93(void *arg0, int arg1) {
    return *(float *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (arg1 * 0xA0))) + 92);
}

void FUN_00171690(void *arg0, void *arg1) {
    if (*(unsigned char *)((char *)(arg1) + 148) != 0) {
        p2SetLight(*(int *)((char *)(arg1) + 144));
    }
}

void FUN_001716c0(void *arg0) {
    *(float *)((char *)(arg0) + 16) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 20) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 24) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 28) = (float) DAT_004e117c[0];
    *(float *)((char *)(arg0) + 0) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 4) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 8) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 12) = (float) DAT_004e117c[0];
    *(float *)((char *)(arg0) + 48) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 52) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 56) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 60) = (float) DAT_004e117c[0];
    *(float *)((char *)(arg0) + 32) = (float) g_vec4Zero[0];
    *(float *)((char *)(arg0) + 36) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 40) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 44) = (float) DAT_004e117c[0];
    *(int *)((char *)(arg0) + 64) = 0;
    *(int *)((char *)(arg0) + 68) = 2;
    *(int *)((char *)(arg0) + 84) = 0;
    *(int *)((char *)(arg0) + 80) = 0;
}

static inline bool colorEqual(const float *a, const float *b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_102(VisualContextColorView *arg0, float *arg1) {
    float *cur = arg0->f1344->v;
    VisualColorBlock *p;
    if (colorEqual(cur, arg1)) {
        DAT_005608f8[0] += 1;
    }
    p = arg0->f1344;
    p->v[0] = arg1[0];
    p->v[1] = arg1[1];
    p->v[2] = arg1[2];
    p->v[3] = arg1[3];
    FUN_00172330(arg0, arg0->f1344);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_103(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_diffuse[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_diffuse[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_diffuse[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_diffuse[3];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_106(Obj_1718a0 *o, V4_1718a0 *n) {
    Sub *s;
    unsigned old, *f;
    bool eq;
    s = o->s;
    /* matching construct: C++ conversion trial — the four equality tests are one bool && chain */
    eq = s->v.x == n->x && s->v.y == n->y && s->v.z == n->z && s->v.w == n->w;
    if (eq) DAT_005608fc[0]++;
    s = o->s;
    s->v.x = n->x; s->v.y = n->y; s->v.z = n->z; s->v.w = n->w;
    s = o->s;
    f = &s->flags;
    old = s->flags;
    if (n->x != 0.0f || n->y != 0.0f || n->z != 0.0f) *f |= 4;
    else *f = old & ~4u;
    s = o->s;
    f = &s->flags;
    if (old != s->flags) *f = s->flags | 2;
    FUN_00172330(o, o->s);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_107(igPsx2VisualContext *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (void *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(temp_v1) + 12);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_104(struct S_171a10 *arg0, float *arg1) {
    float *temp_a2;
    struct T_171a10 *temp_v1;
    int var_v0;
    struct T_171a10 *temp_v0;

    temp_v1 = arg0->f1344;
    var_v0 = 1;
    temp_a2 = temp_v1->v;
    if (temp_v1->v[0] != arg1[0]) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[1] != arg1[1]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[2] != arg1[2]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (temp_a2[3] != arg1[3]) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        DAT_00560900[0] += 1;
    }
    temp_v0 = arg0->f1344;
    temp_v0->v[0] = arg1[0];
    temp_v0->v[1] = arg1[1];
    temp_v0->v[2] = arg1[2];
    temp_v0->v[3] = arg1[3];
    FUN_00172330(arg0, arg0->f1344);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_105(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_emission[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_emission[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_emission[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_emission[3];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_108(struct Psx2VisualContextView *arg0, struct VisualContextVec4 *arg1) {
    struct VisualContextVec4 *p;
    struct VisualContextState *o;
    unsigned old;
    unsigned *fp;
    bool same;

    o = arg0->o;
    p = &o->v;
    same = p->x == arg1->x && p->y == arg1->y && p->z == arg1->z && p->w == arg1->w;
    if (same) {
        DAT_00560904[0] += 1;
    }
    o = arg0->o;
    o->v.x = arg1->x;
    o->v.y = arg1->y;
    o->v.z = arg1->z;
    o->v.w = arg1->w;
    o = arg0->o;
    fp = &o->flags;
    old = *fp;
    if (arg1->x != 0.0f || arg1->y != 0.0f || arg1->z != 0.0f) {
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

void Gap__Gfx__igPsx2VisualContext__vfunc_109(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_ambient[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_ambient[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_ambient[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_ambient[3];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_98(S0_171c80 *arg0, float fparg0) {
    if (arg0->f1344->f64 == fparg0) {
        DAT_00560908[0] += 1;
    }
    arg0->f1344->f64 = fparg0;
    FUN_00172330(arg0, arg0->f1344);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_99(void *arg0) {
    return *(float *)((char *)(*(int *)((char *)(arg0) + 1344)) + 64);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_112(O_171cd0 *arg0, V4_171cd0 *arg1, V4_171cd0 *arg2, V4_171cd0 *arg3, V4_171cd0 *arg4, float fparg0) {
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

void FUN_001720d0(struct O_1720d0 *arg0, int arg1) {
    if (arg0->p->f == arg1) {
        DAT_0056090c[0] += 1;
    }
    arg0->p->f = arg1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_110(igPsx2VisualContext *self, int enable)
{
    if (self->_materialSpecularState == (enable & 0xFF))
        DAT_00560910 += 1;
    self->_materialSpecularState = enable;
    FUN_001f8750(enable);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_100(igPsx2VisualContext *self, unsigned int mode) {
    if (((MaterialState *)self->_currentMaterial)->blendMode == mode) {
        DAT_00560914[0] += 1;
    }
    ((MaterialState *)self->_currentMaterial)->blendMode = mode;
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

int Gap__Gfx__igPsx2VisualContext__vfunc_101(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 1344)) + 84);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_115(struct H_172230 *arg0, float *arg1) {
    float *a2;
    struct O_172230 *o;
    int r;
    o = arg0->o;
    r = 1;
    a2 = o->v;
    if (o->v[0] != arg1[0]) r = 0;
    if (r != 0) { r = 1; if (a2[1] != arg1[1]) r = 0; }
    if (r != 0) { r = 1; if (a2[2] != arg1[2]) r = 0; }
    if (r != 0) { r = 1; if (a2[3] != arg1[3]) r = 0; }
    if (r != 0) {
        DAT_00560918[0] += 1;
    }
    o = arg0->o;
    o->v[0] = arg1[0];
    o->v[1] = arg1[1];
    o->v[2] = arg1[2];
    o->v[3] = arg1[3];
    p2SetLightingColor(arg1);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_116(igPsx2VisualContext *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (void *)(arg0->_currentMaterial);
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1) + 88);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1) + 92);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1) + 96);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(temp_v1) + 100);
}

void FUN_00172330(void *arg0, void *arg1) {
    p2SetMaterial(*(int *)((char *)arg1 + 80));
    p2SetLightingColor(*(int *)((char *)arg0 + 1344) + 0x58);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_199(Obj_172370 *o, int k, int n) {
    switch (k) {
    case 0:
        if (n >= o->s[0]->count) List_Reserve(o->s[0], n, 64);
        break;
    case 1:
        if (n >= o->s[1]->count) List_Reserve(o->s[1], n, 64);
        break;
    case 2:
        if (n >= o->s[2]->count) List_Reserve(o->s[2], n, 64);
        break;
    case 10:
        if (n >= o->s[4]->count) List_Reserve(o->s[4], n, 64);
        if (n >= o->s[8]->count) List_Reserve(o->s[8], n, 64);
        break;
    case 11:
        if (n >= o->s[5]->count) List_Reserve(o->s[5], n, 64);
        if (n >= o->s[9]->count) List_Reserve(o->s[9], n, 64);
        break;
    case 12:
        if (n >= o->s[6]->count) List_Reserve(o->s[6], n, 64);
        if (n >= o->s[10]->count) List_Reserve(o->s[10], n, 64);
        break;
    case 13:
        if (n >= o->s[7]->count) List_Reserve(o->s[7], n, 64);
        if (n >= o->s[11]->count) List_Reserve(o->s[11], n, 64);
        break;
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_200(struct S_172550 *arg0, int arg1) {
    switch (arg1) {
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

static inline int count_of_172600(const L_172600 *list) { return list->count; }

void Gap__Gfx__igPsx2VisualContext__vfunc_201(S_172600 *arg0, int arg1) {
    switch (arg1) {
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

void Gap__Gfx__igPsx2VisualContext__vfunc_202(Obj_172910 *o, int k) {
    Mat_172910 m0, m1, m2, m3, m4;
    switch (k) {
    case 0:
        o->s[0]->count--;
        FUN_001fbce0(3, o->s[0]->data + ((o->s[0]->count - 1) << 6));
        break;
    case 1:
        o->s[1]->count--;
        FUN_001fbce0(0, o->s[1]->data + ((o->s[1]->count - 1) << 6));
        break;
    case 2: {
        Stk *s = o->s[2];
        s->count--;
        igMatrix44f_Copy((float *)&m0, (float *)(s->data + (s->count << 6)));
        FUN_001fbce0(4, o->s[2]->data + ((o->s[2]->count - 1) << 6));
        break; }
    case 10: { Stk *s = o->s[4]; s->count--; igMatrix44f_Copy((float *)&m1, (float *)(s->data + (s->count << 6))); break; }
    case 11: { Stk *s = o->s[5]; s->count--; igMatrix44f_Copy((float *)&m2, (float *)(s->data + (s->count << 6))); break; }
    case 12: { Stk *s = o->s[6]; s->count--; igMatrix44f_Copy((float *)&m3, (float *)(s->data + (s->count << 6))); break; }
    case 13: { Stk *s = o->s[7]; s->count--; igMatrix44f_Copy((float *)&m4, (float *)(s->data + (s->count << 6))); break; }
    }
}

static inline int n_of(const St_172b00 *list) { return list->n; }

void Gap__Gfx__igPsx2VisualContext__vfunc_203(O_172b00 *arg0, int arg1, char *arg2) {
    int sp15C, sp158, sp154, sp150;
    char sp110[64];
    char spD0[64];
    char sp90[64];
    char sp50[64];
    St_172b00 *t;
    switch (arg1) {
    case 0:
        SET(arg0->s972, arg2)
        t = arg0->s972;
        FUN_001fbce0(3, t->data + ((t->n - 1) << 6));
        break;
    case 1:
        SET(arg0->s976, arg2)
        t = arg0->s976;
        FUN_001fbce0(0, t->data + ((t->n - 1) << 6));
        break;
    case 2:
        SET(arg0->s980, arg2)
        t = arg0->s980;
        FUN_001fbce0(4, t->data + ((t->n - 1) << 6));
        break;
    case 10:
        igMatrix44f_SetIdentity((float *)sp110);
        SETB(arg0->s988, arg2)
        igMatrix44f_Invert(&sp15C, sp110, arg2);
        FUN_001903d0(sp110);
        SET(arg0->s1004, sp110)
        break;
    case 11:
        igMatrix44f_SetIdentity((float *)spD0);
        SETB(arg0->s992, arg2)
        igMatrix44f_Invert(&sp158, spD0, arg2);
        FUN_001903d0(spD0);
        SET(arg0->s1008, spD0)
        break;
    case 12:
        igMatrix44f_SetIdentity((float *)sp90);
        SETB(arg0->s996, arg2)
        igMatrix44f_Invert(&sp154, sp90, arg2);
        FUN_001903d0(sp90);
        SET(arg0->s1012, sp90)
        break;
    case 13:
        igMatrix44f_SetIdentity((float *)sp50);
        SETB(arg0->s1000, arg2)
        igMatrix44f_Invert(&sp150, sp50, arg2);
        FUN_001903d0(sp50);
        SET(arg0->s1016, sp50)
        break;
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_206(Obj_173900 *self, int kind, int arg) {
    switch (kind) {
    case 0:
        FUN_001e6ae0(self->s[0], arg);
        self->vf(kind, self->s[0]->data + ((self->s[0]->cnt - 1) << 6));
        break;
    case 1:
        FUN_001e6ae0(self->s[1], arg);
        self->vf(kind, self->s[1]->data + ((self->s[1]->cnt - 1) << 6));
        break;
    case 2:
        FUN_001e6ae0(self->s[2], arg);
        self->vf(kind, self->s[2]->data + ((self->s[2]->cnt - 1) << 6));
        break;
    case 10:
        FUN_001e6ae0(self->s[4], arg);
        self->vf(kind, self->s[4]->data + ((self->s[4]->cnt - 1) << 6));
        break;
    case 11:
        FUN_001e6ae0(self->s[5], arg);
        self->vf(kind, self->s[5]->data + ((self->s[5]->cnt - 1) << 6));
        break;
    case 12:
        FUN_001e6ae0(self->s[6], arg);
        self->vf(kind, self->s[6]->data + ((self->s[6]->cnt - 1) << 6));
        break;
    case 13:
        FUN_001e6ae0(self->s[7], arg);
        self->vf(kind, self->s[7]->data + ((self->s[7]->cnt - 1) << 6));
        break;
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_207(S_173b30 *self, int arg1, int arg2) {
    L_173b30 *l;
    switch (arg1) {
    case 0:
        FUN_001e6b00(self->f972, arg2);
        l = self->f972;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 1:
        FUN_001e6b00(self->f976, arg2);
        l = self->f976;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 2:
        FUN_001e6b00(self->f980, arg2);
        l = self->f980;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 10:
        FUN_001e6b00(self->f988, arg2);
        l = self->f988;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 11:
        FUN_001e6b00(self->f992, arg2);
        l = self->f992;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 12:
        FUN_001e6b00(self->f996, arg2);
        l = self->f996;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
        break;
    case 13:
        FUN_001e6b00(self->f1000, arg2);
        l = self->f1000;
        self->vX(arg1, (char *)l->data + ((l->cnt - 1) << 6));
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_208(O_173d60 *o, int k, int dst) {
    St_173d60 *s;
    switch (k) {
    case 0:  s = o->s972; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 1:  s = o->s976; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 2:  s = o->s980; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 10: s = o->s988; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 11: s = o->s992; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 12: s = o->s996; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    case 13: s = o->s1000; igMatrix44f_Copy((float *)dst, (float *)(s->data + ((s->n - 1) << 6))); break;
    }
}

void FUN_00173ed0(Obj_173ed0 *self, int op, void *m) {
    List_173ed0 *l;
    int n;
    switch (op) {
    case 14:
        l = self->list;
        n = l->getCount();
        if (n == 0) {
            if (n < l->cap) l->count = l->count + 1;
            else List_Resize(l, n + 1, 64);
            igMatrix44f_Copy((float *)(l->data + n * 64), (float *)m);
        } else {
            igMatrix44f_Copy((float *)(l->data + (l->count - 1) * 64), (float *)m);
        }
        l = self->list;
        FUN_001fbce0(5, l->data + (l->count - 1) * 64);
        break;
    default:
        self->v203(op, m);
        break;
    }
}

void FUN_00173fd0(int *arg0, int arg1, int arg2) {
    int *temp_v0;
    switch (arg1) {
    case 0xE:
        temp_v0 = (int *)arg0[246];
        igMatrix44f_Copy((float *)arg2, (float *)(temp_v0[4] + ((temp_v0[2] - 1) << 6)));
        break;
    default:
        ((A_173fd0 *)arg0)->vX(arg1, arg2);
        break;
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_209(struct O_174030 *arg0, int arg1, int arg2) {
    if (arg0->f == (arg2 & 0xFF)) {
        DAT_0056091c[0] += 1;
    }
    arg0->f = arg2;
    if (arg2 != 0) {
        p2EnableCapability(0xD);
        return;
    }
    p2DisableCapability(0xD);
}

void FUN_00174090(void *arg0) {
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(0), (int)(4));
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(1), (int)(4));
    ((DW4VC_796_2 *)(((char *)(arg0) + 0)))->vX((int)(2), (int)(4));
    ((DW4VC_740_6 *)(((char *)(arg0) + 0)))->vX(0, 0, *(int *)((char *)(arg0) + 908), *(int *)((char *)(arg0) + 912), 0.0f, 1.0f);
    ((DW4VC_864_1 *)(((char *)(arg0) + 0)))->vX((int)(-1));
    FUN_00174850((S174 *)arg0, 1);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_216(void *a0, int arg1) {
    float m[16];
    struct V4 { float x, y, z; int w; } v;
    VC104 *o;
    FUN_00166400((igVisualContext_166400 *)a0, arg1);
    if (arg1 & 4) {
        FUN_0017c880((igPsx2VisualContext *)a0, ((VC596 *)a0)->vX(0), 1);
    }
    if (arg1 & 0x40) {
        o = (VC104 *)((VC104 *)a0)->vX(&igDecalExt_className[0]);
        if (o != 0) {
            ((VC120 *)o)->vX(0);
        }
    }
    if (arg1 & 2) {
        FUN_001720d0((O_1720d0 *)a0, 0);
    }
    if (arg1 & 0x20) {
        FUN_00175090((S0_175090 *)a0, 2);
    }
    igMatrix44f_SetIdentity(m);
    igMatrix44f_SetIdentity(m);
    FUN_00173ed0((Obj_173ed0 *)a0, 14, (void *)m);
    FUN_0016cc50((int)a0, 0);
    v.w = 0x3F800000;
    v.x = 0.501960754f;
    v.y = 0.501960754f;
    v.z = 0.501960754f;
    FUN_00175510((S_175510 *)a0, (float *)&v);
    FUN_001754b0((S1754 *)a0, 1);
    FUN_001755e0((S0_1755e0 *)a0, 1);
    FUN_001757c0((igPsx2VisualContext *)a0, 0);
    p2DisableCapability(23);
    FUN_00175640((S_175640 *)a0, 0);
    FUN_00175670((O_175670 *)a0, 0);
    FUN_0017c710((int)a0, 0, 0);
    FUN_00175790((S_175790 *)a0, 0x71603524 | (0x40712635LL << 32));
    FUN_00174950(a0, 0);
    FUN_00169be0(a0, 1);
    ((VC696 *)a0)->vX();
}

void Gap__Gfx__igPsx2VisualContext__vfunc_113(S0_174300 *arg0, unsigned char arg1) {
    int temp_v1;

    temp_v1 = arg1 & 0xFF;
    if (arg0->f55C == temp_v1) {
        DAT_00560920[0] += 1;
    }
    arg0->f55C = arg1;
    if (temp_v1 == 1) {
        p2EnableCapability(0x12);
        return;
    }
    p2DisableCapability(0x12);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_114(void *arg0) {
    return *(int *)((char *)(arg0) + 1372);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_211(S_174370 *arg0, int arg1) {
    int var_a1;

    var_a1 = arg1;
    if (GPR_00554b4c != 0) {
        var_a1 = 0;
    }
    if (arg0->f == (var_a1 & 0xFF)) {
        DAT_005608a8[0] += 1;
    }
    arg0->f = var_a1;
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_212(void *arg0) {
    return *(int *)((char *)(arg0) + 1020);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_152(struct S_1743c0 *arg0, int arg1) {
    if (GPR_00554b48 != 0) {
        arg1 = 0;
    }
    if (arg0->f1032 == (arg1 & 0xFF)) {
        DAT_00560924[0] += 1;
    }
    arg0->f1032 = arg1;
    if (arg0->f1032 != 0) {
        p2EnableCapability(2, arg1);
        return;
    }
    p2DisableCapability(2, arg1);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_153(void *arg0) {
    return *(int *)((char *)(arg0) + 1032);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_154(int *arg0, int arg1) {
    if (arg0[259] == arg1) {
        DAT_00560928[0] += 1;
    }
    arg0[259] = arg1;
    FUN_00174640((int)arg0, 0);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_156(struct S174470 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_00560968[0] += 1;
    }
    arg0->f = arg1;
    FUN_00174640((int)arg0, 0);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_155(void *arg0) {
    return *(int *)((char *)(arg0) + 1036);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_157(void *arg0) {
    return *(int *)((char *)(arg0) + 1100);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_158(S_1744c0 *arg0, int arg1, int arg2) {
    if (arg0->f1036 == arg1) {
        DAT_00560928[0] += 1;
    }
    if (arg0->f1100 == arg2) {
        DAT_00560968[0] += 1;
    }
    arg0->f1036 = arg1;
    arg0->f1100 = arg2;
    FUN_00174640((int)arg0, 0);
}

void FUN_00174510(struct R_174510 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int n;
    int j;
    int off;
    char *p;
    if (arg4 < 15) {
        n = arg4;
    } else {
        n = 15;
    }
    off = n * 4;
    if (n < 8) {
        if (arg0->a[n] == arg1) {
            DAT_00560928[n] += 1;
        }
        if (arg0->b[n] == arg2) {
            DAT_00560968[n] += 1;
        }
        if (arg0->c[n] == (arg3 & 0xFF)) {
            DAT_00560948[n] += 1;
        }
    }
    off = n * 4;
    p = (char *)(off + (int)arg0);
    *(int *)(p + 1036) = arg1;
    *(int *)(p + 1100) = arg2;
    *(int *)(p + 1164) = arg3 & 0xFF;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram[0] = n;
    p2CurrentGsRegisters[0] = (StageState *)((int *)p2GsRegisterSets + j * 112);
    FUN_00174640((int)arg0, n);
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = p2GsRegisterSets;
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
    p2SetBlendEquation(var_a0, var_a1, var_a2, var_a3, var_a4, temp_a5, tab);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_217(igPsx2VisualContext *self, unsigned char enable)
{
    if (GPR_00554b50 != 0)
        enable = 0;
    if (self->_alphaEnable == enable)
        DAT_0056098c += 1;
    self->_alphaEnable = enable;
    if (enable) {
        p2EnableCapability(3);
        FUN_001747f0((S_1747f0 *)self);
    } else {
        p2DisableCapability(3);
    }
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_218(void *arg0) {
    return *(int *)((char *)(arg0) + 1022);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_219(int *arg0, int arg1) {
    if (arg0[256] == arg1) {
        DAT_00560998[0] += 1;
    }
    arg0[256] = arg1;
    FUN_001747f0((S_1747f0 *)arg0);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_220(void *arg0) {
    return *(int *)((char *)(arg0) + 1024);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_221(struct S_1747b0 *arg0, float fparg0) {
    if (arg0->f == fparg0) {
        DAT_0056099c[0] += 1;
    }
    arg0->f = fparg0;
    FUN_001747f0((S_1747f0 *)arg0);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_222(void *arg0) {
    return *(float *)((char *)arg0 + 1028);
}

void FUN_001747f0(S_1747f0 *s) { if (s->b == 1) { int a = (int)(128.0f * (float)s->f); p2SetAlphaTest(DAT_0048a500[s->i], a, 0); } }

void FUN_00174850(struct S174 *arg0, int arg1) {
    int temp_v1;
    if (GPR_00554b64 != 0) {
        arg1 = 0;
    }
    temp_v1 = arg1 & 0xFF;
    if (arg0->f == temp_v1) {
        DAT_005609a0[0] += 1;
    }
    arg0->f = arg1;
    if (temp_v1 == 1) {
        p2DisableCapability(0x13, arg1);
        return;
    }
    p2EnableCapability(0x13, arg1);
}

unsigned char FUN_001748c0(int *p)
{
    return *(unsigned char *)((char *)p + 1373);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_223(O_1748d0 *o, unsigned char a) {
    if (GPR_00554b54 != 0) a = 0;
    if (o->v == a) DAT_005608b8[0] += 1;
    o->v = a;
    if (a == 1) p2EnableCapability(6);
    else p2DisableCapability(6);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_224(void *arg0) {
    return *(int *)((char *)(arg0) + 1228);
}

void FUN_00174950(void *d0, int arg1) {
    if (arg1 == 1) {
        p2EnableCapability(0x19);
        return;
    }
    p2DisableCapability(0x19);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_225(void *arg0, int arg1, int arg2, int arg3, int arg4) {
    *(char *)((char *)(arg0) + 1252) = arg1;
    *(char *)((char *)(arg0) + 1253) = arg2;
    *(char *)((char *)(arg0) + 1254) = arg3;
    *(char *)((char *)(arg0) + 1255) = arg4;
    p2SetColourMask(arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, arg4 & 0xFF);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_226(void *arg0, unsigned char *arg1, unsigned char *arg2, unsigned char *arg3, unsigned char *arg4) {
    *arg1 = *(unsigned char *)((char *)(arg0) + 1252);
    *arg2 = *(unsigned char *)((char *)(arg0) + 1253);
    *arg3 = *(unsigned char *)((char *)(arg0) + 1254);
    *arg4 = *(unsigned char *)((char *)(arg0) + 1255);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_227(S_1749f0 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_005608b0[0] += 1;
    }
    arg0->f = arg1;
    if (DAT_0048a530[arg1] == 1) {
        p2DisableCapability(0x11);
        return;
    }
    p2EnableCapability(0x11);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_228(void *arg0) {
    return *(int *)((char *)(arg0) + 1256);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_229(struct S_174a70 *arg0, int arg1) {

    if (GPR_00554b58 != 0) {
        arg1 = 0;
    }
    if (arg0->f1268 == (arg1 & 0xFF)) {
        DAT_005609a4[0] += 1;
    }
    arg0->f1268 = arg1;
    if (arg1 != 0) {
        p2EnableCapability(DAT_0048a538[arg0->f1272], arg1);
        return;
    }
    p2DisableCapability(DAT_0048a538[arg0->f1272], arg1);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_230(void *arg0) {
    return *(int *)((char *)(arg0) + 1268);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_231(struct P_174b10 *arg0, int arg1) {
    int temp_a0;

    temp_a0 = arg0->f1272;
    if ((temp_a0 != arg1) && (arg0->f1268 != 0)) {
        p2DisableCapability(DAT_0048a538[temp_a0]);
        p2EnableCapability(DAT_0048a538[arg1]);
    }
    if (arg0->f1272 == arg1) {
        DAT_005609a8[0] += 1;
    }
    arg0->f1272 = arg1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_232(void *arg0) {
    return *(int *)((char *)(arg0) + 1272);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_233(struct S_174bc0 *s, int v) {
    int m;
    if (GPR_00554b5c != 0) {
        v = 0;
    }
    m = v & 0xFF;
    if (s->f == m) {
        DAT_005609ac[0] += 1;
    }
    if (s->f != m) {
        s->f = v;
        if (v != 0) {
            p2EnableCapability(0);
            FUN_00174db0(s);
            return;
        }
        p2DisableCapability(0);
    }
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_234(void *arg0) {
    return *(int *)((char *)(arg0) + 1277);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_235(S_174c50 *arg0, unsigned arg1) {
    if (arg0->f1280 == arg1) {
        DAT_005609b0[0] += 1;
    }
    arg0->f1280 = arg1;
    FUN_00174db0(arg0);
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2147483648.0f * arg0->f892);
    } else {
        arg0->f900 = (unsigned)(2147483648.0f * (1.0f - arg0->f892));
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_236(void *arg0) {
    return *(int *)((char *)(arg0) + 1280);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_237(struct S_174d70 *arg0, int arg1) {
    if (arg0->b == (arg1 & 0xFF)) {
        DAT_005609b4[0] += 1;
    }
    arg0->b = arg1;
    FUN_00174db0(arg0);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_238(void *arg0) {
    return *(int *)((char *)(arg0) + 1276);
}

void FUN_00174db0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 1276) == 1) {
        p2SetDepthFunction(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 0);
        return;
    }
    p2SetDepthFunction(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 1);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_159(S_174e20 *arg0, int arg1) {
    if (arg0->f1260 == ((unsigned char)arg1)) {
        DAT_005609b8[0] += 1;
    }
    arg0->f1260 = ((unsigned char)arg1);
    if ((arg1 != 0) && (arg0->f1288 != 7)) {
        p2EnableCapability(4);
    } else {
        p2DisableCapability(4);
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_160(void *arg0) {
    return *(int *)((char *)(arg0) + 1260) != 0;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_161(int *arg0, int arg1) {
    if (arg0[316] == arg1) {
        DAT_005609bc[0] += 1;
    }
    arg0[316] = arg1;
    p2SetDestinationAlphaMode(arg0[316] & 1);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_162(void *arg0) {
    return *(int *)((char *)(arg0) + 1264);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_163(S0_174ee0 *arg0, unsigned int arg1) {
    switch (arg1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if ((arg0->f4EC != 0) && (p2IsCapabilityEnabled(4) == 0)) {
            p2EnableCapability(4);
        }
        break;
    case 7:
        p2DisableCapability(4);
        break;
    }
    if (arg0->f508 == arg1) {
        DAT_005609c0[0] += 1;
    }
    arg0->f508 = arg1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_164(void *arg0) {
    return *(int *)((char *)(arg0) + 1288);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_165(void)
{
}

void Gap__Gfx__igPsx2VisualContext__vfunc_166(void) {

}

void Gap__Gfx__igPsx2VisualContext__vfunc_167(void)
{
}

int Gap__Gfx__igPsx2VisualContext__vfunc_168(void) {
    return -1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_169(void)
{
}

int Gap__Gfx__igPsx2VisualContext__vfunc_170(void) {
    return -1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_239(S_175000 *arg0, int arg1) {
    if (arg0->f1292 == arg1) {
        DAT_005609c4[0] += 1;
    }
    arg0->f1292 = arg1;
    if (arg1 == 0) {
        FUN_001f7470(2);
    } else if (arg1 == 1) {
        FUN_001f7470(1);
    } else if (arg1 == 2) {
        FUN_001f7470(0);
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_240(void *arg0) {
    return *(int *)((char *)(arg0) + 1292);
}

void FUN_00175090(S0_175090 *arg0, int arg1) {
    if (arg0->f510 == arg1) {
        DAT_005609c8[0] += 1;
    }
    arg0->f510 = arg1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_241(struct S_1750c0 *arg0, int arg1) {
    if (GPR_00554b60 != 0) {
        arg1 = 0;
    }
    if (arg0->mode == (arg1 & 0xFF)) {
        DAT_005609cc[0] += 1;
    }
    arg0->mode = arg1;
    if (arg1 != 0) {
        p2EnableCapability(7, arg1);
        return;
    }
    p2DisableCapability(7, arg1);
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_242(void *arg0) {
    return *(int *)((char *)(arg0) + 1300);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_243(struct S_175140 *arg0, float fparg0) {
    int i;
    if (arg0->f1304 == fparg0) {
        DAT_005609d0[0] += 1;
    }
    arg0->f1304 = fparg0;
    i = arg0->f1308;
    p2SetFog(DAT_0048a560[i], i, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_244(void *arg0) {
    return *(float *)((char *)arg0 + 1304);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_245(struct S1304 *arg0, int arg1) {
    if (arg0->f1308 == arg1) {
        DAT_005609d4[0] += 1;
    }
    arg0->f1308 = arg1;
    p2SetFog(DAT_0048a560[arg0->f1308], arg0->f1308, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_246(void *arg0) {
    return *(int *)((char *)(arg0) + 1308);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_247(struct O_175220 *arg0, struct V_175220 *arg1) {
    int var_v0;
    var_v0 = 1;
    if (arg0->f0 != arg1->f0) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f4 != arg1->f4) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f8 != arg1->f8) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (arg0->f12 != arg1->f12) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        DAT_005609d8[0] += 1;
    }
    arg0->f0 = arg1->f0;
    arg0->f4 = arg1->f4;
    arg0->f8 = arg1->f8;
    arg0->f12 = arg1->f12;
    p2SetFogColour(arg1->f0, arg1->f4, arg1->f8);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_248(void *arg0, void *arg1) {
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(arg0) + 1312);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(arg0) + 1316);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(arg0) + 1320);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(arg0) + 1324);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_249(struct S_175310 *arg0, float fparg0) {
    int temp_a1;

    if (arg0->f1328 == fparg0) {
        DAT_005609dc[0] += 1;
    }
    arg0->f1328 = fparg0;
    temp_a1 = arg0->i1308;
    p2SetFog(*(int *)((char *)&DAT_0048a560[0] + (temp_a1 * 4)), temp_a1, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_250(void *arg0) {
    return *(float *)((char *)arg0 + 1328);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_251(igPsx2VisualContext *arg0, float fparg0) {
    int temp_a1;

    if (arg0->_fogFar == fparg0) {
        DAT_005609e0[0] += 1;
    }
    arg0->_fogFar = fparg0;
    temp_a1 = arg0->_fogMode;
    p2SetFog(DAT_0048a560[temp_a1], temp_a1, arg0->_fogNear, arg0->_fogFar, arg0->_fogDensity, 1.0f, 0.0f, 0.0f);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_252(void *arg0) {
    return *(float *)((char *)arg0 + 1332);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_253(int *arg0, struct S_1753f0 *arg1, struct E_1753f0 *arg2) {
    if (arg1->b322 == 1) {
        *arg0 = g_resultFailure[0];
    } else if (arg2 == 0) {
        *arg0 = g_resultFailure[0];
    } else {
        arg1->b1348 = arg2->b0;
        arg1->b1349 = arg2->b1;
        arg1->f1352 = arg2->f4;
        arg1->f1356 = arg2->f8;
        arg1->f1360 = arg2->f12;
        arg1->f1364 = arg2->f16;
        arg1->f1368 = arg2->f20;
        *arg0 = g_resultSuccess[0];
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_254(igPsx2VisualContext *arg0, void *arg1) {
    *(unsigned char *)((char *)(arg1) + 0) = (unsigned char) *(unsigned char *)&arg0->_videoMode[0];
    *(unsigned char *)((char *)(arg1) + 1) = (unsigned char) ((unsigned char *)&arg0->_videoMode[0])[1];
    *(int *)((char *)(arg1) + 4) = (int)((int) arg0->_videoMode[1]);
    *(int *)((char *)(arg1) + 8) = (int)((int) arg0->_videoMode[2]);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&arg0->_videoMode[3];
    *(int *)((char *)(arg1) + 16) = (int)((int) arg0->_videoMode[4]);
    *(int *)((char *)(arg1) + 20) = (int)((int) arg0->_videoMode[5]);
}

int FUN_001754b0(struct S1754 *arg0, int arg1) {
    if (arg0->f == arg1) {
        DAT_005609e4[0] += 1;
    }
    arg0->f = arg1;
    return p2SetColorScaler(DAT_0048a520[arg1], (char *)arg0 + 0x598) != 0;
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

void Gap__Gfx__igPsx2VisualContext__vfunc_146(igPsx2VisualContext *context, int mode) {
    if (context->_pixelPipelineMode == mode) {
        DAT_005609f8++;
    }
    context->_pixelPipelineMode = mode;
    if (context->_bMultiPassNum > 1 && context->_pixelPipelineMode == 3) {
        if (p2IsCapabilityEnabled(23) == 0) {
            p2EnableCapability(23);
        }
    } else {
        if (p2IsCapabilityEnabled(23) != 0) {
            p2DisableCapability(23);
        }
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_145(S_175730 *arg0, int arg1) {
    if (arg0->f == (arg1 & 0xFF)) {
        DAT_005609fc[0] += 1;
    }
    arg0->f = arg1;
    if (arg1 != 0) {
        p2EnableCapability(0xB);
    } else {
        p2DisableCapability(0xB);
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

