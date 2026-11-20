void igDoubleArrayMetaField_SwapBytes(igDoubleArrayMetaField *self, int data, int count) {
    void **element;

    element = (void **)(((void **)Gap::Core::igDoubleMetaField::getMetaField()));
    ((igMetaFieldView *)(element))->SwapBytes((void *)(data), (int)(count * self->_num));
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (double), truncated to
 * the 16-bit size the meta field system uses. */

int igDoubleArrayMetaField_GetSize(igDoubleArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

