extern "C" {
void FUN_00358430(void);
extern struct G *DAT_00588fc0[4];
void *FUN_003583a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003583a0(void) {
    struct G *g = DAT_00588fc0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00358430();
    }
    return DAT_00588fc0[0];
}
