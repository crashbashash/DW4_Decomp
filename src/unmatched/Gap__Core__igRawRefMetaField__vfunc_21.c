int igRawRefMetaField_EnsureRegistered();
int FUN_00305480();
int igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int Gap__Core__igRawRefMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        igRawRefMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = igObject_AllocateRawStorageDefault(0x38, 0);
    if (temp_v0 != 0) {
        temp_v0 = FUN_00305480(temp_v0, arg0);
    }
    return temp_v0;
}
