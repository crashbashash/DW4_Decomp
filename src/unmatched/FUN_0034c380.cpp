extern "C" {
void FUN_0034c460(void);
extern struct G *DAT_005884e0[4];
void *FUN_0034c380(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034c380(void) {
    struct G *g = DAT_005884e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034c460();
    }
    return DAT_005884e0[0];
}
