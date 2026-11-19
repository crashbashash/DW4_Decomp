void igRadioGroup_resetFields(igRadioGroup *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    *(int *)((char *)(self->_selectedObserver) + 12) = (int)(self);
    igView_SetModel((igView *)(self->_selectedObserver), (igModel *)(self->_model));
}

