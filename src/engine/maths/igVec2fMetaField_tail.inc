void igVec2fMetaField_SwapBytes(igVec2fMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igFloatMetaField_GetDefaultDescriptor());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * ((unsigned int)arg0->_size >> 2)));
}

void igVec2fMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    FUN_0018be80(arg2, arg1, 2, 4, 1);
}

void igVec2fMetaField_ValueToString(int *out, void *field, const float *value) {
    char text[1024];
    sprintf(text, "%f,%f", value[0], value[1]);
    *out = internString(text);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec2f is two 32-bit
 * floats, 8 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
int igVec2fMetaField_GetSize(void) {
    return 8;
}

void igVec2fMetaField_SetDefault(igMetaField *self, const float *value)
{
    ((igVec2fMetaFieldView *)self)->SetDefault(value);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 8-byte element size. The receiver is not read. */
int igVec2fMetaField_GetAlignment(void) {
    return 0x10;
}

