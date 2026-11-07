extern "C" {
void FUN_003b5d70(void);
extern struct G *DAT_0058ac38[4];
void *FUN_003b5bb0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b5bb0(void) {
    struct G *g = DAT_0058ac38[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b5d70();
    }
    return DAT_0058ac38[0];
}
