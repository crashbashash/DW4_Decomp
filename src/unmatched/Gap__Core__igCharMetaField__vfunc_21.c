int FUN_002cc160();
void *igObject_AllocateRawStorageDefault(int, int);
void *igObject_CloneViaMetadata(void *, void *);
void *FUN_002d4de0(void *, void *);
extern unsigned char *DAT_00586dc8[4];
void *Gap__Core__igCharMetaField__vfunc_21(void *arg0, void *arg1) {
    void *p;
    if (*DAT_00586dc8[0] != 0) {
        FUN_002cc160();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    p = igObject_AllocateRawStorageDefault(0x34, 0);
    if (p) p = FUN_002d4de0(p, arg0);
    return p;
}
