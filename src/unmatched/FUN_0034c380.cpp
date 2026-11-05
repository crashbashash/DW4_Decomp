extern "C" {
void FUN_0034c460(void);
extern struct G *DAT_005884e0[4];
void *FUN_0034c380(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034c380(void) {
    struct G *g = DAT_005884e0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034c460();
end:
    return DAT_005884e0[0];
}
