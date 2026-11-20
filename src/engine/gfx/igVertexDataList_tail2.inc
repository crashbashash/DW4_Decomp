igMetaObject *igVertexDataList_GetElementMeta(void) {
    return g_igVertexData_metaObject;
}

void igDataList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void FUN_001815b0(int n, unsigned i, int base, int stride, CountedVertexWriter *a4, CountedVertexWriter *a5, float f) {
    int p2;
    int p;
    int x2;
    float A[3];
    unsigned end;
    igVec2f B;
    int x;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            
            p = base + i * stride;
            x = ParticleArray_GetPosition(p);
            ParticleArray_EvaluateLinearVec3((float *)A, (float *)x, (float *)(ParticleArray_GetVelocity(p)), f);
            x = ParticleArray_GetSize(p);
            ParticleArray_EvaluateLinearVec2(B.vec, (float *)x, (float *)(ParticleArray_GetSizeVelocity(p)), f);
            a5->v144(i, A);
            igPointSpriteExt_SetSize((igPointSpriteExt *)a5, i, B);
        }
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        
        p2 = base + i * stride;
        x2 = ParticleArray_GetPosition(p2);
        ParticleArray_EvaluateLinearVec3((float *)A, (float *)x2, (float *)(ParticleArray_GetVelocity(p2)), f);
        x2 = ParticleArray_GetSize(p2);
        ParticleArray_EvaluateLinearVec2(B.vec, (float *)x2, (float *)(ParticleArray_GetSizeVelocity(p2)), f);
        a4->v116(i, A);
        a4->v220(i, B);
    }
}

void ParticleArray_EvaluateLinearVec2(float *a, float *b, float *c, float s) {
    float t1;
    float u1;
    float t0;
    float u0;
    u1 = b[1];
    u0 = b[0];
    t0 = c[0];
    t1 = c[1];
    t0 = t0 * s;
    t1 = t1 * s;
    u0 = u0 + t0;
    u1 = u1 + t1;
    a[0] = u0;
    a[1] = u1;
}

int ParticleArray_GetSizeVelocity(int arg0) {
    return arg0 + 0x5C;
}

int ParticleArray_GetSize(int arg0) {
    return arg0 + 0x54;
}

void ParticleArray_EvaluateLinearVec3(float *a, float *b, float *c, float s) {
    float t0 = c[0] * s;
    float t1 = c[1] * s;
    float t2 = c[2] * s;
    float u0 = b[0] + t0;
    float u2 = b[2] + t2;
    float u1 = b[1] + t1;
    a[0] = u0;
    a[1] = u1;
    a[2] = u2;
}

int ParticleArray_GetVelocity(int arg0) {
    return arg0 + 0xC;
}

int ParticleArray_GetPosition(int a0)
{
    return a0;
}

void FUN_001818c0(int arg0, unsigned arg1, int arg2, int arg3, B_1818c0 *arg4, B_1818c0 *arg5, float fparg0) {
    int position[3];
    float size;
    float temp_f20;
    int temp_s1;
    int temp_s6_2;
    int temp_s1_3;
    B_1818c0 *t2;
    B_1818c0 *t;
    int temp_s0_2;
    int temp_s0;
    unsigned end;
    unsigned end2;
    int temp_s1_4;
    int temp_s1_2;
    int temp_s6_3;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s0, (float *)(ParticleArray_GetVelocity(temp_s1)), fparg0);
            temp_s0_2 = ParticleArray_GetSize(temp_s1);
            temp_s1_2 = ParticleArray_GetSizeVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s0_2, (float *)temp_s1_2, (float *)(ParticleArray_GetSizeAcceleration(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = ParticleArray_GetPosition(temp_s6_2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s1_3, (float *)(ParticleArray_GetVelocity(temp_s6_2)), fparg0);
            temp_s1_4 = ParticleArray_GetSize(temp_s6_2);
            temp_s6_3 = ParticleArray_GetSizeVelocity(temp_s6_2);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s1_4, (float *)temp_s6_3, (float *)(ParticleArray_GetSizeAcceleration(temp_s6_2)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v212(arg1, size);
        }
    }
}

void ParticleArray_EvaluateQuadraticFloat(float *a, float *b, float *c, float *d, float x, float y) {
    *a = *b + *c * x + *d * y;
}

int ParticleArray_GetSizeAcceleration(int arg0) {
    return arg0 + 0x64;
}

void FUN_00181b60(int n, unsigned int i, int particles, int particleSize, CountedVertexWriter *array, CountedVertexWriter *sprite, float time) {
    float position[3];
    igVec2f size;
    float timeSquared;
    int particle;
    int particle2;
    int pos2;
    CountedVertexWriter *old2;
    CountedVertexWriter *old;
    int sizePos;
    int pos;
    unsigned end;
    unsigned end2;
    int sizePos2;
    int sizeVel;
    int sizeVel2;

    timeSquared = time * time;
    if (sprite != 0) {
        if (array != 0) {
            array->refs = array->refs + 1;
        }
        old = sprite->f24;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)((long long)(int)old->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        sprite->f24 = array;
        end = i + n;
        for (; i < end; i++) {
            particle = particles + i * particleSize;
            pos = ParticleArray_GetPosition(particle);
            ParticleArray_EvaluateLinearVec3(position, (float *)pos, (float *)ParticleArray_GetVelocity(particle), time);
            sizePos = ParticleArray_GetSize(particle);
            sizeVel = ParticleArray_GetSizeVelocity(particle);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)sizePos, (float *)sizeVel, (float *)ParticleArray_GetSizeAcceleration(particle), time, timeSquared);
            sprite->v144(i, position);
            igPointSpriteExt_SetSize((igPointSpriteExt *)sprite, i, size);
        }
        old2 = sprite->f24;
        if (old2 != 0) {
            old2->refs = old2->refs - 1;
            if (((unsigned long long)((long long)(int)old2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old2);
            }
        }
        sprite->f24 = 0;
    } else {
        end2 = i + n;
        for (; i < end2; i++) {
            particle2 = particles + i * particleSize;
            pos2 = ParticleArray_GetPosition(particle2);
            ParticleArray_EvaluateLinearVec3(position, (float *)pos2, (float *)ParticleArray_GetVelocity(particle2), time);
            sizePos2 = ParticleArray_GetSize(particle2);
            sizeVel2 = ParticleArray_GetSizeVelocity(particle2);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)sizePos2, (float *)sizeVel2, (float *)ParticleArray_GetSizeAcceleration(particle2), time, timeSquared);
            array->v116(i, position);
            array->v220(i, size);
        }
    }
}

static inline void scale(float *r, const float *v, float s) { r[0] = v[0]*s; r[1] = v[1]*s; }

void ParticleArray_EvaluateQuadraticVec2(float *o, float *a, float *b, float *c, float x, float y) {
    /* matching construct: manual trial — b*x through an inline helper takes f5/f2, a[] f4/f1 */
    float u[2];
    float t0, t1;
    scale(u, b, x);
    t0 = a[0] + u[0] + c[0]*y;
    t1 = a[1] + u[1] + c[1]*y;
    o[0] = t0; o[1] = t1; }

void FUN_00181e30(int cnt, unsigned idx, int base, int stride, A_181e30 *arg4, Hold *arg5, float f) {
    char bufA[16];
    char bufB[16];
    if (arg5 != 0) {
        Obj_181e30 *old;
        int p;
        unsigned end;
        if (arg4 != 0) {
            ((Obj_181e30*)arg4)->ref = ((Obj_181e30*)arg4)->ref + 1;
        }
        old = arg5->obj;
        if (old != 0) {
            old->ref = old->ref - 1;
            if (((unsigned long long)((long long)old->ref << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        arg5->obj = (Obj_181e30*)arg4;
        end = idx + cnt;
        while (idx < end) {
            p = base + idx * stride;
            ParticleArray_EvaluateLinearVec3((float *)bufA, (float *)(ParticleArray_GetPosition(p)), (float *)(ParticleArray_GetVelocity(p)), f);
            ParticleArray_EvaluateLinearVec4((float *)bufB, (void *)(ParticleArray_GetColor(p)), (void *)(ParticleArray_GetColorVelocity(p)), f);
            arg5->s0(idx, bufA);
            arg5->s1(idx, (void*)igVec4f_PackColor((float *)bufB, 1));
            idx++;
        }
        old = arg5->obj;
        if (old != 0) {
            old->ref = old->ref - 1;
            if (((unsigned long long)((long long)old->ref << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        arg5->obj = 0;
        return;
    }
    {
        int p;
        unsigned end;
        end = idx + cnt;
        while (idx < end) {
            p = base + idx * stride;
            ParticleArray_EvaluateLinearVec3((float *)bufA, (float *)(ParticleArray_GetPosition(p)), (float *)(ParticleArray_GetVelocity(p)), f);
            ParticleArray_EvaluateLinearVec4((float *)bufB, (void *)(ParticleArray_GetColor(p)), (void *)(ParticleArray_GetColorVelocity(p)), f);
            arg4->s0(idx, bufA);
            arg4->s1(idx, (void*)igVec4f_PackColor((float *)bufB, 1));
            idx++;
        }
    }
}

void ParticleArray_EvaluateLinearVec4(float *dst, void *arg1, void *arg2, float fparg0) {
    float r0;
    float r1;
    float r2;
    float r3;
    r0 = *(float *)((char *)(arg1) + 0) + (*(float *)((char *)(arg2) + 0) * fparg0);
    r3 = *(float *)((char *)(arg1) + 12) + (*(float *)((char *)(arg2) + 12) * fparg0);
    r2 = *(float *)((char *)(arg1) + 8) + (*(float *)((char *)(arg2) + 8) * fparg0);
    r1 = *(float *)((char *)(arg1) + 4) + (*(float *)((char *)(arg2) + 4) * fparg0);
    dst[0] = r0;
    dst[1] = r1;
    dst[2] = r2;
    dst[3] = r3;
}

int ParticleArray_GetColorVelocity(int arg0) {
    return arg0 + 0x34;
}

int ParticleArray_GetColor(int arg0) {
    return arg0 + 0x24;
}

void FUN_00182110(int arg0, unsigned arg1, int arg2, int arg3, B_182110 *arg4, B_182110 *arg5, float fparg0) {
    int position[3];
    float size;
    igVec4f color;
    float temp_f20;
    int temp_s1;
    int temp_s0;
    int temp_s0_2;
    int temp_s6;
    int temp_s0_3;
    int temp_s2;
    int temp_s1_2;
    int temp_s1_3;
    int temp_s6_2;
    int temp_s1_4;
    B_182110 *t2;
    B_182110 *t;
    unsigned end;
    unsigned end2;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s0, (float *)(ParticleArray_GetVelocity(temp_s1)), fparg0);
            temp_s0_2 = ParticleArray_GetColor(temp_s1);
            temp_s6 = ParticleArray_GetColorVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s0_2, (igVec4f *)temp_s6, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s1)), fparg0, temp_f20);
            temp_s0_3 = ParticleArray_GetSize(temp_s1);
            ParticleArray_EvaluateLinearFloat(&size, (float *)temp_s0_3, (float *)(ParticleArray_GetSizeVelocity(temp_s1)), fparg0);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1_2 = ParticleArray_GetPosition(temp_s2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s1_2, (float *)(ParticleArray_GetVelocity(temp_s2)), fparg0);
            temp_s1_3 = ParticleArray_GetColor(temp_s2);
            temp_s6_2 = ParticleArray_GetColorVelocity(temp_s2);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s1_3, (igVec4f *)temp_s6_2, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s2)), fparg0, temp_f20);
            temp_s1_4 = ParticleArray_GetSize(temp_s2);
            ParticleArray_EvaluateLinearFloat(&size, (float *)temp_s1_4, (float *)(ParticleArray_GetSizeVelocity(temp_s2)), fparg0);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v212(arg1, size);
        }
    }
}

void ParticleArray_EvaluateLinearFloat(float *arg0, float *arg1, float *arg2, float fparg0) {
    *arg0 = *arg1 + (*arg2 * fparg0);
}

void ParticleArray_EvaluateQuadraticVec4(igVec4f *out, const igVec4f *a, const igVec4f *b, const igVec4f *c, float s, float t) {
    *out = *a + *b * s + *c * t;
}

int ParticleArray_GetColorAcceleration(int arg0) {
    return arg0 + 0x44;
}

void FUN_001824d0(int arg0, unsigned arg1, int arg2, int arg3, B_1824d0 *arg4, B_1824d0 *arg5, float fparg0) {
    int position[3];
    igVec2f size;
    igVec4f color;
    float sq;
    B_1824d0 *t;
    B_1824d0 *t2;
    unsigned end;
    int p;
    int a;
    int b;
    int p2;
    unsigned end2;
    int a2;
    int b2;

    sq = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            p = arg2 + arg1 * arg3;
            a = ParticleArray_GetPosition(p);
            b = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)a, (float *)b, fparg0);
            a = ParticleArray_GetColor(p);
            b = ParticleArray_GetColorVelocity(p);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)a, (igVec4f *)b, (igVec4f *)(ParticleArray_GetColorAcceleration(p)), fparg0, sq);
            a = ParticleArray_GetSize(p);
            b = ParticleArray_GetSizeVelocity(p);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)a, (float *)b, fparg0);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            p2 = arg2 + arg1 * arg3;
            a2 = ParticleArray_GetPosition(p2);
            b2 = ParticleArray_GetVelocity(p2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)a2, (float *)b2, fparg0);
            a2 = ParticleArray_GetColor(p2);
            b2 = ParticleArray_GetColorVelocity(p2);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)a2, (igVec4f *)b2, (igVec4f *)(ParticleArray_GetColorAcceleration(p2)), fparg0, sq);
            a2 = ParticleArray_GetSize(p2);
            b2 = ParticleArray_GetSizeVelocity(p2);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)a2, (float *)b2, fparg0);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v220(arg1, size);
        }
    }
}

void FUN_00182800(int arg0, unsigned arg1, int arg2, int arg3, Ref_182800 *arg4, Ref_182800 *arg5, float fparg0) {
    Ref_182800 *t;
    int temp_s1_2;
    int temp_s0_2;
    float temp_f20;
    Ref_182800 *t2;
    int temp_s6_2;
    int temp_s1_4;
    unsigned end2;
    int temp_s1;
    int position[3];
    int temp_s1_3;
    igVec4f color;
    float size;
    int temp_s0;
    unsigned end;
    int temp_s6_3;
    int temp_s0_3, temp_s2_2, temp_s1_5, temp_s0_4;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->refs = arg4->refs + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s0, (float *)(ParticleArray_GetVelocity(temp_s1)), fparg0);
            temp_s0_2 = ParticleArray_GetColor(temp_s1);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s0_2, (void *)(ParticleArray_GetColorVelocity(temp_s1)), fparg0);
            temp_s0_3 = ParticleArray_GetSize(temp_s1);
            temp_s2_2 = ParticleArray_GetSizeVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s0_3, (float *)temp_s2_2, (float *)(ParticleArray_GetSizeAcceleration(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->refs = t2->refs - 1;
            if (((unsigned long long)((long long)t2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = ParticleArray_GetPosition(temp_s6_2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s1_3, (float *)(ParticleArray_GetVelocity(temp_s6_2)), fparg0);
            temp_s1_4 = ParticleArray_GetColor(temp_s6_2);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s1_4, (void *)(ParticleArray_GetColorVelocity(temp_s6_2)), fparg0);
            temp_s1_5 = ParticleArray_GetSize(temp_s6_2);
            temp_s0_4 = ParticleArray_GetSizeVelocity(temp_s6_2);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s1_5, (float *)temp_s0_4, (float *)(ParticleArray_GetSizeAcceleration(temp_s6_2)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v212(arg1, size);
        }
    }
}

void FUN_00182b00(int arg0, unsigned arg1, int arg2, int arg3, VertexArrayTargetEx *arg4, VertexArrayTargetEx *arg5, float fparg0) {
    int position[3];
    igVec2f size;
    igVec4f color;
    float temp_f20;
    VertexArrayTargetEx *t;
    unsigned end2;
    unsigned end;
    VertexArrayTargetEx *t2;
    int temp_s2;
    int temp_s1;
    int temp_s1_2;
    int temp_s1_3;
    int temp_s2_2;
    int temp_s1_4;
    int temp_s0;
    int temp_s0_2;
    int temp_s0_3;
    int temp_s1_5;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1 = ParticleArray_GetPosition(temp_s2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s1, (float *)(ParticleArray_GetVelocity(temp_s2)), fparg0);
            temp_s1_2 = ParticleArray_GetColor(temp_s2);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s1_2, (void *)(ParticleArray_GetColorVelocity(temp_s2)), fparg0);
            temp_s1_3 = ParticleArray_GetSize(temp_s2);
            temp_s2_2 = ParticleArray_GetSizeVelocity(temp_s2);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)temp_s1_3, (float *)temp_s2_2, (float *)(ParticleArray_GetSizeAcceleration(temp_s2)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s1_4 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1_4);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s0, (float *)(ParticleArray_GetVelocity(temp_s1_4)), fparg0);
            temp_s0_2 = ParticleArray_GetColor(temp_s1_4);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s0_2, (void *)(ParticleArray_GetColorVelocity(temp_s1_4)), fparg0);
            temp_s0_3 = ParticleArray_GetSize(temp_s1_4);
            temp_s1_5 = ParticleArray_GetSizeVelocity(temp_s1_4);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)temp_s0_3, (float *)temp_s1_5, (float *)(ParticleArray_GetSizeAcceleration(temp_s1_4)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v220(arg1, size);
        }
    }
}

void FUN_00182e20(int arg0, unsigned arg1, int arg2, int arg3, B_182e20 *arg4, B_182e20 *arg5, float fparg0) {
    B_182e20 *t;
    int temp_s1_2;
    int temp_s0_2;
    float temp_f20;
    B_182e20 *t2;
    int temp_s6_2;
    int temp_s1_4;
    unsigned end2;
    int temp_s1;
    int position[3];
    int temp_s1_3;
    igVec4f color;
    int temp_s0;
    unsigned end;
    int temp_s6_3;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s0, (float *)(ParticleArray_GetVelocity(temp_s1)), fparg0);
            temp_s0_2 = ParticleArray_GetColor(temp_s1);
            temp_s1_2 = ParticleArray_GetColorVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s0_2, (igVec4f *)temp_s1_2, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = ParticleArray_GetPosition(temp_s6_2);
            ParticleArray_EvaluateLinearVec3((float *)position, (float *)temp_s1_3, (float *)(ParticleArray_GetVelocity(temp_s6_2)), fparg0);
            temp_s1_4 = ParticleArray_GetColor(temp_s6_2);
            temp_s6_3 = ParticleArray_GetColorVelocity(temp_s6_2);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s1_4, (igVec4f *)temp_s6_3, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s6_2)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
        }
    }
}

void FUN_001830b0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1830b0 *arg5, float fparg0) {
    float size;
    igVec3f position;
    igVec4f color;
    float f20 = fparg0 * fparg0;
    unsigned i = arg1;
    unsigned end;
    if (arg5 != 0) {
        igObject *t;
        igVertexArray1_1 *va = (igVertexArray1_1 *)arg5;
        if (arg4 != 0) ++arg4->_refCount;
        t = (igObject *)va->_memPool;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        va->_memPool = (int)arg4;
        end = i + arg0;
        while (i < end) {
            int e;
            int s7;
            int s6;
            int s8;
            int s0;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)s0, (float *)(ParticleArray_GetVelocity(e)), fparg0);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateLinearFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), fparg0);
            arg5->v144(i, &position);
            arg5->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
            i++;
        }
        t = (igObject *)va->_memPool;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        va->_memPool = 0;
        return;
    }
    end = i + arg0;
    {
        B_1830b0 *b = (B_1830b0 *)arg4;
        while (i < end) {
            int s0;
            int e;
            int s7;
            int s8;
            int s6;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)s0, (float *)(ParticleArray_GetVelocity(e)), fparg0);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateLinearFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), fparg0);
            b->v116(i, &position);
            b->v164(i, igVec4f_PackColor(color.vec, 1));
            b->v212(i, size);
            i++;
        }
    }
}

void FUN_001833c0(int n, unsigned int i, int particles, int particleSize, MeshTarget *array, MeshTarget *sprite, float time) {
    igVec3f position;
    igVec2f size;
    igVec4f color;
    float timeSquared;
    unsigned end;
    MeshTarget *old;
    int particle;
    timeSquared = time * time;
    if (sprite != 0) {
        if (array != 0) {
            array->f4 = array->f4 + 1;
        }
        old = sprite->f24;
        if (old != 0) {
            old->f4 = old->f4 - 1;
            if (((unsigned long long)((long long)old->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        sprite->f24 = array;
        end = i + n;
        for (; i < end; i++) {
            particle = particles + i * particleSize;
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)(ParticleArray_GetPosition(particle)), (float *)(ParticleArray_GetVelocity(particle)), time);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(particle)), (igVec4f *)(ParticleArray_GetColorVelocity(particle)), (igVec4f *)(ParticleArray_GetColorAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)(ParticleArray_GetSize(particle)), (float *)(ParticleArray_GetSizeVelocity(particle)), time);
            sprite->v144(i, &position);
            sprite->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)sprite, i, size);
        }
        old = sprite->f24;
        if (old != 0) {
            old->f4 = old->f4 - 1;
            if (((unsigned long long)((long long)old->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        sprite->f24 = 0;
    } else {
        end = i + n;
        for (; i < end; i++) {
            particle = particles + i * particleSize;
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)(ParticleArray_GetPosition(particle)), (float *)(ParticleArray_GetVelocity(particle)), time);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(particle)), (igVec4f *)(ParticleArray_GetColorVelocity(particle)), (igVec4f *)(ParticleArray_GetColorAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)(ParticleArray_GetSize(particle)), (float *)(ParticleArray_GetSizeVelocity(particle)), time);
            array->v116(i, &position);
            array->v164(i, igVec4f_PackColor(color.vec, 1));
            array->v220(i, size);
        }
    }
}

void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1836f0 *arg5, float fparg0) {
    float size;
    igVec3f position;
    igVec4f color;
    float f20 = fparg0 * fparg0;
    unsigned i = arg1;
    unsigned end;
    if (arg5 != 0) {
        igObject *t;
        if (arg4 != 0) ++arg4->_refCount;
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = arg4;
        end = i + arg0;
        while (i < end) {
            int e;
            int s7;
            int s6;
            int s8;
            int s0;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)s0, (float *)(ParticleArray_GetVelocity(e)), fparg0);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, f20);
            arg5->v144(i, &position);
            arg5->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
            i++;
        }
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = 0;
        return;
    }
    end = i + arg0;
    {
        B_1836f0 *b = (B_1836f0 *)arg4;
        while (i < end) {
            int s0;
            int e;
            int s7;
            int s8;
            int s6;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)s0, (float *)(ParticleArray_GetVelocity(e)), fparg0);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, f20);
            b->v116(i, &position);
            b->v164(i, igVec4f_PackColor(color.vec, 1));
            b->v212(i, size);
            i++;
        }
    }
}

void FUN_00183a20(int arg0, unsigned arg1, int arg2, int arg3, MeshTarget *arg4, MeshTarget *arg5, float fparg0) {
    igVec3f position;
    igVec2f size;
    igVec4f color;
    float temp_f20;
    unsigned end;
    MeshTarget *t;
    int e;
    int p, r;
    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)(ParticleArray_GetPosition(e)), (float *)(ParticleArray_GetVelocity(e)), fparg0);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(e)), (igVec4f *)(ParticleArray_GetColorVelocity(e)), (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, temp_f20);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(e)), (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, temp_f20);
            arg5->v144(arg1, &position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = 0;
    } else {
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            ParticleArray_EvaluateLinearVec3(position.vec, (float *)(ParticleArray_GetPosition(e)), (float *)(ParticleArray_GetVelocity(e)), fparg0);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(e)), (igVec4f *)(ParticleArray_GetColorVelocity(e)), (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, temp_f20);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(e)), (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, temp_f20);
            arg4->v116(arg1, &position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v220(arg1, size);
        }
    }
}

void FUN_00183d70(int n, unsigned i, int base, int stride, IndexedValueWriter *a4, IndexedValueWriter *a5, float f) {
    int position[4];
    float f2 = f * f;
    int y2;
    int y;
    unsigned end;
    int p;
    int x2;
    int x;
    unsigned end2;
    int p2;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            IndexedValueWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            p = base + i * stride;
            x = ParticleArray_GetPosition(p);
            y = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)x, (igVec3f *)y, (igVec3f *)(ParticleArray_GetAcceleration(p)), f, f2);
            a5->v144(i, position);
        }
        {
            IndexedValueWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end2 = i + n;
    for (; i < end2; i++) {
        p2 = base + i * stride;
        x2 = ParticleArray_GetPosition(p2);
        y2 = ParticleArray_GetVelocity(p2);
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)x2, (igVec3f *)y2, (igVec3f *)(ParticleArray_GetAcceleration(p2)), f, f2);
        a4->v116(i, position);
    }
}

void ParticleArray_EvaluateQuadraticVec3(igVec3f *out, const igVec3f *a, const igVec3f *b, const igVec3f *c, float s, float t) {
    *out = *a + *b * s + *c * t;
}

int ParticleArray_GetAcceleration(int arg0) {
    return arg0 + 0x18;
}

void FUN_00183fd0(int n, unsigned i, int base, int stride, Ref_183fd0 *a4, Ref_183fd0 *a5, float f) {
    int p; unsigned end; int x; int x2; int p2;
    float B; float A[3]; float ff;
    ff = f * f;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            Ref_183fd0 *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            p = base + i * stride;
            x = ParticleArray_GetPosition(p);
            x2 = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)A, (igVec3f *)x, (igVec3f *)x2, (igVec3f *)(ParticleArray_GetAcceleration(p)), f, ff);
            x = ParticleArray_GetSize(p);
            ParticleArray_EvaluateLinearFloat(&B, (float *)x, (float *)(ParticleArray_GetSizeVelocity(p)), f);
            a5->v144(i, A);
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)a5, i, B);
        }
        {
            Ref_183fd0 *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        p2 = base + i * stride;
        x = ParticleArray_GetPosition(p2);
        x2 = ParticleArray_GetVelocity(p2);
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)A, (igVec3f *)x, (igVec3f *)x2, (igVec3f *)(ParticleArray_GetAcceleration(p2)), f, ff);
        x = ParticleArray_GetSize(p2);
        ParticleArray_EvaluateLinearFloat(&B, (float *)x, (float *)(ParticleArray_GetSizeVelocity(p2)), f);
        a4->v116(i, A);
        a4->v212(i, B);
    }
}

/* matching construct: greedy declaration-order climb */
void FUN_00184240(int n, unsigned i, int base, int stride, CountedVertexWriter *a4, CountedVertexWriter *a5, float f) {
    int p2;
    int p;
    float A[3];
    unsigned end;
    igVec2f B;
    int x;
    int x2;
    float ff;
    ff = f * f;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            
            p = base + i * stride;
            x = ParticleArray_GetPosition(p);
            x2 = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)A, (igVec3f *)x, (igVec3f *)x2, (igVec3f *)(ParticleArray_GetAcceleration(p)), f, ff);
            x = ParticleArray_GetSize(p);
            ParticleArray_EvaluateLinearVec2(B.vec, (float *)x, (float *)(ParticleArray_GetSizeVelocity(p)), f);
            a5->v144(i, A);
            igPointSpriteExt_SetSize((igPointSpriteExt *)a5, i, B);
        }
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        
        p2 = base + i * stride;
        x = ParticleArray_GetPosition(p2);
        x2 = ParticleArray_GetVelocity(p2);
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)A, (igVec3f *)x, (igVec3f *)x2, (igVec3f *)(ParticleArray_GetAcceleration(p2)), f, ff);
        x2 = ParticleArray_GetSize(p2);
        ParticleArray_EvaluateLinearVec2(B.vec, (float *)x2, (float *)(ParticleArray_GetSizeVelocity(p2)), f);
        a4->v116(i, A);
        a4->v220(i, B);
    }
}

void FUN_001844d0(int arg0, unsigned int arg1, int arg2, int arg3, A4 *arg4, A5 *arg5, float fparg0) {
    float size;
    int position[3];
    float temp_f20 = fparg0 * fparg0;
    unsigned int i = arg1;
    if (arg5 != 0) {
        R_1844d0 *o;
        unsigned int end;
        if (arg4 != 0) {
            ((R_1844d0 *)arg4)->refs += 1;
        }
        o = arg5->obj;
        if (o != 0) {
            o->refs -= 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        arg5->obj = (R_1844d0 *)arg4;
        end = i + arg0;
        for (; i < end; i++) {
            int p; int a; int b;
            p = arg2 + (i * arg3);
            a = ParticleArray_GetPosition(p);
            b = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)a, (igVec3f *)b, (igVec3f *)(ParticleArray_GetAcceleration(p)), fparg0, temp_f20);
            a = ParticleArray_GetSize(p);
            b = ParticleArray_GetSizeVelocity(p);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)a, (float *)b, (float *)(ParticleArray_GetSizeAcceleration(p)), fparg0, temp_f20);
            arg5->v34(i, position);
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
        }
        o = arg5->obj;
        if (o != 0) {
            o->refs -= 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        arg5->obj = 0;
        return;
    }
    {
    int p; unsigned int end2; int a; int b;
    end2 = i + arg0;
    for (; i < end2; i++) {
        p = arg2 + (i * arg3);
        a = ParticleArray_GetPosition(p);
        b = ParticleArray_GetVelocity(p);
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)a, (igVec3f *)b, (igVec3f *)(ParticleArray_GetAcceleration(p)), fparg0, temp_f20);
        a = ParticleArray_GetSize(p);
        b = ParticleArray_GetSizeVelocity(p);
        ParticleArray_EvaluateQuadraticFloat(&size, (float *)a, (float *)b, (float *)(ParticleArray_GetSizeAcceleration(p)), fparg0, temp_f20);
        arg4->v27(i, position);
        arg4->v51(i, size);
    }
    }
}

void FUN_00184770(int arg0, unsigned arg1, int arg2, int arg3, B_184770 *arg4, B_184770 *arg5, float fparg0) {
    int position[3];
    igVec2f size;
    float sq;
    B_184770 *t;
    B_184770 *t2;
    unsigned end;
    int p;
    int a;
    int b;
    int p2;
    unsigned end2;

    sq = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            p = arg2 + arg1 * arg3;
            a = ParticleArray_GetPosition(p);
            b = ParticleArray_GetVelocity(p);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)a, (igVec3f *)b, (igVec3f *)(ParticleArray_GetAcceleration(p)), fparg0, sq);
            a = ParticleArray_GetSize(p);
            b = ParticleArray_GetSizeVelocity(p);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)a, (float *)b, (float *)(ParticleArray_GetSizeAcceleration(p)), fparg0, sq);
            arg5->v144(arg1, position);
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            p2 = arg2 + arg1 * arg3;
            a = ParticleArray_GetPosition(p2);
            b = ParticleArray_GetVelocity(p2);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)a, (igVec3f *)b, (igVec3f *)(ParticleArray_GetAcceleration(p2)), fparg0, sq);
            a = ParticleArray_GetSize(p2);
            b = ParticleArray_GetSizeVelocity(p2);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)a, (float *)b, (float *)(ParticleArray_GetSizeAcceleration(p2)), fparg0, sq);
            arg4->v116(arg1, position);
            arg4->v220(arg1, size);
        }
    }
}

void FUN_00184a30(int arg0, unsigned arg1, int arg2, int arg3, B_184a30 *arg4, B_184a30 *arg5, float fparg0) {
    int temp_s1_2;
    int temp_s1;
    igVec4f color;
    int temp_s1_3;
    float temp_f20;
    B_184a30 *t2;
    unsigned end;
    unsigned end2;
    int temp_s6;
    int temp_s6_2;
    B_184a30 *t;
    int position[3];
    int temp_s7_2;
    int temp_s1_4;
    int temp_s7;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s6 = ParticleArray_GetPosition(temp_s1);
            temp_s7 = ParticleArray_GetVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)temp_s6, (igVec3f *)temp_s7, (igVec3f *)(ParticleArray_GetAcceleration(temp_s1)), fparg0, temp_f20);
            temp_s1_2 = ParticleArray_GetColor(temp_s1);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s1_2, (void *)(ParticleArray_GetColorVelocity(temp_s1)), fparg0);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s1_3 = arg2 + arg1 * arg3;
            temp_s6_2 = ParticleArray_GetPosition(temp_s1_3);
            temp_s7_2 = ParticleArray_GetVelocity(temp_s1_3);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)temp_s6_2, (igVec3f *)temp_s7_2, (igVec3f *)(ParticleArray_GetAcceleration(temp_s1_3)), fparg0, temp_f20);
            temp_s1_4 = ParticleArray_GetColor(temp_s1_3);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s1_4, (void *)(ParticleArray_GetColorVelocity(temp_s1_3)), fparg0);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
        }
    }
}

void FUN_00184cc0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_184cc0 *arg5, float fparg0) {
    float size;
    igVec3f position;
    igVec4f color;
    float f20 = fparg0 * fparg0;
    unsigned i = arg1;
    unsigned end;
    if (arg5 != 0) {
        igObject *t;
        if (arg4 != 0) ++arg4->_refCount;
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = arg4;
        end = i + arg0;
        while (i < end) {
            int e;
            int s7;
            int s6;
            int s8;
            int s0;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)s0, (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, f20);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateLinearFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), fparg0);
            arg5->v144(i, &position);
            arg5->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
            i++;
        }
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = 0;
        return;
    }
    end = i + arg0;
    {
        B_184cc0 *b = (B_184cc0 *)arg4;
        while (i < end) {
            int s0;
            int e;
            int s7;
            int s8;
            int s6;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)s0, (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, f20);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateLinearFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), fparg0);
            b->v116(i, &position);
            b->v164(i, igVec4f_PackColor(color.vec, 1));
            b->v212(i, size);
            i++;
        }
    }
}

void FUN_00184ff0(int n, unsigned int i, int particles, int particleSize, MeshTarget *array, MeshTarget *sprite, float time) {
    igVec3f position;
    igVec2f size;
    igVec4f color;
    float timeSquared;
    unsigned end;
    MeshTarget *old;
    int particle;
    timeSquared = time * time;
    if (sprite != 0) {
        if (array != 0) {
            array->f4 = array->f4 + 1;
        }
        old = sprite->f24;
        if (old != 0) {
            old->f4 = old->f4 - 1;
            if (((unsigned long long)((long long)old->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        sprite->f24 = array;
        end = i + n;
        for (; i < end; i++) {
            particle = particles + i * particleSize;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)(ParticleArray_GetPosition(particle)), (igVec3f *)(ParticleArray_GetVelocity(particle)), (igVec3f *)(ParticleArray_GetAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(particle)), (igVec4f *)(ParticleArray_GetColorVelocity(particle)), (igVec4f *)(ParticleArray_GetColorAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)(ParticleArray_GetSize(particle)), (float *)(ParticleArray_GetSizeVelocity(particle)), time);
            sprite->v144(i, &position);
            sprite->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)sprite, i, size);
        }
        old = sprite->f24;
        if (old != 0) {
            old->f4 = old->f4 - 1;
            if (((unsigned long long)((long long)old->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        sprite->f24 = 0;
    } else {
        end = i + n;
        for (; i < end; i++) {
            particle = particles + i * particleSize;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)(ParticleArray_GetPosition(particle)), (igVec3f *)(ParticleArray_GetVelocity(particle)), (igVec3f *)(ParticleArray_GetAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(particle)), (igVec4f *)(ParticleArray_GetColorVelocity(particle)), (igVec4f *)(ParticleArray_GetColorAcceleration(particle)), time, timeSquared);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)(ParticleArray_GetSize(particle)), (float *)(ParticleArray_GetSizeVelocity(particle)), time);
            array->v116(i, &position);
            array->v164(i, igVec4f_PackColor(color.vec, 1));
            array->v220(i, size);
        }
    }
}

void FUN_00185340(int arg0, unsigned arg1, int arg2, int arg3, B_185340 *arg4, B_185340 *arg5, float fparg0) {
    int temp_s1_5;
    float size;
    int position[3];
    int temp_s1;
    int temp_s6_2;
    int temp_s0;
    int temp_s6;
    unsigned temp_s7;
    igVec4f color;
    B_185340 *temp_a0_2;
    int temp_s1_4;
    float temp_f20;
    unsigned temp_s7_2;
    int temp_s1_3;
    int temp_s1_2;
    int temp_s0_3;
    int temp_s2_2;
    int temp_s2;
    B_185340 *temp_a0;
    int temp_s0_2;

    temp_f20 = fparg0 * fparg0;
    if (arg5) {
        if (arg4) {
            arg4->f4 += 1;
        }
        temp_a0 = arg5->f24;
        if (temp_a0) {
            temp_a0->f4 -= 1;
            if (((unsigned long long)((long long)temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        arg5->f24 = arg4;
        temp_s7 = arg1 + arg0;
        for (; arg1 < temp_s7; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            temp_s6 = ParticleArray_GetVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)temp_s0, (igVec3f *)temp_s6, (igVec3f *)(ParticleArray_GetAcceleration(temp_s1)), fparg0, temp_f20);
            temp_s0_2 = ParticleArray_GetColor(temp_s1);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s0_2, (void *)(ParticleArray_GetColorVelocity(temp_s1)), fparg0);
            temp_s0_3 = ParticleArray_GetSize(temp_s1);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s0_3, (float *)((ParticleArray_GetSizeVelocity(temp_s1))), (float *)(ParticleArray_GetSizeAcceleration(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, arg1, size);
        }
        temp_a0_2 = arg5->f24;
        if (temp_a0_2) {
            temp_a0_2->f4 = temp_a0_2->f4 - 1;
            if (0 == ((unsigned long long)((long long)temp_a0_2->f4 << 0x29) >> 0x29)) {
                igObject_Destroy((igObject *)temp_a0_2);
            }
        }
        arg5->f24 = 0;
    } else {
        temp_s7_2 = arg1 + arg0;
        for (; arg1 < temp_s7_2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)(ParticleArray_GetPosition(temp_s2)), (igVec3f *)(ParticleArray_GetVelocity(temp_s2)), (igVec3f *)(ParticleArray_GetAcceleration(temp_s2)), fparg0, temp_f20);
            temp_s1_4 = ParticleArray_GetColor(temp_s2);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)temp_s1_4, (void *)(ParticleArray_GetColorVelocity(temp_s2)), fparg0);
            temp_s1_5 = ParticleArray_GetSize(temp_s2);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)temp_s1_5, (float *)((ParticleArray_GetSizeVelocity(temp_s2))), (float *)(ParticleArray_GetSizeAcceleration(temp_s2)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v212(arg1, size);
        }
    }
}

void FUN_00185670(int arg0, unsigned arg1, int arg2, int arg3, B_185670 *arg4, B_185670 *arg5, float fparg0) {
    unsigned end;
    float temp_f20;
    igVec3f position;
    int e;
    igVec2f size;
    igVec4f color;
    B_185670 *t;
    int p, r;
    temp_f20 = fparg0 * fparg0;
    if (arg5) {
        if (0 != arg4) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (0 != t) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)(ParticleArray_GetPosition(e)), (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, temp_f20);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)(ParticleArray_GetColor(e)), (void *)(ParticleArray_GetColorVelocity(e)), fparg0);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(e)), (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, temp_f20);
            arg5->v144(arg1, &position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (0 == ((unsigned long long)((long long)t->f4 << 0x29) >> 0x29)) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = 0;
    } else {
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)(ParticleArray_GetPosition(e)), (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, temp_f20);
            ParticleArray_EvaluateLinearVec4(color.vec, (void *)(ParticleArray_GetColor(e)), (void *)(ParticleArray_GetColorVelocity(e)), fparg0);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(e)), (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, temp_f20);
            arg4->v116(arg1, &position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v220(arg1, size);
        }
    }
}

void FUN_001859c0(int arg0, unsigned arg1, int arg2, int arg3, B_1859c0 *arg4, B_1859c0 *arg5, float fparg0) {
//DECL
    B_1859c0 *t;
    B_1859c0 *t2;
    float temp_f20;
    float position[4];
    igVec4f color;
    int temp_s0_2;
    int temp_s1;
    int temp_s0;
    int temp_s1_2;
    int temp_s1_4;
    int temp_s2;
    int temp_s1_3;
    int temp_s2_2;
    int temp_s6;
    int temp_s6_2;
    unsigned temp_s7;
    unsigned temp_s7_2;
//ENDDECL
    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        temp_s7 = arg1 + arg0;
        for (; arg1 < temp_s7; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = ParticleArray_GetPosition(temp_s1);
            temp_s6 = ParticleArray_GetVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)temp_s0, (igVec3f *)temp_s6, (igVec3f *)(ParticleArray_GetAcceleration(temp_s1)), fparg0, temp_f20);
            temp_s0_2 = ParticleArray_GetColor(temp_s1);
            temp_s1_2 = ParticleArray_GetColorVelocity(temp_s1);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s0_2, (igVec4f *)temp_s1_2, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        temp_s7_2 = arg1 + arg0;
        for (; arg1 < temp_s7_2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1_3 = ParticleArray_GetPosition(temp_s2);
            temp_s6_2 = ParticleArray_GetVelocity(temp_s2);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)temp_s1_3, (igVec3f *)temp_s6_2, (igVec3f *)(ParticleArray_GetAcceleration(temp_s2)), fparg0, temp_f20);
            temp_s1_4 = ParticleArray_GetColor(temp_s2);
            temp_s2_2 = ParticleArray_GetColorVelocity(temp_s2);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)temp_s1_4, (igVec4f *)temp_s2_2, (igVec4f *)(ParticleArray_GetColorAcceleration(temp_s2)), fparg0, temp_f20);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
        }
    }
}

void FUN_00185c80(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_185c80 *arg5, float fparg0) {
float size;
igVec3f position;
igVec4f color;
float f20;
unsigned end;
unsigned end2;
igObject *t;
igObject *t2;
int a1;
int b1;
int c1;
int d1;
int e1;
int f1;
int a2;
int b2;
int c2;
int d2;
int e2;
int f2;
    unsigned i = arg1;
    f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) ++arg4->_refCount;
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = arg4;
        end = i + arg0;
        while (i < end) {
            a1 = arg2 + i * arg3;
            b1 = ParticleArray_GetPosition(a1);
            c1 = ParticleArray_GetVelocity(a1);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)b1, (igVec3f *)c1, (igVec3f *)(ParticleArray_GetAcceleration(a1)), fparg0, f20);
            d1 = ParticleArray_GetColor(a1);
            e1 = ParticleArray_GetColorVelocity(a1);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)d1, (igVec4f *)e1, (igVec4f *)(ParticleArray_GetColorAcceleration(a1)), fparg0, f20);
            f1 = ParticleArray_GetSize(a1);
            ParticleArray_EvaluateLinearFloat(&size, (float *)f1, (float *)(ParticleArray_GetSizeVelocity(a1)), fparg0);
            arg5->v144(i, &position);
            arg5->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
            i++;
        }
        t2 = arg5->f24;
        if (t2 != 0) { --t2->_refCount; if ((t2->_refCount & 0x7fffff) == 0) igObject_Destroy(t2); }
        arg5->f24 = 0;
        return;
    }
    end2 = i + arg0;
    B_185c80 *b = (B_185c80 *)arg4;
    while (i < end2) {
        a2 = arg2 + i * arg3;
        b2 = ParticleArray_GetPosition(a2);
        c2 = ParticleArray_GetVelocity(a2);
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)b2, (igVec3f *)c2, (igVec3f *)(ParticleArray_GetAcceleration(a2)), fparg0, f20);
        d2 = ParticleArray_GetColor(a2);
        e2 = ParticleArray_GetColorVelocity(a2);
        ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)d2, (igVec4f *)e2, (igVec4f *)(ParticleArray_GetColorAcceleration(a2)), fparg0, f20);
        f2 = ParticleArray_GetSize(a2);
        ParticleArray_EvaluateLinearFloat(&size, (float *)f2, (float *)(ParticleArray_GetSizeVelocity(a2)), fparg0);
        b->v116(i, &position);
        b->v164(i, igVec4f_PackColor(color.vec, 1));
        b->v212(i, size);
        i++;
    }
}

void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0) {
    VertexSink *t;
    VertexSink *t2;
    float temp_f20;
    float position[3];
    int i2;
    igVec2f size;
    igVec4f color;
    unsigned end;
    int i1;
    int b2;
    int b1;
    int f1;
    int c1;
    int c2;
    int f2;
    int d1;
    int e1;
    int d2;
    int e2;
    unsigned end2;

    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            i1 = arg2 + arg1 * arg3;
            b1 = ParticleArray_GetPosition(i1);
            c1 = ParticleArray_GetVelocity(i1);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)b1, (igVec3f *)c1, (igVec3f *)(ParticleArray_GetAcceleration(i1)), fparg0, temp_f20);
            d1 = ParticleArray_GetColor(i1);
            e1 = ParticleArray_GetColorVelocity(i1);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)d1, (igVec4f *)e1, (igVec4f *)(ParticleArray_GetColorAcceleration(i1)), fparg0, temp_f20);
            f1 = ParticleArray_GetSize(i1);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)f1, (float *)(ParticleArray_GetSizeVelocity(i1)), fparg0);
            arg5->v144(arg1, position);
            arg5->v152(arg1, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, arg1, size);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            i2 = arg2 + arg1 * arg3;
            b2 = ParticleArray_GetPosition(i2);
            c2 = ParticleArray_GetVelocity(i2);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)b2, (igVec3f *)c2, (igVec3f *)(ParticleArray_GetAcceleration(i2)), fparg0, temp_f20);
            d2 = ParticleArray_GetColor(i2);
            e2 = ParticleArray_GetColorVelocity(i2);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)d2, (igVec4f *)e2, (igVec4f *)(ParticleArray_GetColorAcceleration(i2)), fparg0, temp_f20);
            f2 = ParticleArray_GetSize(i2);
            ParticleArray_EvaluateLinearVec2(size.vec, (float *)f2, (float *)(ParticleArray_GetSizeVelocity(i2)), fparg0);
            arg4->v116(arg1, position);
            arg4->v164(arg1, igVec4f_PackColor(color.vec, 1));
            arg4->v220(arg1, size);
        }
    }
}

void FUN_00186300(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_186300 *arg5, float fparg0) {
    float size;
    igVec3f position;
    igVec4f color;
    float f20 = fparg0 * fparg0;
    unsigned i = arg1;
    unsigned end;
    if (arg5 != 0) {
        igObject *t;
        if (arg4 != 0) ++arg4->_refCount;
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = arg4;
        end = i + arg0;
        while (i < end) {
            int e;
            int s7;
            int s6;
            int s8;
            int s0;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)s0, (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, f20);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, f20);
            arg5->v144(i, &position);
            arg5->v152(i, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetUniformSize((igPointSpriteExtView *)arg5, i, size);
            i++;
        }
        t = arg5->f24;
        if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); }
        arg5->f24 = 0;
        return;
    }
    end = i + arg0;
    {
        B_186300 *b = (B_186300 *)arg4;
        while (i < end) {
            int s0;
            int e;
            int s7;
            int s8;
            int s6;
            e = arg2 + i * arg3;
            s0 = ParticleArray_GetPosition(e);
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)&position, (igVec3f *)s0, (igVec3f *)(ParticleArray_GetVelocity(e)), (igVec3f *)(ParticleArray_GetAcceleration(e)), fparg0, f20);
            s7 = ParticleArray_GetColor(e);
            s6 = ParticleArray_GetColorVelocity(e);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)s7, (igVec4f *)s6, (igVec4f *)(ParticleArray_GetColorAcceleration(e)), fparg0, f20);
            s8 = ParticleArray_GetSize(e);
            ParticleArray_EvaluateQuadraticFloat(&size, (float *)s8, (float *)(ParticleArray_GetSizeVelocity(e)), (float *)(ParticleArray_GetSizeAcceleration(e)), fparg0, f20);
            b->v116(i, &position);
            b->v164(i, igVec4f_PackColor(color.vec, 1));
            b->v212(i, size);
            i++;
        }
    }
}

void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0) {
    int position[3];
    igVec4f color;
    igVec2f size;
    float f20;
    unsigned s5;
    unsigned s7;
    int s1;
    PackedVertexWriter *o;
    s5 = arg1;
    f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) arg4->refs = arg4->refs + 1;
        o = arg5->f24;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)o);
        }
        arg5->f24 = arg4;
        s7 = s5 + arg0;
        while (s5 < s7) {
            s1 = arg2 + s5 * arg3;
            ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)(ParticleArray_GetPosition(s1)), (igVec3f *)(ParticleArray_GetVelocity(s1)), (igVec3f *)(ParticleArray_GetAcceleration(s1)), fparg0, f20);
            ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(s1)), (igVec4f *)(ParticleArray_GetColorVelocity(s1)), (igVec4f *)(ParticleArray_GetColorAcceleration(s1)), fparg0, f20);
            ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(s1)), (float *)(ParticleArray_GetSizeVelocity(s1)), (float *)(ParticleArray_GetSizeAcceleration(s1)), fparg0, f20);
            arg5->v144(s5, position);
            arg5->v152(s5, igVec4f_PackColor(color.vec, 1));
            igPointSpriteExt_SetSize((igPointSpriteExt *)arg5, s5, size);
            s5 += 1;
        }
        o = arg5->f24;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)o);
        }
        arg5->f24 = 0;
        return;
    }
    s7 = s5 + arg0;
    while (s5 < s7) {
        s1 = arg2 + s5 * arg3;
        ParticleArray_EvaluateQuadraticVec3((igVec3f *)position, (igVec3f *)(ParticleArray_GetPosition(s1)), (igVec3f *)(ParticleArray_GetVelocity(s1)), (igVec3f *)(ParticleArray_GetAcceleration(s1)), fparg0, f20);
        ParticleArray_EvaluateQuadraticVec4(&color, (igVec4f *)(ParticleArray_GetColor(s1)), (igVec4f *)(ParticleArray_GetColorVelocity(s1)), (igVec4f *)(ParticleArray_GetColorAcceleration(s1)), fparg0, f20);
        ParticleArray_EvaluateQuadraticVec2(size.vec, (float *)(ParticleArray_GetSize(s1)), (float *)(ParticleArray_GetSizeVelocity(s1)), (float *)(ParticleArray_GetSizeAcceleration(s1)), fparg0, f20);
        arg4->v116(s5, position);
        arg4->v164(s5, igVec4f_PackColor(color.vec, 1));
        arg4->v220(s5, size);
        s5 += 1;
    }
}

