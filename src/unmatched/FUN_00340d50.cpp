extern "C" {
void FUN_00340e80(void);
extern struct G *DAT_00587bf8[4];
void *FUN_00340d50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00340d50(void) {
    struct G *g = DAT_00587bf8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00340e80();
end:
    return DAT_00587bf8[0];
}
