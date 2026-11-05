extern "C" {
void FUN_003b5d70(void);
extern struct G *DAT_0058ac38[4];
void *FUN_003b5bb0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b5bb0(void) {
    struct G *g = DAT_0058ac38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b5d70();
end:
    return DAT_0058ac38[0];
}
