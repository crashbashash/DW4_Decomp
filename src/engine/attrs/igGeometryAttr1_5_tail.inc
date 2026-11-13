int FUN_0013d030(void *arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 32));
    if (temp_v0 != 0) {
        return *(int *)(*(int *)((char *)(temp_v0) + 16) + (arg1 * 4));
    }
    return 0;
}

void thunk_FUN_0013cf70(void) {
    FUN_0013cf70();
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_20(S_13d180 *arg0, int arg1) {
    Rc *sp3C;
    Rc *s0;
    Rc *old;
    int i;
    if ((int)g_igGeometryAttr_metaObject[0] == arg1 && arg0->f32 != 0) {
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        sp3C = (Rc *)FUN_0014bff0(igObject_GetAllocator(arg0));
        s0 = *(Rc **)&sp3C;
        if (s0 != 0) s0->refs = s0->refs + 1;
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        arg0->f48 = s0;
        REL(&sp3C)
        X_13d180 *x = (X_13d180 *)arg0->f48;
        x->grow(arg0->f32->n, 32, 0);
        for (i = 0; i < arg0->f32->n; i++) {
            Gap__Attrs__igGeometryAttr1_5__vfunc_40((S_13de80 *)arg0, i, FUN_0013d030(arg0, i));
        }
    }
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_24(igGeometryAttr1_5 *self, void *context)
{
    /* matching construct: declaration and load order permutation sweep (5040 + 120 variants) */
    int primType;
    unsigned numPrims;
    unsigned offset;
    int stripType;
    int indexArray;
    int overlap;
    StripLengths *lengths;

    Gap__Gfx__igPsx2VisualContext__vfunc_59(context, self->_vertexArray);
    offset = self->_offset;
    numPrims = self->_numPrims;
    primType = self->_primType;
    lengths = (StripLengths *)self->_stripLengths;
    indexArray = self->_indexArray;
    if (indexArray != 0) Gap__Gfx__igPsx2VisualContext__vfunc_60(context, indexArray);
    if (lengths != 0) {
        if (primType == 2) {
            stripType = 0;
            overlap = 1;
        } else if (primType == 4) {
            stripType = 1;
            overlap = 2;
        } else {
            if (primType != 5) return;
            stripType = 2;
            overlap = 2;
        }
        switch (numPrims) {
        case 0:
            break;
        case 1:
            Gap__Gfx__igPsx2VisualContext__vfunc_71(context, primType, lengths->get(0) - overlap, offset);
            break;
        default:
            Gap__Gfx__igPsx2VisualContext__vfunc_63(context, lengths);
            Gap__Gfx__igPsx2VisualContext__vfunc_74(context, stripType, numPrims, offset, 0);
        }
        if (lengths != 0) Gap__Gfx__igPsx2VisualContext__vfunc_63(context, 0);
    } else {
        Gap__Gfx__igPsx2VisualContext__vfunc_71(context, primType, numPrims, offset);
    }
    if (indexArray != 0) Gap__Gfx__igPsx2VisualContext__vfunc_60(context, 0);
}

inline void T_13d460::setBuffer(const igSmartPointer<R_13d460> &buffer) {
    R_13d460 *held = buffer.get();
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    R_13d460 *previous = (R_13d460 *)f48;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    f48 = (Buf *)held;
}

int Gap__Attrs__igGeometryAttr1_5__vfunc_39(T_13d460 *arg0, int arg1, unsigned arg2, int arg3) {
    arg0->f20 = arg1;
    arg0->f24 = arg2;
    arg0->f28 = arg3;
    int t = arg0->f20;
    if ((unsigned)(t - 4) <= 1U || t == 2) {
        if (arg0->f48 == 0) {
            arg0->setBuffer(igSmartPointer<R_13d460>((R_13d460 *)FUN_0014bff0(igObject_GetAllocator(arg0))));
        }
        if (((R_13d460 *)arg0->f48)->cap < arg2) {
            arg0->f48->v92(arg2, 0x20, 0);
        }
    }
    return 1;
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_40(S_13de80 *arg0, int arg1, int arg2) {
    Rc *sp5C;
    Rc *s0;
    Rc *old;
    if (arg0->f48 == 0) {
        sp5C = (Rc *)FUN_0014bff0(igObject_GetAllocator());
        s0 = *(Rc **)&sp5C;
        if (s0 != 0) s0->refs = s0->refs + 1;
        old = arg0->f48;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        arg0->f48 = s0;
        REL(&sp5C)
    }
    X_13de80 *x = (X_13de80 *)arg0->f48;
    unsigned n = arg1 + 1;
    if (((Y *)x)->f12 < n) x->grow(n, 32, 0);
    x = (X_13de80 *)arg0->f48;
    x->setAt(arg1, arg2);
}

unsigned int Gap__Attrs__igGeometryAttr1_5__vfunc_42(GeometryPrimitiveView *self) {
    unsigned int i;
    unsigned int total;
    PrimLengthArray *lengths;
    int type;
    unsigned int count;
    unsigned int vertexCount;
    unsigned int offset;

    /* matching construct: statement-order sweep — offset read second */
    vertexCount = self->_vertexArray->_vertexCount;
    offset = self->_offset;
    count = self->_numPrims;
    type = self->_primType;
    lengths = self->_stripLengths;
    if (self->_indexArray != 0) {
        total = vertexCount - offset;
    } else {
        total = 0;
        if (type == 4 || type == 5 || type == 2) {
            for (i = 0; i < count; i++) {
                total += lengths->getLength(i);
            }
        } else {
            if (type == 0) {
                total = count;
            } else {
                if (type == 1) {
                    count *= 2;
                } else if (type == 3) {
                    count *= 3;
                } else {
                    count = 0;
                }
                total = count;
            }
        }
    }
    return total;
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_34(GeometryAttrView *arg0, float *arg1, float *arg2) {
    VertexRangeAccess acc;
    float mz = 1e20f;
    float my = mz;
    float mx = mz;
    float nz = -1e20f;
    float ny = nz;
    float nx = nz;
    unsigned int i;
        igVertexArrayLock_Init(&acc);
    acc.f4 = 0;
    acc.f0 = 0;
    acc.f8 = arg0->f28;
    acc.cnt = 0;
    arg0->f12->v108(&acc, 0);
    for (i = 0; i < acc.cnt; i++) {
        BoundsVertex *p = (BoundsVertex *)(acc.data + i * acc.stride);
        if (!(mx <= p->x)) { mx = p->x; }
        if (!(my <= p->y)) { my = p->y; }
        if (!(mz <= p->z)) { mz = p->z; }
        { float t = p->getX(); if (nx < t) { nx = t; } }
        { float t = p->getY(); if (ny < t) { ny = t; } }
        { float t = p->getZ(); if (nz < t) { nz = t; } }
    }
    arg1[0] = mx;
    arg1[1] = my;
    arg1[2] = mz;
    arg2[0] = nx;
    arg2[1] = ny;
    arg2[2] = nz;
    arg0->f12->v112(&acc, 0);
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_17(O_13e230 *arg0) {
    int sp4C;
    unsigned s0, s1;
    Ar *a0;
    FUN_0013b820(arg0);
    if (arg0->f40 != 0 || arg0->f44 != 0) {
        sp4C = *arg0->f12->v100();
        if (arg0->f44 != 0) {
            sp4C = sp4C | 0x400000;
        } else {
            sp4C = sp4C & 0xFFBFFFFF;
        }
        if (arg0->f40 != 0) {
            sp4C = sp4C | 0x800000;
        } else {
            sp4C = sp4C & 0xFF7FFFFF;
        }
        s1 = arg0->f12->f12;
        arg0->f12->v240(&sp4C, s1, arg0->f12->f20, 0);
        s0 = 0;
        if (arg0->f44 != 0) {
            for (; s0 < s1; s0++) {
                arg0->f12->v140(s0, &arg0->f44->f16[s0]);
            }
            a0 = arg0->f44;
            if (a0 != 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7fffff) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->f44 = 0;
        }
        s0 = 0;
        if (arg0->f40 != 0) {
            for (; s0 < s1; s0++) {
                arg0->f12->v152(s0, &arg0->f40->f16[s0]);
            }
            a0 = arg0->f40;
            if (a0 != 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7fffff) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->f40 = 0;
        }
    }
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_37(int *arg0, A_13e440 *arg1, B *arg2) {
    unsigned n;
    unsigned i;
    VertexFormat fl;
    Obj_13e440 *o;
    o = arg1->f12;
    n = arg2->f8;
    if (o->f12 < n) {
        *arg0 = g_resultFailure[0];
    } else {
        fl = *o->v100();
        if (!fl.has()) {
            fl.set();
            o = arg1->f12;
            o->v240(&fl, o->f12, o->f20, 0);
        }
        for (i = 0; i < n; i++) {
            o = arg1->f12;
            o->v152(i, arg2->f16 + i * 12);
        }
        *arg0 = g_resultSuccess[0];
    }
}

void Gap__Attrs__igGeometryAttr1_5__vfunc_38(int *arg0, A_13e550 *arg1, R_13e550 *arg2) {
    VertexFormat_13e550 sp6C;
    unsigned int s0;
    unsigned int s1;
    B_13e550 *b = arg1->buf;
    s1 = arg2->cnt;
    if (b->f12 < s1) {
        *arg0 = g_resultFailure[0];
        return;
    }
    sp6C = *b->v100();
    s0 = 0;
    if (!sp6C.has()) {
        sp6C.set();
        b = arg1->buf;
        b->v240(&sp6C, b->f12, b->f20, 0);
        ;
    }
    { int i = s0; for (; i < s1; i++) { b = arg1->buf; b->v140(i, arg2->arr + i * 3); } }
    *arg0 = g_resultSuccess[0];
}

