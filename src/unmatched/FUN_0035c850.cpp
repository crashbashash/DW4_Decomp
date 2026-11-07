extern "C" {
void FUN_0035c930(void);
extern struct G *DAT_00589280[4];
void *FUN_0035c850(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035c850(void) {
    struct G *g = DAT_00589280[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035c930();
    }
    return DAT_00589280[0];
}
