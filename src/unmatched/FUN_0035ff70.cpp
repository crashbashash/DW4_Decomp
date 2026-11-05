extern "C" {
void FUN_00360000(void);
extern struct G *DAT_00589558[4];
void *FUN_0035ff70(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035ff70(void) {
    struct G *g = DAT_00589558[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00360000();
end:
    return DAT_00589558[0];
}
