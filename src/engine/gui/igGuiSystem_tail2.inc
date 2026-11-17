bool igGuiSystem_OnKeyEvent(Ob *arg0, int arg1, int arg2) {
    if (arg0->f12->f160 == 0) {
        return false;
    }
    bool r = false;
    switch (arg1) {
    case 0x81:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 2);
        }
        r = true;
        break;
    case 0x83:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 3);
        }
        r = true;
        break;
    case 0x80:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 0);
        }
        r = true;
        break;
    case 0x82:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 1);
        }
        r = true;
        break;
    case 0x9:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 4);
        }
        r = true;
        break;
    case 0xD:
    case 0x20:
        if (arg2 != 0) {
            FUN_004570a0(arg0);
        }
        r = true;
        break;
    default:
        break;
    }
    return r;
}

void FUN_004570a0(void *arg0) {
    unsigned char temp_s1;
    int temp_s0;
    temp_s0 = *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 168);
    if (temp_s0 != 0) {
        temp_s1 = FUN_00455620((void *)temp_s0) & 0xFF;
        FUN_00455610((int *)temp_s0, !temp_s1);
        FUN_00455610((int *)temp_s0, temp_s1);
    }
}

int Gap__Gui__igGuiSystem__vfunc_24(A_457100 *arg0, float fparg0, float fparg1) {
    struct { int a; int b; int c; } s;
    B_457100 *temp_v1;

    temp_v1 = arg0->fc;
    if (temp_v1->fa0 == 0) {
        return 0;
    }
    temp_v1->f14 = fparg0;
    temp_v1->f18 = fparg1;
    s.a = 2;
    s.b = 0;
    s.c = g_igGuiSystemModelMousePositionField[0];
    igModel_NotifyViews((igModel *)arg0->fc, (ModelChange *)&s);
    return arg0->fc->fb0 != 0;
}

int Gap__Gui__igGuiSystem__vfunc_32(int *self, int x, int y) {
    struct P_457170 p;
    float *f = (float *)self[3];
    f[3] = (float)x;
    f[4] = (float)y;
    p.a = 2;
    p.b = 0;
    p.c = (int)g_igGuiSystemModel_windowSizeMetaField;
    igModel_NotifyViews((igModel *)((void *)self[3]), (ModelChange *)&p);
    return 0;
}

int Gap__Gui__igGuiSystem__vfunc_34(igGuiSystem *arg0) {
    int buf[3];

    *(char *)((char *)(arg0->_model) + 180) = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = (int)g_igGuiSystemModel_windowCloseRequestedMetaField;
    igModel_NotifyViews((igModel *)arg0->_model, (ModelChange *)buf);
    return 1;
}

int Gap__Gui__igGuiSystem__vfunc_25(struct P_457220 *arg0, int arg1, char arg2) {
    int sp[3];
    struct O_457220 *o;

    o = arg0->o;
    if (o->fa0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        return 0;
    }
    o->f1c = arg2;
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = (int)g_igGuiSystemModel_mousePressedMetaField;
    igModel_NotifyViews((igModel *)arg0->o, (ModelChange *)&sp[0]);
    return arg0->o->fac != 0;
}

bool Gap__Gui__igGuiSystem__vfunc_27(igGuiSystem *system, int device, int key, int pressed) {
    bool handled;

    if (!((GuiModelView *)system->_model)->enabled) {
        return false;
    }
    handled = false;
    switch (key) {
    case 4:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 2);
        }
        handled = true;
        break;
    case 6:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 3);
        }
        handled = true;
        break;
    case 7:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 0);
        }
        handled = true;
        break;
    case 5:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 1);
        }
        handled = true;
        break;
    case 8:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 5);
        }
        handled = true;
        break;
    case 9:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 4);
        }
        handled = true;
        break;
    case 13:
        if (pressed) {
            FUN_004570a0(system);
        }
        handled = true;
        break;
    }
    return handled;
}

int Gap__Gui__igGuiSystem__vfunc_26(void) {
    return 0;
}

void igHotKeyEventReceiver_AddKey(igHotKeyEventReceiver *receiver, int key, igObject *action) {
    igHotKeyEventReceiver_AddBinding(receiver, key, 32, action);
}

void igHotKeyEventReceiver_AddButton(igHotKeyEventReceiver *receiver, int button, igObject *action) {
    igHotKeyEventReceiver_AddBinding(receiver, 0, button, action);
}

static inline void assign(igObject **slot, igObject *value) {
    igObject *old;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    old = *slot;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = value;
}

void igHotKeyEventReceiver_AddBinding(igHotKeyEventReceiver *receiver, int key, int button, igObject *action) {
    igSmartPointer<Entry> entry((Entry *)FUN_0044dc20((int)(igObject_GetAllocator(receiver))));
    entry->a = key;
    entry->b = button;
    assign(&entry->value, action);
    ObjectList_AppendRetained((igObjectList *)receiver->_hotKeyList, (igObject *)(entry.get()));
}

void igHotKeyEventReceiver_RemoveBinding(igHotKeyEventReceiver *receiver, int button) {
    E_4574f0 *temp_a0;
    int var_s1;
    LST *temp_s0;

    for (var_s1 = ((LST *)receiver->_hotKeyList)->f8 - 1; var_s1 >= 0; var_s1 -= 1) {
        temp_s0 = (LST *)receiver->_hotKeyList;
        temp_a0 = temp_s0->f16[var_s1];
        if (temp_a0->f12 == button) {
            if (temp_a0->f8 == 0) {
                if (temp_a0 != 0) {
                    temp_a0->f4 = temp_a0->f4 - 1;
                    if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy((igObject *)temp_a0);
                    }
                }
                List_RemoveWordAt((igDataList *)temp_s0, var_s1);
                temp_s0->f16[temp_s0->f8] = 0;
            } else {
                temp_a0->f12 = 0x20;
            }
        }
    }
}

