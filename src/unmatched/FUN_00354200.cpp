extern "C" {
void FUN_00354290(void);
extern struct G *DAT_00588c98[4];
void *FUN_00354200(void);
}
struct G { int pad[9]; int f; };
void *FUN_00354200(void) {
    struct G *g = DAT_00588c98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00354290();
    }
    return DAT_00588c98[0];
}
