extern "C" {
void FUN_00367f40(void);
extern struct G *DAT_00589b48[4];
void *FUN_00367e50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00367e50(void) {
    struct G *g = DAT_00589b48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00367f40();
    }
    return DAT_00589b48[0];
}
