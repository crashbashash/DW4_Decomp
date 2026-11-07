extern "C" {
void FUN_003c75a0(void);
extern struct G *DAT_0058be70[4];
void *beLoadIntf2ComMdlData_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beLoadIntf2ComMdlData_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be70[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c75a0();
    }
    return DAT_0058be70[0];
}
