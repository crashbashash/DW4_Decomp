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

void igEnumArrayMetaField_SetDefault(void *arg0, int arg1) {
    int *a;
    int i;
    ((igMetaFieldView *)arg0)->SetDefault(0);
    a = (int *)*(int *)((char *)arg0 + 32);
    for (i = 0; i < *(int *)((char *)arg0 + 56); i++) {
        a[i] = arg1;
    }
}

void igEnumMetaField_SetDefaultValue(igMetaFieldView *self, const int *value)
{
    self->SetDefault(value);
}

