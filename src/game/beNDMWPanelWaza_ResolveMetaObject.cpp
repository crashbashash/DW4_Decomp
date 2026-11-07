extern "C" {
void FUN_003bf050(void);
extern struct G *DAT_0058b358[4];
void *beNDMWPanelWaza_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWPanelWaza_ResolveMetaObject(void) {
    struct G *g = DAT_0058b358[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bf050();
    }
    return DAT_0058b358[0];
}
