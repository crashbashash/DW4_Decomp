void Gap__igDefaultInterfaceManager__vfunc_26(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_mouseMotionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_27(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_mouseButtonDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_28(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_mouseButtonUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_29(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_windowMoveFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_30(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_windowResizeFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_31(igDefaultInterfaceManager *arg0, void **arg1) {
    bool var_a0;
    bool (*temp_v1)(void **);
    var_a0 = true;
    temp_v1 = (bool (*)(void **))(arg0->_windowCloseFunction);
    if (temp_v1 != 0) {
        var_a0 = temp_v1(arg1);
    }
    if (var_a0) {
        ((DW4VC_104_0 *)(arg1))->vX();
    }
}

void Gap__igDefaultInterfaceManager__vfunc_40(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_41(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_32(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerJoystickMotionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_33(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_34(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_35(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonPressureFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_36(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerConnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_37(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerDisconnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_38(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerSliderFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_39(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerPointOfViewFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void FUN_00147840(struct A *arg0) {
    int n2; int j; L_147840 *l; int n1; int i; R *p;
    l = arg0->list;
    n1 = l->cnt;
    for (i = 0; i < n1; i++) {
        p = l->arr[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->cnt;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->cnt = 0;
    if (0 >= arg0->list->cnt) {
        List_Reserve(arg0->list, 0, 4);
    }
}

void FUN_00147930(S *arg0) {
    int n = arg0->list->count;
    int i;
    for (i = 0; i < n; i++) {
        arg0->list->data[i]->vX(arg0);
    }
}

