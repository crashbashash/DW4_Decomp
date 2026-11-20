void igBoolArrayMetaField_SwapBytes(igBoolArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)Gap::Core::igBoolMetaField::getMetaField()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

unsigned short igBoolArrayMetaField_GetSize(void *self) {
    return ((igBoolArrayMetaField *)self)->_num;
}

void igBoolArrayMetaField_SetDefaultAll(igBoolArrayMetaField *self, int value) {
    char *base;
    int i;
    ((igMetaFieldView *)self)->SetDefault(0);
    base = (char *)self->_default;
    for (i = 0; i < self->_num; i++) {
        base[i] = value;
    }
}

