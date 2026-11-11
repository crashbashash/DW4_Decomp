void Gap__Gfx__igPsx2VertexStream__vfunc_24(Src_17fe50 *self, Dst *x) {
    if (self->f24 == 0) FUN_00180020((long long *)self);
    int k = self->f24;
    if (!(k == 2 || k == 3)) {
        igSmartPointer<Obj_17fe50> r((Obj_17fe50 *)FUN_0015f4a0((S_15f430 *)self->f20, x->f0, x->f12), kRetainReference);
        int s = r.p->f24;
        int c = r.p->buf->v23();
        int a2 = c * s;
        x->f16 = r.p->buf->f16 + x->f4 * a2;
        x->f20 = a2;
        x->f8 = r.p->buf->w8 - x->f4;
    }
    x->f24 = 1;
}

void Gap__Gfx__igPsx2VertexStream__vfunc_27(A_17ff60 *arg0) {
    int temp_a0;
    int temp_a0_2;

    if ((arg0->f16 != 0) && (arg0->vX() != 0)) {
        FUN_001eeda0(arg0->f128);
        arg0->f12 = 0;
    } else {
        if (arg0->f40 != 0) {
            FUN_00180020((long long *)arg0);
        }
        arg0->f12 = 0;
    }
    arg0->f128 = 0;
    temp_a0 = arg0->f132;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        arg0->f132 = 0;
    }
    temp_a0_2 = arg0->f136;
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        arg0->f136 = 0;
    }
    Gap__Gfx__igVertexStream__vfunc_27((igVertexStream *)arg0);
}

