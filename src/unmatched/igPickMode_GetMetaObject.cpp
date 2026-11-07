extern "C" {
void FUN_0045c330(void);
extern struct G *DAT_0058cb88[4];
void *igPickMode_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igPickMode_GetMetaObject(void) {
    struct G *g = DAT_0058cb88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045c330();
    }
    return DAT_0058cb88[0];
}
