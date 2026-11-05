extern "C" {
int FUN_0045cdc0();
struct G { char pad[36]; int f; };
extern G *DAT_0058cce0[4];
G *igCameraMode_GetMetaObject(void);
}
G *igCameraMode_GetMetaObject(void) {
    G *g = DAT_0058cce0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0045cdc0();
    return DAT_0058cce0[0];
}
