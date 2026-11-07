extern "C" {
void FUN_003c8e60(void);
extern struct G *DAT_0058bf68[4];
void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf68[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c8e60();
    }
    return DAT_0058bf68[0];
}
