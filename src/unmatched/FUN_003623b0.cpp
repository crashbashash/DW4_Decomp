extern "C" {
void FUN_00362440(void);
extern struct G *DAT_005896d0[4];
void *FUN_003623b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003623b0(void) {
    struct G *g = DAT_005896d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00362440();
    }
    return DAT_005896d0[0];
}
