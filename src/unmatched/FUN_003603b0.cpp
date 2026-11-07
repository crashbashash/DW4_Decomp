extern "C" {
void FUN_00360440(void);
extern struct G *DAT_00589588[4];
void *FUN_003603b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003603b0(void) {
    struct G *g = DAT_00589588[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360440();
    }
    return DAT_00589588[0];
}
