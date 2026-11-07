extern "C" {
void FUN_003c6520(void);
extern struct G *DAT_0058bd00[4];
void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bd00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c6520();
    }
    return DAT_0058bd00[0];
}
