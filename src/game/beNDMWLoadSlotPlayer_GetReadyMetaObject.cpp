extern "C" {
void FUN_003c6520(void);
extern struct G *DAT_0058bd00[4];
void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bd00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c6520();
end:
    return DAT_0058bd00[0];
}
