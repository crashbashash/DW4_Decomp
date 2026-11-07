extern "C" {
void FUN_0045d000(void);
extern struct G *DAT_0058ccf8[4];
void *igViewMode_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewMode_GetMetaObject(void) {
    struct G *g = DAT_0058ccf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d000();
    }
    return DAT_0058ccf8[0];
}
