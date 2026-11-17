void igIntArrayMetaField_SwapBytes(igIntArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementDescriptor))->SwapBytes((void *)(passThrough), (int)(perElement * self->_num));
}

int igIntArrayMetaField_GetSize(igIntArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igIntArrayMetaField_SetDefaultValue(igMetaField *field, int value) {
    int *p;
    igIntArrayMetaField *o = (igIntArrayMetaField *)field;
    ((igMetaFieldView *)field)->SetDefault(0);
    int i;
    p = (int *)o->_default;
    for (i = 0; i < o->_num; i++) {
        p[i] = value;
    }
}

