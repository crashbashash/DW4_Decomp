extern "C" {
void FUN_003c9650(void);
extern struct G *DAT_0058bfb0[4];
void *beNDMWShinkaCtrl_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWShinkaCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058bfb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c9650();
    }
    return DAT_0058bfb0[0];
}
