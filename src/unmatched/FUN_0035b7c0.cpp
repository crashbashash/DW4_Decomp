extern "C" {
void FUN_0035b9c0(void);
extern struct G *DAT_00589208[4];
void *FUN_0035b7c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035b7c0(void) {
    struct G *g = DAT_00589208[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035b9c0();
    }
    return DAT_00589208[0];
}
