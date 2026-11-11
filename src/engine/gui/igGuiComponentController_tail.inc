void Gap__Gui__igGuiComponentController__vfunc_23(igGuiComponentController *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}

void Gap__Gui__igGuiComponentController__vfunc_24(igGuiComponentController *arg0, void *arg1) {
    int temp_a1;
    igGuiComponentModel *temp_a2;

    temp_a1 = *(int *)((char *)(arg1) + 8);
    temp_a2 = (igGuiComponentModel *)(arg0->_model);
    if (temp_a1 == DAT_0058c448[0]) {
        if (temp_a2->_enabled != 0) {
            ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_108_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c450[0]) {
        if (temp_a2->_hasFocus != 0) {
            ((DW4VC_112_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_116_2_4556e0 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c458[0]) {
        if (temp_a2->_mouseOver != 0) {
            ((DW4VC_120_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_124_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c460[0]) {
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
    int sp10[4];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c450[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)&sp10[0]);
    }
}

void FUN_00455900(struct S_455900 *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->f;
    if (temp_a2 != arg1) {
        arg0->f = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c458[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp10);
    }
}

void FUN_00455950(S_455950 *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != (arg1 & 0xFF)) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c460[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp10);
    }
}

void FUN_004559a0(struct S_4559a0 *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp[0] = 2;
        sp[1] = 0;
        sp[2] = DAT_0058c470[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp);
    }
}

