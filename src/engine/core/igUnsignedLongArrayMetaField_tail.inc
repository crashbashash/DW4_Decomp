void igUnsignedLongArrayMetaField_SwapBytes(igUnsignedLongArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igUnsignedLongMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(descriptor))->SwapBytes((void *)(item), (int)(count * self->_num));
}

/* Byte size of the array field's storage: `_num` elements of 8 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int igUnsignedLongArrayMetaField_GetSize(igUnsignedLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

