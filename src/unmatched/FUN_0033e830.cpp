extern "C" {
void FUN_0033ea40(void);
extern struct G *DAT_00587a20[4];
void *FUN_0033e830(void);
}
struct G { int pad[9]; int f; };
void *FUN_0033e830(void) {
    struct G *g = DAT_00587a20[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0033ea40();
end:
    return DAT_00587a20[0];
}
