int igStringMetaField_EnsureRegistered();
int FUN_0030b2c0(int, int);
int igObject_AllocateRawStorageDefault(int, int);
int igObject_CloneViaMetadata(int, int);
extern unsigned char * DAT_00586dc8[4];
int Gap__Core__igStringMetaField__vfunc_21(int arg0, int arg1) {
    int temp_v0;
    if (*DAT_00586dc8[0] != 0) {
        igStringMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = igObject_AllocateRawStorageDefault(0x3C, 0);
    if (temp_v0 != 0) {
        temp_v0 = FUN_0030b2c0(temp_v0, arg0);
    }
    return temp_v0;
}
