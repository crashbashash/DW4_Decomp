void igGuiSystemModel_resetFields(int arg0, int arg1) {
    float vec[3];

    Gap__Core__igObject__resetFields((igObject *)arg0, arg1);
    if (arg1 != 0) {
        igMatrix44f_SetIdentity((float *)(arg0 + 0x20));
        vec[0] = 0.375f;
        vec[2] = -0.5f;
        vec[1] = 0.375f;
        igMatrix44f_SetTranslation((float *)(arg0 + 0x20), (const float *)vec);
        igNotifyEvent args((Gap::Core::igMetaField *)g_igGuiSystemModel_viewMatrixMetaField);
        ((Gap::Gui::igModel *)arg0)->notifyAllViews(args);
    }
}

