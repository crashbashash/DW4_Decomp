void igWindowSizeObserver_OnModelChange(igWindowSizeObserver *self, int *arg1) {
    int sp30[3];
    struct T_455b90 *temp_s0;
    if ((arg1[2] == (int)g_igGuiSystemModel_windowSizeMetaField) || (arg1[0] == 0)) {
        temp_s0 = (struct T_455b90 *)self->_model;
        FUN_00191860((char *)temp_s0 + 0x60, 0.0f, temp_s0->w, temp_s0->h, 0.0f, 0.0f, 2.0f);
        sp30[0] = 2;
        sp30[1] = (int)self;
        sp30[2] = (int)g_igGuiSystemModel_projectionMatrixMetaField;
        igModel_NotifyViews((igModel *)temp_s0, (ModelChange *)sp30);
    }
}

