extern "C" {
void FUN_003bfae0(void);
extern struct G *DAT_0058b3a8[4];
void *beNDMWMdlPlayer_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPlayer_ResolveMetaObject(void) {
    struct G *g = DAT_0058b3a8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bfae0();
end:
    return DAT_0058b3a8[0];
}
