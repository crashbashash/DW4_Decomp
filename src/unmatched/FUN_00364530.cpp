extern "C" {
void FUN_00364660(void);
extern struct G *DAT_00589858[4];
void *FUN_00364530(void);
}
struct G { int pad[9]; int f; };
void *FUN_00364530(void) {
    struct G *g = DAT_00589858[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00364660();
    }
    return DAT_00589858[0];
}
