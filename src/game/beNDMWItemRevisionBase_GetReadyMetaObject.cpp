extern "C" {
void FUN_003c8fd0(void);
extern struct G *DAT_0058bf78[4];
void *beNDMWItemRevisionBase_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemRevisionBase_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf78[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c8fd0();
end:
    return DAT_0058bf78[0];
}
