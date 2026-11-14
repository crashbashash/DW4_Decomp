void igBoolArrayMetaField_SwapBytes(igBoolArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igBoolMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

unsigned short igBoolArrayMetaField_GetSize(void *arg0) {
    return *(int *)((char *)(arg0) + 52);
}

void igBoolArrayMetaField_SetDefaultAll(igBoolArrayMetaField *arg0, int arg1) {
    char *base;
    int i;
    ((igMetaFieldView *)arg0)->SetDefault(0);
    base = (char *)arg0->_default;
    for (i = 0; i < arg0->_num; i++) {
        base[i] = arg1;
    }
}

