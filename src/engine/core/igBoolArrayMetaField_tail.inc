void Gap__Core__igBoolArrayMetaField__vfunc_52(igBoolArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)FUN_002cce00()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

unsigned short Gap__Core__igBoolArrayMetaField__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 52);
}

void FUN_002d35d0(igBoolArrayMetaField *arg0, int arg1) {
    char *base;
    int i;
    ((igMetaFieldView *)arg0)->SetDefault(0);
    base = (char *)arg0->_default;
    for (i = 0; i < arg0->_num; i++) {
        base[i] = arg1;
    }
}

