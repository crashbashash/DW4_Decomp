extern "C" {
void FUN_003c8e60(void);
extern struct G *DAT_0058bf68[4];
void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf68[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c8e60();
end:
    return DAT_0058bf68[0];
}
