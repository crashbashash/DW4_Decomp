extern "C" {
void FUN_0034fbc0(void);
extern struct G *DAT_00588840[4];
void *FUN_0034fb70(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034fb70(void) {
    struct G *g = DAT_00588840[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034fbc0();
    }
    return DAT_00588840[0];
}
