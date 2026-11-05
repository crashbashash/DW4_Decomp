extern "C" {
int FUN_0045a7a0();
struct G { char pad[36]; int f; };
extern G *DAT_0058c910[4];
G *igViewerLoadingFileMessage_GetMetaObject(void);
}
G *igViewerLoadingFileMessage_GetMetaObject(void) {
    G *g = DAT_0058c910[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0045a7a0();
    return DAT_0058c910[0];
}
