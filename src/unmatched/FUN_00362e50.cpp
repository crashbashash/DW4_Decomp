extern "C" {
void FUN_00362ee0(void);
extern struct G *DAT_00589778[4];
void *FUN_00362e50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00362e50(void) {
    struct G *g = DAT_00589778[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00362ee0();
    }
    return DAT_00589778[0];
}
