extern "C" {
void FUN_00367b20(void);
extern struct G *DAT_00589ad8[4];
void *FUN_003678f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003678f0(void) {
    struct G *g = DAT_00589ad8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00367b20();
    }
    return DAT_00589ad8[0];
}
