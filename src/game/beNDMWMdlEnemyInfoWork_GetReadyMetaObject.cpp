extern "C" {
void FUN_003c1a00(void);
extern struct G *DAT_0058b510[4];
void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b510[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c1a00();
    }
    return DAT_0058b510[0];
}
