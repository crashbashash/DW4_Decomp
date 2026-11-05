extern "C" {
int FUN_003c1270();
struct G { char pad[36]; int f; };
extern G *DAT_0058b4a8[4];
G *beNDMWMdlItem_GetReadyMetaObject(void);
}
G *beNDMWMdlItem_GetReadyMetaObject(void) {
    G *g = DAT_0058b4a8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c1270();
    return DAT_0058b4a8[0];
}
