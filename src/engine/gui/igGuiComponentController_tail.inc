void igGuiComponentController_IsCompatible(igGuiComponentController *self, int model) {
    ((Gap::Core::igObject *)model)->isOfType(igGuiComponentModel_GetMetaObject());
}

void igGuiComponentController_OnModelChange(igGuiComponentController *arg0, void *arg1) {
    int temp_a1;
    igGuiComponentModel *temp_a2;

    temp_a1 = *(int *)((char *)(arg1) + 8);
    temp_a2 = (igGuiComponentModel *)(arg0->_model);
    if (temp_a1 == (int)g_igGuiComponentModel_enabledMetaField) {
        if (temp_a2->_enabled != 0) {
            ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_108_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)g_igGuiComponentModel_hasFocusMetaField) {
        if (temp_a2->_hasFocus != 0) {
            ((DW4VC_112_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_116_2_4556e0 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)g_igGuiComponentModel_mouseOverMetaField) {
        if (temp_a2->_mouseOver != 0) {
            ((DW4VC_120_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_124_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == (int)g_igGuiComponentModel_pushedMetaField) {
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

void FUN_004558b0(struct S_4558b0 *arg0, unsigned char arg1) {
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        igNotifyEvent sp10((Gap::Core::igMetaField *)g_igGuiComponentModel_hasFocusMetaField);
        ((Gap::Gui::igModel *)arg0)->notifyAllViews(sp10);
    }
}

void FUN_00455900(struct S_455900 *arg0, unsigned char arg1) {
    unsigned char temp_a2;

    temp_a2 = arg0->f;
    if (temp_a2 != arg1) {
        arg0->f = arg1;
        igNotifyEvent sp10((Gap::Core::igMetaField *)g_igGuiComponentModel_mouseOverMetaField);
        ((Gap::Gui::igModel *)arg0)->notifyAllViews(sp10);
    }
}

void FUN_00455950(S_455950 *arg0, unsigned char arg1) {
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != (arg1 & 0xFF)) {
        arg0->b = arg1;
        igNotifyEvent sp10((Gap::Core::igMetaField *)g_igGuiComponentModel_pushedMetaField);
        ((Gap::Gui::igModel *)arg0)->notifyAllViews(sp10);
    }
}

void FUN_004559a0(struct S_4559a0 *arg0, unsigned char arg1) {
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        igNotifyEvent sp((Gap::Core::igMetaField *)g_igGuiComponentModel_childHasFocusMetaField);
        ((Gap::Gui::igModel *)arg0)->notifyAllViews(sp);
    }
}

