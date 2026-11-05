extern "C" {
void FUN_003c7b60(void);
extern struct G *DAT_0058beb0[4];
void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void) {
    struct G *g = DAT_0058beb0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c7b60();
end:
    return DAT_0058beb0[0];
}
