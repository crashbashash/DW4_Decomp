extern "C" {
void FUN_003c1a00(void);
extern struct G *DAT_0058b510[4];
void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b510[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c1a00();
end:
    return DAT_0058b510[0];
}
