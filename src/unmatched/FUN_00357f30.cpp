extern "C" {
void FUN_00357fc0(void);
extern struct G *DAT_00588f80[4];
void *FUN_00357f30(void);
}
struct G { int pad[9]; int f; };
void *FUN_00357f30(void) {
    struct G *g = DAT_00588f80[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00357fc0();
    }
    return DAT_00588f80[0];
}
