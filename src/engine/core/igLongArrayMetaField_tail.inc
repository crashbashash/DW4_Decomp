void igLongArrayMetaField_SwapBytes(igLongArrayMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)FUN_002c1c70()));
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_num));
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (long), truncated to the
 * 16-bit size the meta field system uses. */

int igLongArrayMetaField_GetSize(igLongArrayMetaField *self) {
    return (self->_num * 8) & 0xFFFF;
}

