extern "C" {
void FUN_003344f0(void);
extern struct G *DAT_00587628[4];
void *FUN_00334460(void);
}
struct G { int pad[9]; int f; };
void *FUN_00334460(void) {
    struct G *g = DAT_00587628[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003344f0();
end:
    return DAT_00587628[0];
}
