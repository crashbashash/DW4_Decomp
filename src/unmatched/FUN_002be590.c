/* 116 bytes. */
int igMetaObject_EnsureRegistered();
void *igMetaObject_CopyConstruct(void *, int);
void *igObject_AllocateRawStorageDefault(int, int);
void *igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
void *FUN_002be590(int arg0, int arg1) {
    void *r;
    if (*DAT_00586dc8[0] != 0) {
        igMetaObject_EnsureRegistered();
        r = igObject_CloneViaMetadata(arg0, arg1);
    } else {
        r = igObject_AllocateRawStorageDefault(0x64, 0);
        if (r != 0) {
            r = igMetaObject_CopyConstruct(r, arg0);
        }
    }
    return r;
}
