extern "C" {
void FUN_003c59f0(void);
extern struct G *DAT_0058bc90[4];
void *beNDMWMcSlotList_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMcSlotList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bc90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c59f0();
    }
    return DAT_0058bc90[0];
}
