extern "C" {
void FUN_00345bc0(void);
extern struct G *DAT_00587f98[4];
void *FUN_00345a90(void);
}
struct G { int pad[9]; int f; };
void *FUN_00345a90(void) {
    struct G *g = DAT_00587f98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345bc0();
    }
    return DAT_00587f98[0];
}
