extern "C" {
void FUN_003c62b0(void);
extern struct G *DAT_0058bcf8[4];
void *beNDMWLoadSlotPlayerList_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSlotPlayerList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bcf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c62b0();
    }
    return DAT_0058bcf8[0];
}
