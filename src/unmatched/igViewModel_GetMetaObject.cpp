extern "C" {
void FUN_0045d5c0(void);
extern struct G *DAT_0058cd30[4];
void *igViewModel_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewModel_GetMetaObject(void) {
    struct G *g = DAT_0058cd30[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d5c0();
    }
    return DAT_0058cd30[0];
}
