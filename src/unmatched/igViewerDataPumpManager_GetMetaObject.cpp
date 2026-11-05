extern "C" {
void FUN_0045bfa0(void);
extern struct G *DAT_0058cb70[4];
void *igViewerDataPumpManager_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewerDataPumpManager_GetMetaObject(void) {
    struct G *g = DAT_0058cb70[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045bfa0();
end:
    return DAT_0058cb70[0];
}
