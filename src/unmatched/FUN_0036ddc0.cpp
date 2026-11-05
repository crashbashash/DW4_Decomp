extern "C" {
void FUN_0036def0(void);
extern struct G *DAT_0058a028[4];
void *FUN_0036ddc0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036ddc0(void) {
    struct G *g = DAT_0058a028[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0036def0();
end:
    return DAT_0058a028[0];
}
