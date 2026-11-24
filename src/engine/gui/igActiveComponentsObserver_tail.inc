static inline void setComponent_4561e0(int *slot, igObject *next) {
    igObject::ref(next);
    igObject::release((igObject *)*slot);
    *slot = (int)next;
}
void igActiveComponentsObserver_OnModelChange(igActiveComponentsObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    type = msg->type;
    model = (igGuiSystemModel *)self->_model;
    if (type == (int)Gap::Gui::igGuiSystemModel::k_componentUnderMouse) {
        igObject *under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)self->_oldComponentUnderMouse != under) {
            if (self->_oldComponentUnderMouse != 0) {
                ((Gap::Gui::igGuiComponent *)self->_oldComponentUnderMouse)->setMouseOver(0);
            }
            if (under != 0) {
                ((Gap::Gui::igGuiComponent *)under)->setMouseOver(1);
            }
        }
        if (under != 0 && ((Gap::Gui::igGuiComponent *)under)->isEnabled() != 0 && under != (igObject *)model->_focusedComponent) {
            ((Gap::Gui::igGuiSystemModel *)model)->setFocusedComponent((Gap::Gui::igGuiComponent *)under);
        }
        setComponent_4561e0(&self->_oldComponentUnderMouse, under);
    } else if (type == (int)Gap::Gui::igGuiSystemModel::k_focusedComponent) {
        igObject *focused = (igObject *)model->_focusedComponent;
        void *common = FUN_004565c0((int)self, focused);
        if (self->_oldFocusedComponent != 0) {
            ((Gap::Gui::igGuiComponent *)self->_oldFocusedComponent)->setHasFocus(0);
            FUN_00456540((int)self, (N *)self->_oldFocusedComponent, (N *)common, 0);
        }
        if (focused != 0) {
            ((Gap::Gui::igGuiComponent *)focused)->setHasFocus(1);
            FUN_00456540((int)self, (N *)focused, (N *)common, 1);
        }
        setComponent_4561e0(&self->_oldFocusedComponent, focused);
    } else if (type == (int)Gap::Gui::igGuiSystemModel::k_pushedComponent) {
        igObject *pushed = (igObject *)model->_pushedComponent;
        if (self->_oldPushedComponent != 0) {
            ((Gap::Gui::igGuiComponent *)self->_oldPushedComponent)->setPushed(0);
        }
        if (pushed != 0) {
            ((Gap::Gui::igGuiComponent *)pushed)->setPushed(1);
        }
        setComponent_4561e0(&self->_oldPushedComponent, pushed);
    } else if (msg->handled == 0) {
        setComponent_4561e0(&self->_oldPushedComponent, (igObject *)model->_pushedComponent);
        setComponent_4561e0(&self->_oldFocusedComponent, (igObject *)model->_focusedComponent);
        setComponent_4561e0(&self->_oldComponentUnderMouse, (igObject *)model->_componentUnderMouse);
        if (self->_oldPushedComponent != 0) {
            ((Gap::Gui::igGuiComponent *)self->_oldPushedComponent)->setPushed(1);
        }
        if (self->_oldFocusedComponent != 0) {
            ((Gap::Gui::igGuiComponent *)self->_oldFocusedComponent)->setHasFocus(1);
        }
        if (self->_oldComponentUnderMouse != 0) {
            ((Gap::Gui::igGuiComponent *)self->_oldComponentUnderMouse)->setMouseOver(1);
        }
    }
}

int FUN_00456540(int arg0, N *arg1, N *arg2, unsigned char arg3) {
    int r;

    if (arg1 != 0) {
        if (arg1 == arg2) {
            return r;
        }
        ((Gap::Gui::igGuiComponentModel *)arg1->f10)->setChildHasFocus(arg3);
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

