extern "C" {
void FUN_00364390(void);
extern struct G *DAT_00589848[4];
void *FUN_00364260(void);
}
struct G { int pad[9]; int f; };
void *FUN_00364260(void) {
    struct G *g = DAT_00589848[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00364390();
end:
    return DAT_00589848[0];
}
