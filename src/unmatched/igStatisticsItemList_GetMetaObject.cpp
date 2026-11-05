extern "C" {
void FUN_00458bc0(void);
extern struct G *DAT_0058c700[4];
void *igStatisticsItemList_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igStatisticsItemList_GetMetaObject(void) {
    struct G *g = DAT_0058c700[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00458bc0();
end:
    return DAT_0058c700[0];
}
