extern "C" {
void FUN_003525e0(void);
extern struct G *DAT_00588b00[4];
void *FUN_00352460(void);
}
struct G { int pad[9]; int f; };
void *FUN_00352460(void) {
    struct G *g = DAT_00588b00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003525e0();
    }
    return DAT_00588b00[0];
}
