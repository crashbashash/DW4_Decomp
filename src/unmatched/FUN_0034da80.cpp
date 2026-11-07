extern "C" {
void FUN_0034db60(void);
extern struct G *DAT_00588690[4];
void *FUN_0034da80(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034da80(void) {
    struct G *g = DAT_00588690[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034db60();
    }
    return DAT_00588690[0];
}
