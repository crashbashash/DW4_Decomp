void igVec4fMetaField_SwapBytes(igVec4fMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igFloatMetaField_GetDefaultDescriptor());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * ((unsigned int)(arg0->_size) >> 2)));
}

void Gap__igVec4fMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    FUN_0018be80(arg2, arg1, 4, 4, 1);
}

void Gap__igVec4fMetaField__vfunc_57(int *out, void *field, const float *value) {
    char text[1024];
    sprintf(text, text_f_f_f_f, value[0], value[1], value[2], value[3]);
    *out = internString(text);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec4f is four 32-bit
 * floats, 16 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
int igVec4fMetaField_GetSize(void) {
    return 0x10;
}

void FUN_0018e670(igVec4fMetaFieldView *self, const float *value)
{
    self->SetDefault(value);
}

int Gap__igVec4fMetaField__vfunc_27(void) {
    return 0x10;
}

