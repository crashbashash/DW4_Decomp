void Gap__Core__igUnsignedIntArrayMetaField__vfunc_52(igUnsignedIntArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igUnsignedIntMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(descriptor))->SwapBytes((void *)(item), (int)(count * self->_num));
}

/* Size in bytes of the array field: `_num` unsigned-int elements, truncated to the 16-bit `_size`
 * field width of the meta-field (`_num` +52, `_size` +20 unsigned short). */

int Gap__Core__igUnsignedIntArrayMetaField__vfunc_25(igUnsignedIntArrayMetaField *self) {
    return (self->_num * sizeof(unsigned int)) & 0xFFFF;
}

