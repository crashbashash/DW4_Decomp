extern "C" {
void FUN_003bc820(void);
extern struct G *DAT_0058b0b0[4];
void *FUN_003bc710(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bc710(void) {
    struct G *g = DAT_0058b0b0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bc820();
    }
    return DAT_0058b0b0[0];
}
