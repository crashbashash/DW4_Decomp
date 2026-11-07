extern "C" {
void FUN_00347ce0(void);
extern struct G *DAT_00588148[4];
void *FUN_00347c50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00347c50(void) {
    struct G *g = DAT_00588148[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00347ce0();
    }
    return DAT_00588148[0];
}
