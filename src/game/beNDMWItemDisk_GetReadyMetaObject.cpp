extern "C" {
void FUN_003c86d0(void);
extern struct G *DAT_0058bf38[4];
void *beNDMWItemDisk_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemDisk_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf38[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c86d0();
    }
    return DAT_0058bf38[0];
}
