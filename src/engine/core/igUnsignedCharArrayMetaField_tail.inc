void igUnsignedCharArrayMetaField_SwapBytes(igUnsignedCharArrayMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)igUnsignedCharMetaField_GetDefaultDescriptor()));
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_num));
}

/* Storage size in bytes of the field's array. One byte per element, so the size is the element
 * count `_num` (returned as a 16-bit value, like the `_size` field of igMetaField that it feeds). */

unsigned short igUnsignedCharArrayMetaField_GetSize(igUnsignedCharArrayMetaField *self) {
    return self->_num;
}

