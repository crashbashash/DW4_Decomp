void igIntArrayMetaField_SwapBytes(igIntArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementDescriptor))->SwapBytes((void *)(passThrough), (int)(perElement * self->_num));
}

int igIntArrayMetaField_GetSize(void *arg0) {
    return (*(int *)((char *)(arg0) + 52) * 4) & 0xFFFF;
}

void igIntArrayMetaField_SetDefaultValue(void **arg0, int arg1) {
    int *p;
    igIntArrayMetaField *o = (igIntArrayMetaField *)arg0;
    ((igMetaFieldView *)arg0)->SetDefault(0);
    int i;
    p = (int *)o->_default;
    for (i = 0; i < o->_num; i++) {
        p[i] = arg1;
    }
}

