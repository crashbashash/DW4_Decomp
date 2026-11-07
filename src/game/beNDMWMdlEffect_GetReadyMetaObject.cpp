extern "C" {
void FUN_003c1bf0(void);
extern struct G *DAT_0058b518[4];
void *beNDMWMdlEffect_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlEffect_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b518[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c1bf0();
    }
    return DAT_0058b518[0];
}
