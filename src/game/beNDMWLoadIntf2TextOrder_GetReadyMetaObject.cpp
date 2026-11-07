extern "C" {
void FUN_003c7830(void);
extern struct G *DAT_0058be90[4];
void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c7830();
    }
    return DAT_0058be90[0];
}
