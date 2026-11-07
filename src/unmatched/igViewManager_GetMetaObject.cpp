extern "C" {
void FUN_0045d2f0(void);
extern struct G *DAT_0058cd08[4];
void *igViewManager_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewManager_GetMetaObject(void) {
    struct G *g = DAT_0058cd08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d2f0();
    }
    return DAT_0058cd08[0];
}
