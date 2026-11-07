extern "C" {
void FUN_00351c60(void);
extern struct G *DAT_00588a90[4];
void *FUN_00351b10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00351b10(void) {
    struct G *g = DAT_00588a90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00351c60();
    }
    return DAT_00588a90[0];
}
