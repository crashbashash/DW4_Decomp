extern "C" {
void FUN_003c73a0(void);
extern struct G *DAT_0058be68[4];
void *beLoadIntf2ComMdlDataList_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beLoadIntf2ComMdlDataList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be68[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c73a0();
    }
    return DAT_0058be68[0];
}
