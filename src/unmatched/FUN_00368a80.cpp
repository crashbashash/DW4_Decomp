extern "C" {
void FUN_00368bc0(void);
extern struct G *DAT_00589b90[4];
void *FUN_00368a80(void);
}
struct G { int pad[9]; int f; };
void *FUN_00368a80(void) {
    struct G *g = DAT_00589b90[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00368bc0();
end:
    return DAT_00589b90[0];
}
