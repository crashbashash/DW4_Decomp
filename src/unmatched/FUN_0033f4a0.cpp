extern "C" {
void FUN_0033f750(void);
extern struct G *DAT_00587a68[4];
void *FUN_0033f4a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0033f4a0(void) {
    struct G *g = DAT_00587a68[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0033f750();
    }
    return DAT_00587a68[0];
}
