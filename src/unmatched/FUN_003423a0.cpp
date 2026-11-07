extern "C" {
void FUN_003424e0(void);
extern struct G *DAT_00587cb8[4];
void *FUN_003423a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003423a0(void) {
    struct G *g = DAT_00587cb8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003424e0();
    }
    return DAT_00587cb8[0];
}
