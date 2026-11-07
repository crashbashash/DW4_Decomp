extern "C" {
void FUN_00459190(void);
extern struct G *DAT_0058c770[4];
void *igViewerAction_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerAction_GetMetaObject(void) {
    struct G *g = DAT_0058c770[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00459190();
    }
    return DAT_0058c770[0];
}
