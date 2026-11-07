extern "C" {
void FUN_00363480(void);
extern struct G *DAT_00589790[4];
void *FUN_003632a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003632a0(void) {
    struct G *g = DAT_00589790[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00363480();
    }
    return DAT_00589790[0];
}
