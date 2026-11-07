extern "C" {
void FUN_0035a380(void);
extern struct G *DAT_00589140[4];
void *FUN_0035a2f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035a2f0(void) {
    struct G *g = DAT_00589140[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a380();
    }
    return DAT_00589140[0];
}
