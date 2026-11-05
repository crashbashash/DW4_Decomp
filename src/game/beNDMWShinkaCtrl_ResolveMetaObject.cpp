extern "C" {
void FUN_003c9650(void);
extern struct G *DAT_0058bfb0[4];
void *beNDMWShinkaCtrl_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWShinkaCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058bfb0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c9650();
end:
    return DAT_0058bfb0[0];
}
