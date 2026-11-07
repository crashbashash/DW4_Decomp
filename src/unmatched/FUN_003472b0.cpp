extern "C" {
void FUN_003473f0(void);
extern struct G *DAT_00588040[4];
void *FUN_003472b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003472b0(void) {
    struct G *g = DAT_00588040[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003473f0();
    }
    return DAT_00588040[0];
}
