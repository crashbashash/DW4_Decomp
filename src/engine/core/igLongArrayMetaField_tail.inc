void igLongArrayMetaField_SwapBytes(igLongArrayMetaField *self, int data, int count) {
    void **element;

    element = (void **)(((void **)igLongMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(element))->SwapBytes((void *)(data), (int)(count * self->_num));
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (long), truncated to the
 * 16-bit size the meta field system uses. */

int igLongArrayMetaField_GetSize(igLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

