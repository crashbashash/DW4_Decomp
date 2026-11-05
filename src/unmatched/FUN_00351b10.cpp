extern "C" {
void FUN_00351c60(void);
extern struct G *DAT_00588a90[4];
void *FUN_00351b10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00351b10(void) {
    struct G *g = DAT_00588a90[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00351c60();
end:
    return DAT_00588a90[0];
}
