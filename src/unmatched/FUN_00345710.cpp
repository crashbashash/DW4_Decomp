extern "C" {
void FUN_00345830(void);
extern struct G *DAT_00587f60[4];
void *FUN_00345710(void);
}
struct G { int pad[9]; int f; };
void *FUN_00345710(void) {
    struct G *g = DAT_00587f60[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345830();
    }
    return DAT_00587f60[0];
}
