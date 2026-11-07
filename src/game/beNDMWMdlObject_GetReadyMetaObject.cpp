extern "C" {
void FUN_003c0c90(void);
extern struct G *DAT_0058b490[4];
void *beNDMWMdlObject_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlObject_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b490[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c0c90();
    }
    return DAT_0058b490[0];
}
