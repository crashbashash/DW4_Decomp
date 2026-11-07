extern "C" {
void FUN_0034a580(void);
extern struct G *DAT_00588330[4];
void *FUN_0034a4f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034a4f0(void) {
    struct G *g = DAT_00588330[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034a580();
    }
    return DAT_00588330[0];
}
