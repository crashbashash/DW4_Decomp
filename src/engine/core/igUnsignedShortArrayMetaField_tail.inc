void igUnsignedShortArrayMetaField_SwapBytes(igUnsignedShortArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igUnsignedShortMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(descriptor))->SwapBytes((void *)(item), (int)(count * self->_num));
}

/* Byte size of the array field's storage: `_num` elements of 2 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int igUnsignedShortArrayMetaField_GetSize(igUnsignedShortArrayMetaField *self) {
    return (self->_num * 2) & 0xFFFF;
}

