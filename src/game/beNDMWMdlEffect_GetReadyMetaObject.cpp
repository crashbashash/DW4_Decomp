extern "C" {
void FUN_003c1bf0(void);
extern struct G *DAT_0058b518[4];
void *beNDMWMdlEffect_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlEffect_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b518[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c1bf0();
end:
    return DAT_0058b518[0];
}
