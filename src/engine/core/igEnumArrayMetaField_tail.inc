void igEnumArrayMetaField_SwapBytes(igEnumArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igEnumMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

/* IgEnumArrayMetaField virtual getter 25. Returns the array's storage size in bytes truncated to
 * 16 bits: `_num` elements of 4 bytes each (the enum values are ints). The 16-bit result matches
 * the reflected `_size` field (unsigned short, +20) that the metafield base class carries. */

int igEnumArrayMetaField_GetSize(igEnumArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igEnumArrayMetaField_SetDefault(void *self, int value) {
    int *a;
    int i;
    ((igMetaFieldView *)self)->SetDefault(0);
    a = (int *)((igEnumArrayMetaField *)self)->_default;
    for (i = 0; i < ((igEnumArrayMetaField *)self)->_num; i++) {
        a[i] = value;
    }
}

void igEnumMetaField_SetDefaultValue(igMetaFieldView *self, const int *value)
{
    self->SetDefault(value);
}

