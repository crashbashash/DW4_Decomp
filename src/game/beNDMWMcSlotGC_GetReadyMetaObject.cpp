extern "C" {
int FUN_003c5dc0();
struct G { char pad[36]; int f; };
extern G *DAT_0058bca8[4];
G *beNDMWMcSlotGC_GetReadyMetaObject(void);
}
G *beNDMWMcSlotGC_GetReadyMetaObject(void) {
    G *g = DAT_0058bca8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c5dc0();
    return DAT_0058bca8[0];
}
