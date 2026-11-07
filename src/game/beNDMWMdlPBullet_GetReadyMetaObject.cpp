extern "C" {
void FUN_003c0aa0(void);
extern struct G *DAT_0058b488[4];
void *beNDMWMdlPBullet_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPBullet_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b488[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c0aa0();
    }
    return DAT_0058b488[0];
}
