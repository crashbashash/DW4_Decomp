extern "C" {
void FUN_0036def0(void);
extern struct G *DAT_0058a028[4];
void *FUN_0036ddc0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036ddc0(void) {
    struct G *g = DAT_0058a028[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036def0();
    }
    return DAT_0058a028[0];
}
