extern "C" {
void FUN_003c75a0(void);
extern struct G *DAT_0058be70[4];
void *beLoadIntf2ComMdlData_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beLoadIntf2ComMdlData_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be70[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c75a0();
end:
    return DAT_0058be70[0];
}
