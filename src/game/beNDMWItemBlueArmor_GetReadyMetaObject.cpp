extern "C" {
void FUN_003c8bd0(void);
extern struct G *DAT_0058bf58[4];
void *beNDMWItemBlueArmor_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemBlueArmor_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf58[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c8bd0();
    }
    return DAT_0058bf58[0];
}
