void igUnsignedCharArrayMetaField_SwapBytes(igUnsignedCharArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)Gap::Core::igUnsignedCharMetaField::getMetaField()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

/* Storage size in bytes of the field's array. One byte per element, so the size is the element
 * count `_num` (returned as a 16-bit value, like the `_size` field of igMetaField that it feeds). */

unsigned short igUnsignedCharArrayMetaField_GetSize(igUnsignedCharArrayMetaField *self) {
    return self->_num;
}

