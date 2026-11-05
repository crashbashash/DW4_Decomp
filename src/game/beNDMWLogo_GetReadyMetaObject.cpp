extern "C" {
void FUN_003c2490(void);
extern struct G *DAT_0058b570[4];
void *beNDMWLogo_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLogo_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b570[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c2490();
end:
    return DAT_0058b570[0];
}
