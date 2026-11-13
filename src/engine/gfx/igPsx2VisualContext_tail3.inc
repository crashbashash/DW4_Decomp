void Gap__Gfx__igPsx2VisualContext__vfunc_65(VisualContextView *arg0, void *color) {
    unsigned int value = FUN_001931b0((float *)color, 1);
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((value >> 1) & 0x7F000000) + (value & 0x01000000);
    lo = value & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    FUN_001f7250(arg0->f3bc);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_66(VisualContextView *arg0, unsigned int arg1) {
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((arg1 >> 1) & 0x7F000000) + (arg1 & 0x01000000);
    lo = arg1 & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    FUN_001f7250(arg0->f3bc);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_67(S_16d010 *arg0, float *arg1) {
    unsigned int t;
    float f;
    t = (arg0->f956 >> 24) & 0xFF;
    f = (float)t;

    arg1[0] = 0.0078125f * f;
    t = (arg0->f956 >> 16) & 0xFF;
    f = (float)t;

    arg1[1] = 0.00392156886f * f;
    t = (arg0->f956 >> 8) & 0xFF;
    f = (float)t;

    arg1[2] = 0.00392156886f * f;
    t = arg0->f956 & 0xFF;
    f = (float)t;

    arg1[3] = 0.00392156886f * f;
}

unsigned int Gap__Gfx__igPsx2VisualContext__vfunc_68(void *arg0) {
    unsigned int t = *(unsigned int *)((char *)arg0 + 956);
    unsigned int a = (t & 0x80000000) >> 7;
    return (t & 0xFFFFFF) | (a + (((t & 0xFF000000) - a) * 2));
}

void Gap__Gfx__igPsx2VisualContext__vfunc_69(void *arg0, int *arg1) {
    *(int *)((char *)arg0 + 952) = (int) *arg1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_70(int *arg0, void *arg1)
{
  int new_var;
  new_var = *((int *) (((char *) arg1) + 952));
  *arg0 = 0;
  *arg0 = new_var;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_59(int *arg0, Obj_16d190 *arg1) {
    Obj_16d190 *o;
    if ((Obj_16d190 *)arg0[235] == arg1) {
        DAT_005608c0[0] += 1;
    }
    if (arg1) {
        arg1->refs++;
    }
    o = (Obj_16d190 *)arg0[235];
    if (o != 0) {
        --o->refs;
        if ((o->refs & 0x7fffff) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0[235] = (int)arg1;
    if (arg1 != 0) {
        ((VC_16d190 *)arg0)->vX(0, 0);
    }
}

/* IgPsx2VisualContext vtable slot 61, a plain getter that returns the reflected field
 * _pVertexArray (the vertex-array object reference, +940). */

int Gap__Gfx__igPsx2VisualContext__vfunc_61(igPsx2VisualContext *self) {
    return self->_pVertexArray;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_63(int *arg0, Obj_16d250 *arg1) {
    Obj_16d250 *o;
    if ((Obj_16d250 *)arg0[237] == arg1) {
        DAT_005608c4[0] += 1;
    }
    if (arg1) {
        arg1->refs++;
    }
    o = (Obj_16d250 *)arg0[237];
    if (o != 0) {
        --o->refs;
        if ((o->refs & 0x7fffff) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0[237] = (int)arg1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_64(void *arg0) {
    return *(int *)((char *)(arg0) + 948);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_60(int *arg0, Obj_16d300 *arg1) {
    Obj_16d300 *o;
    if ((Obj_16d300 *)arg0[236] == arg1) {
        DAT_005608c8[0] += 1;
    }
    if (arg1) {
        arg1->refs++;
    }
    o = (Obj_16d300 *)arg0[236];
    if (o != 0) {
        --o->refs;
        if ((o->refs & 0x7fffff) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0[236] = (int)arg1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_62(void *arg0) {
    return *(int *)((char *)(arg0) + 944);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_74(struct R_16d660 *arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp8C;
    int sp88;
    int *p;
    int s6, i, *s1, *s0;
    int *rec;
    int *tbl;
    struct Q_16d660 *q;
    int t;
    if (arg0->f940 != 0) {
        sp8C = 0;
        sp88 = 0;
        s6 = FUN_00177010((igPsx2VisualContext *)arg0, &sp8C, &sp88, -1, -1);
        FUN_0016cc60((char *)arg0);
        p = (int *)(arg0->f948[2] + arg4 * 4);
        switch (arg1) {
        case 0:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(arg0, *p, arg3, sp8C, sp88, p2DrawLineStrip, 0);
                arg3 += *p;
                p++;
            }
            break;
        case 2:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(arg0, *p, arg3, sp8C, sp88, p2DrawTriangleFan, p2DrawIndexedTriangleFan);
                arg3 += *p;
                p++;
            }
            break;
        case 1:
            i = 0;
            if (arg0->f944 != 0) {
                for (; i < arg2; i++) {
                    FUN_0016d910(arg0, *p, arg3, sp8C, sp88, p2DrawTriangleStrip, p2DrawIndexedTriangleStrip);
                    arg3 += *p;
                    p++;
                }
            } else {
                tbl = arg0->f940->f8;
                t = arg0->f708 + 11; rec = (int *)tbl[t];
                s1 = 0;
                if (rec != 0) {
                    s1 = (int *)((char *)rec + arg3 * 8);
                }
                s0 = 0;
                if (tbl[2] != 0) {
                    s0 = (int *)(tbl[2] + arg3 * 4);
                }
                FUN_0016db20(arg0, arg3);
                t = arg3 * 12;
                p2SetVertexArrays(sp8C + t, sp88 + t, s0, s1);
                p2DrawTriangleStrips(arg2, p);
            }
            break;
        }
        FUN_0016cd10(arg0);
        if (s6 == 1) {
            q = arg0->f940;
            FUN_0016e140(q, (int)p2GetVif1WaitSequence());
        }
        q = arg0->f940;
        if (q->f20 & 4) {
            q->f64 = p2GetVif1WaitSequence();
        }
    } else {
        FUN_0017f080(arg0, arg1 + 0x2000);
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_173(A_16dbe0 *arg0) {
    N *var_s0;

    if (arg0->f60 != 0) {
        arg0->f68 = __floatdisf(arg0->f56->vX());
    }
    var_s0 = arg0->f1552;
    if (var_s0 != 0) {
        while (var_s0 != 0) {
            if (var_s0->f16 != 0) {
                if (var_s0->f8 == 0) {
                    FUN_001f6f50(&var_s0->f24[0]);
                    var_s0->f936 = arg0->f56->vX();
                }
                var_s0->f8 = var_s0->f8 - 1;
            }
            var_s0 = var_s0->f952;
        }
    }
    return 1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_174(A_16dca0 *arg0) {
    float f20 = 0.0f;
    N_16dca0 *n;
    if (arg0->b60 != 0) {
        f20 = dptofp(arg0->f56->v100());
        arg0->f56->v116();
    }
    p2EndFrame();
    p2SwapBuffers();
    if (arg0->b60 != 0) {
        arg0->v112(f20, f20 - arg0->f68);
        arg0->v116(f20);
        arg0->f64 = 0;
    }
    n = arg0->f1552;
    if (n != 0) {
      while (n != 0) {
        if (n->b16 != 0 && n->f8 == -n->f4) {
            FUN_001f6f50(n->f480);
            n->f936 = arg0->f56->v104();
            FUN_00178970(arg0, n);
            n->b16 = 0;
        }
        n = n->f952;
      }
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_175(void) {
    p2WaitFinishSequence(p2NewFinishSequence(1));
    p2SetSingleFrameLatency();
}

void FUN_0016e140(void *arg0, int arg1) {
    long long v;
    int temp_a2;
    void *temp_a1;
    int temp_v1;
    v = arg1;
    temp_a2 = *(int *)((char *)(arg0) + 60);
    temp_a1 = (void *)(*(int *)((char *)(arg0) + 56));
    temp_v1 = *(int *)((char *)(temp_a1) + 8);
    if ((temp_v1 != 0) && (temp_a2 >= 0) && (temp_a2 < temp_v1)) {
        *(long long *)(*(int *)((char *)(temp_a1) + 16) + (temp_a2 * 8)) = (long long)v;
    }
}

