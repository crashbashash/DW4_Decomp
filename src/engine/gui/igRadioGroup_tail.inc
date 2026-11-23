void igRadioGroup_resetFields(igRadioGroup *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    *(int *)((char *)(self->_selectedObserver) + 12) = (int)(self);
    ((Gap::Gui::igView *)self->_selectedObserver)->setModel((Gap::Gui::igModel *)(self->_model));
}

