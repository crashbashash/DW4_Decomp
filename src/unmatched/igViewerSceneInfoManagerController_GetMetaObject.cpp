extern "C" {
void FUN_0045a9a0(void);
extern struct G *DAT_0058c928[4];
void *igViewerSceneInfoManagerController_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    struct G *g = DAT_0058c928[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045a9a0();
end:
    return DAT_0058c928[0];
}
