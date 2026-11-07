extern "C" {
void FUN_003badf0(void);
extern struct G *DAT_0058af88[4];
void *FUN_003bad20(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bad20(void) {
    struct G *g = DAT_0058af88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003badf0();
    }
    return DAT_0058af88[0];
}
