void igMatrix44fMetaField_SwapBytes(igMatrix44fMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igFloatMetaField_GetDefaultDescriptor());
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * (int)((unsigned int) arg0->_size >> 2)));
}

void Gap__igMatrix44fMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    FUN_0018be80(arg2, arg1, 16, 4, 1);
}

void Gap__igMatrix44fMetaField__vfunc_57(int *out, void *field, const float *value) {
    char text[1024];
    sprintf(text, "\n%f,%f,%f,%f,\n%f,%f,%f,%f,\n%f,%f,%f,%f,\n%f,%f,%f,%f\n", value[0], value[1], value[2], value[3],
            value[4], value[5], value[6], value[7], value[8], value[9], value[10], value[11], value[12], value[13],
            value[14], value[15]);
    *out = internString(text);
}

/* igMatrix44fMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A 4x4 float
 * matrix is 16 floats * 4 bytes = 0x40. */
int igMatrix44fMetaField_GetSize(void) {
    return 0x40;
}

void FUN_0018c640(igMatrix44fMetaFieldView *self, const float *value)
{
    self->SetDefault(value);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 64-byte matrix size. The receiver is not read. */
int Gap__igMatrix44fMetaField__vfunc_27(void) {
    return 0x10;
}

