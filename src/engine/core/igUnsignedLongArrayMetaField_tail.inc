void Gap__Core__igUnsignedLongArrayMetaField__vfunc_52(igUnsignedLongArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)FUN_002b69f0()));
    ((DW4VC_208_2 *)(descriptor))->vX((int)(item), (int)(count * self->_num));
}

/* Byte size of the array field's storage: `_num` elements of 8 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int Gap__Core__igUnsignedLongArrayMetaField__vfunc_25(igUnsignedLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

