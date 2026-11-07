extern "C" {
void FUN_003c5600(void);
extern struct G *DAT_0058bc10[4];
void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void) {
    struct G *g = DAT_0058bc10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c5600();
    }
    return DAT_0058bc10[0];
}
