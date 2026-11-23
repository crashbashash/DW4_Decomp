static inline void set(R_456780 *&field, R_456780 *value) {
    igObject::ref(value);
    R_456780 *old = field;
    igObject::release(old);
    field = value;
}

void igGuiSystem_resetFields(A_456780 *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    igSmartPointer<R_456780> first(0);
    int allocator = (int)(((Gap::Core::igObject *)self)->getMemoryPool());
    first.release();
    first.p = (R_456780 *)igWindowSizeObserver_Create(allocator);
    ((Gap::Gui::igView *)(first.get()))->setModel((Gap::Gui::igModel *)self->f12);
    ((Gap::Core::igObjectList *)self->f16)->append((Gap::Core::igObject *)(first.get()));
    igSmartPointer<R_456780> second((R_456780 *)igMousePosObserver_Create((int)(((Gap::Core::igObject *)self)->getMemoryPool())));
    second.get()->wc = (int)self;
    ((Gap::Gui::igView *)(second.get()))->setModel((Gap::Gui::igModel *)self->f12);
    ((Gap::Core::igObjectList *)self->f16)->append((Gap::Core::igObject *)(second.get()));
    allocator = (int)(((Gap::Core::igObject *)self)->getMemoryPool());
    first.release();
    first.p = (R_456780 *)igActiveComponentsObserver_Create(allocator);
    ((Gap::Gui::igView *)(first.get()))->setModel((Gap::Gui::igModel *)self->f12);
    ((Gap::Core::igObjectList *)self->f16)->append((Gap::Core::igObject *)(first.get()));
    igGroup_AppendChild((igGroup *)self->f20, (igNode *)self->f28);
    R_456780 *value = self->f20;
    X_456780 *x = self->f8;
    set(x->f12, value);
    value = (R_456780 *)self->f12;
    x = self->f8;
    set(x->f16, value);
}

void igGuiSystem_SetMouseCursorVisible(igGuiSystem *gui, bool visible) {
    T_4569c0 *temp_a0;
    gui->_mouseCursorVisible = visible;
    if (visible) {
        temp_a0 = ((M_4569c0 *)gui->_mouseCursor)->t;
        temp_a0->f24 = 1.0f;
        temp_a0->f28 = 1.0f;
        temp_a0->f32 = 1.0f;
        temp_a0->f36 = 1.0f;
        temp_a0->vX();
        return;
    }
    temp_a0 = ((M_4569c0 *)gui->_mouseCursor)->t;
    temp_a0->f24 = g_vec4Zero[0];
    temp_a0->f28 = g_vec4Zero[1];
    temp_a0->f32 = g_vec4Zero[2];
    temp_a0->f36 = g_vec4Zero[3];
    temp_a0->vX();
}

void igGuiSystem_SetMouseCursor(igGuiSystem *gui, igMouseCursor *cursor) {
    A_456a60 *arg0 = (A_456a60 *)gui;
    R_456a60 *arg1 = (R_456a60 *)cursor;
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
            igObject_Destroy((igObject *)temp_a0);
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
        igGroup_RemoveChildAt((igGroup *)temp_a1, 0);
    }
    if (arg1 != 0) {
        igGroup_AppendChild((igGroup *)arg0->f28, (igNode *)arg1->f8->f8);
    }
    igGuiSystem_SetMouseCursorVisible(gui, arg0->f32);
    igNotifyEvent sp30((Gap::Core::igMetaField *)g_igGuiSystemModel_mousePositionMetaField);
    ((Gap::Gui::igModel *)arg0->f12)->notifyAllViews(sp30);
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
        igMatrix44f_SetTranslation(m, arg1);
        ((Obj_456b80 *)arg0[7])->vX(m);
    }
}

void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1) {
    igGuiComponent *o;
    igObject::ref(arg1);
    o = (igGuiComponent *)arg0->_focusedComponent;
    igObject::release(o);
    arg0->_focusedComponent = (int)arg1;
    igNotifyEvent sp30((Gap::Core::igMetaField *)g_igGuiSystemModel_focusedComponentMetaField);
    ((Gap::Gui::igModel *)arg0)->notifyAllViews(sp30);
}

void igGuiSystem_SetRootComponent(igGuiSystem *gui, igGuiComponent *root) {
    W *arg0 = (W *)gui;
    T_456cc0 *arg1 = (T_456cc0 *)root;
    T_456cc0 **p; T_456cc0 *old; int v; LL *l;
    if (arg0->f12->f164 != 0) { arg0->f12->f164->f8 = 0; }
    p = &arg0->f12->f164;
    if (arg1 != 0) { arg1->references = arg1->references + 1; }
    old = *p;
    if (old != 0) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) { igObject_Destroy((igObject *)old); }
    }
    *p = arg1;
    igNotifyEvent sp40((Gap::Core::igMetaField *)g_igGuiSystemModel_rootComponentMetaField);
    ((Gap::Gui::igModel *)arg0->f12)->notifyAllViews(sp40);
    l = arg0->f20->f28;
    if (l != 0) { v = l->f8; } else { v = 0; }
    if (v > 1) {
        igGroup_RemoveChildAt((igGroup *)arg0->f20, 0);
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

