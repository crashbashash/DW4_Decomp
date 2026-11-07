extern "C" {
void FUN_0045a9a0(void);
extern struct G *DAT_0058c928[4];
void *igViewerSceneInfoManagerController_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    struct G *g = DAT_0058c928[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045a9a0();
    }
    return DAT_0058c928[0];
}
