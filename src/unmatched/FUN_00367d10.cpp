extern "C" {
void FUN_00367da0(void);
extern struct G *DAT_00589b40[4];
void *FUN_00367d10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00367d10(void) {
    struct G *g = DAT_00589b40[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00367da0();
    }
    return DAT_00589b40[0];
}
