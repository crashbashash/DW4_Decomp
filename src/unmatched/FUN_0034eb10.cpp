extern "C" {
void FUN_0034ebd0(void);
extern struct G *DAT_00588758[4];
void *FUN_0034eb10(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034eb10(void) {
    struct G *g = DAT_00588758[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034ebd0();
    }
    return DAT_00588758[0];
}
