int Gap__Gfx__igPsx2ParticleArray__vfunc_28(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status) {
    void *context;

    if (!self->_hardwareSupport) {
        return Gap__Gfx__igParticleArray__vfunc_28((PA *)self, num, offset, status, time);
    }
    self->_currentTime = time;
    if (!(time <= self->_particleLifeEnd + self->_particleLifetimeEndOffset)) {
        *status = 1;
        return 1;
    }
    if (time < self->_particleLifeStart) {
        *status = 2;
        return 1;
    }
    DAT_00560668[0]++;
    self->_particleNum = num;
    self->_particleOffset = offset;
    if (self->_context == 0) {
        context = (void *)FUN_00166d40();
        if (context != 0) {
            ((ParticleArrayCalls *)self)->configure(self->_particleLifeStart, self->_particleFormat, self->_particleLifeEnd, self->_maxNum, context);
            *status = 0;
        } else {
            *status = 1;
            return 0;
        }
    } else {
        *status = 0;
    }
    if (DAT_00554b68) {
        *status = 1;
        self->_currentTime = 1.0f + self->_particleLifeEnd;
    }
    return 1;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA_175ba0 *arg0) {
    if (arg0->f92 == 0) {
        Gap__Bec__ParticleArray__vfunc_27(arg0);
        return;
    }
    float t = arg0->f28;
    if (!(t <= arg0->f24 + arg0->f84) || t < arg0->f20) return;
        DAT_00560660[0] += arg0->f56;
        if (FUN_001e7560(0x17) != 0) {
            FUN_001e7500(0x17);
        }
        FUN_001fe390(arg0->f100, arg0->f56, arg0->f52, arg0->f28);
        if (arg0->f104 != 0) {
            arg0->f112 = p2GetVif1WaitSequence();
        }
}

int Gap__Gfx__igPsx2ParticleArray__vfunc_24(PA_175c70 *arg0, int arg1) {
    ((DW4VC_100_1 *)arg0)->vX(arg1, arg0->n);
    return arg0->n - 1;
}

int *Gap__Gfx__igPsx2ParticleArray__vfunc_26(igPsx2ParticleArray *self, unsigned int index) {
    int ps2Format;

    self->_currentEditIndex = index;
    if (self->_hardwareSupport == 0) {
        return (int *)Gap__Bec__ParticleArray__vfunc_24((ParticleArray *)self, index);
    }
    if (index >= (unsigned int) self->_arrayIndex) {
        return 0;
    }
    FUN_0015b1e0(&g_decodedParticle_00560ac0[0]);
    ps2Format = self->_ps2ParticleFormat;
    FUN_001fdca0(ps2Format, index, &g_decodedParticle_00560ac0[0], &g_decodedParticle_00560acc[0], &g_decodedParticle_00560ad8[0]);
    FUN_001fdd60(ps2Format, index, &g_decodedParticle_00560ae4[0], &g_decodedParticle_00560af4[0], &g_decodedParticle_00560b04[0]);
    FUN_001fdeb0(ps2Format, index, &g_decodedParticle_00560b14[0], &g_decodedParticle_00560b1c[0], &g_decodedParticle_00560b24[0]);
    FUN_001fe100(ps2Format, index, &g_decodedParticle_00560b44[0], &g_decodedParticle_00560b40[0], &g_decodedParticle_00560b3c[0]);
    FUN_001fe260(ps2Format, index, &g_decodedParticle_00560b4c[0], &g_decodedParticle_00560b48[0]);
    FUN_001fe320(ps2Format, index, &g_decodedParticle_00560b2c[0]);
    return &g_decodedParticle_00560ac0[0];
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_27(igPsx2ParticleArray *arg0, char *arg1) {
    char b[144];
    FUN_00175f20(&b[0], arg1);
    FUN_00175f20(&b[12], arg1 + 12);
    FUN_00175f20(&b[24], arg1 + 24);
    FUN_00175ef0(&b[36], arg1 + 36);
    FUN_00175ef0(&b[52], arg1 + 52);
    FUN_00175ef0(&b[68], arg1 + 68);
    FUN_00175ed0(&b[84], arg1 + 84);
    FUN_00175ed0(&b[92], arg1 + 92);
    FUN_00175ed0(&b[100], arg1 + 100);
    FUN_00175ed0(&b[108], arg1 + 108);
    FUN_00175ed0(&b[116], arg1 + 116);
    FUN_00175f20(&b[124], arg1 + 124);
    FUN_00175ed0(&b[136], arg1 + 136);
    ((DW4VC_100_2_175df0 *)(arg0))->vX(&b[0], arg0->_currentEditIndex);
}

void *FUN_00175ed0(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    return arg0;
}

void *FUN_00175ef0(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
    *(float *)((char *)(arg0) + 12) = (float) *(float *)((char *)(arg1) + 12);
    return arg0;
}

void *FUN_00175f20(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
    return arg0;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_34(igPsx2ParticleArray *arg0, float fp) {
    arg0->_particleLifeStart = fp;
    if (arg0->_timeControlState & 2) {
        *(float *)(arg0->_ps2ParticleFormat + 24) = fp;
        return;
    }
    *(int *)(arg0->_ps2ParticleFormat + 24) = 0xFF800000;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_35(int *arg0, float fparg0) {
    *(float *)(arg0 + 6) = fparg0;
    if (arg0[20] & 2) {
        *(float *)(arg0[25] + 28) = fparg0;
        return;
    }
    *(int *)(arg0[25] + 28) = 0x7f800000;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_39(igPsx2ParticleArray *arg0, int arg1) {
    arg0->_timeControlState = arg1;
    ((DW4VC_136_1 *)(((char *)(arg0) + 0)))->vX((float)(arg0->_particleLifeStart));
    ((DW4VC_140_1 *)(((char *)(arg0) + 0)))->vX((float)(arg0->_particleLifeEnd));
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_19(PA_1765f0 *arg0) {
    char *e;
    char *buf;
    unsigned i;
    char *d;
    if (arg0->flag != 0) {
        buf = ((AL *)igObject_GetAllocator(arg0))->vX(arg0->stride * arg0->n);
        for (i = 0; i < arg0->n; i++) {
            e = ((PV *)arg0)->vX(i);
            d = buf + i * arg0->stride;
            FUN_0015b820(d, e);
            FUN_0015b820(d + 12, e + 12);
            FUN_0015b820(d + 24, e + 24);
            FUN_0015b7f0(d + 36, e + 36);
            FUN_0015b7f0(d + 52, e + 52);
            FUN_0015b7f0(d + 68, e + 68);
            FUN_0015b7d0(d + 84, e + 84);
            FUN_0015b7d0(d + 92, e + 92);
            FUN_0015b7d0(d + 100, e + 100);
            FUN_0015b7d0(d + 108, e + 108);
            FUN_0015b7d0(d + 116, e + 116);
            FUN_0015b820(d + 124, e + 124);
            FUN_0015b7d0(d + 136, e + 136);
        }
        if (arg0->data != 0) {
            Memory_FreeBuffer(arg0->data);
        }
        arg0->data = buf;
    }
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_12(igPsx2ParticleArray *self) {
    long long sequence;

    if (self->_ps2ParticleFormat != 0) {
        if (self->_bSynchronize != 0) {
            sequence = self->_lSequence;
            if (sequence != 0) {
                p2WaitDmaSequence(1, sequence);
            }
        }
        Memory_FreeBuffer(self->_ps2ParticleFormat);
    }
    Gap__Bec__ParticleArray__vfunc_10((ParticleArray *)self);
}

/* Run the shared slot-57 step, then store the value into the +392 word of the object (past the
 * reflected igPsx2UserUCodeExt fields). */
void FUN_001767c0(void *self, int value) {
    FUN_0015cb50((int)self, value);
    *(int *)((char *)self + 392) = value;
}

void FUN_00176800(int *arg0, int arg1, int arg2) {
    int *p;
    int *q;
    int s3, a1, a0_3, s3_2;
    if (!(((int *)arg0[6])[5] & 0x10)) {
        FUN_0015d0d0(arg0);
        return;
    }
    p = ((VA_1767c0 *)arg0[6])->vX();
    s3 = ((unsigned int)(*p & 0xF0000) >> 0x10) & 0xFF;
    q = ((VA_1767c0 *)arg0[6])->vX();
    a1 = *q;
    a0_3 = ((unsigned int)(a1 & 0x300000) >> 0x14) & 0xFF;
    s3_2 = DAT_004df6b0[a0_3 | (((s3 & 0xFF) == 2) * 4)];
    if (s3_2 != FUN_001f7360(a0_3, a1)) {
        FUN_001f7340(s3_2);
    }
    ((VB *)arg0[98])->vX(0x1000, arg1, arg2);
}

void FUN_00176900(int arg0, float farg0) {
    *(float *)((char *)(arg0) + 28) = farg0;
    FUN_001f7370((0.5f * farg0));
}

void FUN_00176920(UCodeState *state) {
    UCodeAttr *attr = state->source->currentAttr();
    UCodeAttr *previous;

    if (attr != 0) {
        attr->_refCount = attr->_refCount + 1;
    }
    previous = state->attr;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    state->attr = attr;
    if (!(state->attr->flags & 0x10)) {
        FUN_0015ce90((OO *)state);
        return;
    }
    if (state->mode == 1) {
        FUN_0015ce90((OO *)state);
    }
    state->loaded = 1;
}

void FUN_001769f0(void *arg0) {
    int temp_a1;

    if (!(*(int *)((char *)(*(int *)((char *)(arg0) + 24)) + 20) & 0x10)) {
        FUN_0015cfb0((Y *)arg0);
        return;
    }
    temp_a1 = *(int *)((char *)(arg0) + 36);
    if (temp_a1 == 1) {
        FUN_0015cfb0((Y *)arg0);
    }
    *(char *)((char *)(arg0) + 32) = 0;
}

void FUN_00176a50(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4) {
    int sp6C;
    int temp_v1;
    R_1767c0 *a0;

    if (arg1 != 0) {
        ((R_1767c0 *)arg1)->rc = ((R_1767c0 *)arg1)->rc + 1;
    }
    a0 = (R_1767c0 *)arg0->f24;
    if (a0 != 0) {
        a0->rc = a0->rc - 1;
        if ((a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = arg1;
    if (((V188 *)arg0)->v188(arg2) == 0) {
        FUN_0015cb60((O_15cb50 *)arg0, (A1 *)arg1, arg2, arg3, (arg4 & ~0x10) | 4);
        return;
    }
    sp6C = *arg2;
    if ((((unsigned int)(*arg2 & 0xF0000) >> 0x10) & 0xFF) == 1) {
        temp_v1 = sp6C & 0xFFF0FFFF;
        sp6C = temp_v1;
        sp6C = sp6C | 0x20000;
    }
    arg1->v96((int *)&sp6C, arg3, arg4 | 0x10, arg0->f392);
}

int FUN_00176ba0(void *arg0) {
    return *(int *)((char *)(arg0) + 36) != 1;
}

void FUN_00176bb0(void *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_116_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d6c0(arg0, arg1, arg2);
}

void FUN_00176c00(void *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_120_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d700((igPsx2PointSpriteExt *)arg0, arg1, arg2);
}

void FUN_00176c50(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_164_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d740((S740 *)arg0, arg1, arg2);
}

void FUN_00176ca0(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_168_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d7c0((S7c0 *)arg0, arg1, arg2);
}

void FUN_00176cf0(void *arg0, unsigned int arg1) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_172_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d840((igPointSpriteExtView *)arg0, arg1);
}

void FUN_00176d40(void *arg0, unsigned int arg1) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_176_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015d860((igPointSpriteExtView *)arg0, arg1);
}

void FUN_00176d90(W_1767c0 *arg0, int arg1, int arg2, float *arg3) {
    /* matching construct: variant search — locals declared in reverse order, which sets their stack slots and registers */
    V2_1767c0 a;
    V2_1767c0 b;
    if (arg0->o->flags & 0x10) {
        arg0->o->get(0, arg2, &a.x);
        arg0->o->get(1, arg2, &b.x);
        if (arg1 == 0) {
            b.y = arg3[1];
            a.x = arg3[0];
            arg0->o->set(0, arg2, &a.x);
            arg0->o->set(1, arg2, &b.x);
            return;
        }
        a.y = arg3[1];
        b.x = arg3[0];
        arg0->o->set(0, arg2, &a.x);
        arg0->o->set(1, arg2, &b.x);
        return;
    }
    FUN_0015d880((O880 *)arg0, arg1, arg2, arg3);
}

void FUN_00176ed0(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_204_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015da00(arg0, arg1, arg2);
}

void FUN_00176f20(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_208_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015da70(arg0, arg1, arg2);
}

void FUN_00176f70(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_228_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015db40((igPointSpriteExtView *)arg0);
}

void FUN_00176fc0(void *arg0) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 24));
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_232_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    FUN_0015db60((igPointSpriteExtView *)arg0);
}

