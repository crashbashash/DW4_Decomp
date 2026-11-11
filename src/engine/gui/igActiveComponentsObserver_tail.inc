static inline void setComponent_4561e0(int *slot, igObject *next) {
    if (next != 0) {
        next->_refCount = next->_refCount + 1;
    }
    igRelease((igObject *)*slot);
    *slot = (int)next;
}
void Gap__Gui__igActiveComponentsObserver__vfunc_24(igActiveComponentsObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    type = msg->type;
    model = (igGuiSystemModel *)self->_model;
    if (type == DAT_0058c410[0]) {
        igObject *under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)self->_oldComponentUnderMouse != under) {
            if (self->_oldComponentUnderMouse != 0) {
                FUN_00455600((int *)self->_oldComponentUnderMouse, 0);
            }
            if (under != 0) {
                FUN_00455600((int *)under, 1);
            }
        }
        if (under != 0 && FUN_004555e0(under) != 0 && under != (igObject *)model->_focusedComponent) {
            FUN_00456c20(model, (igGuiComponent *)under);
        }
        setComponent_4561e0(&self->_oldComponentUnderMouse, under);
    } else if (type == DAT_0058c408[0]) {
        igObject *focused = (igObject *)model->_focusedComponent;
        void *common = FUN_004565c0((int)self, focused);
        if (self->_oldFocusedComponent != 0) {
            FUN_004555f0((int *)self->_oldFocusedComponent, 0);
            FUN_00456540((int)self, (N *)self->_oldFocusedComponent, (N *)common, 0);
        }
        if (focused != 0) {
            FUN_004555f0((int *)focused, 1);
            FUN_00456540((int)self, (N *)focused, (N *)common, 1);
        }
        setComponent_4561e0(&self->_oldFocusedComponent, focused);
    } else if (type == DAT_0058c418[0]) {
        igObject *pushed = (igObject *)model->_pushedComponent;
        if (self->_oldPushedComponent != 0) {
            FUN_00455610((int *)self->_oldPushedComponent, 0);
        }
        if (pushed != 0) {
            FUN_00455610((int *)pushed, 1);
        }
        setComponent_4561e0(&self->_oldPushedComponent, pushed);
    } else if (msg->handled == 0) {
        setComponent_4561e0(&self->_oldPushedComponent, (igObject *)model->_pushedComponent);
        setComponent_4561e0(&self->_oldFocusedComponent, (igObject *)model->_focusedComponent);
        setComponent_4561e0(&self->_oldComponentUnderMouse, (igObject *)model->_componentUnderMouse);
        if (self->_oldPushedComponent != 0) {
            FUN_00455610((int *)self->_oldPushedComponent, 1);
        }
        if (self->_oldFocusedComponent != 0) {
            FUN_004555f0((int *)self->_oldFocusedComponent, 1);
        }
        if (self->_oldComponentUnderMouse != 0) {
            FUN_00455600((int *)self->_oldComponentUnderMouse, 1);
        }
    }
}

int FUN_00456540(int arg0, N *arg1, N *arg2, unsigned char arg3) {
    int r;

    if (arg1 != 0) {
        if (arg1 == arg2) {
            return r;
        }
        FUN_004559a0((S_4559a0 *)arg1->f10, arg3);
        r = FUN_00456540(arg0, arg1->f18, arg2, arg3);
    }
    return r;
}

void *FUN_004565c0(int arg0, void *arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (*(unsigned char *)(*(int *)((char *)arg1 + 16) + 28) != 0) {
        return arg1;
    }
    return FUN_004565c0(arg0, *(void **)((char *)arg1 + 24));
}

