void igWindowSizeObserver_OnModelChange(igWindowSizeObserver *self, int *arg1) {
    struct T_455b90 *temp_s0;
    if ((arg1[2] == (int)Gap::Gui::igGuiSystemModel::k_windowSize) || (arg1[0] == 0)) {
        temp_s0 = (struct T_455b90 *)self->_model;
        FUN_00191860((char *)temp_s0 + 0x60, 0.0f, temp_s0->w, temp_s0->h, 0.0f, 0.0f, 2.0f);
        igNotifyEvent sp30((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_projectionMatrix, (Gap::Gui::igView *)(int)self);
        ((Gap::Gui::igModel *)temp_s0)->notifyAllViews(sp30);
    }
}

