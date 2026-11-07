extern "C" {
void FUN_003c0e80(void);
extern struct G *DAT_0058b498[4];
void *beNDMWMdlMapCursor_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlMapCursor_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b498[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c0e80();
    }
    return DAT_0058b498[0];
}
