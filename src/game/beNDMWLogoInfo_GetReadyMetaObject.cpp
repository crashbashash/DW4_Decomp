extern "C" {
void FUN_003c1f50(void);
extern struct G *DAT_0058b528[4];
void *beNDMWLogoInfo_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLogoInfo_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b528[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c1f50();
end:
    return DAT_0058b528[0];
}
