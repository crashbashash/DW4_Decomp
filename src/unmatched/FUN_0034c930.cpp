extern "C" {
void FUN_0034cb30(void);
extern struct G *DAT_00588518[4];
void *FUN_0034c930(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034c930(void) {
    struct G *g = DAT_00588518[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034cb30();
    }
    return DAT_00588518[0];
}
