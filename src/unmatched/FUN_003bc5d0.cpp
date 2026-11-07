extern "C" {
void FUN_003bc660(void);
extern struct G *DAT_0058b0a8[4];
void *FUN_003bc5d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bc5d0(void) {
    struct G *g = DAT_0058b0a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bc660();
    }
    return DAT_0058b0a8[0];
}
