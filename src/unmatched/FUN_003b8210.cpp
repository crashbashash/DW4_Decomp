extern "C" {
void FUN_003b82e0(void);
extern struct G *DAT_0058adb8[4];
void *FUN_003b8210(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b8210(void) {
    struct G *g = DAT_0058adb8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b82e0();
    }
    return DAT_0058adb8[0];
}
