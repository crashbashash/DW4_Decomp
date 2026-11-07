extern "C" {
void FUN_0045bfa0(void);
extern struct G *DAT_0058cb70[4];
void *igViewerDataPumpManager_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerDataPumpManager_GetMetaObject(void) {
    struct G *g = DAT_0058cb70[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045bfa0();
    }
    return DAT_0058cb70[0];
}
