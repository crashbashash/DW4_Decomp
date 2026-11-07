extern "C" {
void FUN_003c2710(void);
extern struct G *DAT_0058b5d0[4];
void *beNDMWLoadIntf2Info_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2Info_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b5d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c2710();
    }
    return DAT_0058b5d0[0];
}
