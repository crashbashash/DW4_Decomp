void igVec4ucMetaField_SwapBytes(igVec4ucMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(Gap::Core::igUnsignedCharMetaField::getMetaField());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_size));
}

void igVec4ucMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    FUN_0018be80((const char *)arg2, (void *)arg1, 4, 1, 0);
}

void igVec4ucMetaField_ValueToString(int *out, void *field, const unsigned char *value) {
    char text[1024];
    sprintf(text, "%uc,%uc,%uc,%uc", value[0], value[1], value[2], value[3]);
    *out = internString(text);
}

int Gap__igVec4ucMetaField__vfunc_25(void) {
    return 4;
}

int igVec4ucMetaField_GetAlignment(void) {
    return 1;
}

