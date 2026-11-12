igMetaObject *Gap__Gfx__igVertexDataList__vfunc_24(void) {
    return g_igVertexData_metaObject[0];
}

void FUN_00181110(igDataList *arg0) {
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
    float B[2];
    float C[2];
    float D[2];
    int x;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            
            p = base + i * stride;
            x = FUN_001818b0(p);
            FUN_00181860((float *)A, (float *)x, (float *)(FUN_001818a0(p)), f);
            x = FUN_00181850(p);
            FUN_00181810((float *)B, (float *)x, (float *)(FUN_00181840(p)), f);
            a5->v144(i, A);
            C[0] = B[0]; C[1] = B[1];
            FUN_0015db00((Sdb00 *)a5, i, (V2f *)C);
        }
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        
        p2 = base + i * stride;
        x2 = FUN_001818b0(p2);
        FUN_00181860((float *)A, (float *)x2, (float *)(FUN_001818a0(p2)), f);
        x2 = FUN_00181850(p2);
        FUN_00181810((float *)B, (float *)x2, (float *)(FUN_00181840(p2)), f);
        a4->v116(i, A);
        D[0] = B[0]; D[1] = B[1];
        a4->v220(i, D);
    }
}

void FUN_00181810(float *a, float *b, float *c, float s) {
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

int FUN_00181840(int arg0) {
    return arg0 + 0x5C;
}

int FUN_00181850(int arg0) {
    return arg0 + 0x54;
}

void FUN_00181860(float *a, float *b, float *c, float s) {
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

int FUN_001818a0(int arg0) {
    return arg0 + 0xC;
}

int FUN_001818b0(int a0)
{
    return a0;
}

void FUN_001818c0(int arg0, unsigned arg1, int arg2, int arg3, B_1818c0 *arg4, B_1818c0 *arg5, float fparg0) {
    int sp90[3];
    float sp9C;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            FUN_00181860((float *)sp90, (float *)temp_s0, (float *)(FUN_001818a0(temp_s1)), fparg0);
            temp_s0_2 = FUN_00181850(temp_s1);
            temp_s1_2 = FUN_00181840(temp_s1);
            FUN_00181b30(&sp9C, (float *)temp_s0_2, (float *)temp_s1_2, (float *)(FUN_00181b50(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, sp90);
            FUN_0015dae0((igPointSpriteExtView *)arg5, arg1, sp9C);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = FUN_001818b0(temp_s6_2);
            FUN_00181860((float *)sp90, (float *)temp_s1_3, (float *)(FUN_001818a0(temp_s6_2)), fparg0);
            temp_s1_4 = FUN_00181850(temp_s6_2);
            temp_s6_3 = FUN_00181840(temp_s6_2);
            FUN_00181b30(&sp9C, (float *)temp_s1_4, (float *)temp_s6_3, (float *)(FUN_00181b50(temp_s6_2)), fparg0, temp_f20);
            arg4->v116(arg1, sp90);
            arg4->v212(arg1, sp9C);
        }
    }
}

void FUN_00181b30(float *a, float *b, float *c, float *d, float x, float y) {
    *a = *b + *c * x + *d * y;
}

int FUN_00181b50(int arg0) {
    return arg0 + 0x64;
}

static inline void scale(float *r, const float *v, float s) { r[0] = v[0]*s; r[1] = v[1]*s; }

void FUN_00181df0(float *o, float *a, float *b, float *c, float x, float y) {
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
                igObject_Destroy(old);
            }
        }
        arg5->obj = (Obj_181e30*)arg4;
        end = idx + cnt;
        while (idx < end) {
            p = base + idx * stride;
            FUN_00181860((float *)bufA, (float *)(FUN_001818b0(p)), (float *)(FUN_001818a0(p)), f);
            FUN_00182090((void *)bufB, (void *)(FUN_00182100(p)), (void *)(FUN_001820f0(p)), f);
            arg5->s0(idx, bufA);
            arg5->s1(idx, (void*)FUN_001931b0((float *)bufB, 1));
            idx++;
        }
        old = arg5->obj;
        if (old != 0) {
            old->ref = old->ref - 1;
            if (((unsigned long long)((long long)old->ref << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
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
            FUN_00181860((float *)bufA, (float *)(FUN_001818b0(p)), (float *)(FUN_001818a0(p)), f);
            FUN_00182090((void *)bufB, (void *)(FUN_00182100(p)), (void *)(FUN_001820f0(p)), f);
            arg4->s0(idx, bufA);
            arg4->s1(idx, (void*)FUN_001931b0((float *)bufB, 1));
            idx++;
        }
    }
}

void FUN_00182090(void *arg0, void *arg1, void *arg2, float fparg0) {
    float r0;
    float r1;
    float r2;
    float r3;
    r0 = *(float *)((char *)(arg1) + 0) + (*(float *)((char *)(arg2) + 0) * fparg0);
    r3 = *(float *)((char *)(arg1) + 12) + (*(float *)((char *)(arg2) + 12) * fparg0);
    r2 = *(float *)((char *)(arg1) + 8) + (*(float *)((char *)(arg2) + 8) * fparg0);
    r1 = *(float *)((char *)(arg1) + 4) + (*(float *)((char *)(arg2) + 4) * fparg0);
    *(float *)((char *)(arg0) + 0) = r0;
    *(float *)((char *)(arg0) + 4) = r1;
    *(float *)((char *)(arg0) + 8) = r2;
    *(float *)((char *)(arg0) + 12) = r3;
}

int FUN_001820f0(int arg0) {
    return arg0 + 0x34;
}

int FUN_00182100(int arg0) {
    return arg0 + 0x24;
}

void FUN_00182110(int arg0, unsigned arg1, int arg2, int arg3, B_182110 *arg4, B_182110 *arg5, float fparg0) {
    int spB0[3];
    float spBC;
    float spA0[4];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            FUN_00181860((float *)spB0, (float *)temp_s0, (float *)(FUN_001818a0(temp_s1)), fparg0);
            temp_s0_2 = FUN_00182100(temp_s1);
            temp_s6 = FUN_001820f0(temp_s1);
            FUN_00182440(spA0, temp_s0_2, temp_s6, FUN_001824c0(temp_s1), fparg0, temp_f20);
            temp_s0_3 = FUN_00181850(temp_s1);
            FUN_00182420(&spBC, (float *)temp_s0_3, (float *)(FUN_00181840(temp_s1)), fparg0);
            arg5->v144(arg1, spB0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, arg1, spBC);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1_2 = FUN_001818b0(temp_s2);
            FUN_00181860((float *)spB0, (float *)temp_s1_2, (float *)(FUN_001818a0(temp_s2)), fparg0);
            temp_s1_3 = FUN_00182100(temp_s2);
            temp_s6_2 = FUN_001820f0(temp_s2);
            FUN_00182440(spA0, temp_s1_3, temp_s6_2, FUN_001824c0(temp_s2), fparg0, temp_f20);
            temp_s1_4 = FUN_00181850(temp_s2);
            FUN_00182420(&spBC, (float *)temp_s1_4, (float *)(FUN_00181840(temp_s2)), fparg0);
            arg4->v116(arg1, spB0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
            arg4->v212(arg1, spBC);
        }
    }
}

void FUN_00182420(float *arg0, float *arg1, float *arg2, float fparg0) {
    *arg0 = *arg1 + (*arg2 * fparg0);
}

int FUN_001824c0(int arg0) {
    return arg0 + 0x44;
}

void FUN_001824d0(int arg0, unsigned arg1, int arg2, int arg3, B_1824d0 *arg4, B_1824d0 *arg5, float fparg0) {
    int spD0[3];
    Vec2 spC8;
    int spA0[4];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            p = arg2 + arg1 * arg3;
            a = FUN_001818b0(p);
            b = FUN_001818a0(p);
            FUN_00181860((float *)spD0, (float *)a, (float *)b, fparg0);
            a = FUN_00182100(p);
            b = FUN_001820f0(p);
            FUN_00182440(spA0, a, b, FUN_001824c0(p), fparg0, sq);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181810((float *)&spC8, (float *)a, (float *)b, fparg0);
            arg5->v144(arg1, spD0);
            arg5->v152(arg1, FUN_001931b0((float *)spA0, 1));
            { Vec2 copy = spC8; FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&copy); };
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            p2 = arg2 + arg1 * arg3;
            a2 = FUN_001818b0(p2);
            b2 = FUN_001818a0(p2);
            FUN_00181860((float *)spD0, (float *)a2, (float *)b2, fparg0);
            a2 = FUN_00182100(p2);
            b2 = FUN_001820f0(p2);
            FUN_00182440(spA0, a2, b2, FUN_001824c0(p2), fparg0, sq);
            a2 = FUN_00181850(p2);
            b2 = FUN_00181840(p2);
            FUN_00181810((float *)&spC8, (float *)a2, (float *)b2, fparg0);
            arg4->v116(arg1, spD0);
            arg4->v164(arg1, FUN_001931b0((float *)spA0, 1));
            arg4->v220(arg1, spC8);
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
    int spA0[3];
    int temp_s1_3;
    int sp90[4];
    float spAC;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            FUN_00181860((float *)spA0, (float *)temp_s0, (float *)(FUN_001818a0(temp_s1)), fparg0);
            temp_s0_2 = FUN_00182100(temp_s1);
            FUN_00182090((void *)sp90, (void *)temp_s0_2, (void *)(FUN_001820f0(temp_s1)), fparg0);
            temp_s0_3 = FUN_00181850(temp_s1);
            temp_s2_2 = FUN_00181840(temp_s1);
            FUN_00181b30(&spAC, (float *)temp_s0_3, (float *)temp_s2_2, (float *)(FUN_00181b50(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, spA0);
            arg5->v152(arg1, FUN_001931b0((float *)sp90, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, arg1, spAC);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->refs = t2->refs - 1;
            if (((unsigned long long)((long long)t2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = FUN_001818b0(temp_s6_2);
            FUN_00181860((float *)spA0, (float *)temp_s1_3, (float *)(FUN_001818a0(temp_s6_2)), fparg0);
            temp_s1_4 = FUN_00182100(temp_s6_2);
            FUN_00182090((void *)sp90, (void *)temp_s1_4, (void *)(FUN_001820f0(temp_s6_2)), fparg0);
            temp_s1_5 = FUN_00181850(temp_s6_2);
            temp_s0_4 = FUN_00181840(temp_s6_2);
            FUN_00181b30(&spAC, (float *)temp_s1_5, (float *)temp_s0_4, (float *)(FUN_00181b50(temp_s6_2)), fparg0, temp_f20);
            arg4->v116(arg1, spA0);
            arg4->v164(arg1, FUN_001931b0((float *)sp90, 1));
            arg4->v212(arg1, spAC);
        }
    }
}

void FUN_00182b00(int arg0, unsigned arg1, int arg2, int arg3, VertexArrayTargetEx *arg4, VertexArrayTargetEx *arg5, float fparg0) {
    int spC0[3];
    TexCoordPair spB8;
    TexCoordPair spB0;
    TexCoordPair spA8;
    int sp90[4];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1 = FUN_001818b0(temp_s2);
            FUN_00181860((float *)spC0, (float *)temp_s1, (float *)(FUN_001818a0(temp_s2)), fparg0);
            temp_s1_2 = FUN_00182100(temp_s2);
            FUN_00182090((void *)sp90, (void *)temp_s1_2, (void *)(FUN_001820f0(temp_s2)), fparg0);
            temp_s1_3 = FUN_00181850(temp_s2);
            temp_s2_2 = FUN_00181840(temp_s2);
            FUN_00181df0((float *)&spB8, (float *)temp_s1_3, (float *)temp_s2_2, (float *)(FUN_00181b50(temp_s2)), fparg0, temp_f20);
            arg5->v144(arg1, spC0);
            arg5->v152(arg1, FUN_001931b0((float *)sp90, 1));
            spB0 = spB8;
            FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&spB0);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s1_4 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1_4);
            FUN_00181860((float *)spC0, (float *)temp_s0, (float *)(FUN_001818a0(temp_s1_4)), fparg0);
            temp_s0_2 = FUN_00182100(temp_s1_4);
            FUN_00182090((void *)sp90, (void *)temp_s0_2, (void *)(FUN_001820f0(temp_s1_4)), fparg0);
            temp_s0_3 = FUN_00181850(temp_s1_4);
            temp_s1_5 = FUN_00181840(temp_s1_4);
            FUN_00181df0((float *)&spB8, (float *)temp_s0_3, (float *)temp_s1_5, (float *)(FUN_00181b50(temp_s1_4)), fparg0, temp_f20);
            arg4->v116(arg1, spC0);
            arg4->v164(arg1, FUN_001931b0((float *)sp90, 1));
            spA8 = spB8;
            arg4->v220(arg1, &spA8);
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
    int spA0[3];
    int temp_s1_3;
    float sp90[4];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            FUN_00181860((float *)spA0, (float *)temp_s0, (float *)(FUN_001818a0(temp_s1)), fparg0);
            temp_s0_2 = FUN_00182100(temp_s1);
            temp_s1_2 = FUN_001820f0(temp_s1);
            FUN_00182440(sp90, temp_s0_2, temp_s1_2, FUN_001824c0(temp_s1), fparg0, temp_f20);
            arg5->v144(arg1, spA0);
            arg5->v152(arg1, FUN_001931b0(sp90, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s6_2 = arg2 + arg1 * arg3;
            temp_s1_3 = FUN_001818b0(temp_s6_2);
            FUN_00181860((float *)spA0, (float *)temp_s1_3, (float *)(FUN_001818a0(temp_s6_2)), fparg0);
            temp_s1_4 = FUN_00182100(temp_s6_2);
            temp_s6_3 = FUN_001820f0(temp_s6_2);
            FUN_00182440(sp90, temp_s1_4, temp_s6_3, FUN_001824c0(temp_s6_2), fparg0, temp_f20);
            arg4->v116(arg1, spA0);
            arg4->v164(arg1, FUN_001931b0(sp90, 1));
        }
    }
}

void FUN_001830b0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1830b0 *arg5, float fparg0) {
    float spBC;
    V3_1830b0 spB0;
    V4_1830b0 spA0;
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
            s0 = FUN_001818b0(e);
            FUN_00181860((float *)&spB0, (float *)s0, (float *)(FUN_001818a0(e)), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00182420(&spBC, (float *)s8, (float *)(FUN_00181840(e)), fparg0);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0((float *)&spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spBC);
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
            s0 = FUN_001818b0(e);
            FUN_00181860((float *)&spB0, (float *)s0, (float *)(FUN_001818a0(e)), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00182420(&spBC, (float *)s8, (float *)(FUN_00181840(e)), fparg0);
            b->v116(i, &spB0);
            b->v164(i, FUN_001931b0((float *)&spA0, 1));
            b->v212(i, spBC);
            i++;
        }
    }
}

void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1836f0 *arg5, float fparg0) {
    float spBC;
    V3_1836f0 spB0;
    V4_1836f0 spA0;
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
            s0 = FUN_001818b0(e);
            FUN_00181860((float *)&spB0, (float *)s0, (float *)(FUN_001818a0(e)), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, (float *)s8, (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, f20);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0((float *)&spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spBC);
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
            s0 = FUN_001818b0(e);
            FUN_00181860((float *)&spB0, (float *)s0, (float *)(FUN_001818a0(e)), fparg0);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, (float *)s8, (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, f20);
            b->v116(i, &spB0);
            b->v164(i, FUN_001931b0((float *)&spA0, 1));
            b->v212(i, spBC);
            i++;
        }
    }
}

void FUN_00183a20(int arg0, unsigned arg1, int arg2, int arg3, MeshTarget *arg4, MeshTarget *arg5, float fparg0) {
    MeshVec3 spD0;
    MeshVec2 spC8;
    MeshVec2 spC0;
    MeshVec2 spB8;
    MeshVec4 spA0;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            FUN_00181860((float *)&spD0, (float *)(FUN_001818b0(e)), (float *)(FUN_001818a0(e)), fparg0);
            FUN_00182440(&spA0, FUN_00182100(e), FUN_001820f0(e), FUN_001824c0(e), fparg0, temp_f20);
            FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(e)), (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, temp_f20);
            arg5->v144(arg1, &spD0);
            arg5->v152(arg1, FUN_001931b0((float *)&spA0, 1));
            spC0 = spC8;
            FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&spC0);
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg5->f24 = 0;
    } else {
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            FUN_00181860((float *)&spD0, (float *)(FUN_001818b0(e)), (float *)(FUN_001818a0(e)), fparg0);
            FUN_00182440(&spA0, FUN_00182100(e), FUN_001820f0(e), FUN_001824c0(e), fparg0, temp_f20);
            FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(e)), (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, temp_f20);
            arg4->v116(arg1, &spD0);
            arg4->v164(arg1, FUN_001931b0((float *)&spA0, 1));
            spB8 = spC8;
            arg4->v220(arg1, &spB8);
        }
    }
}

void FUN_00183d70(int n, unsigned i, int base, int stride, IndexedValueWriter *a4, IndexedValueWriter *a5, float f) {
    int sp90[4];
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
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            p = base + i * stride;
            x = FUN_001818b0(p);
            y = FUN_001818a0(p);
            FUN_00183f60(sp90, x, y, FUN_00183fc0(p), f, f2);
            a5->v144(i, sp90);
        }
        {
            IndexedValueWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end2 = i + n;
    for (; i < end2; i++) {
        p2 = base + i * stride;
        x2 = FUN_001818b0(p2);
        y2 = FUN_001818a0(p2);
        FUN_00183f60(sp90, x2, y2, FUN_00183fc0(p2), f, f2);
        a4->v116(i, sp90);
    }
}

int FUN_00183fc0(int arg0) {
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
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            p = base + i * stride;
            x = FUN_001818b0(p);
            x2 = FUN_001818a0(p);
            FUN_00183f60(A, x, x2, FUN_00183fc0(p), f, ff);
            x = FUN_00181850(p);
            FUN_00182420(&B, (float *)x, (float *)(FUN_00181840(p)), f);
            a5->v144(i, A);
            FUN_0015dae0((igPointSpriteExtView *)a5, i, B);
        }
        {
            Ref_183fd0 *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        p2 = base + i * stride;
        x = FUN_001818b0(p2);
        x2 = FUN_001818a0(p2);
        FUN_00183f60(A, x, x2, FUN_00183fc0(p2), f, ff);
        x = FUN_00181850(p2);
        FUN_00182420(&B, (float *)x, (float *)(FUN_00181840(p2)), f);
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
    float B[2];
    float C[2];
    float D[2];
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
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            
            p = base + i * stride;
            x = FUN_001818b0(p);
            x2 = FUN_001818a0(p);
            FUN_00183f60(A, x, x2, FUN_00183fc0(p), f, ff);
            x = FUN_00181850(p);
            FUN_00181810((float *)B, (float *)x, (float *)(FUN_00181840(p)), f);
            a5->v144(i, A);
            C[0] = B[0]; C[1] = B[1];
            FUN_0015db00((Sdb00 *)a5, i, (V2f *)C);
        }
        {
            CountedVertexWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        
        p2 = base + i * stride;
        x = FUN_001818b0(p2);
        x2 = FUN_001818a0(p2);
        FUN_00183f60(A, x, x2, FUN_00183fc0(p2), f, ff);
        x2 = FUN_00181850(p2);
        FUN_00181810((float *)B, (float *)x2, (float *)(FUN_00181840(p2)), f);
        a4->v116(i, A);
        D[0] = B[0]; D[1] = B[1];
        a4->v220(i, D);
    }
}

void FUN_001844d0(int arg0, unsigned int arg1, int arg2, int arg3, A4 *arg4, A5 *arg5, float fparg0) {
    float spAC;
    int spA0[3];
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
                igObject_Destroy(o);
            }
        }
        arg5->obj = (R_1844d0 *)arg4;
        end = i + arg0;
        for (; i < end; i++) {
            int p; int a; int b;
            p = arg2 + (i * arg3);
            a = FUN_001818b0(p);
            b = FUN_001818a0(p);
            FUN_00183f60(spA0, a, b, FUN_00183fc0(p), fparg0, temp_f20);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181b30(&spAC, (float *)a, (float *)b, (float *)(FUN_00181b50(p)), fparg0, temp_f20);
            arg5->v34(i, spA0);
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spAC);
        }
        o = arg5->obj;
        if (o != 0) {
            o->refs -= 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
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
        a = FUN_001818b0(p);
        b = FUN_001818a0(p);
        FUN_00183f60(spA0, a, b, FUN_00183fc0(p), fparg0, temp_f20);
        a = FUN_00181850(p);
        b = FUN_00181840(p);
        FUN_00181b30(&spAC, (float *)a, (float *)b, (float *)(FUN_00181b50(p)), fparg0, temp_f20);
        arg4->v27(i, spA0);
        arg4->v51(i, spAC);
    }
    }
}

void FUN_00184770(int arg0, unsigned arg1, int arg2, int arg3, B_184770 *arg4, B_184770 *arg5, float fparg0) {
    int spC0[3];
    Vec2 spB8;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            p = arg2 + arg1 * arg3;
            a = FUN_001818b0(p);
            b = FUN_001818a0(p);
            FUN_00183f60(spC0, a, b, FUN_00183fc0(p), fparg0, sq);
            a = FUN_00181850(p);
            b = FUN_00181840(p);
            FUN_00181df0((float *)&spB8, (float *)a, (float *)b, (float *)(FUN_00181b50(p)), fparg0, sq);
            arg5->v144(arg1, spC0);
            { Vec2 copy = spB8; FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&copy); };
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            p2 = arg2 + arg1 * arg3;
            a = FUN_001818b0(p2);
            b = FUN_001818a0(p2);
            FUN_00183f60(spC0, a, b, FUN_00183fc0(p2), fparg0, sq);
            a = FUN_00181850(p2);
            b = FUN_00181840(p2);
            FUN_00181df0((float *)&spB8, (float *)a, (float *)b, (float *)(FUN_00181b50(p2)), fparg0, sq);
            arg4->v116(arg1, spC0);
            arg4->v220(arg1, spB8);
        }
    }
}

void FUN_00184a30(int arg0, unsigned arg1, int arg2, int arg3, B_184a30 *arg4, B_184a30 *arg5, float fparg0) {
    int temp_s1_2;
    int temp_s1;
    int spA0[4];
    int temp_s1_3;
    float temp_f20;
    B_184a30 *t2;
    unsigned end;
    unsigned end2;
    int temp_s6;
    int temp_s6_2;
    B_184a30 *t;
    int spB0[3];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s6 = FUN_001818b0(temp_s1);
            temp_s7 = FUN_001818a0(temp_s1);
            FUN_00183f60(spB0, temp_s6, temp_s7, FUN_00183fc0(temp_s1), fparg0, temp_f20);
            temp_s1_2 = FUN_00182100(temp_s1);
            FUN_00182090((void *)spA0, (void *)temp_s1_2, (void *)(FUN_001820f0(temp_s1)), fparg0);
            arg5->v144(arg1, spB0);
            arg5->v152(arg1, FUN_001931b0((float *)spA0, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            temp_s1_3 = arg2 + arg1 * arg3;
            temp_s6_2 = FUN_001818b0(temp_s1_3);
            temp_s7_2 = FUN_001818a0(temp_s1_3);
            FUN_00183f60(spB0, temp_s6_2, temp_s7_2, FUN_00183fc0(temp_s1_3), fparg0, temp_f20);
            temp_s1_4 = FUN_00182100(temp_s1_3);
            FUN_00182090((void *)spA0, (void *)temp_s1_4, (void *)(FUN_001820f0(temp_s1_3)), fparg0);
            arg4->v116(arg1, spB0);
            arg4->v164(arg1, FUN_001931b0((float *)spA0, 1));
        }
    }
}

void FUN_00184cc0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_184cc0 *arg5, float fparg0) {
    float spBC;
    V3_184cc0 spB0;
    V4_184cc0 spA0;
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
            s0 = FUN_001818b0(e);
            FUN_00183f60(&spB0, s0, FUN_001818a0(e), FUN_00183fc0(e), fparg0, f20);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00182420(&spBC, (float *)s8, (float *)(FUN_00181840(e)), fparg0);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0((float *)&spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spBC);
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
            s0 = FUN_001818b0(e);
            FUN_00183f60(&spB0, s0, FUN_001818a0(e), FUN_00183fc0(e), fparg0, f20);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00182420(&spBC, (float *)s8, (float *)(FUN_00181840(e)), fparg0);
            b->v116(i, &spB0);
            b->v164(i, FUN_001931b0((float *)&spA0, 1));
            b->v212(i, spBC);
            i++;
        }
    }
}

void FUN_00185340(int arg0, unsigned arg1, int arg2, int arg3, B_185340 *arg4, B_185340 *arg5, float fparg0) {
    int temp_s1_5;
    float spBC;
    int spB0[3];
    int temp_s1;
    int temp_s6_2;
    int temp_s0;
    int temp_s6;
    unsigned temp_s7;
    int spA0[4];
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
                igObject_Destroy(temp_a0);
            }
        }
        arg5->f24 = arg4;
        temp_s7 = arg1 + arg0;
        for (; arg1 < temp_s7; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            temp_s6 = FUN_001818a0(temp_s1);
            FUN_00183f60(spB0, temp_s0, temp_s6, FUN_00183fc0(temp_s1), fparg0, temp_f20);
            temp_s0_2 = FUN_00182100(temp_s1);
            FUN_00182090((void *)spA0, (void *)temp_s0_2, (void *)(FUN_001820f0(temp_s1)), fparg0);
            temp_s0_3 = FUN_00181850(temp_s1);
            FUN_00181b30(&spBC, (float *)temp_s0_3, (float *)((FUN_00181840(temp_s1))), (float *)(FUN_00181b50(temp_s1)), fparg0, temp_f20);
            arg5->v144(arg1, spB0);
            arg5->v152(arg1, FUN_001931b0((float *)spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, arg1, spBC);
        }
        temp_a0_2 = arg5->f24;
        if (temp_a0_2) {
            temp_a0_2->f4 = temp_a0_2->f4 - 1;
            if (0 == ((unsigned long long)((long long)temp_a0_2->f4 << 0x29) >> 0x29)) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg5->f24 = 0;
    } else {
        temp_s7_2 = arg1 + arg0;
        for (; arg1 < temp_s7_2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            FUN_00183f60(spB0, (FUN_001818b0(temp_s2)), (FUN_001818a0(temp_s2)), FUN_00183fc0(temp_s2), fparg0, temp_f20);
            temp_s1_4 = FUN_00182100(temp_s2);
            FUN_00182090((void *)spA0, (void *)temp_s1_4, (void *)(FUN_001820f0(temp_s2)), fparg0);
            temp_s1_5 = FUN_00181850(temp_s2);
            FUN_00181b30(&spBC, (float *)temp_s1_5, (float *)((FUN_00181840(temp_s2))), (float *)(FUN_00181b50(temp_s2)), fparg0, temp_f20);
            arg4->v116(arg1, spB0);
            arg4->v164(arg1, FUN_001931b0((float *)spA0, 1));
            arg4->v212(arg1, spBC);
        }
    }
}

void FUN_00185670(int arg0, unsigned arg1, int arg2, int arg3, B_185670 *arg4, B_185670 *arg5, float fparg0) {
    unsigned end;
    float temp_f20;
    V3_185670 spD0;
    int e;
    V2_185670 spC8;
    V4_185670 spA0;
    B_185670 *t;
    V2_185670 spC0;
    V2_185670 spB8;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            FUN_00183f60(&spD0, FUN_001818b0(e), FUN_001818a0(e), FUN_00183fc0(e), fparg0, temp_f20);
            FUN_00182090((void *)&spA0, (void *)(FUN_00182100(e)), (void *)(FUN_001820f0(e)), fparg0);
            FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(e)), (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, temp_f20);
            arg5->v144(arg1, &spD0);
            arg5->v152(arg1, FUN_001931b0((float *)&spA0, 1));
            spC0 = spC8;
            FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&spC0);
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (0 == ((unsigned long long)((long long)t->f4 << 0x29) >> 0x29)) {
                igObject_Destroy(t);
            }
        }
        arg5->f24 = 0;
    } else {
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            e = arg2 + arg1 * arg3;
            FUN_00183f60(&spD0, FUN_001818b0(e), FUN_001818a0(e), FUN_00183fc0(e), fparg0, temp_f20);
            FUN_00182090((void *)&spA0, (void *)(FUN_00182100(e)), (void *)(FUN_001820f0(e)), fparg0);
            FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(e)), (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, temp_f20);
            arg4->v116(arg1, &spD0);
            arg4->v164(arg1, FUN_001931b0((float *)&spA0, 1));
            spB8 = spC8;
            arg4->v220(arg1, &spB8);
        }
    }
}

void FUN_001859c0(int arg0, unsigned arg1, int arg2, int arg3, B_1859c0 *arg4, B_1859c0 *arg5, float fparg0) {
//DECL
    B_1859c0 *t;
    B_1859c0 *t2;
    float temp_f20;
    float spB0[4];
    float spA0[4];
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        temp_s7 = arg1 + arg0;
        for (; arg1 < temp_s7; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            temp_s6 = FUN_001818a0(temp_s1);
            FUN_00183f60(spB0, temp_s0, temp_s6, FUN_00183fc0(temp_s1), fparg0, temp_f20);
            temp_s0_2 = FUN_00182100(temp_s1);
            temp_s1_2 = FUN_001820f0(temp_s1);
            FUN_00182440(spA0, temp_s0_2, temp_s1_2, FUN_001824c0(temp_s1), fparg0, temp_f20);
            arg5->v144(arg1, spB0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        temp_s7_2 = arg1 + arg0;
        for (; arg1 < temp_s7_2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1_3 = FUN_001818b0(temp_s2);
            temp_s6_2 = FUN_001818a0(temp_s2);
            FUN_00183f60(spB0, temp_s1_3, temp_s6_2, FUN_00183fc0(temp_s2), fparg0, temp_f20);
            temp_s1_4 = FUN_00182100(temp_s2);
            temp_s2_2 = FUN_001820f0(temp_s2);
            FUN_00182440(spA0, temp_s1_4, temp_s2_2, FUN_001824c0(temp_s2), fparg0, temp_f20);
            arg4->v116(arg1, spB0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
        }
    }
}

void FUN_00185c80(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_185c80 *arg5, float fparg0) {
float spBC;
V3_185c80 spB0;
V4_185c80 spA0;
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
            b1 = FUN_001818b0(a1);
            c1 = FUN_001818a0(a1);
            FUN_00183f60(&spB0, b1, c1, FUN_00183fc0(a1), fparg0, f20);
            d1 = FUN_00182100(a1);
            e1 = FUN_001820f0(a1);
            FUN_00182440(&spA0, d1, e1, FUN_001824c0(a1), fparg0, f20);
            f1 = FUN_00181850(a1);
            FUN_00182420(&spBC, (float *)f1, (float *)(FUN_00181840(a1)), fparg0);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0((float *)&spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spBC);
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
        b2 = FUN_001818b0(a2);
        c2 = FUN_001818a0(a2);
        FUN_00183f60(&spB0, b2, c2, FUN_00183fc0(a2), fparg0, f20);
        d2 = FUN_00182100(a2);
        e2 = FUN_001820f0(a2);
        FUN_00182440(&spA0, d2, e2, FUN_001824c0(a2), fparg0, f20);
        f2 = FUN_00181850(a2);
        FUN_00182420(&spBC, (float *)f2, (float *)(FUN_00181840(a2)), fparg0);
        b->v116(i, &spB0);
        b->v164(i, FUN_001931b0((float *)&spA0, 1));
        b->v212(i, spBC);
        i++;
    }
}

void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0) {
    VertexSink *t;
    VertexSink *t2;
    float temp_f20;
    float spD0[3];
    int i2;
    TexCoordPair spC8;
    float spA0[4];
    TexCoordPair spC0;
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
    TexCoordPair spB8;
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
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        end = arg1 + arg0;
        for (; arg1 < end; arg1++) {
            i1 = arg2 + arg1 * arg3;
            b1 = FUN_001818b0(i1);
            c1 = FUN_001818a0(i1);
            FUN_00183f60(spD0, b1, c1, FUN_00183fc0(i1), fparg0, temp_f20);
            d1 = FUN_00182100(i1);
            e1 = FUN_001820f0(i1);
            FUN_00182440(spA0, d1, e1, FUN_001824c0(i1), fparg0, temp_f20);
            f1 = FUN_00181850(i1);
            FUN_00181810((float *)&spC8, (float *)f1, (float *)(FUN_00181840(i1)), fparg0);
            arg5->v144(arg1, spD0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
            spC0 = spC8;
            FUN_0015db00((Sdb00 *)arg5, arg1, (V2f *)&spC0);
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        end2 = arg1 + arg0;
        for (; arg1 < end2; arg1++) {
            i2 = arg2 + arg1 * arg3;
            b2 = FUN_001818b0(i2);
            c2 = FUN_001818a0(i2);
            FUN_00183f60(spD0, b2, c2, FUN_00183fc0(i2), fparg0, temp_f20);
            d2 = FUN_00182100(i2);
            e2 = FUN_001820f0(i2);
            FUN_00182440(spA0, d2, e2, FUN_001824c0(i2), fparg0, temp_f20);
            f2 = FUN_00181850(i2);
            FUN_00181810((float *)&spC8, (float *)f2, (float *)(FUN_00181840(i2)), fparg0);
            arg4->v116(arg1, spD0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
            spB8 = spC8;
            arg4->v220(arg1, &spB8);
        }
    }
}

void FUN_00186300(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_186300 *arg5, float fparg0) {
    float spBC;
    V3_186300 spB0;
    V4_186300 spA0;
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
            s0 = FUN_001818b0(e);
            FUN_00183f60(&spB0, s0, FUN_001818a0(e), FUN_00183fc0(e), fparg0, f20);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, (float *)s8, (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, f20);
            arg5->v144(i, &spB0);
            arg5->v152(i, FUN_001931b0((float *)&spA0, 1));
            FUN_0015dae0((igPointSpriteExtView *)arg5, i, spBC);
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
            s0 = FUN_001818b0(e);
            FUN_00183f60(&spB0, s0, FUN_001818a0(e), FUN_00183fc0(e), fparg0, f20);
            s7 = FUN_00182100(e);
            s6 = FUN_001820f0(e);
            FUN_00182440(&spA0, s7, s6, FUN_001824c0(e), fparg0, f20);
            s8 = FUN_00181850(e);
            FUN_00181b30(&spBC, (float *)s8, (float *)(FUN_00181840(e)), (float *)(FUN_00181b50(e)), fparg0, f20);
            b->v116(i, &spB0);
            b->v164(i, FUN_001931b0((float *)&spA0, 1));
            b->v212(i, spBC);
            i++;
        }
    }
}

void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0) {
    int spD0[3];
    int spA0[4];
    TexCoordPairXY spC8;
    TexCoordPairXY spC0;
    TexCoordPairXY spB8;
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
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg5->f24 = arg4;
        s7 = s5 + arg0;
        while (s5 < s7) {
            s1 = arg2 + s5 * arg3;
            FUN_00183f60(spD0, FUN_001818b0(s1), FUN_001818a0(s1), FUN_00183fc0(s1), fparg0, f20);
            FUN_00182440(spA0, FUN_00182100(s1), FUN_001820f0(s1), FUN_001824c0(s1), fparg0, f20);
            FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(s1)), (float *)(FUN_00181840(s1)), (float *)(FUN_00181b50(s1)), fparg0, f20);
            arg5->v144(s5, spD0);
            arg5->v152(s5, FUN_001931b0((float *)spA0, 1));
            spC0.x = spC8.x;
            spC0.y = spC8.y;
            FUN_0015db00((Sdb00 *)arg5, s5, (V2f *)&spC0);
            s5 += 1;
        }
        o = arg5->f24;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg5->f24 = 0;
        return;
    }
    s7 = s5 + arg0;
    while (s5 < s7) {
        s1 = arg2 + s5 * arg3;
        FUN_00183f60(spD0, FUN_001818b0(s1), FUN_001818a0(s1), FUN_00183fc0(s1), fparg0, f20);
        FUN_00182440(spA0, FUN_00182100(s1), FUN_001820f0(s1), FUN_001824c0(s1), fparg0, f20);
        FUN_00181df0((float *)&spC8, (float *)(FUN_00181850(s1)), (float *)(FUN_00181840(s1)), (float *)(FUN_00181b50(s1)), fparg0, f20);
        arg4->v116(s5, spD0);
        arg4->v164(s5, FUN_001931b0((float *)spA0, 1));
        spB8.x = spC8.x;
        spB8.y = spC8.y;
        arg4->v220(s5, &spB8);
        s5 += 1;
    }
}

