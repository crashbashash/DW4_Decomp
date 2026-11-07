extern "C" {
void FUN_003692d0(void);
extern struct G *DAT_00589c08[4];
void *FUN_003691b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003691b0(void) {
    struct G *g = DAT_00589c08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003692d0();
    }
    return DAT_00589c08[0];
}
