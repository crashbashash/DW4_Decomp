extern "C" {
void FUN_003c9360(void);
extern struct G *DAT_0058bf90[4];
void *beNDMWItemBase_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemBase_ResolveMetaObject(void) {
    struct G *g = DAT_0058bf90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c9360();
    }
    return DAT_0058bf90[0];
}
