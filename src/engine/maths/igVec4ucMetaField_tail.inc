void igVec4ucMetaField_SwapBytes(igVec4ucMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igUnsignedCharMetaField_GetDefaultDescriptor());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_size));
}

void Gap__igVec4ucMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    FUN_0018be80(arg2, arg1, 4, 1, 0);
}

void Gap__igVec4ucMetaField__vfunc_57(int *out, void *field, const unsigned char *value) {
    char text[1024];
    sprintf(text, DAT_004e0de0, value[0], value[1], value[2], value[3]);
    *out = internString(text);
}

int Gap__igVec4ucMetaField__vfunc_25(void) {
    return 4;
}

int Gap__igVec4ucMetaField__vfunc_27(void) {
    return 1;
}

