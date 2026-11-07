extern "C" {
void FUN_0035a560(void);
extern struct G *DAT_00589148[4];
void *FUN_0035a430(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035a430(void) {
    struct G *g = DAT_00589148[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a560();
    }
    return DAT_00589148[0];
}
