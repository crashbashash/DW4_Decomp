void Gap__Bec__ParticleArray__vfunc_15(void *arg0) {
    int temp_v0;

    temp_v0 = FUN_00166d40();
    if (temp_v0 != 0) {
        ((DW4VC_92_5 *)(((char *)(arg0) + 0)))->vX((int)(((ParticleArray *)arg0)->_particleFormat), (int)(*(int *)((char *)(arg0) + 12)), (int)(temp_v0), ((ParticleArray *)arg0)->_particleLifeStart, ((ParticleArray *)arg0)->_particleLifeEnd);
    }
}

void Gap__Bec__ParticleArray__vfunc_36(ParticleArray *arg0) {
    igObject *t;
    PointSpriteView *s0;

    t = (igObject *)arg0->_context;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_context = 0;
    s0 = (PointSpriteView *)arg0->_pointSpriteInterface;
    if (s0 != 0) {
        if ((DW4VC_236 *)s0->f24 == (DW4VC_236 *)arg0->_internalVertexArray) {
            t = s0->getF24();
            if (t != 0) {
                t->_refCount = t->_refCount - 1;
                if ((t->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(t);
                }
            }
            s0->f24 = 0;
        }
        t = (igObject *)arg0->_pointSpriteInterface;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if ((t->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_pointSpriteInterface = 0;
    }
    if (arg0->_internalVertexArray != 0) {
        ((DW4VC_236 *)arg0->_internalVertexArray)->vX();
    }
}

void FUN_0015cb50(int a0, int a1)
{
    *(int *)((char *)a0 + 20) = a1;
}

int FUN_0015cb60(O_15cb50 *arg0, A1 *arg1, int *arg2, unsigned int arg3, int arg4) {
    Rc_15cb50 *a0;
    V2 sp90;
    int sp9C;
    V2 sp88;
    V2 sp80;
    int s5;
    int s3;
    unsigned int s6;
    int m;
    int r1;
    unsigned char t;
    int t2;
    int x;
    unsigned int i;

    if (0 != arg1) {
        arg1->u.w = arg1->u.w + 1;
    }
    a0 = (Rc_15cb50 *)arg0->f24;
    if (a0 != 0) {
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = (Obj2 *)arg1;
    sp9C = *arg2;
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 0) {
        t2 = sp9C & 0xFFF0FFFF;
        sp9C = t2;
        sp9C = 0x10000 | sp9C;
    }
    s6 = arg3 * 6;
    arg4 = arg0->f24->v96((int *)&sp9C, s6, arg4, 0);
    s5 = arg3 * 12;
    arg0->f24->f8->f64 = ((Al *)Memory_GetAllocatorBySelector(DAT_00587020[0]))->v216(s5);
    t = 0xFF & ((unsigned int)(*arg2 & 0x300000) >> 0x14);
    arg4 = s5 + arg4;
    if (t != 0) {
        m = arg3 * 24;
        x = arg0->f24->f8->f60;
        s5 = m * (t & 0xFF);
        if (x != 0) {
            Memory_FreeBuffer(x);
            arg4 -= s5;
            arg0->f24->f8->f60 = 0;
        }
        s5 = ((((unsigned int)(*arg2 & 0x300000) >> 0x14) & 0xFF) * 4) * arg3;
        r1 = arg1->f24->v216(s5);
        arg4 += s5;
        arg0->f24->f8->f60 = r1;
    }
    if (*arg2 & 0x01000000) {
        x = arg0->f24->f8->f76;
        s5 = arg3 * 24;
        if (0 != x) {
            Memory_FreeBuffer(x);
            arg4 = arg4 - s5;
            arg0->f24->f8->f76 = 0;
        }
        s3 = arg3 * 4;
        arg0->f24->f8->f76 = (arg1->f24->v216(s3));
        arg4 += s3;
    }
    for (i = 0; i < s6; i++) {
        sp90.a = 0;
        sp90.b = 0;
        arg0->f24->v200(0, i, &sp90);
    }
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 0) {
        for (i = 0; i < arg3; i++) {
            sp88.a = 0;
            sp88.b = 0;
            arg0->v168(0, i, &sp88);
            sp80.a = 0x3F800000;
            sp80.b = 0x3F800000;
            arg0->v168(1, i, &sp80);
        }
    }
    return arg4;
}

void FUN_0015ce90(OO *arg0) {
    RR *temp_v0;
    RR *old;

    arg0->f32 = 1;
    temp_v0 = (RR *)((DW4VC_244_0 *)(arg0->f20))->vX();
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
    }
    old = arg0->f24;
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->f24 = temp_v0;
    ((DW4VC_832_2 *)(arg0->f20))->vX(1, (char *)arg0 + 0x28);
    ((DW4VC_812_2 *)(arg0->f20))->vX(1, (char *)&DAT_004e0ef0[0]);
    if (arg0->f36 == 1) {
        ((DW4VC_832_2 *)(arg0->f20))->vX(0, (char *)arg0 + 0x68);
        FUN_0015d4d0((S4d0 *)arg0);
        ((DW4VC_812_2 *)(arg0->f20))->vX(0, (char *)arg0 + 0xA8);
        return;
    }
    Matrix44_Copy((float *)((int)arg0 + 0xE8), (float *)((int)arg0 + 0x28));
}

void FUN_0015cfb0(Y *arg0) {
    R_15cb50 *temp_a0_3;

    arg0->b32 = 0;
    arg0->dev->vX(1, (char *)arg0 + 0x28);
    if (arg0->w36 == 1) {
        arg0->dev->vX(0, (char *)arg0 + 0x68);
    }
    temp_a0_3 = arg0->obj;
    if (temp_a0_3 != 0) {
        temp_a0_3->refs = temp_a0_3->refs - 1;
        if (((unsigned long long)((long long)temp_a0_3->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_3);
        }
    }
    arg0->obj = 0;
}

void FUN_0015d050(void *arg0, int dummy1, void *arg2) {
    float temp_f0;

    temp_f0 = 0.5f * *(float *)((char *)(arg0) + 28);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}

void FUN_0015d070(igPointSpriteExt *arg0, int arg1, void *arg2) {
    float temp_f0;
    int b, idx, c;
    b = ((igVertexArray1_1 *)arg0->_vertexArray)->_vdata;
    idx = arg1 * 4;
    c = *(int *)(b + 60);
    temp_f0 = *(float *)(c + idx);
    *(float *)((char *)(arg2) + 0) = temp_f0;
    *(float *)((char *)(arg2) + 4) = temp_f0;
}

void FUN_0015d0a0(igPointSpriteExt *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(((igVertexArray *)(arg0->_vertexArray))->_vdata) + 60) + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
}

void FUN_0015d4d0(S4d0 *s)
{
  int sw, sh;
  int r = s->o->v48();
  s->o->v51(r, &sw, &sh);
  if (s->w == sw) { if (s->h != sh) goto L; } else { L:
    s->w = sw; s->h = sh;
    float hw = (float)sw / 2.0f;
    float hh = (float)sh / 2.0f;
    FUN_00192510((char*)s + 0x68, &s->nl, &s->nr, &s->nb, &s->nt, &s->nn, &s->nf);
    FUN_00191860((char*)s + 0xA8, -hw, hw, -hh, hh, s->nn, s->nf);
    float rw = 1.0f / (s->nr - s->nl);
    s->m[0] = 2.0f * s->nn * rw;
    s->m[4] = 0;
    s->m[8] = rw * (s->nr + s->nl);
    s->m[12] = 0;
    float rh = 1.0f / (s->nt - s->nb);
    s->m[1] = 0;
    s->m[5] = 2.0f * s->nn * rh;
    s->m[9] = rh * (s->nt + s->nb);
    s->m[13] = 0;
    s->m[2] = 0; s->m[6] = 0; s->m[10] = 0; s->m[14] = -1.0f;
    s->m[3] = 0; s->m[7] = 0; s->m[11] = -1.0f; s->m[15] = 0;
    float v[3];
    v[2] = 1.0f;
    v[0] = 0.5f * (float)sw;
    v[1] = 0.5f * (float)sh;
    FUN_00190d80((char*)s + 0x128, v, 0x3f800000);
  }
  FUN_001904f0((char*)s + 0xE8, (char*)s + 0x28, (char*)s + 0x128);
}

void FUN_0015d6c0(void *arg0, int arg1, void *arg2) {
    int temp_a0;
    float *var_v1;
    float *src = (float *)arg2;
    temp_a0 = *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 8)) + 64);
    var_v1 = temp_a0 ? (float *)(temp_a0 + arg1 * 0xC) : 0;
    var_v1[0] = src[0];
    var_v1[1] = src[1];
    var_v1[2] = src[2];
}

/* The pointer is reused across the stride multiply (p = idx*12; p = base + p) with the base as the
 * first addend. */
void FUN_0015d700(igPsx2PointSpriteExt *arg0, int arg1, void *arg2) {
    int temp_a0;
    char *var_v1;
    temp_a0 = *(int *)((char *)(((igVertexArray *)arg0->_vertexArray)->_vdata) + 64);
    if (temp_a0 != 0) { var_v1 = (char *)(arg1 * 0xC); var_v1 = (char *)(temp_a0 + (int)var_v1); } else { var_v1 = 0; }
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(var_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(var_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(var_v1) + 8);
}

void FUN_0015d740(S740 *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < 6; i++) {
        arg0->f24->vX(i + arg1 * 6, arg2);
    }
}

void FUN_0015d7c0(S7c0 *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < 6; i++) {
        arg0->f24->vX(i + arg1 * 6, arg2);
    }
}

void FUN_0015d840(igPointSpriteExtView *self, unsigned int index)
{
    self->_vertexArray->vfunc_41(index * 6);
}

void FUN_0015d860(igPointSpriteExtView *self, unsigned int index)
{
    self->_vertexArray->vfunc_42(index * 6);
}

void FUN_0015d880(O880 *arg0, int arg1, int arg2, float *arg3) {
    float v[2];
    int base;
    int i2, i1;
    unsigned char z;
    if (arg1 == 0) {
        base = arg2 * 6;
        arg0->p->m200(0, base);
    } else {
        base = arg2 * 6;
        arg0->p->m200(0, base + 3);
    }
    i2 = base + 2;
    arg0->p->m204(0, i2, v);
    z = !arg1;
    v[z] = arg3[z];
    arg0->p->m200(0, i2, v);
    arg0->p->m200(0, base + 4, v);
    i1 = base + 1;
    arg0->p->m204(0, i1, v);
    v[arg1] = arg3[arg1];
    arg0->p->m200(0, i1, v);
    arg0->p->m200(0, base + 5, v);
}

void FUN_0015da00(void *arg0, int arg1, int arg2) {
    void **temp_a0;
    void **temp_a0_2;

    if (arg1 == 0) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 24));
        ((DW4VC_204_2 *)(temp_a0))->vX((int)(0), (int)(arg2 * 6));
        return;
    }
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 24));
    ((DW4VC_204_2 *)(temp_a0_2))->vX((int)(0), (int)((arg2 * 6) + 3));
}

void FUN_0015da70(void *arg0, int arg1, int arg2) {
    void **temp_a0;
    void **temp_a0_2;

    if (arg1 == 0) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 24));
        ((DW4VC_208_2 *)(temp_a0))->vX((int)(0), (int)(arg2 * 6));
        return;
    }
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 24));
    ((DW4VC_208_2 *)(temp_a0_2))->vX((int)(0), (int)((arg2 * 6) + 3));
}

void FUN_0015dae0(igPointSpriteExtView *self, unsigned int index, float value)
{
    self->_vertexArray->vfunc_51(index, value);
}

void FUN_0015db00(Sdb00 *arg0, int arg1, V2f *arg2) {
    V2f v;
    v.x = arg2->x;
    v.y = arg2->y;
    arg0->o->vX(arg1, &v);
}

void FUN_0015db40(igPointSpriteExtView *self)
{
    self->_vertexArray->vfunc_55();
}

void FUN_0015db60(igPointSpriteExtView *self)
{
    self->_vertexArray->vfunc_56();
}

