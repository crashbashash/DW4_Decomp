void Gap__Gfx__igPsx2VertexArray1_1__vfunc_12(igPsx2VertexArray1_1 *self) {
    if (self->_usageFlags & 4) {
        p2WaitDmaSequence(1, self->_lSequence);
    }
    if (self->_vdata != 0) {
        FUN_0015e7b0((VertexBufferOwner *)self);
        FUN_00300f50(self, self->_vdata);
        self->_vdata = 0;
        self->_numVerts = 0;
    }
    FUN_0017d2b0((O_17d2b0 *)self);
    Gap__Core__igObject__vfunc_10(self);
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_59(void) {
}

int Gap__Gfx__igPsx2VertexArray1_1__vfunc_24(S_17d0c0 *arg0, int *arg1, int arg2, int arg3) {
    int total;
    VC_17d0c0 *a;

    if (arg0->fc != 0) {
        return 0;
    }
    arg0->fc = arg2;
    total = 0;
    arg0->f1c = *arg1;
    arg0->f10 = 0;
    arg0->f14 = arg3;
    a = (VC_17d0c0 *)igObject_GetAllocator();
    arg0->f8 = a->vX(0x14, 4);
    total += 0x50;
    total += FUN_0015e4e0((VA_15e4e0 *)arg0);
    if ((int)((((unsigned int)(*arg1 & 0xF0) >> 4) & 0xFF)) > 0) {
        FUN_0017d170((V_17d170 *)arg0);
    }
    return total;
}

void FUN_0017d170(V_17d170 *arg0) {
    unsigned *flags = arg0->g();
    if ((unsigned char)((*flags & 0xF0) >> 4) > 0) {
        Obj_17d170 *o;
        int a;
        a = igObject_GetAllocator(arg0);
        o = arg0->f56;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->f56 = (Obj_17d170 *)FUN_001527c0(a);
        a = igObject_GetAllocator(arg0);
        o = arg0->f48;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->f48 = FUN_002c9130(a);
        if (*flags & 2) {
            a = igObject_GetAllocator(arg0);
            o = arg0->f52;
            if (o != 0) {
                o->refs = o->refs - 1;
                if ((o->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
            arg0->f52 = FUN_002c9130(a);
        }
    }
}

void FUN_0017d2b0(struct O_17d2b0 *arg0) {
    int var_s0;
    struct R_17d2b0 *t;

    t = arg0->f56;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f56 = 0;
    var_s0 = 0;
    if (arg0->f48 != 0) {
        while (var_s0 < arg0->f48->n) {
            Memory_FreeBuffer(arg0->f48->items[var_s0]);
            var_s0 += 1;
        }
    }
    var_s0 = 0;
    if (arg0->f52 != 0) {
        while (var_s0 < arg0->f52->n) {
            Memory_FreeBuffer(arg0->f52->items[var_s0]);
            var_s0 += 1;
        }
    }
    t = (struct R_17d2b0 *)arg0->f48;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f48 = 0;
    t = (struct R_17d2b0 *)arg0->f52;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f52 = 0;
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_29(int *arg0, int arg1, float *arg2) {
    float *p = (float *)(**(int **)(arg0 + 2) + arg1 * 12);
    p[0] = arg2[0];
    p[1] = arg2[1];
    p[2] = arg2[2];
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_30(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2) {
    float *p = (float *)(*(int *)arg0->_vdata + arg1 * 12);
    arg2[0] = p[0];
    arg2[1] = p[1];
    arg2[2] = p[2];
}

int Gap__Gfx__igPsx2VertexArray1_1__vfunc_31(int *arg0, int arg1) {
    return **(int **)(arg0 + 2) + arg1 * 12;
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_32(igPsx2VertexArray1_1 *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_vdata) + 4) + (arg1 * 0xC));
    *(float *)((char *)(temp_v1) + 0) = (float) *(float *)((char *)(arg2) + 0);
    *(float *)((char *)(temp_v1) + 4) = (float) *(float *)((char *)(arg2) + 4);
    *(float *)((char *)(temp_v1) + 8) = (float) *(float *)((char *)(arg2) + 8);
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_33(igVertexArray *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_vdata) + 4) + (arg1 * 0xC));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
}

/* Address of vertex `vertexIndex` in the array's vertex data: `_vdata` points at a block whose
 * second word (+4) is the base of the 12-byte (three-float) entries. */


int Gap__Gfx__igPsx2VertexArray1_1__vfunc_34(igPsx2VertexArray1_1 *self, int vertexIndex) {
    return *(int *)((char *)(self->_vdata) + 4) + (vertexIndex * VERTEX_ENTRY_SIZE);
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_41(igPsx2VertexArray1_1 *arg0, int arg1, unsigned int arg2) {
    *(int *)(*(int *)((char *)(arg0->_vdata) + 8) + (arg1 * 4)) = (arg2 & 0xFFFFFF) | (((arg2 >> 1) & 0x7F000000) + (arg2 & 0x01000000));
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_42(ColorArrayView *arg0, int arg1, float *c) {
    float s;
    float a;
    float b;
    float g;
    float r;
    unsigned int v;
    unsigned int ta;
    unsigned int tb;
    unsigned int tg;
    unsigned int tr;
    s = 128.0f;
    a = c[3];
    r = c[0];
    g = c[1];
    b = c[2];
    if (!(a <= 1.0f)) {
        s = 127.9f;
    }
    ta = (unsigned int)(s * a) << 24;
    tb = (unsigned int)(255.0f * b) << 16;
    tg = (unsigned int)(255.0f * g) << 8;
    tr = (unsigned int)(255.0f * r);
    arg0->f8->f8[arg1] = ((ta | tb) | tg) | tr;
}

int Gap__Gfx__igPsx2VertexArray1_1__vfunc_43(igPsx2VertexArray1_1 *arg0, int arg1) {
    int temp_a1;
    unsigned int temp_a0;
    temp_a1 = *(int *)(*(int *)((char *)(arg0->_vdata) + 8) + (arg1 * 4));
    temp_a0 = (unsigned int)(temp_a1 & 0x80000000) >> 7;
    return (temp_a1 & 0xFFFFFF) | (temp_a0 + (((temp_a1 & 0xFF000000) - temp_a0) * 2));
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_44(VertexArrayView *arg0, int arg1, float *arg2) {
    unsigned int c = arg0->b->data[arg1];
    unsigned int t;
    float f, s;
    t = c >> 24;
    s = (t > 128) ? 0.007843138f : 0.0078125f;
    f = (float)(t & 0xFF);
    arg2[3] = f * s;
    t = (c >> 16) & 0xFF;
    f = (float)t;
    arg2[2] = 0.003921568f * f;
    t = (c >> 8) & 0xFF;
    f = (float)t;
    arg2[1] = 0.003921568f * f;
    t = c & 0xFF;
    f = (float)t;
    arg2[0] = 0.003921568f * f;
}

/* Write the {u, v} float pair *uv to vertex `vertexIndex` of texture-coordinate stream
 * `texCoordSet` (_vdata[11 + set], 8 bytes per entry). vfunc_51 is the getter. */

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_50(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv) {
    void *entry;

    entry = (void *)(*(int *)(self->_vdata + ((texCoordSet + 0xB) * 4)) + (vertexIndex * 8));
    *(float *)((char *)(entry) + 0) = (float) *(float *)((char *)(uv) + 0);
    *(float *)((char *)(entry) + 4) = (float) *(float *)((char *)(uv) + 4);
}

/* Read the {u, v} float pair of vertex `vertexIndex` from texture-coordinate stream `texCoordSet`
 * into *uv. The streams are _vdata[11 + set]; each entry is an 8-byte pair. vfunc_50 is the
 * setter, vfunc_52 returns the entry's address. */

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_51(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv) {
    void *entry;

    entry = (void *)(*(int *)(self->_vdata + ((texCoordSet + 0xB) * 4)) + (vertexIndex * 8));
    *(float *)((char *)(uv) + 0) = (float) *(float *)((char *)(entry) + 0);
    *(float *)((char *)(uv) + 4) = (float) *(float *)((char *)(entry) + 4);
}

/* Address of element `element` (8 bytes each) in the sub-array numbered `index`: _vdata points at
 * a table of base pointers whose first entry for sub-array 0 sits at word 11 (0xB), so the base is
 * read from word `index + 11` and offset by `element * 8`. */

int Gap__Gfx__igPsx2VertexArray1_1__vfunc_52(igPsx2VertexArray1_1 *self, int index, int element) {
    return *(int *)(self->_vdata + ((index + 0xB) * 4)) + (element * 8);
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_57(VertexArrayView_17d910 *arg0, int arg1, float x) {
    float t = fmodf(x, 6.2831855f);
    if (FUN_001002f0(fptodp(t), 0) != 0) {
        t += 6.2831855f;
    }
    if (!(x < 0.0f) && x <= 1.5707964f) {
        arg0->b->data[arg1] = t;
    } else if (!(x <= 1.5707964f) && x <= 4.712389f) {
        arg0->b->data[arg1] = 4.712389f - (t - 1.5707964f);
    } else {
        arg0->b->data[arg1] = t - 6.2831855f;
    }
}

float Gap__Gfx__igPsx2VertexArray1_1__vfunc_58(igPsx2VertexArray1_1 *arg0, int arg1) {
    float var_f0;

    var_f0 = *(float *)(*(int *)((char *)(arg0->_vdata) + 76) + (arg1 * 4));
    if (!(var_f0 <= 1.5707964f) && (var_f0 <= 4.712389f)) {
        return 4.712389f - (var_f0 - 1.5707964f);
    }
    if (var_f0 < 0.0f) {
        var_f0 += 6.2831855f;
    }
    return var_f0;
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_27(VA_17da90 *arg0, St_17da90 *arg1) {
    int m;
    int t;
    int s1;
    char *bs;
    int s0;

    if (arg1->f12 == 0) {
        arg1->f12 = arg0->f12 - arg1->f8;
    }
    t = arg1->f4;
    s0 = arg1->f0;
    s1 = arg1->f8;
    switch (t) {
    case 0:
        arg1->f16 = (char *)(arg0->f8->f0 + arg1->getF8() * 12);
        arg1->f20 = 12;
        break;
    case 1:
        arg1->f16 = (char *)(arg0->f8->f4 + arg1->getF8() * 12);
        arg1->f20 = 12;
        break;
    case 2:
        arg1->f16 = (char *)(arg0->f8->f8 + arg1->getF8() * 4);
        arg1->f20 = 4;
        break;
    case 4: {
        int n = ((*arg0->flags() & 0xF0) >> 4) & 0xFF;
        m = (s0 + s1 * n) * 4; arg1->f16 = m + arg0->f32;
        arg1->f20 = n * 4;
        break;
    }
    case 5: {
        int n = ((*arg0->flags() & 0xF00) >> 8) & 0xFF;
        bs = arg0->f36; arg1->f16 = bs + (s0 + s1 * n);
        arg1->f20 = n;
        break;
    }
    case 3:
        arg1->f16 = (char *)(*(int *)((char *)arg0->f8 + (s0 + 11) * 4) + arg1->getF8() * 8);
        arg1->f20 = 8;
        break;
    case 6:
        arg1->f16 = (char *)(arg0->f8->f60 + arg1->getF8() * 4);
        arg1->f20 = (((*arg0->flags() & 0x300000) >> 0x14) & 0xFF) * 4;
        break;
    case 9:
        arg1->f16 = (char *)(arg0->f8->f60 + arg1->getF8() * 4);
        arg1->f20 = 4;
        break;
    case 7:
        arg1->f16 = (char *)(arg0->f8->f68 + arg1->getF8() * 12);
        arg1->f20 = 12;
        break;
    case 8:
        arg1->f16 = (char *)(arg0->f8->f72 + arg1->getF8() * 12);
        arg1->f20 = 12;
        break;
    }
    arg1->f24 = 0;
    if (arg0->f20 & 4) {
        p2WaitDmaSequence(1, arg0->f64);
    }
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_28(void) {

}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_19(struct VertexArrayColorView *s) {
    unsigned int i;
    unsigned int *p;
    unsigned int x;
    unsigned int hi;
    if (s->f20 & 4) {
        p2WaitDmaSequence(1, s->f64);
    }
    FUN_0017d2b0((O_17d2b0 *)s);
    if (s->f28 & 4) {
        p = s->b->data;
        for (i = 0; i < s->count; i++) {
            x = *p;
            hi = (x & 0x80000000) >> 7;
            *p = (x & 0xffffff) | (hi + (((x & 0xff000000) - hi) * 2));
            p++;
        }
    }
}

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_20(void *arg0, int arg1) {
    unsigned int var_a6;
    unsigned int *var_a5;
    unsigned int temp_a4;

    FUN_0015e050((S_arg0_15e050 *)arg0);
    if ((int)g_igVertexArray_metaObject[0] == arg1) {
        FUN_0015e2b0((igVertexArray1_1 *)arg0, arg1);
    }
    FUN_0017d170((V_17d170 *)arg0);
    if (*(int *)((char *)(arg0) + 28) & 4) {
        var_a5 = (unsigned int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8));
        for (var_a6 = 0; var_a6 < (unsigned int) *(int *)((char *)(arg0) + 12); var_a6++) {
            temp_a4 = *var_a5;
            *var_a5 = (temp_a4 & 0xFFFFFF) | (((temp_a4 >> 1) & 0x7F000000) + (temp_a4 & 0x01000000));
            var_a5 += 1;
        }
    }
}

