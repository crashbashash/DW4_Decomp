int __internalObjectList_EnsureRegistered();
int InternalObjectList_CopyConstruct();
int igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int FUN_002c2710(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        __internalObjectList_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = igObject_AllocateRawStorageDefault(0x10, 0);
    if (temp_v0 != 0) {
        temp_v0 = InternalObjectList_CopyConstruct(temp_v0, arg0);
    }
    return temp_v0;
}
