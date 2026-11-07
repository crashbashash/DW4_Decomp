extern "C" {
void FUN_003bcdd0(void);
extern struct G *DAT_0058b160[4];
void *FUN_003bcd10(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bcd10(void) {
    struct G *g = DAT_0058b160[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bcdd0();
    }
    return DAT_0058b160[0];
}
