extern "C" {
void FUN_00360000(void);
extern struct G *DAT_00589558[4];
void *FUN_0035ff70(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035ff70(void) {
    struct G *g = DAT_00589558[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360000();
    }
    return DAT_00589558[0];
}
