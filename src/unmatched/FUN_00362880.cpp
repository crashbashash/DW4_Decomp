extern "C" {
void FUN_003629b0(void);
extern struct G *DAT_005896f8[4];
void *FUN_00362880(void);
}
struct G { int pad[9]; int f; };
void *FUN_00362880(void) {
    struct G *g = DAT_005896f8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003629b0();
    }
    return DAT_005896f8[0];
}
