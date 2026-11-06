int igEnumMetaField_EnsureRegistered();
int FUN_002dc940();
int igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int Gap__Core__igEnumMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        igEnumMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = igObject_AllocateRawStorageDefault(0x38, 0);
    if (temp_v0 != 0) {
        temp_v0 = FUN_002dc940(temp_v0, arg0);
    }
    return temp_v0;
}
