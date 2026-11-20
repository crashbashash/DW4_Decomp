int igPsx2ParticleArray_Update(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status) {
    void *context;

    if (!self->_hardwareSupport) {
        return igParticleArray_Update((igParticleArray *)self, num, offset, status, time);
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
        context = (void *)igVisualContext_FindFirst();
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
    if (g_igPsx2DisableExt_ext12Enabled) {
        *status = 1;
        self->_currentTime = 1.0f + self->_particleLifeEnd;
    }
    return 1;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA_175ba0 *arg0) {
    if (arg0->f92 == 0) {
        Gap__Bec__ParticleArray__vfunc_27((igParticleArrayRefs *)arg0);
        return;
    }
    float t = arg0->f28;
    if (!(t <= arg0->f24 + arg0->f84) || t < arg0->f20) return;
        DAT_00560660[0] += arg0->f56;
        if (p2IsCapabilityEnabled(0x17) != 0) {
            p2DisableCapability(0x17);
        }
        p2DrawParticles(arg0->f100, arg0->f56, arg0->f52, arg0->f28);
        if (arg0->f104 != 0) {
            arg0->f112 = p2GetVif1WaitSequence();
        }
}

int Gap__Gfx__igPsx2ParticleArray__vfunc_24(PA_175c70 *arg0, int arg1) {
    ((DW4VC_100_1 *)arg0)->vX(arg1, arg0->n);
    return arg0->n - 1;
}

int *Gap__Gfx__igPsx2ParticleArray__vfunc_26(igPsx2ParticleArray *self, unsigned int index) {
    Psx2ParticleFormat *ps2Format;

    self->_currentEditIndex = index;
    if (self->_hardwareSupport == 0) {
        return (int *)Gap__Bec__ParticleArray__vfunc_24((ParticleArray *)self, index);
    }
    if (index >= (unsigned int) self->_arrayIndex) {
        return 0;
    }
    FUN_0015b1e0(&g_decodedParticle_00560ac0[0]);
    ps2Format = (Psx2ParticleFormat *)self->_ps2ParticleFormat;
    /* The decoded particle is a block of floats: positions, colours, sizes, angles, the texture coordinate. */
    FUN_001fdca0(ps2Format, index, (float *)&g_decodedParticle_00560ac0[0], (float *)&g_decodedParticle_00560acc[0], (float *)&g_decodedParticle_00560ad8[0]);
    FUN_001fdd60(ps2Format, index, (float *)&g_decodedParticle_00560ae4[0], (float *)&g_decodedParticle_00560af4[0], (float *)&g_decodedParticle_00560b04[0]);
    FUN_001fdeb0(ps2Format, index, (float *)&g_decodedParticle_00560b14[0], (float *)&g_decodedParticle_00560b1c[0], (float *)&g_decodedParticle_00560b24[0]);
    FUN_001fe100(ps2Format, index, (float *)&g_decodedParticle_00560b44[0], (float *)&g_decodedParticle_00560b40[0], (float *)&g_decodedParticle_00560b3c[0]);
    FUN_001fe260(ps2Format, index, (float *)&g_decodedParticle_00560b4c[0], (float *)&g_decodedParticle_00560b48[0]);
    FUN_001fe320(ps2Format, index, (float *)&g_decodedParticle_00560b2c[0]);
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

void Gap__Gfx__igPsx2ParticleArray__vfunc_34(igPsx2ParticleArray *self, float fp) {
    self->_particleLifeStart = fp;
    if (self->_timeControlState & 2) {
        *(float *)(self->_ps2ParticleFormat + 24) = fp;
        return;
    }
    *(int *)(self->_ps2ParticleFormat + 24) = 0xFF800000;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_35(igPsx2ParticleArray *self, float fparg0) {
    self->_particleLifeEnd = fparg0;
    if (self->_timeControlState & 2) {
        *(float *)(self->_ps2ParticleFormat + 28) = fparg0;
        return;
    }
    *(int *)(self->_ps2ParticleFormat + 28) = 0x7f800000;
}

void Gap__Gfx__igPsx2ParticleArray__vfunc_39(igPsx2ParticleArray *arg0, int arg1) {
    arg0->_timeControlState = arg1;
    ((DW4VC_136_1 *)(((char *)(arg0) + 0)))->vX((float)(arg0->_particleLifeStart));
    ((DW4VC_140_1 *)(((char *)(arg0) + 0)))->vX((float)(arg0->_particleLifeEnd));
}

void igPsx2ParticleArray_UserApplyWriteProxy(PA_1765f0 *arg0) {
    char *e;
    char *buf;
    unsigned i;
    char *d;
    if (arg0->flag != 0) {
        buf = ((AL *)((Gap::Core::igObject *)arg0)->getMemoryPool())->vX(arg0->stride * arg0->n);
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

void igPsx2ParticleArray_ReleaseDefaults(igPsx2ParticleArray *self) {
    long long sequence;

    if (self->_ps2ParticleFormat != 0) {
        if (self->_bSynchronize != 0) {
            sequence = self->_lSequence;
            if (sequence != 0) {
                p2WaitDmaSequence(1, sequence);
            }
        }
        Memory_FreeBuffer((void *)self->_ps2ParticleFormat);
    }
    igParticleArray_ReleaseDefaults((ParticleArray *)self);
}

/* Run the shared slot-57 step, then store the value into the +392 word of the object (past the
 * reflected igPsx2UserUCodeExt fields). */
void igPsx2PointSpriteExt_SetContext(void *self, int value) {
    igPointSpriteExt_SetContext((int)self, value);
    *(int *)((char *)self + 392) = value;
}

void igPsx2PointSpriteExt_Draw(int *arg0, int arg1, int arg2) {
    int *p;
    int *q;
    int s3, a1, a0_3, s3_2;
    if (!(((int *)arg0[6])[5] & 0x10)) {
        igPointSpriteExt_Draw((PointSpriteDraw *)arg0, arg1, arg2);
        return;
    }
    p = ((VA_1767c0 *)arg0[6])->vX();
    s3 = ((unsigned int)(*p & 0xF0000) >> 0x10) & 0xFF;
    q = ((VA_1767c0 *)arg0[6])->vX();
    a1 = *q;
    a0_3 = ((unsigned int)(a1 & 0x300000) >> 0x14) & 0xFF;
    s3_2 = DAT_004df6b0[a0_3 | (((s3 & 0xFF) == 2) * 4)];
    if (s3_2 != p2GetSpriteSizeMode()) {
        p2SetSpriteSizeMode(s3_2);
    }
    ((VB *)arg0[98])->vX(0x1000, arg1, arg2);
}

void igPsx2PointSpriteExt_SetSpriteSize(igPsx2PointSpriteExt *self, float size) {
    self->_spriteSize = size;
    p2SetSpriteHalfSize((0.5f * size));
}

void igPsx2PointSpriteExt_BeginSprites(UCodeState *state) {
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
        igPointSpriteExt_BeginSprites((OO *)state);
        return;
    }
    if (state->mode == 1) {
        igPointSpriteExt_BeginSprites((OO *)state);
    }
    state->loaded = 1;
}

void igPsx2PointSpriteExt_EndSprites(igPsx2PointSpriteExt *self) {
    int temp_a1;

    if (!(*(int *)((char *)(self->_vertexArray) + 20) & 0x10)) {
        igPointSpriteExt_EndSprites((Y *)self);
        return;
    }
    temp_a1 = self->_spriteSizeSpace;
    if (temp_a1 == 1) {
        igPointSpriteExt_EndSprites((Y *)self);
    }
    self->_inSpriteMode = 0;
}

void igPsx2PointSpriteExt_ConfigureVertexArray(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4) {
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
            igObject_Destroy((igObject *)a0);
        }
    }
    arg0->f24 = arg1;
    if (((V188 *)arg0)->v188(arg2) == 0) {
        igPointSpriteExt_ConfigureVertexArray((O_15cb50 *)arg0, (A1 *)arg1, arg2, arg3, (arg4 & ~0x10) | 4);
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

void igPsx2PointSpriteExt_SetPosition(igPsx2PointSpriteExt *self, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_116_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_SetPosition(self, arg1, arg2);
}

void igPsx2PointSpriteExt_GetPosition(igPsx2PointSpriteExt *self, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_120_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetPosition((igPsx2PointSpriteExt *)self, arg1, arg2);
}

void igPsx2PointSpriteExt_SetColorPacked(igPsx2PointSpriteExt *self, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_164_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_SetColorPacked((S740 *)self, arg1, arg2);
}

void igPsx2PointSpriteExt_SetColor(igPsx2PointSpriteExt *self, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_168_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_SetColor((S7c0 *)self, arg1, arg2);
}

void igPsx2PointSpriteExt_GetColorPacked(igPsx2PointSpriteExt *self, unsigned int arg1) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_172_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetColorPacked((igPointSpriteExtView *)self, arg1);
}

void igPsx2PointSpriteExt_GetColor(igPsx2PointSpriteExt *self, unsigned int arg1) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_176_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetColor((igPointSpriteExtView *)self, arg1);
}

void igPsx2PointSpriteExt_SetTextureCoord(W_1767c0 *arg0, int arg1, int arg2, float *arg3) {
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
    igPointSpriteExt_SetTextureCoord((O880 *)arg0, arg1, arg2, arg3);
}

void igPsx2PointSpriteExt_GetTextureCoord(igPsx2PointSpriteExt *self, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_204_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetTextureCoord((igPointSpriteExt *)self, arg1, arg2);
}

void igPsx2PointSpriteExt_GetTextureCoordPointer(igPsx2PointSpriteExt *self, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_208_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetTextureCoordPointer((igPointSpriteExt *)self, arg1, arg2);
}

void igPsx2PointSpriteExt_SetRadian(igPsx2PointSpriteExt *self) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_228_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_SetRadian((igPointSpriteExtView *)self);
}

void igPsx2PointSpriteExt_GetRadian(igPsx2PointSpriteExt *self) {
    void *temp_v1;

    temp_v1 = (void *)(self->_vertexArray);
    if (*(int *)((char *)(temp_v1) + 20) & 0x10) {
        ((DW4VC_232_0 *)(((char *)(temp_v1) + 0)))->vX();
        return;
    }
    igPointSpriteExt_GetRadian((igPointSpriteExtView *)self);
}

