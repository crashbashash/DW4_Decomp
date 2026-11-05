extern "C" {
void FUN_004588e0(void);
extern struct G *DAT_0058c680[4];
void *igViewerStatisticsManager_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerStatisticsManager_GetMetaObject(void) {
    struct G *g = DAT_0058c680[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_004588e0();
end:
    return DAT_0058c680[0];
}
