extern "C" {
void FUN_003bf3f0(void);
extern struct G *DAT_0058b368[4];
void *beNDMWMdlPlayer2_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPlayer2_ResolveMetaObject(void) {
    struct G *g = DAT_0058b368[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bf3f0();
    }
    return DAT_0058b368[0];
}
