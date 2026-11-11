int Gap__Gui__igHotKeyEventReceiver__vfunc_23(B_4575d0 *arg0, int arg1, int arg2) {
    int i;
    int n;
    if (arg2 == 0) {
        return 0;
    }
    arg0 = *(B_4575d0 **)((char *)arg0 + 8);
    n = arg0->cnt;
    for (i = 0; i < n; i++) {
        E_4575d0 *e = arg0->arr[i];
        if (e->f08 == arg1) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

int Gap__Gui__igHotKeyEventReceiver__vfunc_27(B_457650 *arg0, int arg1, int arg2, int arg3) {
    int i;
    int n;
    if (arg3 == 0) {
        return 0;
    }
    arg0 = *(B_457650 **)((char *)arg0 + 8);
    n = arg0->cnt;
    for (i = 0; i < n; i++) {
        E_457650 *e = arg0->arr[i];
        if (e->f0c == arg2) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

