extern "C" {
void igIntMetaField_EnsureRegistered();
void *FUN_002ea460(void *, void *);
void *igObject_AllocateRawStorageDefault(int, int);
void *igObject_CloneViaMetadata(void *, void *);
extern unsigned char *DAT_00586dc8[4];
void *Gap__Core__igIntMetaField__vfunc_21(void *self, void *src) {
    void *o;
    if (*DAT_00586dc8[0] != 0) {
        igIntMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(self, src);
    }
    o = igObject_AllocateRawStorageDefault(0x34, 0);
    if (o != 0) {
        o = FUN_002ea460(o, self);
    }
    return o;
}
}
