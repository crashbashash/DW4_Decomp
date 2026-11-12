void igVec4fArrayMetaField_SwapBytes(igVec4fArrayMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(FUN_00187520());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_num));
}

int igVec4fArrayMetaField_GetSize(igVec4fArrayMetaField *self) {
    return (self->_num * 0x10) & 0xFFFF;
}

