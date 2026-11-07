extern "C" {
void FUN_00340990(void);
extern struct G *DAT_00587bc0[4];
void *FUN_003408b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003408b0(void) {
    struct G *g = DAT_00587bc0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00340990();
    }
    return DAT_00587bc0[0];
}
