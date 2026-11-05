int igShortMetaField_EnsureRegistered();
int FUN_0030a4c0();
int igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int FUN_002ba030(int arg0, int arg1) {
    int p;

    if (*DAT_00586dc8[0] != 0) {
        igShortMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    p = igObject_AllocateRawStorageDefault(0x34, 0);
    if (p != 0) {
        p = FUN_0030a4c0(p, arg0);
    }
    return p;
}
