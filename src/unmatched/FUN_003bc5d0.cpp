extern "C" {
void FUN_003bc660(void);
extern struct G *DAT_0058b0a8[4];
void *FUN_003bc5d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bc5d0(void) {
    struct G *g = DAT_0058b0a8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bc660();
end:
    return DAT_0058b0a8[0];
}
