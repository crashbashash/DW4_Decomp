int igHotKeyEventReceiver_OnKeyEvent(igHotKeyEventReceiver *self, int arg1, int arg2) {
    int i;
    int n;
    if (arg2 == 0) {
        return 0;
    }
    B_4575d0 *hotKeys = (B_4575d0 *)self->_hotKeyList;
    n = hotKeys->cnt;
    for (i = 0; i < n; i++) {
        E_4575d0 *e = hotKeys->arr[i];
        if (e->f08 == arg1) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

int igHotKeyEventReceiver_ControllerButtonEvent(igHotKeyEventReceiver *self, int arg1, int arg2, int arg3) {
    int i;
    int n;
    if (arg3 == 0) {
        return 0;
    }
    B_457650 *hotKeys = (B_457650 *)self->_hotKeyList;
    n = hotKeys->cnt;
    for (i = 0; i < n; i++) {
        E_457650 *e = hotKeys->arr[i];
        if (e->f0c == arg2) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

