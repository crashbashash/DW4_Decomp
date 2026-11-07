extern "C" {
void FUN_003630b0(void);
extern struct G *DAT_00589780[4];
void *FUN_00362fd0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00362fd0(void) {
    struct G *g = DAT_00589780[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003630b0();
    }
    return DAT_00589780[0];
}
