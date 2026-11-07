extern "C" {
void FUN_00363930(void);
extern struct G *DAT_005897d8[4];
void *FUN_00363850(void);
}
struct G { int pad[9]; int f; };
void *FUN_00363850(void) {
    struct G *g = DAT_005897d8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00363930();
    }
    return DAT_005897d8[0];
}
