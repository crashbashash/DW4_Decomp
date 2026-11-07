extern "C" {
void FUN_00368e30(void);
extern struct G *DAT_00589bd8[4];
void *FUN_00368d60(void);
}
struct G { int pad[9]; int f; };
void *FUN_00368d60(void) {
    struct G *g = DAT_00589bd8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00368e30();
    }
    return DAT_00589bd8[0];
}
