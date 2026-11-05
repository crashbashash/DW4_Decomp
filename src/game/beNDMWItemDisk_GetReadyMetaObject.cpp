extern "C" {
void FUN_003c86d0(void);
extern struct G *DAT_0058bf38[4];
void *beNDMWItemDisk_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemDisk_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c86d0();
end:
    return DAT_0058bf38[0];
}
