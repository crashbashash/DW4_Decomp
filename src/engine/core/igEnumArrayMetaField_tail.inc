void Gap__Core__igEnumArrayMetaField__vfunc_52(igEnumArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igEnumMetaField_GetDefaultDescriptor()));
    ((MetaFieldSwapBytesSlot *)(elementField))->SwapBytes((int)(buffer), (int)(count * self->_num));
}

/* IgEnumArrayMetaField virtual getter 25. Returns the array's storage size in bytes truncated to
 * 16 bits: `_num` elements of 4 bytes each (the enum values are ints). The 16-bit result matches
 * the reflected `_size` field (unsigned short, +20) that the metafield base class carries. */

int Gap__Core__igEnumArrayMetaField__vfunc_25(igEnumArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void FUN_002dc730(void *arg0, int arg1) {
    int *a;
    int i;
    ((DW4VC_140_1 *)arg0)->vX(0);
    a = (int *)*(int *)((char *)arg0 + 32);
    for (i = 0; i < *(int *)((char *)arg0 + 56); i++) {
        a[i] = arg1;
    }
}

void FUN_002dc7a0(igEnumMetaFieldView *self, const int *value)
{
    self->SetDefault(value);
}

