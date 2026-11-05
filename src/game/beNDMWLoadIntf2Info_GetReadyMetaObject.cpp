extern "C" {
void FUN_003c2710(void);
extern struct G *DAT_0058b5d0[4];
void *beNDMWLoadIntf2Info_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2Info_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b5d0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c2710();
end:
    return DAT_0058b5d0[0];
}
