extern "C" {
void FUN_003c9210(void);
extern struct G *DAT_0058bf88[4];
void *beNDMWItemBaseList_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemBaseList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c9210();
end:
    return DAT_0058bf88[0];
}
