static inline void set(R_456780 *&field, R_456780 *value) {
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    R_456780 *old = field;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    field = value;
}

void Gap__Gui__igGuiSystem__vfunc_13(A_456780 *self) {
    Gap__Core__igObject__vfunc_11(self);
    igSmartPointer<R_456780> first(0);
    int allocator = igObject_GetAllocator(self);
    first.release();
    first.p = (R_456780 *)FUN_0044f0b0(allocator);
    FUN_00457e90((S0_457e90 *)(first.get()), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    igSmartPointer<R_456780> second((R_456780 *)FUN_0044ecb0(igObject_GetAllocator(self)));
    second.get()->wc = (int)self;
    FUN_00457e90((S0_457e90 *)(second.get()), self->f12);
    ObjectList_AppendRetained(self->f16, second.get());
    allocator = igObject_GetAllocator(self);
    first.release();
    first.p = (R_456780 *)FUN_0044e990(allocator);
    FUN_00457e90((S0_457e90 *)(first.get()), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    igGroup_AppendChild(self->f20, self->f28);
    R_456780 *value = self->f20;
    X_456780 *x = self->f8;
    set(x->f12, value);
    value = (R_456780 *)self->f12;
    x = self->f8;
    set(x->f16, value);
}

void FUN_004569c0(O_4569c0 *arg0, int arg1) {
    T_4569c0 *temp_a0;
    arg0->f32 = arg1;
    if (arg1 != 0) {
        temp_a0 = arg0->m->t;
        temp_a0->f24 = 1.0f;
        temp_a0->f28 = 1.0f;
        temp_a0->f32 = 1.0f;
        temp_a0->f36 = 1.0f;
        temp_a0->vX();
        return;
    }
    temp_a0 = arg0->m->t;
    temp_a0->f24 = g_vec4Zero[0];
    temp_a0->f28 = DAT_004e1174[0];
    temp_a0->f32 = DAT_004e1178[0];
    temp_a0->f36 = DAT_004e117c[0];
    temp_a0->vX();
}

void FUN_00456a60(A_456a60 *arg0, R_456a60 *arg1) {
    Rc_456a60 *sp4C;
    V3 sp30;
    int var_v0;
    Rc_456a60 *temp_a0;
    P_456a60 *temp_a1;
    Q *temp_v0;

    if (arg1 != 0) {
        ((Rc_456a60 *)arg1)->rc = ((Rc_456a60 *)arg1)->rc + 1;
    }
    temp_a0 = arg0->f24;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if (((unsigned long long)((long long)temp_a0->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f24 = (Rc_456a60 *)arg1;
    temp_a1 = arg0->f28;
    temp_v0 = temp_a1->f28;
    if (temp_v0 != 0) {
        var_v0 = temp_v0->f8;
    } else {
        var_v0 = 0;
    }
    if (var_v0 > 0) {
        FUN_001c5eb0(&sp4C, temp_a1, 0);
        if (sp4C != 0) {
            sp4C->rc = sp4C->rc - 1;
            if (((unsigned long long)((long long)sp4C->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
    if (arg1 != 0) {
        igGroup_AppendChild(arg0->f28, arg1->f8->f8);
    }
    FUN_004569c0((O_4569c0 *)arg0, arg0->f32);
    sp30.a = 2;
    sp30.b = 0;
    sp30.c = DAT_0058c3d8[0];
    FUN_004578c0((S_4578c0 *)arg0->f12, (S_4578c0 *)&sp30);
}

void FUN_00456b80(int *arg0, float *arg1) {
    float m[16];
    struct P_456b80 *p;
    float fx;
    float fy;
    float z;

    p = (struct P_456b80 *)arg0[6];
    if (p != 0) {
        fx = p->x;
        fy = p->y;
        z = 0.0f;
        igMatrix44f_SetIdentity(m);
        arg1[0] = arg1[0] - fx;
        arg1[1] = arg1[1] - fy;
        arg1[2] = arg1[2] - z;
        Matrix44_SetTranslation(m, arg1);
        ((Obj_456b80 *)arg0[7])->vX(m);
    }
}

void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1) {
    int sp30[3];
    igGuiComponent *o;
    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    o = (igGuiComponent *)arg0->_focusedComponent;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->_focusedComponent = (int)arg1;
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c408[0];
    FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp30);
}

void FUN_00456cc0(W *arg0, T_456cc0 *arg1) {
    T_456cc0 *sp5C; int sp40[4]; T_456cc0 **p; T_456cc0 *old; int v; LL *l;
    if (arg0->f12->f164 != 0) { arg0->f12->f164->f8 = 0; }
    p = &arg0->f12->f164;
    if (arg1 != 0) { arg1->references = arg1->references + 1; }
    old = *p;
    if (old != 0) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) { igObject_Destroy(old); }
    }
    *p = arg1;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058c400[0];
    FUN_004578c0((S_4578c0 *)arg0->f12, (S_4578c0 *)sp40);
    l = arg0->f20->f28;
    if (l != 0) { v = l->f8; } else { v = 0; }
    if (v > 1) {
        FUN_001c5eb0(&sp5C, arg0->f20, 0);
        if (sp5C != 0) {
        --sp5C->references;
        if (((unsigned long long)(long long)sp5C->references & 0x7fffffULL) == 0) { igObject_Destroy(sp5C); }
        }
    }
    if (arg1 != 0) { arg0->f20->v140(0, arg1->f28); }
    if (arg1 != 0) { arg1->f8 = (int)arg0; }
}

void *FUN_00456e10(struct O_456e10 *arg0, struct N_456e10 *arg1, int arg2) {
    struct N_456e10 *temp_s0;
    void *var_v0;

    if (arg1 != 0) {
        while (1) {
            temp_s0 = arg1->f24;
            if (temp_s0 == 0) {
                return 0;
            }
            var_v0 = FUN_004555c0((igGuiComponentView *)temp_s0, (void *)arg1, (void *)arg2);
            arg1 = temp_s0;
            if (var_v0 != 0) {
                break;
            }
        }
    } else {
        var_v0 = arg0->f12->f164;
    }
    while (var_v0 != 0) {
        arg1 = (struct N_456e10 *)var_v0;
        var_v0 = FUN_004555c0((igGuiComponentView *)var_v0, (void *)0, (void *)arg2);
    }
    return arg1;
}

void FUN_00456eb0(Ctl *arg0, int arg1) {
    Item2 *s0;
    int ok;
    ok = 0;
    s0 = arg0->f12->f168;
    if (s0 != 0) {
        ok = s0->f12->test() & 0xFF;
    }
    if (ok == 0) {
        do {
            s0 = (Item2 *)FUN_00456e10((O_456e10 *)arg0, (N_456e10 *)s0, arg1);
            if (s0 == arg0->f12->f168 || s0 == 0) break;
        } while ((FUN_004555e0(s0) != 0) ^ 1);
    }
    FUN_00456c20((igGuiSystemModel *)arg0->f12, (igGuiComponent *)s0);
}

