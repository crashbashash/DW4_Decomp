extern "C" {
void FUN_003344f0(void);
extern struct G *DAT_00587628[4];
void *FUN_00334460(void);
}
struct G { int pad[9]; int f; };
void *FUN_00334460(void) {
    struct G *g = DAT_00587628[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003344f0();
    }
    return DAT_00587628[0];
}
