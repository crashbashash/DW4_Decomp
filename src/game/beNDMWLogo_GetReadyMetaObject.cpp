extern "C" {
void FUN_003c2490(void);
extern struct G *DAT_0058b570[4];
void *beNDMWLogo_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLogo_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b570[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c2490();
    }
    return DAT_0058b570[0];
}
