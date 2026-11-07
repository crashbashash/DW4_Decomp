extern "C" {
void FUN_003b64f0(void);
extern struct G *DAT_0058ac88[4];
void *FUN_003b6350(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b6350(void) {
    struct G *g = DAT_0058ac88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b64f0();
    }
    return DAT_0058ac88[0];
}
