extern "C" {
void FUN_0034c7f0(void);
extern struct G *DAT_00588510[4];
void *FUN_0034c6c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034c6c0(void) {
    struct G *g = DAT_00588510[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034c7f0();
    }
    return DAT_00588510[0];
}
