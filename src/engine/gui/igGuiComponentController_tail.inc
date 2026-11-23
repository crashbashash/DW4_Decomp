void igGuiComponentController_IsCompatible(igGuiComponentController *self, int model) {
    ((Gap::Core::igObject *)model)->isOfType(Gap::Gui::igGuiComponentModel::getClassTypeSafe());
}

void igGuiComponentController_OnModelChange(igGuiComponentController *arg0, void *arg1) {
    int temp_a1;
    igGuiComponentModel *temp_a2;

    temp_a1 = *(int *)((char *)(arg1) + 8);
    temp_a2 = (igGuiComponentModel *)(arg0->_model);
    if (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_enabled) {
        if (temp_a2->_enabled != 0) {
            ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_108_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_hasFocus) {
        if (temp_a2->_hasFocus != 0) {
            ((DW4VC_112_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_116_2_4556e0 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_mouseOver) {
        if (temp_a2->_mouseOver != 0) {
            ((DW4VC_120_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_124_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_pushed) {
        if (temp_a2->_pushed != 0) {
            ((DW4VC_128_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
    }
}

void Gap__Gui__igGuiComponentController__vfunc_33(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_32(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_31(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_30(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_29(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_28(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_27(void) {
}

void Gap__Gui__igGuiComponentController__vfunc_26(void) {
}

int Gap__Gui__igGuiComponentController__vfunc_25(void) {
    return 0;
}

namespace Gap {
namespace Gui {

void igGuiComponentModel::setHasFocus(unsigned char hasFocus)
{
    if (_hasFocus != hasFocus) {
        _hasFocus = hasFocus;
        notifyAllViews(igNotifyEvent(k_hasFocus));
    }
}

void igGuiComponentModel::setMouseOver(unsigned char mouseOver)
{
    if (_mouseOver != mouseOver) {
        _mouseOver = mouseOver;
        notifyAllViews(igNotifyEvent(k_mouseOver));
    }
}

void igGuiComponentModel::setPushed(unsigned char pushed)
{
    if (_pushed != pushed) {
        _pushed = pushed;
        notifyAllViews(igNotifyEvent(k_pushed));
    }
}

void igGuiComponentModel::setChildHasFocus(unsigned char hasFocus)
{
    if (_childHasFocus != hasFocus) {
        _childHasFocus = hasFocus;
        notifyAllViews(igNotifyEvent(k_childHasFocus));
    }
}
}
}

