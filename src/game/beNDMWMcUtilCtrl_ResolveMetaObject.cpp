extern "C" {
void FUN_003c5380(void);
extern struct G *DAT_0058bb80[4];
void *beNDMWMcUtilCtrl_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMcUtilCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058bb80[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c5380();
end:
    return DAT_0058bb80[0];
}
