void Gap__Core__igUnsignedShortArrayMetaField__vfunc_52(igUnsignedShortArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)FUN_002b6330()));
    ((DW4VC_208_2 *)(descriptor))->vX((int)(item), (int)(count * self->_num));
}

/* Byte size of the array field's storage: `_num` elements of 2 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
int Gap__Core__igUnsignedShortArrayMetaField__vfunc_25(igUnsignedShortArrayMetaField *self) {
    return (self->_num * 2) & 0xFFFF;
}

