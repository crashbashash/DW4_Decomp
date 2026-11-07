extern "C" {
void FUN_00340e80(void);
extern struct G *DAT_00587bf8[4];
void *FUN_00340d50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00340d50(void) {
    struct G *g = DAT_00587bf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00340e80();
    }
    return DAT_00587bf8[0];
}
