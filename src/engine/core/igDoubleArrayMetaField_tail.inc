void igDoubleArrayMetaField_SwapBytes(igDoubleArrayMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)igDoubleMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(temp_v0))->SwapBytes((void *)(arg1), (int)(arg2 * arg0->_num));
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (double), truncated to
 * the 16-bit size the meta field system uses. */

int igDoubleArrayMetaField_GetSize(igDoubleArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

