extern "C" {
void FUN_003c5780(void);
extern struct G *DAT_0058bc18[4];
void *beNDMWLoadSavePlWork_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSavePlWork_ResolveMetaObject(void) {
    struct G *g = DAT_0058bc18[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c5780();
    }
    return DAT_0058bc18[0];
}
