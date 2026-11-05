extern "C" {
void FUN_00365830(void);
extern struct G *DAT_005898c8[4];
void *FUN_003657a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003657a0(void) {
    struct G *g = DAT_005898c8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00365830();
end:
    return DAT_005898c8[0];
}
