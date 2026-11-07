extern "C" {
void FUN_00346b70(void);
extern struct G *DAT_00588010[4];
void *FUN_00346ab0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00346ab0(void) {
    struct G *g = DAT_00588010[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00346b70();
    }
    return DAT_00588010[0];
}
